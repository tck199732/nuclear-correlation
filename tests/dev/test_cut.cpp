#include "event.hpp"
#include "event_cut.hpp"
#include "monitor.hpp"
#include "pair_cut.hpp"
#include "track_cut.hpp"
#include <doctest/doctest.h>

class derived_monitor : public monitor {
public:
	derived_monitor() : is_event_fill(false), is_track_fill(false), is_pair_fill(false) { ; }
	derived_monitor(const derived_monitor &) = default;
	~derived_monitor() = default;
	void report() override { ; }
	void fill(const event *) override { this->is_event_fill = true; }
	void fill(const track *) override { this->is_track_fill = true; }
	void fill(const track *first, const track *second) override { this->is_pair_fill = true; }

	bool is_event_fill;
	bool is_track_fill;
	bool is_pair_fill;
};

class mock_event_cut : public event_cut {
public:
	mock_event_cut() = default;
	mock_event_cut(const mock_event_cut &) = default;
	virtual bool pass(const event *) override { return true; }
};

class mock_track_cut : public track_cut {
public:
	mock_track_cut() = default;
	mock_track_cut(const mock_track_cut &) = default;
	virtual bool pass(const track *) override { return true; }
};

class mock_pair_cut : public pair_cut {
public:
	mock_pair_cut() = default;
	mock_pair_cut(const mock_pair_cut &) = default;
	virtual bool pass(const track *first, const track *second) override { return true; }
};

TEST_CASE("check base_cut") {
	// define different types of cut objects
	auto ecut = new mock_event_cut();
	auto tcut = new mock_track_cut();
	auto pcut = new mock_pair_cut();
	// define monitors for both pass & fail cases
	auto monPass = new derived_monitor();
	auto monFail = new derived_monitor();

	// set monitors
	ecut->set_passed_monitor(monPass);
	ecut->set_failed_monitor(monFail);
	tcut->set_passed_monitor(monPass);
	tcut->set_failed_monitor(monFail);
	pcut->set_passed_monitor(monPass);
	pcut->set_failed_monitor(monFail);

	SUBCASE("check monitors assignment") {
		CHECK(ecut->get_passed_monitor() == monPass);
		CHECK(ecut->get_failed_monitor() == monFail);
		CHECK(tcut->get_passed_monitor() == monPass);
		CHECK(tcut->get_failed_monitor() == monFail);
		CHECK(pcut->get_passed_monitor() == monPass);
		CHECK(pcut->get_failed_monitor() == monFail);
	}

	SUBCASE("check fill_monitor") {
		auto evt = new event();
		auto trk = new track();
		ecut->fill_monitor(evt, true);
		ecut->fill_monitor(evt, false);
		tcut->fill_monitor(trk, true);
		tcut->fill_monitor(trk, false);
		pcut->fill_monitor(trk, trk, true);
		pcut->fill_monitor(trk, trk, false);

		CHECK(monPass->is_event_fill == true);
		CHECK(monPass->is_track_fill == true);
		CHECK(monPass->is_pair_fill == true);
		CHECK(monFail->is_event_fill == true);
		CHECK(monFail->is_track_fill == true);
		CHECK(monFail->is_pair_fill == true);
	}

	SUBCASE("check copy constructor") {
		auto ecut2 = new mock_event_cut(*ecut);
		auto tcut2 = new mock_track_cut(*tcut);
		auto pcut2 = new mock_pair_cut(*pcut);
		CHECK(ecut2->get_passed_monitor() == monPass);
		CHECK(ecut2->get_failed_monitor() == monFail);
		CHECK(tcut2->get_passed_monitor() == monPass);
		CHECK(tcut2->get_failed_monitor() == monFail);
		CHECK(pcut2->get_passed_monitor() == monPass);
		CHECK(pcut2->get_failed_monitor() == monFail);
	}
}
