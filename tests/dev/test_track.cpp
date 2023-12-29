#include "track.hpp"
#include <doctest/doctest.h>
#include <random>

// deuteron
constexpr int N = 1;
constexpr int Z = 1;
constexpr int mass = 1876.1239277295715;
constexpr double vmin = -300.;
constexpr double vmax = 300.;

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<double> dis(vmin, vmax);

TEST_CASE("check default constructor") {
	track original_track;
	CHECK(original_track.get_N() == 0);
	CHECK(original_track.get_Z() == 0);
	// all other properties should be initialized to 0.
	CHECK(original_track.get_mass() == 0.);
	CHECK(original_track.get_px_per_nucleon() == 0.);
	CHECK(original_track.get_py_per_nucleon() == 0.);
	CHECK(original_track.get_pz_per_nucleon() == 0.);
	CHECK(original_track.get_x() == 0.);
	CHECK(original_track.get_y() == 0.);
	CHECK(original_track.get_z() == 0.);
	CHECK(original_track.get_t() == 0.);
	CHECK(original_track.get_px() == 0.);
	CHECK(original_track.get_py() == 0.);
	CHECK(original_track.get_pz() == 0.);
	CHECK(original_track.get_E() == 0.);
}

TEST_CASE("check constructor") {
	track original_track(N, Z);
	CHECK(original_track.get_N() == N);
	CHECK(original_track.get_Z() == Z);
	// explicitly set all uninitialized properties
	original_track.set_mass(mass);
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	original_track.set_px_per_nucleon(px);
	original_track.set_py_per_nucleon(py);
	original_track.set_pz_per_nucleon(pz);

	auto x = dis(gen), y = dis(gen), z = dis(gen), t = std::abs(dis(gen));
	original_track.set_x(x);
	original_track.set_y(y);
	original_track.set_z(z);
	original_track.set_t(t);

	// explicitly call initialize() to update px, py, pz, E
	original_track.initalize();

	CHECK(original_track.get_mass() == mass);
	CHECK(original_track.get_px_per_nucleon() == px);
	CHECK(original_track.get_py_per_nucleon() == py);
	CHECK(original_track.get_pz_per_nucleon() == pz);
	CHECK(original_track.get_px() == px * (N + Z));
	CHECK(original_track.get_py() == py * (N + Z));
	CHECK(original_track.get_pz() == pz * (N + Z));
	CHECK(original_track.get_E() >= mass);
	CHECK(original_track.get_x() == x);
	CHECK(original_track.get_y() == y);
	CHECK(original_track.get_z() == z);
	CHECK(original_track.get_t() == t);
}

TEST_CASE("check full constructor") {
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	track original_track(N, Z, mass, px, py, pz);
	CHECK(original_track.get_N() == N);
	CHECK(original_track.get_Z() == Z);
	CHECK(original_track.get_mass() == mass);
	CHECK(original_track.get_px_per_nucleon() == px);
	CHECK(original_track.get_py_per_nucleon() == py);
	CHECK(original_track.get_pz_per_nucleon() == pz);
	// do not have to explicitly call initialize() because it is called in the constructor
	CHECK(original_track.get_px() == px * (N + Z));
	CHECK(original_track.get_py() == py * (N + Z));
	CHECK(original_track.get_pz() == pz * (N + Z));
	CHECK(original_track.get_E() >= mass);

	SUBCASE("check copy constructor") {
		track track_copy(original_track);
		CHECK(track_copy.get_N() == N);
		CHECK(track_copy.get_Z() == Z);

		CHECK(track_copy.get_mass() == mass);
		CHECK(track_copy.get_px_per_nucleon() == px);
		CHECK(track_copy.get_py_per_nucleon() == py);
		CHECK(track_copy.get_pz_per_nucleon() == pz);
		CHECK(track_copy.get_px() == px * (N + Z));
		CHECK(track_copy.get_py() == py * (N + Z));
		CHECK(track_copy.get_pz() == pz * (N + Z));
		CHECK(track_copy.get_E() >= mass);

		CHECK(track_copy.get_x() == 0.);
		CHECK(track_copy.get_y() == 0.);
		CHECK(track_copy.get_z() == 0.);
		CHECK(track_copy.get_t() == 0.);
	}

	SUBCASE("check move constructor") {
		track track_copy(original_track);
		track track_move(std::move(track_copy));
		CHECK(track_move.get_N() == N);
		CHECK(track_move.get_Z() == Z);

		CHECK(track_move.get_mass() == mass);
		CHECK(track_move.get_px_per_nucleon() == px);
		CHECK(track_move.get_py_per_nucleon() == py);
		CHECK(track_move.get_pz_per_nucleon() == pz);
		CHECK(track_move.get_px() == px * (N + Z));
		CHECK(track_move.get_py() == py * (N + Z));
		CHECK(track_move.get_pz() == pz * (N + Z));
		CHECK(track_move.get_E() >= mass);

		CHECK(track_move.get_x() == 0.);
		CHECK(track_move.get_y() == 0.);
		CHECK(track_move.get_z() == 0.);
		CHECK(track_move.get_t() == 0.);
	}

	SUBCASE("check copy assignment") {
		track track_copy = original_track;
		CHECK(track_copy.get_N() == N);
		CHECK(track_copy.get_Z() == Z);

		CHECK(track_copy.get_mass() == mass);
		CHECK(track_copy.get_px_per_nucleon() == px);
		CHECK(track_copy.get_py_per_nucleon() == py);
		CHECK(track_copy.get_pz_per_nucleon() == pz);
		CHECK(track_copy.get_px() == px * (N + Z));
		CHECK(track_copy.get_py() == py * (N + Z));
		CHECK(track_copy.get_pz() == pz * (N + Z));
		CHECK(track_copy.get_E() >= mass);

		CHECK(track_copy.get_x() == 0.);
		CHECK(track_copy.get_y() == 0.);
		CHECK(track_copy.get_z() == 0.);
		CHECK(track_copy.get_t() == 0.);
	}

	SUBCASE("check move assignment") {
		track track_copy = original_track;
		track track_move = std::move(track_copy);
		CHECK(track_move.get_N() == N);
		CHECK(track_move.get_Z() == Z);

		CHECK(track_move.get_mass() == mass);
		CHECK(track_move.get_px_per_nucleon() == px);
		CHECK(track_move.get_py_per_nucleon() == py);
		CHECK(track_move.get_pz_per_nucleon() == pz);
		CHECK(track_move.get_px() == px * (N + Z));
		CHECK(track_move.get_py() == py * (N + Z));
		CHECK(track_move.get_pz() == pz * (N + Z));
		CHECK(track_move.get_E() >= mass);

		CHECK(track_move.get_x() == 0.);
		CHECK(track_move.get_y() == 0.);
		CHECK(track_move.get_z() == 0.);
		CHECK(track_move.get_t() == 0.);
	}
}

