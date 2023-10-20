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

std::optional<double> ame::get_mass(const std::string &symbol) const {
	auto lower = [](const std::string &input) -> std::string {
		std::string output = input;
		auto lower_char = [](const unsigned char &c) -> unsigned char { return std::tolower(c); };
		std::transform(output.begin(), output.end(), output.begin(), lower_char);
		return output;
	};

	std::string lower_case_symbol = lower(symbol);
	if (this->mass_table.count(lower_case_symbol) == 0) {
		if (this->alias.count(symbol) == 0) {
			return std::nullopt;
		}
		std::string ame_symbol = this->alias.at(symbol);
		return this->mass_table.at(ame_symbol);
	}
	return this->mass_table.at(lower_case_symbol);
}

std::optional<std::string> ame::get_symbol(const int &neutron, const int &proton) const {
	if (this->symbol_table.count({neutron, proton}) == 0) {
		return std::nullopt;
	}
	return this->symbol_table.at({neutron, proton});
}

std::optional<std::string> ame::get_symbol(const std::string &alias) const {
	// if alias is a symbol, return itself
	if (this->neutron_proton_table.count(alias) == 1) {
		return alias;
	}
	// if alias is found in alias table, return the corresponding symbol
	return (this->alias.count(alias) == 0) ? std::nullopt
										   : std::optional<std::string>(this->alias.at(alias));
}

std::optional<double> ame::get_mass(const int &neutron, const int &proton) const {
	if (this->symbol_table.count({neutron, proton}) == 0) {
		return this->get_unphysical_mass(neutron, proton);
	}
	std::string symbol = this->symbol_table.at({neutron, proton});
	return this->mass_table.at(symbol);
}

std::optional<double> ame::get_unphysical_mass(const int &neutron, const int &proton) const {
	if (neutron < 0 || proton < 0) {
		return std::nullopt;
	}
	return (neutron + proton) * this->default_nucleon_mass;
}

std::optional<std::pair<int, int>> ame::get_neutron_proton_number(const std::string &symbol) const {
	auto lower = [](const std::string &input) -> std::string {
		std::string output = input;
		std::transform(output.begin(), output.end(), output.begin(),
					   [](unsigned char c) { return std::tolower(c); });
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
	return (neutron_proton) ? std::optional<int>(neutron_proton->first) : std::nullopt;
}

std::optional<int> ame::get_neutron_number(const std::string &symbol) const {
	auto neutron_proton = this->get_neutron_proton_number(symbol);
	return (neutron_proton) ? std::optional<int>(neutron_proton->second) : std::nullopt;
}