#include "analysis.hpp"
#include <doctest/doctest.h>

// mock classes from other test files
class mock_correlation : public correlation {
public:
	mock_correlation() : called_add_real_pair(false), called_add_mixed_pair(false) {}
	mock_correlation(const mock_correlation &other) = default;
	~mock_correlation() = default;
	virtual void add_real_pair(const std::pair<track *, track *> &) override { this->called_add_real_pair = true; }
	virtual void add_mixed_pair(const std::pair<track *, track *> &) override { this->called_add_mixed_pair = true; }
	bool called_add_real_pair, called_add_mixed_pair;
};

class mock_monitor : public monitor {
public:
	mock_monitor() : is_event_fill(false), is_track_fill(false), is_pair_fill(false) { ; }
	mock_monitor(const mock_monitor &) = default;
	~mock_monitor() = default;
	void report() override { ; }
	void fill(const event *) override { this->is_event_fill = true; }
	void fill(const track *) override { this->is_track_fill = true; }
	void fill(const std::pair<track *, track *> &) override { this->is_pair_fill = true; }

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
	virtual bool pass(const std::pair<track *, track *> &) override { return true; }
};

TEST_CASE("check initialization") {
	auto ana = new analysis();
	auto mixing_size = rand() % 100;
	ana->set_event_mixing_size(mixing_size);
	CHECK(ana->get_event_mixing_size() == mixing_size);

	// objects required for analysis
	auto ecut = new mock_event_cut();
	auto tcut1 = new mock_track_cut();
	auto pcut_real = new mock_pair_cut();
	auto pcut_imag = new mock_pair_cut();
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
	pcut_imag->set_passed_monitor(pmonPass_imag);
	pcut_imag->set_failed_monitor(pmonFail_imag);

	ana->set_event_cut(ecut);
	ana->set_first_track_cut(tcut1);
	ana->set_real_pair_cut(pcut_real);
	ana->set_mixed_pair_cut(pcut_imag);

	CHECK(ana->get_event_cut() == ecut);
	CHECK(ana->get_first_track_cut() == tcut1);
	CHECK(ana->get_real_pair_cut() == pcut_real);
	CHECK(ana->get_mixed_pair_cut() == pcut_imag);

	SUBCASE("non-identical analysis") {
		auto tcut2 = new mock_track_cut();
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
}