TEST_CASE("check constructor from std::array") {
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	std::array<double, 3> mom = {px, py, pz};
	std::array<double, 4> spacetime = {0., 0., 0., 0.};
	track original_track(N, Z, mass, mom, spacetime);

	CHECK(original_track.get_N() == N);
	CHECK(original_track.get_Z() == Z);
	CHECK(original_track.get_mass() == mass);
	CHECK(original_track.get_px_per_nucleon() == px);
	CHECK(original_track.get_py_per_nucleon() == py);
	CHECK(original_track.get_pz_per_nucleon() == pz);
	CHECK(original_track.get_px() == px * (N + Z));
	CHECK(original_track.get_py() == py * (N + Z));
	CHECK(original_track.get_pz() == pz * (N + Z));
	CHECK(original_track.get_E() >= mass);
}

TEST_CASE("check constructor from std::vector") {
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	std::vector<double> mom = {px, py, pz};
	std::vector<double> spacetime = {0., 0., 0., 0.};
	track original_track(N, Z, mass, mom, spacetime);

	CHECK(original_track.get_N() == N);
	CHECK(original_track.get_Z() == Z);
	CHECK(original_track.get_mass() == mass);
	CHECK(original_track.get_px_per_nucleon() == px);
	CHECK(original_track.get_py_per_nucleon() == py);
	CHECK(original_track.get_pz_per_nucleon() == pz);
	CHECK(original_track.get_px() == px * (N + Z));
	CHECK(original_track.get_py() == py * (N + Z));
	CHECK(original_track.get_pz() == pz * (N + Z));
	CHECK(original_track.get_E() >= mass);
}

TEST_CASE("check constructor from std::initializer_list") {
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	std::initializer_list<double> mom = {px, py, pz};
	std::initializer_list<double> spacetime = {0., 0., 0., 0.};
	track original_track(N, Z, mass, mom, spacetime);

	CHECK(original_track.get_N() == N);
	CHECK(original_track.get_Z() == Z);
	CHECK(original_track.get_mass() == mass);
	CHECK(original_track.get_px_per_nucleon() == px);
	CHECK(original_track.get_py_per_nucleon() == py);
	CHECK(original_track.get_pz_per_nucleon() == pz);
	CHECK(original_track.get_px() == px * (N + Z));
	CHECK(original_track.get_py() == py * (N + Z));
	CHECK(original_track.get_pz() == pz * (N + Z));
	CHECK(original_track.get_E() >= mass);
}

TEST_CASE("check = operator") {
	track original_track(N, Z);
	original_track.set_mass(mass);
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	original_track.set_px_per_nucleon(px);
	original_track.set_py_per_nucleon(py);
	original_track.set_pz_per_nucleon(pz);

	auto x = dis(gen), y = dis(gen), z = dis(gen), t = std::abs(dis(gen));
	original_track.set_x(x);
	original_track.set_y(y);
	original_track.set_z(z);
	original_track.set_t(t);

	// explicitly call initialize() to update px, py, pz, E
	original_track.initalize();

	track track_copy = original_track;
	CHECK(track_copy.get_N() == N);
	CHECK(track_copy.get_Z() == Z);

	CHECK(track_copy.get_mass() == mass);
	CHECK(track_copy.get_px_per_nucleon() == px);
	CHECK(track_copy.get_py_per_nucleon() == py);
	CHECK(track_copy.get_pz_per_nucleon() == pz);
	CHECK(track_copy.get_px() == px * (N + Z));
	CHECK(track_copy.get_py() == py * (N + Z));
	CHECK(track_copy.get_pz() == pz * (N + Z));
	CHECK(track_copy.get_E() >= mass);

	CHECK(track_copy.get_x() == x);
	CHECK(track_copy.get_y() == y);
	CHECK(track_copy.get_z() == z);
	CHECK(track_copy.get_t() == t);
}