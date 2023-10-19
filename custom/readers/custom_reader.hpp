#ifndef custom_reader_hpp
#define custom_reader_hpp
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "custom_event.hpp"
#include "custom_track.hpp"
#include "event.hpp"
#include "reader.hpp"
#include "track.hpp"

constexpr int MAX_MULTI = 128;
struct custom_branches {
	int multi;
	double b;
	std::array<int, MAX_MULTI> N;
	std::array<int, MAX_MULTI> Z;
	std::array<double, MAX_MULTI> vx;
	std::array<double, MAX_MULTI> vy;
	std::array<double, MAX_MULTI> vz;
};

class custom_reader : public reader {
public:
	custom_reader(const std::string &tree_name, const std::string &filename);
	custom_reader(const custom_reader &reader);
	~custom_reader();
	event *return_event();

private:
	std::random_device rd;
	std::mt19937 gen;

	std::string tree_name;
	TChain *chain;
	long current_event_index;
	custom_branches branches;
	void set_branches(TChain *&chain);
	event *read();

protected:
	const double proton_mass = 938.272;
	const double neutron_mass = 939.565;
	const double nucleon_mass = 938.918;
};
#endif
