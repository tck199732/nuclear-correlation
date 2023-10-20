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
namespace fs = std::filesystem;

class ame {
public:
	ame(ame const &) = delete;
	ame &operator=(ame const &) = delete;
	~ame() = default;

	// We don't want getters to be thread-safe in our case.
	std::optional<double> get_mass(const std::string &symbol) const;
	std::optional<double> get_mass(const int &neutron, const int &proton) const;

	std::optional<std::pair<int, int>> get_neutron_proton_number(const std::string &symbol) const;
	std::optional<int> get_neutron_number(const std::string &symbol) const;
	std::optional<int> get_proton_number(const std::string &symbol) const;

	std::optional<std::string> get_symbol(const int &neutron, const int &proton) const;
	std::optional<std::string> get_symbol(const std::string &alias) const;

	static ame *get_instance(const std::string &version = "20") {
		// Static local variable initialization is thread-safe and will be initialized only once.
		static ame instance(version);
		return &instance;
	}

private:
	bool is_loaded;
	std::string version;
	std::mutex m_mutex;
	std::map<std::string, double> mass_table;
	std::map<std::string, std::pair<int, int>> neutron_proton_table;
	std::map<std::pair<int, int>, std::string> symbol_table;

	explicit ame(const std::string &version) {
		this->version = version;
		this->is_loaded = false;
		this->read_ame_table();
	}
	void read_ame_table();
	std::optional<double> get_unphysical_mass(const int &neutron, const int &proton) const;

protected:
	const double default_nucleon_mass = 938.918;
	const std::map<std::string, std::string> alias = {
		{"n", "n1"},	{"p", "h1"},	{"d", "h2"},	  {"t", "h3"},
		{"3He", "he3"}, {"4He", "he4"}, {"alpha", "he4"},
	};
};

#endif