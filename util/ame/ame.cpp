#include "ame.hpp"

void ame::read_ame_table() {
	std::lock_guard<std::mutex> lock(m_mutex);
	if (this->is_loaded) {
		return;
	}

	fs::path path = std::getenv("PROJECT_DIR");
	path = path / ("assets/ame/ame-" + this->version + ".tbl");
	if (!fs::exists(path)) {
		throw std::runtime_error("ame source file not found: " + path.string());
	}

	std::ifstream infile(path.c_str());
	infile.ignore(99, '\n');

	std::string symbol;
	int neutron, proton;
	double mass; // MeV/c^2

	while (infile >> symbol >> neutron >> proton >> mass) {
		this->mass_table[symbol] = mass;
		this->neutron_proton_table[symbol] = {neutron, proton};
		this->symbol_table[{neutron, proton}] = symbol;
	}
	this->is_loaded = true;
	infile.close();
	return;
}

void ame::extract_elements() {
	std::map<std::string, int> element_counter;
	for (auto &[isotope, _] : this->mass_table) {
		std::string element = isotope.substr(0, isotope.find_first_of("0123456789"));
		if (element_counter.count(element) == 0) {
			this->elements.push_back(element);
			element_counter[element]++;
		}
	}
	return;
}

void ame::extract_maximum_mass_number() {
	for (auto &[_, np] : this->neutron_proton_table) {
		this->maximum_mass_number = std::max(this->maximum_mass_number, np.first + np.second);
	}
	return;
}

std::optional<double> ame::get_mass(const std::string &symbol) const {
	auto lower = [](const std::string &input) -> std::string {
		std::string output = input;
		auto lower_char = [](const unsigned char &c) -> unsigned char { return std::tolower(c); };
		std::transform(output.begin(), output.end(), output.begin(), lower_char);
		return output;
	};

	auto get_element = [](const std::string &symbol) -> std::string {
		return symbol.substr(0, symbol.find_first_of("0123456789"));
	};

	auto get_nucleons = [](const std::string &symbol) -> int {
		auto pos = symbol.find_first_of("0123456789");
		return pos != std::string::npos ? std::stoi(symbol.substr(pos)) : -1;
	};

	auto find = [this](const std::string &ele) -> bool {
		return std::find(this->elements.begin(), this->elements.end(), ele) != this->elements.end();
	};

	std::string key;
	if (this->alias.count(symbol) == 1) {
		key = this->alias.at(symbol);
	} else {
		key = lower(symbol);
	}
	if (this->mass_table.count(key) == 0) {
		auto ele = get_element(key);
		auto nucleons = get_nucleons(key);
		if (find(ele) && nucleons != -1) {
			return this->get_unphysical_mass(nucleons);
		}
		return std::nullopt;
	}
	return std::optional<double>(this->mass_table.at(key));
}

std::optional<std::string> ame::get_symbol(const unsigned int &neutron, const unsigned int &proton) const {
	if (this->symbol_table.count({neutron, proton}) == 0) {
		return std::nullopt;
	}
	return std::optional<std::string>(this->symbol_table.at({neutron, proton}));
}

std::optional<std::string> ame::get_symbol(const std::string &alias) const {
	// if alias is a symbol, return itself
	if (this->neutron_proton_table.count(alias) == 1) {
		return std::optional<std::string>(alias);
	}
	// if alias is found in alias table, return the corresponding symbol
	return (this->alias.count(alias) == 0) ? std::nullopt : std::optional<std::string>(this->alias.at(alias));
}

std::optional<std::string> ame::get_alias(const unsigned int &neutron, const unsigned int &proton) const {
	if (this->symbol_table.count({neutron, proton}) == 0) {
		return std::nullopt;
	}
	std::string symbol = this->symbol_table.at({neutron, proton});
	return this->get_alias(symbol);
}

std::optional<std::string> ame::get_alias(const std::string &symbol) const {
	auto it = std::find_if(this->alias.begin(), this->alias.end(), [symbol](const auto &pair) {
		return pair.second == symbol;
	});
	return (it == this->alias.end()) ? std::nullopt : std::optional<std::string>(it->first);
}

std::optional<double> ame::get_mass(const unsigned int &neutron, const unsigned int &proton) const {
	if (this->symbol_table.count({neutron, proton}) == 0) {
		return this->get_unphysical_mass(neutron, proton);
	}
	std::string symbol = this->symbol_table.at({neutron, proton});
	return std::optional<double>(this->mass_table.at(symbol));
}

std::optional<double> ame::get_unphysical_mass(const unsigned int &neutron, const unsigned int &proton) const {
	return this->get_unphysical_mass(neutron + proton);
}

std::optional<double> ame::get_unphysical_mass(const unsigned int &nucleons) const {
	std::optional<double> mass = nucleons * this->default_nucleon_mass;
	return (nucleons > this->maximum_mass_number) ? std::nullopt : mass;
}

std::optional<std::pair<int, int>> ame::get_neutron_proton_number(const std::string &symbol) const {
	auto lower = [](const std::string &input) -> std::string {
		std::string output = input;
		std::transform(output.begin(), output.end(), output.begin(), [](unsigned char c) { return std::tolower(c); });
		return output;
	};

	std::string lower_case_symbol = lower(symbol);
	if (this->neutron_proton_table.count(lower_case_symbol) == 0) {
		if (this->alias.count(symbol) == 0) {
			return std::nullopt;
		}
		return this->neutron_proton_table.at(alias.at(symbol));
	}
	return this->neutron_proton_table.at(lower_case_symbol);
}

std::optional<int> ame::get_proton_number(const std::string &symbol) const {
	auto neutron_proton = this->get_neutron_proton_number(symbol);
	return (neutron_proton) ? std::optional<int>(neutron_proton->second) : std::nullopt;
}

std::optional<int> ame::get_neutron_number(const std::string &symbol) const {
	auto neutron_proton = this->get_neutron_proton_number(symbol);
	return (neutron_proton) ? std::optional<int>(neutron_proton->first) : std::nullopt;
}
