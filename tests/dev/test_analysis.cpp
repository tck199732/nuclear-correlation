#include "analysis.hpp"
#include <doctest/doctest.h>

// mock classes from other test files
class mock_correlation : public correlation {
public:
	mock_correlation() : called_add_real_pair(false), called_add_mixed_pair(false) {}
	mock_correlation(const mock_correlation &other) = default;
	~mock_correlation() = default;
	virtual void add_real_pair(const track *first, const track *second) override { this->called_add_real_pair = true; }
	virtual void add_mixed_pair(const track *first, const track *second) override {
		this->called_add_mixed_pair = true;
	}
	bool called_add_real_pair, called_add_mixed_pair;
};

class mock_monitor : public monitor {
public:
	mock_monitor() : is_event_fill(false), is_track_fill(false), is_pair_fill(false) { ; }
	mock_monitor(const mock_monitor &) = default;
	~mock_monitor() = default;
	void report() override { ; }
	virtual void fill(const event *) override { this->is_event_fill = true; }
	virtual void fill(const track *) override { this->is_track_fill = true; }
	virtual void fill(const track *first, const track *second) override { this->is_pair_fill = true; }

	bool is_event_fill;
	bool is_track_fill;
	bool is_pair_fill;
};

class mock_event_cut_ : public event_cut {
public:
	mock_event_cut_() : event_cut() { this->processed_events = 0; }
	mock_event_cut_(const mock_event_cut_ &) = default;
	virtual ~mock_event_cut_(){};
	virtual bool pass(const event *evt) override {
		this->processed_events++;
		return true;
	}
	int processed_events;
};

class mock_track_cut_ : public track_cut {
public:
	mock_track_cut_() : track_cut() {
		this->processed_tracks = 0;
		this->N = 0;
		this->Z = 0;
	}
	mock_track_cut_(const mock_track_cut_ &) = default;
	virtual ~mock_track_cut_() = default;
	virtual bool pass(const track *trk) override {
		processed_tracks++;
		return trk->get_N() == this->N && trk->get_Z() == this->Z;
	}
	void setN(int N) { this->N = N; }
	void setZ(int Z) { this->Z = Z; }
	int processed_tracks;
	int N, Z;
};

class mock_pair_cut_ : public pair_cut {
public:
	mock_pair_cut_() : pair_cut() { this->processed_pairs = 0; }
	mock_pair_cut_(const mock_pair_cut_ &) = default;
	virtual ~mock_pair_cut_() = default;
	virtual bool pass(const track *first, const track *second) override {
		processed_pairs++;
		return true;
	}
	int processed_pairs;
};

