#include "HbtEvent.hpp"
#include <doctest/doctest.h>
#include <memory>
#include <random>

constexpr unsigned int imin = 0;
constexpr unsigned int imax = 100;
constexpr double dmin = 0.0;
constexpr double dmax = 10.0;

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<unsigned int> dis_int(imin, imax);
static std::uniform_real_distribution<double> dis_double(dmin, dmax);

class mock_track : public HbtTrack {
public:
	mock_track(const int &idx = 0) : HbtTrack() { this->index = idx; }
	mock_track(const mock_track &trk) : HbtTrack(trk) { this->index = trk.index; }
	~mock_track() {}
	int index;
};

TEST_CASE("HbtEvent default constructor") {
	auto evt = std::make_unique<HbtEvent>();
	CHECK(evt->GetMultiplicity() == 0);
	CHECK(evt->GetImpactParameter() == 0.0);
	CHECK(evt->GetTrackCollection() != nullptr);
	CHECK(evt->GetTrackCollection()->size() == 0);

	auto coll = evt->GetTrackCollection();
	auto ntracks = dis_int(gen);
	for (unsigned int i = 0; i < ntracks; i++) {
		coll->push_back(new mock_track(i));
	}
	CHECK(coll->size() == ntracks);
}

TEST_CASE("HbtEvent set multiplicity") {
	auto evt = std::make_unique<HbtEvent>();
	auto mult = dis_int(gen);
	evt->SetMultiplicity(mult);
	CHECK(evt->GetMultiplicity() == mult);
}

TEST_CASE("HbtEvent set impact parameter") {
	auto evt = std::make_unique<HbtEvent>();
	auto b = dis_double(gen);
	evt->SetImpactParameter(b);
	CHECK(evt->GetImpactParameter() == b);
}

TEST_CASE("HbtEvent copy constructor") {
	auto evt = std::make_unique<HbtEvent>();
	auto mult = dis_int(gen);
	auto b = dis_double(gen);
	evt->SetMultiplicity(mult);
	evt->SetImpactParameter(b);

	auto coll = evt->GetTrackCollection();
	auto ntracks = dis_int(gen);
	for (unsigned int i = 0; i < ntracks; i++) {
		coll->push_back(new mock_track(i));
	}

	auto evt_copy = std::make_unique<HbtEvent>(*evt);
	CHECK(evt_copy->GetMultiplicity() == mult);
	CHECK(evt_copy->GetImpactParameter() == b);
	CHECK(evt_copy->GetTrackCollection() != nullptr);
	CHECK(evt_copy->GetTrackCollection()->size() == ntracks);
}
