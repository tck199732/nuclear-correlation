#include "event.hpp"
#include "monitor.hpp"
#include "track.hpp"
#include <doctest/doctest.h>
#include <memory>

class derived_event_monitor : public monitor {
public:
	derived_event_monitor() : is_called_report(false), is_called_fill(false) { ; }
	derived_event_monitor(const derived_event_monitor &) { ; }
	~derived_event_monitor() { ; }
	void report() override {
		this->is_called_report = true;
		return;
	}
	virtual void fill(const event *) override {
		this->is_called_fill = true;
		return;
	}
	virtual void fill(const track *) override { return; }
	virtual void fill(const track *first, const track *second) override { return; }
	bool is_called_report;
	bool is_called_fill;
};

class derived_track_monitor : public monitor {
public:
	derived_track_monitor() : is_called_report(false), is_called_fill(false) { ; }
	derived_track_monitor(const derived_track_monitor &) { ; }
	~derived_track_monitor() { ; }
	void report() override {
		this->is_called_report = true;
		return;
	}
	virtual void fill(const event *) override { return; }
	virtual void fill(const track *) override {
		this->is_called_fill = true;
		return;
	}
	virtual void fill(const track *first, const track *second) override { return; }
	bool is_called_report;
	bool is_called_fill;
};

class derived_pair_monitor : public monitor {
public:
	derived_pair_monitor() : is_called_report(false), is_called_fill(false) { ; }
	derived_pair_monitor(const derived_pair_monitor &) { ; }
	~derived_pair_monitor() { ; }
	virtual void report() override {
		this->is_called_report = true;
		return;
	}
	virtual void fill(const event *) override { return; }
	virtual void fill(const track *) override { return; }
	virtual void fill(const track *first, const track *second) override {
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

	SUBCASE("check report()") {
		evt_mon->report();
		trk_mon->report();
		pr_mon->report();
		CHECK(evt_mon->is_called_report == true);
		CHECK(trk_mon->is_called_report == true);
		CHECK(pr_mon->is_called_report == true);
	}

	SUBCASE("check fill(event *)") {
		auto evt = std::make_unique<event>();
		evt_mon->fill(evt.get());
		CHECK(evt_mon->is_called_fill == true);
	}

	SUBCASE("check fill(track *)") {
		auto trk = std::make_unique<track>();
		trk_mon->fill(trk.get());
		CHECK(trk_mon->is_called_fill == true);
	}

	SUBCASE("check fill(std::pair<track *, track *>)") {
		auto trk = std::make_unique<track>();
		pr_mon->fill(trk.get(), trk.get());
		CHECK(pr_mon->is_called_fill == true);
	}
}