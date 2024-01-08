#include "HbtCorrelation.hpp"
#include <doctest/doctest.h>

class derived_correlation : public HbtCorrelation {
public:
	derived_correlation() : called_add_real_pair(false), called_add_mixed_pair(false) {}
	derived_correlation(const derived_correlation &other) = default;
	~derived_correlation() = default;
	virtual void FillRealCorrelation(const HbtTrack *track1, const HbtTrack *track2) { this->called_add_real_pair = true; }
	virtual void FillMixedCorrelation(const HbtTrack *track1, const HbtTrack *track2) { this->called_add_mixed_pair = true; }
	bool called_add_real_pair, called_add_mixed_pair;
};

TEST_CASE("check HbtCorrelation") {
	auto corr = new derived_correlation();
	auto track1 = new HbtTrack();
	auto track2 = new HbtTrack();
	corr->FillRealCorrelation(track1, track2);
	CHECK(corr->called_add_real_pair);
	corr->FillMixedCorrelation(track1, track2);
	CHECK(corr->called_add_mixed_pair);
	delete corr;
	delete track1;
	delete track2;
}
