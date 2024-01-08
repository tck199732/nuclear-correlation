#include "HbtTempEvent.hpp"

HbtTempEvent::HbtTempEvent() {
	mFirstTrackCollection = new HbtTrackCollection();
	mSecTrackCollection = new HbtTrackCollection();
}

HbtTempEvent::~HbtTempEvent() {
	for (auto &ptcl : *(mFirstTrackCollection)) {
		delete ptcl;
		ptcl = nullptr;
	}
	mFirstTrackCollection->clear();
	delete mFirstTrackCollection;
	mFirstTrackCollection = nullptr;

	for (auto &ptcl : *(mSecTrackCollection)) {
		delete ptcl;
		ptcl = nullptr;
	}
	mSecTrackCollection->clear();
	delete mSecTrackCollection;
	mSecTrackCollection = nullptr;
}