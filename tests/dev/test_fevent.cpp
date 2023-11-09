#include "fevent.hpp"
#include "particle.hpp"
#include <doctest/doctest.h>

TEST_CASE("check default constructor") {
	fevent fevt;
	CHECK(fevt.get_first_collection() != nullptr);
	CHECK(fevt.get_second_collection() != nullptr);
	CHECK(fevt.get_first_collection()->size() == 0);
	CHECK(fevt.get_second_collection()->size() == 0);
}
