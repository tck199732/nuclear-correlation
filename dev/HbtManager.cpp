#include "HbtManager.hpp"

HbtManager::HbtManager() {
	this->mReader = 0;
	this->mAnalysisCollection = new HbtAnalysisCollection();
}

HbtManager::~HbtManager() {
	if (this->mReader) {
		delete this->mReader;
	}
	for (auto &anal : *this->mAnalysisCollection) {
		delete anal;
	}
	this->mAnalysisCollection->clear();
	delete this->mAnalysisCollection;
}

int HbtManager::Process() {
	auto evt = mReader->ReturnHbtEvent();
	if (!evt) {
		return mReader->GetStatus();
	}
	for (auto &anal : *this->mAnalysisCollection) {
		anal->Process(evt);
	}
	if (evt) {
		delete evt;
	}
	return 0;
}
