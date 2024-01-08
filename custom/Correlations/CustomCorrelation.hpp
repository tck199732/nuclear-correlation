#ifndef CustomCorrelation_hpp
#define CustomCorrelation_hpp

#include "HbtCorrelation.hpp"
#include "HbtTrack.hpp"
#include "TH1D.h"
#include "physics/physics.hpp"
#include <stdexcept>
#include <string>

class CustomCorrelation : public HbtCorrelation {
public:
	CustomCorrelation(const std::string &mName = "");
	CustomCorrelation(const std::string &mName, const int &bins, const double &vmin, const double &vmax);
	CustomCorrelation(const CustomCorrelation &other);
	~CustomCorrelation();

	virtual void FillRealCorrelation(const HbtTrack *track1, const HbtTrack *track2) override;
	virtual void FillMixedCorrelation(const HbtTrack *track1, const HbtTrack *track2) override;

	TH1D *GetNumerator() const { return mNumerator; }
	TH1D *GetDenominator() const { return mDenominator; }

private:
	std::string mName;
	TH1D *mNumerator;
	TH1D *mDenominator;
	double CalcRelativeMomentum(const HbtTrack *track1, const HbtTrack *track2);
};

#endif
