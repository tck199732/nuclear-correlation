#ifndef HbtPairCut_hpp
#define HbtPairCut_hpp

#include "HbtBaseCut.hpp"
class HbtPairCut : public HbtBaseCut {
public:
	HbtPairCut() = default;
	HbtPairCut(const HbtPairCut &) = default;
	virtual ~HbtPairCut() = default;
	virtual bool Pass(const HbtTrack *track1, const HbtTrack *track2) = 0;
};

#endif