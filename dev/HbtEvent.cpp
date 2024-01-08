#include "HbtEvent.hpp"

HbtEvent::HbtEvent() : mMultiplicity(0), mMultiplicity4Pi(0), mImpactParameter(0.0) {
	mTrackCollection = new HbtTrackCollection();
}

HbtEvent::HbtEvent(const HbtEvent &evt) {
	mMultiplicity = evt.mMultiplicity;
	mMultiplicity4Pi = evt.mMultiplicity4Pi;
	mImpactParameter = evt.mImpactParameter;
	mTrackCollection = new HbtTrackCollection();
	// explicitly copy the tracks
	for (auto &track : *evt.mTrackCollection) {
		mTrackCollection->push_back(new HbtTrack(*track));
	}
	mProperties = evt.mProperties;
}

HbtEvent::~HbtEvent() {
	// delete all tracks
	for (auto &track : *mTrackCollection) {
		if (track != nullptr) {
			delete track;
		}
	}
	mTrackCollection->clear();
	delete mTrackCollection;
}