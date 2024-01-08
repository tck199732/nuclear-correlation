#include "CustomTrackCut.hpp"

CustomTrackCut::CustomTrackCut() {
	mPassTracks = 0;
	mFailTracks = 0;
	mNeutron = 0;
	mProton = 0;
	mPtransRange = {0., DBL_MAX};
}

CustomTrackCut::CustomTrackCut(const CustomTrackCut &cut) {
	mPassTracks = cut.mPassTracks;
	mFailTracks = cut.mFailTracks;
	mNeutron = cut.mNeutron;
	mProton = cut.mProton;
	mPtransRange = cut.mPtransRange;
}

bool CustomTrackCut::Pass(const HbtTrack *trk) {
	double px_ = trk->GetPxPerNucleon();
	double py_ = trk->GetPyPerNucleon();
	double pT_ = std::sqrt(px_ * px_ + py_ * py_);

	auto is_inside = [](const double &x, const std::array<double, 2> &range) -> bool {
		return (x >= range[0] && x <= range[1]);
	};
	bool accepted = (trk->GetNeutron() == this->mNeutron && trk->GetProton() == this->mProton);
	accepted = accepted && is_inside(pT_, this->mPtransRange);

	accepted ? mPassTracks++ : mFailTracks++;
	return accepted;
}