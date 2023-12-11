#include "fevent.hpp"
#include "track.hpp"
#include <doctest/doctest.h>
#include <memory>

class mock_track : public track {
public:
	mock_track(const int &idx = 0) : track() { this->index = idx; }
	mock_track(const mock_track &trk) : track(trk) { this->index = trk.index; }
	~mock_track() {}
	int index;
};

TEST_CASE("check deleted copy constructor") { CHECK(std::is_copy_constructible<fevent>::value == false); }

TEST_CASE("check deleted move constructor") { CHECK(std::is_move_constructible<fevent>::value == false); }

TEST_CASE("check deleted copy assignment") { CHECK(std::is_copy_assignable<fevent>::value == false); }

TEST_CASE("check deleted move assignment") { CHECK(std::is_move_assignable<fevent>::value == false); }

TEST_CASE("check constructor") {
	auto fevt = std::make_unique<fevent>();
	CHECK(fevt->get_first_collection() != nullptr);
	CHECK(fevt->get_second_collection() != nullptr);
	CHECK(fevt->get_first_collection()->size() == 0);
	CHECK(fevt->get_second_collection()->size() == 0);

	auto trk1 = new mock_track(1);
	auto trk2 = new mock_track(2);
	fevt->get_first_collection()->push_back(trk1);
	fevt->get_second_collection()->push_back(trk2);
	CHECK(fevt->get_first_collection()->size() == 1);
	CHECK(fevt->get_second_collection()->size() == 1);
	CHECK(dynamic_cast<mock_track *>(fevt->get_first_collection()->at(0))->index == 1);
	CHECK(dynamic_cast<mock_track *>(fevt->get_second_collection()->at(0))->index == 2);

	// deletion of trk1 and trk2 are handled by unique_ptr of fevt
}

// TEST_CASE("check destructor") {
// 	auto fevt = new fevent();
// 	auto trk1 = new mock_track();
// 	auto trk2 = new mock_track();
// 	auto coll1 = fevt->get_first_collection();
// 	auto coll2 = fevt->get_second_collection();
// 	coll1->push_back(trk1);
// 	coll2->push_back(trk2);
// 	// deletion of trk1 and trk2 are handled by fevt destructor
// 	delete fevt;
// 	fevt = nullptr;

// }
