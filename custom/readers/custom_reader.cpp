#include "readers/custom_reader.hpp"
custom_reader::custom_reader() : reader() {
	// random generators
	this->gen = std::mt19937(this->rd());
	this->chain = nullptr;
	this->tree_name = "";
	// this->branches = {};
	this->file_paths = {};
	current_event_index = 0;
}

custom_reader::custom_reader(const std::string &tree_name,
							 const std::vector<std::string> &filenames)
	: reader() {
	// random generators
	this->gen = std::mt19937(this->rd());

	this->chain = new TChain(tree_name.c_str(), "");
	this->tree_name = tree_name;
	// this->branches = {};
	current_event_index = 0;

	for (auto &file_path : filenames) {
		if (!std::filesystem::exists(file_path)) {
			throw std::runtime_error("File does not exist: " + file_path);
		}
		this->file_paths.push_back(file_path);
		this->chain->Add(file_path.c_str());
	}
	this->set_branches(this->chain);
}

custom_reader::~custom_reader() {
	if (chain) {
		delete chain;
	}
}

event *custom_reader::return_event() {
	try {
		if (this->current_event_index >= this->chain->GetEntries()) {
			this->status = 1;
			throw std::runtime_error("Finished reading all entries");
		}
		return this->read();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		this->status = 1;
		return 0;
	}
	return nullptr;
}

event *custom_reader::read() {
	this->begin_event();
	auto eventClass = new event();
	eventClass->set_multiplicity(2);
	eventClass->set_impact_parameter(branches.b);
	auto tracks = eventClass->get_track_collection();

	for (int j = 0; j < 2; j++) {

		auto N = branches.N[j];
		auto Z = branches.Z[j];
		auto px_ = branches.px[j];
		auto py_ = branches.py[j];
		auto pz_ = branches.pz[j];

		// use ame to determine the mass
		double mass = ame::get_instance()->get_mass(N, Z).value_or(DBL_MAX);
		auto trackClass = new track(N, Z, px_, py_, pz_, mass);
		// do NOT derive the `track` class
		// use `track::set_property` to set important properties which is crucial in the pair-cut
		// e.g. set the detector index so as to exclude pairs from the neighboring detectors

		// fake detector index, either 0 or 1
		std::bernoulli_distribution d(0.5);
		trackClass->set_property("detector_index", d(this->gen) ? 0 : 1);
		// fake detector efficiency, between 0 and 1
		std::uniform_real_distribution<double> eff(0.0, 1.0);
		trackClass->set_property("efficiency", eff(this->gen));
		tracks->push_back(trackClass);
	}
	this->end_event();
	return eventClass;
}

void custom_reader::set_branches(TChain *&chain) {
	chain->SetMakeClass(1);
	chain->SetBranchStatus("*", 0);

	chain->SetBranchAddress("impact_parameter", &branches.b);
	chain->SetBranchAddress("N", &branches.N[0]);
	chain->SetBranchAddress("Z", &branches.Z[0]);
	chain->SetBranchAddress("px", &branches.px[0]);
	chain->SetBranchAddress("py", &branches.py[0]);
	chain->SetBranchAddress("pz", &branches.pz[0]);

	chain->SetMakeClass(1);
	chain->SetBranchStatus("*", false);
	chain->SetBranchStatus("impact_parameter", true);
	chain->SetBranchStatus("N", true);
	chain->SetBranchStatus("Z", true);
	chain->SetBranchStatus("px", true);
	chain->SetBranchStatus("py", true);
	chain->SetBranchStatus("pz", true);
	return;
}

void custom_reader::begin_event() {
	this->chain->GetEntry(current_event_index);
	return;
}
void custom_reader::end_event() {
	this->current_event_index += 1;
	return;
}
