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

TEST_CASE("copy-constructor") {
	physics::four_vector vec(1, 2, 3, 10);
	physics::four_vector vec2(vec);
	REQUIRE_EQ(vec, vec2);

	physics::four_vector vec3 = vec;
	REQUIRE_EQ(vec, vec3);
}

TEST_CASE("operators") {
	physics::four_vector vec(1, 2, 3, 10);
	physics::four_vector vec_equal = vec;

	REQUIRE_EQ(vec, vec_equal);
	REQUIRE_EQ(vec + vec, physics::four_vector(2, 4, 6, 20));
	REQUIRE_EQ(vec - vec, physics::four_vector(0, 0, 0, 0));
	REQUIRE_EQ(vec * 2, physics::four_vector(2, 4, 6, 20));
	REQUIRE_EQ(vec / 2, physics::four_vector(0.5, 1, 1.5, 5));
}

TEST_CASE("+= operator") {
	physics::four_vector vec(1, 2, 3, 10);
	physics::four_vector vec2(1, 2, 3, 10);
	vec += vec2;
	REQUIRE_EQ(vec, physics::four_vector(2, 4, 6, 20));
}

TEST_CASE("-= operator") {
	physics::four_vector vec(1, 2, 3, 10);
	physics::four_vector vec2(1, 2, 3, 10);
	vec -= vec2;
	REQUIRE_EQ(vec, physics::four_vector(0, 0, 0, 0));
}

TEST_CASE("*= operator") {
	physics::four_vector vec(1, 2, 3, 10);
	vec *= 2;
	REQUIRE_EQ(vec, physics::four_vector(2, 4, 6, 20));
}

TEST_CASE("/= operator") {
	physics::four_vector vec(1, 2, 3, 10);
	vec /= 2;
	REQUIRE_EQ(vec, physics::four_vector(0.5, 1, 1.5, 5));
}

TEST_CASE("==, != operator") {
	physics::four_vector vec(1, 1, 1, 10);
	physics::four_vector vec2(1, 1, 1, 10);
	physics::four_vector vec3(1, 1, 1, 11);
	REQUIRE(vec == vec2);
	REQUIRE(vec != vec3);
}

TEST_CASE("check-beta-component") {
	physics::four_vector vec(100, 200, 300, 4000);
	ROOT::Math::PxPyPzEVector vec_root(100, 200, 300, 4000);
	auto beta = vec_root.BoostToCM();
	CHECK(vec.beta_x() == doctest::Approx(beta.X()));
	CHECK(vec.beta_y() == doctest::Approx(beta.Y()));
	CHECK(vec.beta_z() == doctest::Approx(beta.Z()));
}

TEST_CASE("check-boosting") {
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

TEST_CASE("check-boosting-zero") {
	physics::four_vector vec(100, 200, 300, 4000);
	ROOT::Math::PxPyPzEVector vec_root(100, 200, 300, 4000);
	const std::array<double, 3> beta = {0.0, 0.0, 0.0};
	vec.boost(beta[0], beta[1], beta[2]);

	ROOT::Math::Boost boost(beta[0], beta[1], beta[2]);
	auto vec_root_boosted = boost(vec_root);
	CHECK(vec.Px() == doctest::Approx(vec_root_boosted.Px()));
	CHECK(vec.Py() == doctest::Approx(vec_root_boosted.Py()));
	CHECK(vec.Pz() == doctest::Approx(vec_root_boosted.Pz()));
	CHECK(vec.E() == doctest::Approx(vec_root_boosted.E()));
}

TEST_CASE("check physics class method") {
	physics::four_vector vec(100, 200, 300, 4000);
	ROOT::Math::PxPyPzEVector vec_root(100, 200, 300, 4000);

	CHECK(vec.Pt() == doctest::Approx(vec_root.Pt()));
	CHECK(vec.Mag() == doctest::Approx(vec_root.P()));
	CHECK(vec.M() == doctest::Approx(vec_root.M()));
}

TEST_CASE("check physics calculation") {
	physics::four_vector vec1(100, 200, 300, 4000);
	physics::four_vector vec2(100, -200, -300, 4000);
	ROOT::Math::PxPyPzEVector vec1_root(100, 200, 300, 4000);
	ROOT::Math::PxPyPzEVector vec2_root(100, -200, -300, 4000);

	CHECK(get_minv(vec1, vec2) == doctest::Approx((vec1_root + vec2_root).M()));
	CHECK(get_qinv(vec1, vec2) == doctest::Approx((vec1_root - vec2_root).M()));

	auto qx_root = (vec1_root.Px() * vec2_root.M() - vec2_root.Px() * vec1_root.M()) / (vec1_root.M() + vec2_root.M());
	auto qy_root = (vec1_root.Py() * vec2_root.M() - vec2_root.Py() * vec1_root.M()) / (vec1_root.M() + vec2_root.M());
	auto qz_root = (vec1_root.Pz() * vec2_root.M() - vec2_root.Pz() * vec1_root.M()) / (vec1_root.M() + vec2_root.M());
	CHECK(get_qx(vec1, vec2) == doctest::Approx(qx_root));
	CHECK(get_qy(vec1, vec2) == doctest::Approx(qy_root));
	CHECK(get_qz(vec1, vec2) == doctest::Approx(qz_root));

	auto q_root = vec1_root - vec2_root;
	auto P_root = vec1_root + vec2_root;

	auto qout_root = (q_root.Px() * P_root.Px() + q_root.Py() * P_root.Py()) / P_root.Pt();
	auto qside_root = (q_root.Py() * P_root.Px() - q_root.Px() * P_root.Py()) / P_root.Pt();
	ROOT::Math::Boost boost(0, 0, -P_root.Pz() / P_root.E());
	auto qlong_root = boost(q_root).Pz();

	CHECK(get_qout(vec1, vec2) == doctest::Approx(qout_root));
	CHECK(get_qside(vec1, vec2) == doctest::Approx(qside_root));
	CHECK(get_qlong(vec1, vec2) == doctest::Approx(qlong_root));
}

TEST_CASE("check relative four vector") {
	physics::four_vector vec1(100, 200, 300, 4000);
	physics::four_vector vec2(100, -200, -300, 4000);

	auto vec3 = physics::relative_four_vector(vec1, vec2);

	CHECK(vec3.Px() == doctest::Approx((vec1.Px() * vec2.M() - vec2.Px() * vec1.M()) / (vec1.M() + vec2.M())));
	CHECK(vec3.Py() == doctest::Approx((vec1.Py() * vec2.M() - vec2.Py() * vec1.M()) / (vec1.M() + vec2.M())));
	CHECK(vec3.Pz() == doctest::Approx((vec1.Pz() * vec2.M() - vec2.Pz() * vec1.M()) / (vec1.M() + vec2.M())));
	CHECK(vec3.E() == doctest::Approx((vec1.E() * vec2.M() - vec2.E() * vec1.M()) / (vec1.M() + vec2.M())));
}