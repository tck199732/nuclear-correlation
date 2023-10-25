#include "readers/custom_reader.hpp"
// forawrd declaration of helper function
double get_mass(const int &N, const int &Z);

custom_reader::custom_reader(const std::string &tree_name, const std::string &filename) : reader() {
	// random generators
	this->gen = std::mt19937(this->rd());

	// set the tree name and the TChain
	chain = new TChain(tree_name.c_str(), "");
	chain->AddFile(filename.c_str());
	this->set_branches(chain);
	current_event_index = 0;
}

custom_reader::custom_reader(const custom_reader &reader) {
	this->chain = 0;
	this->tree_name = reader.tree_name;
	this->branches = reader.branches;
	this->current_event_index = reader.current_event_index;
}

custom_reader::~custom_reader() { delete chain; }

event *custom_reader::return_event() {
	event *evt = 0;
	try {
		evt = read();
	} catch (std::exception &e) {
		return 0;
	}
	if (!evt)
		this->status = 1;
	return evt;
}

event *custom_reader::read() {
	this->begin_event();

	// derived event class
	auto *evt = new custom_event();
	evt->set_multiplicity(branches.multi);
	evt->set_impact_parameter(branches.b);
	// set additional properties
	evt->set_trigger_condition("");
	evt->set_trigger(0.0);

	track_collection *tracks = evt->get_track_collection();
	for (int j = 0; j < branches.multi; j++) {

		auto N = branches.N[j];
		auto Z = branches.Z[j];
		auto vx = branches.vx[j];
		auto vy = branches.vy[j];
		auto vz = branches.vz[j];
		// use ame to determine the mass
		double mass = get_mass(N, Z);
		auto trk = new track(N, Z, mass, vx, vy, vz);

		// do NOT derive the `track` class
		// use `track::set_property` to set important properties which is crucial in the pair-cut
		// e.g. set the detector index so as to exclude pairs from the neighboring detectors

		// fake detector index, either 0 or 1
		std::bernoulli_distribution d(0.5);
		trk->set_property("detector_index", d(this->gen) ? 0 : 1);
		// fake detector efficiency, between 0 and 1
		std::uniform_real_distribution<double> eff(0.0, 1.0);
		trk->set_property("efficiency", eff(this->gen));
		tracks->push_back(trk);
	}
	this->end_event();
	// cast a pointer up the class hierarchy, return the complete object.
	return dynamic_cast<event *>(evt);
}

void custom_reader::set_branches(TChain *&chain) {
	chain->SetMakeClass(1);
	chain->SetBranchStatus("*", 0);

	chain->SetBranchAddress("multi", &branches.multi);
	chain->SetBranchAddress("b", &branches.b);
	chain->SetBranchAddress("N", &branches.N[0]);
	chain->SetBranchAddress("Z", &branches.Z[0]);
	chain->SetBranchAddress("vx", &branches.vx[0]);
	chain->SetBranchAddress("vy", &branches.vy[0]);
	chain->SetBranchAddress("vz", &branches.vz[0]);

	chain->SetMakeClass(1);
	chain->SetBranchStatus("*", false);
	chain->SetBranchStatus("multi", true);
	chain->SetBranchStatus("b", true);
	chain->SetBranchStatus("N", true);
	chain->SetBranchStatus("Z", true);
	chain->SetBranchStatus("vx", true);
	chain->SetBranchStatus("vy", true);
	chain->SetBranchStatus("vz", true);
	return;
}

void custom_reader::begin_event() { this->chain->GetEntry(current_event_index); }
void custom_reader::end_event() { this->current_event_index += 1; }

double get_mass(const int &N, const int &Z) {
	return ame::get_instance()->get_mass(N, Z).value_or(DBL_MAX);
}