TEST_CASE("check initialization") {
	auto ana = new analysis();
	auto mixing_size = rand() % 10 + 1;
	ana->set_event_mixing_size(mixing_size);
	CHECK(ana->get_event_mixing_size() == mixing_size);

	// objects required for analysis
	auto ecut = new mock_event_cut_();
	auto tcut1 = new mock_track_cut_();
	auto pcut_real = new mock_pair_cut_();
	auto pcut_mixed = new mock_pair_cut_();
	auto emonPass = new mock_monitor();
	auto emonFail = new mock_monitor();
	auto tmonPass1 = new mock_monitor();
	auto tmonFail1 = new mock_monitor();
	auto pmonPass_real = new mock_monitor();
	auto pmonFail_real = new mock_monitor();
	auto pmonPass_imag = new mock_monitor();
	auto pmonFail_imag = new mock_monitor();

	// any number of correlations can be added
	auto corr1 = new mock_correlation();
	auto corr2 = new mock_correlation();
	auto corr3 = new mock_correlation();

	ecut->set_passed_monitor(emonPass);
	ecut->set_failed_monitor(emonFail);
	tcut1->set_passed_monitor(tmonPass1);
	tcut1->set_failed_monitor(tmonFail1);
	pcut_real->set_passed_monitor(pmonPass_real);
	pcut_real->set_failed_monitor(pmonFail_real);
	pcut_mixed->set_passed_monitor(pmonPass_imag);
	pcut_mixed->set_failed_monitor(pmonFail_imag);

	ana->set_event_cut(ecut);
	ana->set_first_track_cut(tcut1);
	ana->set_real_pair_cut(pcut_real);
	ana->set_mixed_pair_cut(pcut_mixed);

	CHECK(ana->get_event_cut() == ecut);
	CHECK(ana->get_first_track_cut() == tcut1);
	CHECK(ana->get_real_pair_cut() == pcut_real);
	CHECK(ana->get_mixed_pair_cut() == pcut_mixed);

	SUBCASE("non-identical analysis") {
		auto tcut2 = new mock_track_cut_();
		auto tmonPass2 = new mock_monitor();
		auto tmonFail2 = new mock_monitor();
		tcut2->set_passed_monitor(tmonPass2);
		tcut2->set_failed_monitor(tmonFail2);
		ana->set_second_track_cut(tcut2);
		CHECK(ana->get_second_track_cut() == tcut2);
		CHECK(ana->get_first_track_cut() != ana->get_second_track_cut());
	}

	SUBCASE("identical analysis") {
		ana->set_second_track_cut(tcut1);
		CHECK(ana->get_second_track_cut() == tcut1);
	}

	ana->add_correlation(corr1);
	ana->add_correlation(corr2);
	ana->add_correlation(corr3);
	CHECK(ana->get_correlation(0) == corr1);
	CHECK(ana->get_correlation(1) == corr2);
	CHECK(ana->get_correlation(2) == corr3);

	SUBCASE("check copy constructor") {
		auto ana2 = new analysis(*ana);
		CHECK(ana2->get_event_mixing_size() == mixing_size);
		CHECK(ana2->get_event_cut() == ecut);
		CHECK(ana2->get_first_track_cut() == tcut1);
		CHECK(ana2->get_real_pair_cut() == pcut_real);
		CHECK(ana2->get_mixed_pair_cut() == pcut_mixed);
		CHECK(ana2->get_correlation(0) == corr1);
		CHECK(ana2->get_correlation(1) == corr2);
		CHECK(ana2->get_correlation(2) == corr3);
	}
	SUBCASE("check destructor") { delete ana; }
}

TEST_CASE("check identical analysis") {
	auto ana = new analysis();
	auto mixing_size = rand() % 10 + 1;
	ana->set_event_mixing_size(mixing_size);

	// objects required for analysis
	auto ecut = new mock_event_cut_();
	auto tcut1 = new mock_track_cut_();
	tcut1->setN(0);
	tcut1->setZ(1);
	auto pcut_real = new mock_pair_cut_();
	auto pcut_mixed = new mock_pair_cut_();

	auto emonPass = new mock_monitor();
	auto emonFail = new mock_monitor();
	auto tmonPass1 = new mock_monitor();
	auto tmonFail1 = new mock_monitor();
	auto pmonPass_real = new mock_monitor();
	auto pmonFail_real = new mock_monitor();
	auto pmonPass_imag = new mock_monitor();
	auto pmonFail_imag = new mock_monitor();

	// any number of correlations can be added
	auto corr1 = new mock_correlation();

	ecut->set_passed_monitor(emonPass);
	ecut->set_failed_monitor(emonFail);
	tcut1->set_passed_monitor(tmonPass1);
	tcut1->set_failed_monitor(tmonFail1);
	pcut_real->set_passed_monitor(pmonPass_real);
	pcut_real->set_failed_monitor(pmonFail_real);
	pcut_mixed->set_passed_monitor(pmonPass_imag);
	pcut_mixed->set_failed_monitor(pmonFail_imag);

	ana->set_event_cut(ecut);
	ana->set_first_track_cut(tcut1);
	ana->set_real_pair_cut(pcut_real);
	ana->set_mixed_pair_cut(pcut_mixed);
	ana->set_second_track_cut(tcut1);
	ana->add_correlation(corr1);

	// generate events
	int ntracks = rand() % 10;
	for (int in = 0; in <= mixing_size; in++) {
		auto evt = new event();
		auto tcoll = evt->get_track_collection();
		for (int _ = 0; _ < ntracks; ++_) {
			auto trk = new track(0, 1, 938.272, 0., 0., 0.);
			tcoll->push_back(trk);
		}
		ana->process(evt);
	}

	CHECK(ecut->processed_events == mixing_size + 1);
	CHECK(tcut1->processed_tracks == ntracks * (mixing_size + 1));
	CHECK(pcut_real->processed_pairs == ntracks * (ntracks - 1) / 2 * (mixing_size + 1));

	CHECK(emonPass->is_event_fill == true);
	CHECK(emonFail->is_event_fill == false);
	CHECK(tmonPass1->is_track_fill == true);
	CHECK(tmonFail1->is_track_fill == false);
	CHECK(pmonPass_real->is_pair_fill == true);
	CHECK(pmonFail_real->is_pair_fill == false);
	CHECK(pmonPass_imag->is_pair_fill == true);
	CHECK(pmonFail_imag->is_pair_fill == false);
	CHECK(corr1->called_add_real_pair == true);
	CHECK(corr1->called_add_mixed_pair == true);
}

