#include "HbtTempEvent.hpp"
#include "HbtTrack.hpp"
#include <doctest/doctest.h>
#include <memory>

class mock_track : public HbtTrack {
public:
	mock_track(const int &idx = 0) : HbtTrack() { this->index = idx; }
	mock_track(const mock_track &trk) : HbtTrack(trk) { this->index = trk.index; }
	~mock_track() {}
	int index;
};

TEST_CASE("check deleted copy constructor") { CHECK(std::is_copy_constructible<HbtTempEvent>::value == false); }

TEST_CASE("check deleted copy assignment") { CHECK(std::is_copy_assignable<HbtTempEvent>::value == false); }

TEST_CASE("check constructor") {
	auto fevt = std::make_unique<HbtTempEvent>();
	CHECK(fevt->GetFirstTrackCollection() != nullptr);
	CHECK(fevt->GetSecTrackCollection() != nullptr);
	CHECK(fevt->GetFirstTrackCollection()->size() == 0);
	CHECK(fevt->GetSecTrackCollection()->size() == 0);

	auto trk1 = new mock_track(1);
	auto trk2 = new mock_track(2);
	fevt->GetFirstTrackCollection()->push_back(trk1);
	fevt->GetSecTrackCollection()->push_back(trk2);
	CHECK(fevt->GetFirstTrackCollection()->size() == 1);
	CHECK(fevt->GetSecTrackCollection()->size() == 1);
	CHECK(dynamic_cast<mock_track *>(fevt->GetFirstTrackCollection()->at(0))->index == 1);
	CHECK(dynamic_cast<mock_track *>(fevt->GetSecTrackCollection()->at(0))->index == 2);

	// deletion of trk1 and trk2 are handled by unique_ptr of fevt
}
