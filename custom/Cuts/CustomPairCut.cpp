#include "CustomPairCut.hpp"

CustomPairCut::CustomPairCut() : mPassPairs(0), mFailPairs(0) {
	this->mPtransRange = {0.0, DBL_MAX};
	this->mConsiderDetEffect = false;
}

CustomPairCut::CustomPairCut(const CustomPairCut &cut) {
	mPassPairs = cut.mPassPairs;
	mFailPairs = cut.mFailPairs;
	mPtransRange = cut.mPtransRange;
	mConsiderDetEffect = cut.mConsiderDetEffect;
}

bool CustomPairCut::Pass(const HbtTrack *track1, const HbtTrack *track2) {
	// kinematic cut obtained from the particle class
	auto px_ = track1->GetPxPerNucleon() + track2->GetPxPerNucleon();
	auto py_ = track1->GetPyPerNucleon() + track2->GetPyPerNucleon();
	auto kT = std::sqrt(px_ * px_ + py_ * py_);
	bool accepted = (kT >= this->mPtransRange[0] && kT <= this->mPtransRange[1]);

	if (this->mConsiderDetEffect) {
		// throw if
		// 1. name is not found in the std::map
		// 2. type is incorrect
		auto detID_1 = track1->GetProperty<int>("detector_index");
		auto detID_2 = track2->GetProperty<int>("detector_index");

		// reject if pair comes from the same detector
		accepted = accepted && (detID_1 != detID_2);
	}
	accepted ? mPassPairs++ : mFailPairs++;
	return accepted;
}
