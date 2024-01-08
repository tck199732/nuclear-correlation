#ifndef HbtEventCut_hpp
#define HbtEventCut_hpp

#include "HbtBaseCut.hpp"
class HbtEventCut : public HbtBaseCut {
public:
	HbtEventCut() = default;
	HbtEventCut(const HbtEventCut &) = default;
	virtual ~HbtEventCut() = default;
	virtual bool Pass(const HbtEvent *HbtEvent) = 0;
};
#endif
