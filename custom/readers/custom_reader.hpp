#ifndef custom_reader_hpp
#define custom_reader_hpp

#include <array>
#include <cfloat>
#include <filesystem>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

// root libraries
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

// utlities and base classes
#include "ame/ame.hpp"
#include "event.hpp"
#include "reader.hpp"
#include "track.hpp"

constexpr int MAX_MULTI = 128;
struct custom_branches {
	double b;
	std::array<int, MAX_MULTI> N;
	std::array<int, MAX_MULTI> Z;
	// momentum per nucleon
	std::array<double, MAX_MULTI> px;
	std::array<double, MAX_MULTI> py;
	std::array<double, MAX_MULTI> pz;
};

class custom_reader : public reader {
public:
	custom_reader();
	custom_reader(const std::string &tree_name, const std::vector<std::string> &filenames);
	custom_reader(const custom_reader &reader) = delete;
	~custom_reader();
	event *return_event();
	void set_tree_name(const std::string &tree_name);
	void set_filenames(const std::vector<std::string> &filenames);
	void add_file(const std::string &file_path);

	double get_entries() const { return chain->GetEntries(); }
	std::string get_tree_name() const { return tree_name; }
	std::vector<std::filesystem::path> get_filenames() const { return file_paths; }

private:
	// random generators for making fake detector IDs
	std::random_device rd;
	std::mt19937 gen;

	// for reading ROOT files
	TChain *chain;
	std::string tree_name;
	std::vector<std::filesystem::path> file_paths;
	custom_branches branches;
	long current_event_index;

	event *read();
	void set_branches(TChain *&chain);
	void begin_event();
	void end_event();
};

inline void custom_reader::set_tree_name(const std::string &tree_name) { this->tree_name = tree_name; }

inline void custom_reader::set_filenames(const std::vector<std::string> &filenames) { this->file_paths = file_paths; }

inline void custom_reader::add_file(const std::string &file_path) { this->file_paths.push_back(file_path); }

#endif
