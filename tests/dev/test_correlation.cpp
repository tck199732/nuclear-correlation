#include "correlation.hpp"
#include <doctest/doctest.h>

class derived_correlation : public correlation {
public:
	derived_correlation() : called_add_real_pair(false), called_add_mixed_pair(false) {}
	derived_correlation(const derived_correlation &other) = default;
	~derived_correlation() = default;
	virtual void add_real_pair(const track *first, const track *second) { this->called_add_real_pair = true; }
	virtual void add_mixed_pair(const track *first, const track *second) { this->called_add_mixed_pair = true; }
	bool called_add_real_pair, called_add_mixed_pair;
};

TEST_CASE("check correlation") {
	auto corr = new derived_correlation();
	auto track1 = new track();
	auto track2 = new track();
	corr->add_real_pair(track1, track2);
	CHECK(corr->called_add_real_pair);
	corr->add_mixed_pair(track1, track2);
	CHECK(corr->called_add_mixed_pair);
	delete corr;
	delete track1;
	delete track2;
}
