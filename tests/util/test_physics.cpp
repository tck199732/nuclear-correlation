#include <Math/Boost.h>
#include <Math/Vector4D.h>
#include <doctest/doctest.h>
#include <physics/physics.hpp>

#include <array>
#include <vector>

TEST_CASE("initialize-with-vector/array") {
	std::vector<double> vec = {1, 2, 3, 10};
	physics::four_vector v_vec(vec);

	std::array<double, 4> arr = {1, 2, 3, 10};
	physics::four_vector v_arr(arr);
	REQUIRE_EQ(v_vec, v_arr);

	std::array<double, 5> invalid_arr = {1, 2, 3, 4, 5};
	std::vector<double> invalid_vec = {1, 2, 3, 4, 5};
	CHECK_THROWS(physics::four_vector(invalid_arr));
	CHECK_THROWS(physics::four_vector(invalid_vec));
}

TEST_CASE("initialize-with-list") {
	physics::four_vector v_list({1, 2, 3, 10});
	physics::four_vector v_list2 = {1, 2, 3, 10};
	REQUIRE_EQ(v_list, v_list2);
}

TEST_CASE("check-beta") {
	physics::four_vector vec(100, 200, 300, 4000);
	ROOT::Math::PxPyPzEVector vec_root(100, 200, 300, 4000);
	auto beta = vec_root.BoostToCM();
	CHECK(vec.beta_x() == doctest::Approx(beta.X()));
	CHECK(vec.beta_y() == doctest::Approx(beta.Y()));
	CHECK(vec.beta_z() == doctest::Approx(beta.Z()));
}

TEST_CASE("check-beta") {
	physics::four_vector vec(100, 200, 300, 4000);
	ROOT::Math::PxPyPzEVector vec_root(100, 200, 300, 4000);

	const std::array<double, 3> beta = {0.1, -0.2, 0.3};
	vec.boost(beta[0], beta[1], beta[2]);

	ROOT::Math::Boost boost(beta[0], beta[1], beta[2]);
	auto vec_root_boosted = boost(vec_root);

	CHECK(vec.Px() == doctest::Approx(vec_root_boosted.Px()));
	CHECK(vec.Py() == doctest::Approx(vec_root_boosted.Py()));
	CHECK(vec.Pz() == doctest::Approx(vec_root_boosted.Pz()));
	CHECK(vec.E() == doctest::Approx(vec_root_boosted.E()));
}
