#include "HbtEvent.hpp"
#include "HbtMonitor.hpp"
#include "HbtTrack.hpp"
#include <doctest/doctest.h>
#include <memory>

class derived_event_monitor : public HbtMonitor {
public:
	derived_event_monitor() : is_called_report(false), is_called_fill(false) { ; }
	derived_event_monitor(const derived_event_monitor &) { ; }
	~derived_event_monitor() { ; }
	void Report() override {
		this->is_called_report = true;
		return;
	}
	virtual void Fill(const HbtEvent *) override {
		this->is_called_fill = true;
		return;
	}
	virtual void Fill(const HbtTrack *) override { return; }
	virtual void Fill(const HbtTrack *track1, const HbtTrack *track2) override { return; }
	bool is_called_report;
	bool is_called_fill;
};

class derived_track_monitor : public HbtMonitor {
public:
	derived_track_monitor() : is_called_report(false), is_called_fill(false) { ; }
	derived_track_monitor(const derived_track_monitor &) { ; }
	~derived_track_monitor() { ; }
	void Report() override {
		this->is_called_report = true;
		return;
	}
	virtual void Fill(const HbtEvent *) override { return; }
	virtual void Fill(const HbtTrack *) override {
		this->is_called_fill = true;
		return;
	}
	virtual void Fill(const HbtTrack *track1, const HbtTrack *track2) override { return; }
	bool is_called_report;
	bool is_called_fill;
};

class derived_pair_monitor : public HbtMonitor {
public:
	derived_pair_monitor() : is_called_report(false), is_called_fill(false) { ; }
	derived_pair_monitor(const derived_pair_monitor &) { ; }
	~derived_pair_monitor() { ; }
	virtual void Report() override {
		this->is_called_report = true;
		return;
	}
	virtual void Fill(const HbtEvent *) override { return; }
	virtual void Fill(const HbtTrack *) override { return; }
	virtual void Fill(const HbtTrack *track1, const HbtTrack *track2) override {
		this->is_called_fill = true;
		return;
	}
	bool is_called_report;
	bool is_called_fill;
};

TEST_CASE("check derived method") {
	auto evt_mon = std::make_unique<derived_event_monitor>();
	auto trk_mon = std::make_unique<derived_track_monitor>();
	auto pr_mon = std::make_unique<derived_pair_monitor>();

	SUBCASE("check Report()") {
		evt_mon->Report();
		trk_mon->Report();
		pr_mon->Report();
		CHECK(evt_mon->is_called_report == true);
		CHECK(trk_mon->is_called_report == true);
		CHECK(pr_mon->is_called_report == true);
	}

	SUBCASE("check Fill(HbtEvent *)") {
		auto evt = std::make_unique<HbtEvent>();
		evt_mon->Fill(evt.get());
		CHECK(evt_mon->is_called_fill == true);
	}

	SUBCASE("check Fill(HbtTrack *)") {
		auto trk = std::make_unique<HbtTrack>();
		trk_mon->Fill(trk.get());
		CHECK(trk_mon->is_called_fill == true);
	}

	SUBCASE("check Fill(std::pair<HbtTrack *, HbtTrack *>)") {
		auto trk = std::make_unique<HbtTrack>();
		pr_mon->Fill(trk.get(), trk.get());
		CHECK(pr_mon->is_called_fill == true);
	}
}