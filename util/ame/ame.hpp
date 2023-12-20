#ifndef ame_hpp
#define ame_hpp

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <vector>
namespace fs = std::filesystem;

class ame {
public:
	ame(ame const &) = delete;
	ame &operator=(ame const &) = delete;
	~ame() = default;

	// Set value has to be thread-safe.
	void set_version(const std::string &ver) {
		std::lock_guard<std::mutex> lock(m_mutex);
		this->version = ver;
	}

	void set_maximum_mass_number(const int &A) {
		std::lock_guard<std::mutex> lock(m_mutex);
		this->maximum_mass_number = A;
	}

	// We don't want getters to be thread-safe in our case.
	std::optional<double> get_mass(const std::string &symbol) const;
	std::optional<double> get_mass(const unsigned int &neutron, const unsigned int &proton) const;

	std::optional<std::pair<int, int>> get_neutron_proton_number(const std::string &symbol) const;
	std::optional<int> get_neutron_number(const std::string &symbol) const;
	std::optional<int> get_proton_number(const std::string &symbol) const;

	std::optional<std::string> get_symbol(const unsigned int &neutron, const unsigned int &proton) const;
	std::optional<std::string> get_symbol(const std::string &alias) const;
	std::optional<std::string> get_alias(const unsigned int &neutron, const unsigned int &proton) const;
	std::optional<std::string> get_alias(const std::string &symbol) const;

	unsigned int get_number_of_instances() const { return this->instance_counts; }
	unsigned int get_number_of_elements() const { return this->elements.size(); }
	unsigned int get_maximum_mass_number() const { return this->maximum_mass_number; }

	static ame *get_instance(const std::string &version = "20") {
		// Static local variable initialization is thread-safe and will be initialized only once.
		static ame instance(version);
		return &instance;
	}

private:
	bool is_loaded;
	unsigned int instance_counts = 0;
	unsigned int maximum_mass_number;
	std::string version;
	std::mutex m_mutex;
	std::map<std::string, double> mass_table;
	std::map<std::string, std::pair<unsigned int, unsigned int>> neutron_proton_table;
	std::map<std::pair<unsigned int, unsigned int>, std::string> symbol_table;
	std::vector<std::string> elements;

	explicit ame(const std::string &version) {
		this->version = version;
		this->is_loaded = false;
		this->maximum_mass_number = 0;
		this->instance_counts += 1;
		this->read_ame_table();
		this->extract_elements();
		this->extract_maximum_mass_number();
	}
	void read_ame_table();
	void extract_elements();
	void extract_maximum_mass_number();

	std::optional<double> get_unphysical_mass(const unsigned int &neutron, const unsigned int &proton) const;
	std::optional<double> get_unphysical_mass(const unsigned int &nucleons) const;

protected:
	const double default_nucleon_mass = 938.918;
	const std::map<std::string, std::string> alias = {
		{"n", "n1"}, {"p", "h1"}, {"d", "h2"}, {"t", "h3"}, {"3He", "he3"}, {"4He", "he4"}, {"alpha", "he4"},
	};
};

#endif