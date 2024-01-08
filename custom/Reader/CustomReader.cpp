#include "Reader/CustomReader.hpp"
CustomReader::CustomReader() : HbtReader() {
	// random generators
	this->mGenerator = std::mt19937(this->mRdnDevice());
	this->mChain = nullptr;
	this->mTreeName = "";
	// this->mBranches = {};
	this->mFilePaths = {};
	mCurrEventIndex = 0;
}

CustomReader::CustomReader(const std::string &mTreeName, const std::vector<std::string> &filenames) : HbtReader() {
	// random generators
	this->mGenerator = std::mt19937(this->mRdnDevice());

	this->mChain = new TChain(mTreeName.c_str(), "");
	this->mTreeName = mTreeName;
	// this->mBranches = {};
	mCurrEventIndex = 0;

	for (auto &file_path : filenames) {
		if (!std::filesystem::exists(file_path)) {
			throw std::runtime_error("File does not exist: " + file_path);
		}
		this->mFilePaths.push_back(file_path);
		this->mChain->Add(file_path.c_str());
	}
	this->SetBranches(this->mChain);
}

CustomReader::~CustomReader() {
	if (mChain) {
		delete mChain;
	}
}

HbtEvent *CustomReader::ReturnHbtEvent() {
	try {
		if (this->mCurrEventIndex >= this->mChain->GetEntries()) {
			this->mStatus = 1;
			throw std::runtime_error("Finished reading all entries");
		}
		return this->ReadEvent();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		this->mStatus = 1;
		return 0;
	}
	return nullptr;
}

HbtEvent *CustomReader::ReadEvent() {
	this->BeginEvent();
	auto eventClass = new HbtEvent();
	eventClass->SetMultiplicity(2);
	eventClass->SetImpactParameter(mBranches.b);
	auto tracks = eventClass->GetTrackCollection();

	for (int j = 0; j < 2; j++) {

		auto N = mBranches.N[j];
		auto Z = mBranches.Z[j];
		auto px_ = mBranches.px[j];
		auto py_ = mBranches.py[j];
		auto pz_ = mBranches.pz[j];

		// use ame to determine the mass
		double mass = ame::get_instance()->GetMass(N, Z).value_or(DBL_MAX);
		auto trackClass = new HbtTrack(N, Z);
		trackClass->SetMass(mass);
		trackClass->SetPxPerNucleon(px_);
		trackClass->SetPyPerNucleon(py_);
		trackClass->SetPzPerNucleon(pz_);
		// need to call Initialize() to calculate the four-momentum
		// not required if full constructor is used
		trackClass->Initialize();

		// do NOT derive the `HbtTrack` class
		// use `HbtTrack::SetProperty` to set important properties which is crucial in the pair-cut
		// e.g. set the detector index so as to exclude pairs from the neighboring detectors

		// fake detector index, either 0 or 1
		std::bernoulli_distribution d(0.5);
		trackClass->SetProperty("detector_index", d(this->mGenerator) ? 0 : 1);
		// fake detector efficiency, between 0 and 1
		std::uniform_real_distribution<double> eff(0.0, 1.0);
		trackClass->SetEfficiency(eff(this->mGenerator));
		tracks->push_back(trackClass);
	}
	this->EndEvent();
	return eventClass;
}

void CustomReader::SetBranches(TChain *&mChain) {
	mChain->SetMakeClass(1);
	mChain->SetBranchStatus("*", 0);

	mChain->SetBranchAddress("impact_parameter", &mBranches.b);
	mChain->SetBranchAddress("N", &mBranches.N[0]);
	mChain->SetBranchAddress("Z", &mBranches.Z[0]);
	mChain->SetBranchAddress("px", &mBranches.px[0]);
	mChain->SetBranchAddress("py", &mBranches.py[0]);
	mChain->SetBranchAddress("pz", &mBranches.pz[0]);

	mChain->SetMakeClass(1);
	mChain->SetBranchStatus("*", false);
	mChain->SetBranchStatus("impact_parameter", true);
	mChain->SetBranchStatus("N", true);
	mChain->SetBranchStatus("Z", true);
	mChain->SetBranchStatus("px", true);
	mChain->SetBranchStatus("py", true);
	mChain->SetBranchStatus("pz", true);
	return;
}

void CustomReader::BeginEvent() {
	this->mChain->GetEntry(mCurrEventIndex);
	return;
}
void CustomReader::EndEvent() {
	this->mCurrEventIndex += 1;
	return;
}
