#ifndef CustomTrackCut_hpp
#define CustomTrackCut_hpp

#include "HbtTrack.hpp"
#include "HbtTrackCut.hpp"
#include <array>
#include <cfloat>
#include <climits>
#include <cmath>
#include <iostream>

class CustomTrackCut : public HbtTrackCut {
public:
	CustomTrackCut();
	CustomTrackCut(const CustomTrackCut &);
	virtual bool Pass(const HbtTrack *trk);

	void SetNeutron(const unsigned int &N) { mNeutron = N; }
	void SetProton(const unsigned int &Z) { mProton = Z; }
	void SetPtransRange(const double &vmin, const double &vmax) { mPtransRange = {vmin, vmax}; }

	unsigned int GetNeutron() const { return mNeutron; }
	unsigned int GetProton() const { return mProton; }
	std::array<double, 2> GetPtransRange() const { return mPtransRange; }

	long GetPassTracks() const { return mPassTracks; }
	long GetFailTracks() const { return mFailTracks; }

private:
	unsigned int mNeutron, mProton;
	std::array<double, 2> mPtransRange;
	long mPassTracks, mFailTracks;
};
#endif