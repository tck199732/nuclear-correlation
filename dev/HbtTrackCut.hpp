#ifndef HbtTrackCut_hpp
#define HbtTrackCut_hpp

#include "HbtBaseCut.hpp"
class HbtTrackCut : public HbtBaseCut {
public:
	HbtTrackCut() = default;
	HbtTrackCut(const HbtTrackCut &) = default;
	virtual ~HbtTrackCut() = default;
	virtual bool Pass(const HbtTrack *trk) = 0;
};

#endif