TEST_CASE("test non-identical particle") {
	auto ana = new analysis();
	auto mixing_size = rand() % 10 + 1;
	ana->set_event_mixing_size(mixing_size);

	// objects required for analysis
	auto ecut = new mock_event_cut_();
	auto tcut1 = new mock_track_cut_();
	auto tcut2 = new mock_track_cut_();
	tcut1->setN(0);
	tcut1->setZ(1);
	tcut2->setN(1);
	tcut2->setZ(1);

	auto pcut_real = new mock_pair_cut_();
	auto pcut_mixed = new mock_pair_cut_();

	auto emonPass = new mock_monitor();
	auto emonFail = new mock_monitor();
	auto tmonPass1 = new mock_monitor();
	auto tmonFail1 = new mock_monitor();
	auto tmonPass2 = new mock_monitor();
	auto tmonFail2 = new mock_monitor();
	auto pmonPass_real = new mock_monitor();
	auto pmonFail_real = new mock_monitor();
	auto pmonPass_imag = new mock_monitor();
	auto pmonFail_imag = new mock_monitor();

	// any number of correlations can be added
	auto corr1 = new mock_correlation();

	ecut->set_passed_monitor(emonPass);
	ecut->set_failed_monitor(emonFail);
	tcut1->set_passed_monitor(tmonPass1);
	tcut1->set_failed_monitor(tmonFail1);
	tcut2->set_passed_monitor(tmonPass2);
	tcut2->set_failed_monitor(tmonFail2);
	pcut_real->set_passed_monitor(pmonPass_real);
	pcut_real->set_failed_monitor(pmonFail_real);
	pcut_mixed->set_passed_monitor(pmonPass_imag);
	pcut_mixed->set_failed_monitor(pmonFail_imag);

	ana->set_event_cut(ecut);
	ana->set_first_track_cut(tcut1);
	ana->set_real_pair_cut(pcut_real);
	ana->set_mixed_pair_cut(pcut_mixed);
	ana->set_second_track_cut(tcut2);
	ana->add_correlation(corr1);

	// generate events
	int ntracks1 = rand() % 10 + 2;
	int ntracks2 = rand() % 10 + 2;

	for (int in = 0; in <= mixing_size; in++) {
		auto evt = new event();
		auto tcoll = evt->get_track_collection();
		for (int _ = 0; _ < ntracks1; ++_) {
			auto trk = new track(0, 1, 938.272, 0., 0., 0.);
			tcoll->push_back(trk);
		}
		for (int _ = 0; _ < ntracks2; ++_) {
			auto trk = new track(1, 1, 1876.124, 0., 0., 0.);
			tcoll->push_back(trk);
		}
		ana->process(evt);
		delete evt;
	}

	CHECK(ecut->processed_events == mixing_size + 1);
	CHECK(tcut1->processed_tracks == (ntracks1 + ntracks2) * (mixing_size + 1));
	CHECK(tcut2->processed_tracks == (ntracks1 + ntracks2) * (mixing_size + 1));
	CHECK(pcut_real->processed_pairs == ntracks1 * ntracks2 * (mixing_size + 1));
}

TEST_CASE("check behaviour if no cuts are set") {
	auto ana = new analysis();
	auto mixing_size = rand() % 10;
	ana->set_event_mixing_size(mixing_size);
	// only correlations are set
	auto corr1 = new mock_correlation();

	// generate events
	int ntracks = rand() % 10 + 2;
	for (int in = 0; in <= mixing_size; in++) {
		auto evt = new event();
		auto tcoll = evt->get_track_collection();
		for (int _ = 0; _ < ntracks; ++_) {
			auto trk = new track(0, 1, 938.272, 0., 0., 0.);
			tcoll->push_back(trk);
		}
		ana->process(evt);
		delete evt;
	}
}
