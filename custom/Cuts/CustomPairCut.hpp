#ifndef CustomPairCut_hpp
#define CustomPairCut_hpp

#include <array>
#include <cfloat>

#include "HbtPairCut.hpp"

class CustomPairCut : public HbtPairCut {
public:
	CustomPairCut();
	CustomPairCut(const CustomPairCut &cut);
	virtual bool Pass(const HbtTrack *track1, const HbtTrack *track2) override;

	void SetPairPtrans(const double &vmin, const double &vmax);
	void SetConsiderDetEffect(const bool &v);

	bool IsConsiderDetEffect() const { return mConsiderDetEffect; }
	std::array<double, 2> GetPairPtrans() const { return mPtransRange; }

	long GetPassPairs() const { return mPassPairs; }
	long GetFailPairs() const { return mFailPairs; }

private:
	long mPassPairs, mFailPairs;
	bool mConsiderDetEffect;
	std::array<double, 2> mPtransRange;
};

inline void CustomPairCut::SetPairPtrans(const double &vmin, const double &vmax) { mPtransRange = {vmin, vmax}; }

inline void CustomPairCut::SetConsiderDetEffect(const bool &v) { mConsiderDetEffect = v; }

#endif
