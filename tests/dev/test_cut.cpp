#include "HbtEvent.hpp"
#include "HbtEventCut.hpp"
#include "HbtMonitor.hpp"
#include "HbtPairCut.hpp"
#include "HbtTrackCut.hpp"
#include <doctest/doctest.h>

class derived_monitor : public HbtMonitor {
public:
	derived_monitor() : is_event_fill(false), is_track_fill(false), is_pair_fill(false) { ; }
	derived_monitor(const derived_monitor &) = default;
	~derived_monitor() = default;
	void Report() override { ; }
	void Fill(const HbtEvent *) override { this->is_event_fill = true; }
	void Fill(const HbtTrack *) override { this->is_track_fill = true; }
	void Fill(const HbtTrack *track1, const HbtTrack *track2) override { this->is_pair_fill = true; }

	bool is_event_fill;
	bool is_track_fill;
	bool is_pair_fill;
};

class mock_event_cut : public HbtEventCut {
public:
	mock_event_cut() = default;
	mock_event_cut(const mock_event_cut &) = default;
	virtual ~mock_event_cut() = default;
	virtual bool Pass(const HbtEvent *) override { return true; }
};

class mock_track_cut : public HbtTrackCut {
public:
	mock_track_cut() = default;
	mock_track_cut(const mock_track_cut &) = default;
	virtual ~mock_track_cut() = default;
	virtual bool Pass(const HbtTrack *) override { return true; }
};

class mock_pair_cut : public HbtPairCut {
public:
	mock_pair_cut() = default;
	mock_pair_cut(const mock_pair_cut &) = default;
	virtual ~mock_pair_cut() = default;
	virtual bool Pass(const HbtTrack *track1, const HbtTrack *track2) override { return true; }
};

TEST_CASE("check HbtBaseCut") {
	// define different types of cut objects
	auto ecut = new mock_event_cut();
	auto tcut = new mock_track_cut();
	auto pcut = new mock_pair_cut();
	// define monitors for both Pass & fail cases
	auto monPass = new derived_monitor();
	auto monFail = new derived_monitor();

	// set monitors
	ecut->SetPassMonitor(monPass);
	ecut->SetFailMonitor(monFail);
	tcut->SetPassMonitor(monPass);
	tcut->SetFailMonitor(monFail);
	pcut->SetPassMonitor(monPass);
	pcut->SetFailMonitor(monFail);

	SUBCASE("check monitors assignment") {
		CHECK(ecut->GetPassMonitor() == monPass);
		CHECK(ecut->GetFailMonitor() == monFail);
		CHECK(tcut->GetPassMonitor() == monPass);
		CHECK(tcut->GetFailMonitor() == monFail);
		CHECK(pcut->GetPassMonitor() == monPass);
		CHECK(pcut->GetFailMonitor() == monFail);
	}

	SUBCASE("check FillMonitor") {
		auto evt = new HbtEvent();
		auto trk = new HbtTrack();
		ecut->FillMonitor(evt, true);
		ecut->FillMonitor(evt, false);
		tcut->FillMonitor(trk, true);
		tcut->FillMonitor(trk, false);
		pcut->FillMonitor(trk, trk, true);
		pcut->FillMonitor(trk, trk, false);

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
		CHECK(ecut2->GetPassMonitor() == monPass);
		CHECK(ecut2->GetFailMonitor() == monFail);
		CHECK(tcut2->GetPassMonitor() == monPass);
		CHECK(tcut2->GetFailMonitor() == monFail);
		CHECK(pcut2->GetPassMonitor() == monPass);
		CHECK(pcut2->GetFailMonitor() == monFail);
	}
}
