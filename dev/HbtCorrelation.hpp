#ifndef HbtCorrelation_hpp
#define HbtCorrelation_hpp

#include "HbtTrack.hpp"
class HbtCorrelation {
public:
	HbtCorrelation() = default;
	HbtCorrelation(const HbtCorrelation &corr) = default;
	HbtCorrelation(HbtCorrelation &&corr) = default;
	HbtCorrelation &operator=(const HbtCorrelation &corr) = default;
	HbtCorrelation &operator=(HbtCorrelation &&corr) = default;
	virtual ~HbtCorrelation() = default;

	virtual void FillRealCorrelation(const HbtTrack *, const HbtTrack *) = 0;
	virtual void FillMixedCorrelation(const HbtTrack *, const HbtTrack *) = 0;
};
#endif
