#include "event.hpp"
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

class mock_track : public track {
public:
	mock_track(const int &idx = 0) : track() { this->index = idx; }
	mock_track(const mock_track &trk) : track(trk) { this->index = trk.index; }
	~mock_track() {}
	int index;
};

TEST_CASE("event default constructor") {
	auto evt = std::make_unique<event>();
	CHECK(evt->get_multiplicity() == 0);
	CHECK(evt->get_impact_parameter() == 0.0);
	CHECK(evt->get_track_collection() != nullptr);
	CHECK(evt->get_track_collection()->size() == 0);

	auto coll = evt->get_track_collection();
	auto ntracks = dis_int(gen);
	for (unsigned int i = 0; i < ntracks; i++) {
		coll->push_back(new mock_track(i));
	}
	CHECK(coll->size() == ntracks);
}

TEST_CASE("event set multiplicity") {
	auto evt = std::make_unique<event>();
	auto mult = dis_int(gen);
	evt->set_multiplicity(mult);
	CHECK(evt->get_multiplicity() == mult);
}

TEST_CASE("event set impact parameter") {
	auto evt = std::make_unique<event>();
	auto b = dis_double(gen);
	evt->set_impact_parameter(b);
	CHECK(evt->get_impact_parameter() == b);
}

TEST_CASE("event copy constructor") {
	auto evt = std::make_unique<event>();
	auto mult = dis_int(gen);
	auto b = dis_double(gen);
	evt->set_multiplicity(mult);
	evt->set_impact_parameter(b);

	auto coll = evt->get_track_collection();
	auto ntracks = dis_int(gen);
	for (unsigned int i = 0; i < ntracks; i++) {
		coll->push_back(new mock_track(i));
	}

	auto evt_copy = std::make_unique<event>(*evt);
	CHECK(evt_copy->get_multiplicity() == mult);
	CHECK(evt_copy->get_impact_parameter() == b);
	CHECK(evt_copy->get_track_collection() != nullptr);
	CHECK(evt_copy->get_track_collection()->size() == ntracks);
}
