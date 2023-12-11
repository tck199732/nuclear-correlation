#include "base_cut.hpp"
#include "event.hpp"
#include "monitor.hpp"
#include <doctest/doctest.h>

class derived_monitor : public monitor {
public:
	derived_monitor() { ; }
	derived_monitor(const derived_monitor &) { ; }
	~derived_monitor() { ; }
	void report() override { ; }
	void fill(const event *) override { ; }
	void fill(const track *) override { ; }
	void fill(const std::pair<track *, track *> &) override { ; }
};

TEST_CASE("check constructor") {
	auto cut = new base_cut();
	CHECK(cut->get_passed_monitor() == nullptr);
	CHECK(cut->get_failed_monitor() == nullptr);

	auto passed_monitor = new derived_monitor();
	auto failed_monitor = new derived_monitor();

	SUBCASE("check setters") {
		cut->set_passed_monitor(passed_monitor);
		cut->set_failed_monitor(failed_monitor);
		CHECK(cut->get_passed_monitor() == passed_monitor);
		CHECK(cut->get_failed_monitor() == failed_monitor);

		SUBCASE("check copy constructor") {
			auto copied_cut = new base_cut(*cut);
			CHECK(copied_cut->get_passed_monitor() == passed_monitor);
			CHECK(copied_cut->get_failed_monitor() == failed_monitor);
			delete copied_cut;
		}

		SUBCASE("check fill monitor functions") {
			auto evt = new event();
			auto trk = new track();
			auto pr = std::make_pair(trk, trk);

			SUBCASE("check fill_monitor(event *, bool)") {
				cut->fill_monitor(evt, true);
				CHECK(cut->get_passed_monitor() == passed_monitor);
				CHECK(cut->get_failed_monitor() == failed_monitor);
				cut->fill_monitor(evt, false);
				CHECK(cut->get_passed_monitor() == passed_monitor);
				CHECK(cut->get_failed_monitor() == failed_monitor);
			}

			SUBCASE("check fill_monitor(track *, bool)") {
				cut->fill_monitor(trk, true);
				CHECK(cut->get_passed_monitor() == passed_monitor);
				CHECK(cut->get_failed_monitor() == failed_monitor);
				cut->fill_monitor(trk, false);
				CHECK(cut->get_passed_monitor() == passed_monitor);
				CHECK(cut->get_failed_monitor() == failed_monitor);
			}

			SUBCASE("check fill_monitor(pair *, bool)") {
				cut->fill_monitor(pr, true);
				CHECK(cut->get_passed_monitor() == passed_monitor);
				CHECK(cut->get_failed_monitor() == failed_monitor);
				cut->fill_monitor(pr, false);
				CHECK(cut->get_passed_monitor() == passed_monitor);
				CHECK(cut->get_failed_monitor() == failed_monitor);
			}
			delete evt;
			delete trk;
		}
	}
	SUBCASE("check destructor") {
		delete cut;
		CHECK(passed_monitor != nullptr);
		CHECK(failed_monitor != nullptr);
		delete passed_monitor;
		delete failed_monitor;
	}
}
