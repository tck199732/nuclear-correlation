#include "HbtTrack.hpp"
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
	HbtTrack original_track;
	CHECK(original_track.GetNeutron() == 0);
	CHECK(original_track.GetProton() == 0);
	// all other properties should be initialized to 0.
	CHECK(original_track.GetMass() == 0.);
	CHECK(original_track.GetPxPerNucleon() == 0.);
	CHECK(original_track.GetPyPerNucleon() == 0.);
	CHECK(original_track.GetPzPerNucleon() == 0.);
	CHECK(original_track.GetX() == 0.);
	CHECK(original_track.GetY() == 0.);
	CHECK(original_track.GetZ() == 0.);
	CHECK(original_track.GetTime() == 0.);
	CHECK(original_track.GetPx() == 0.);
	CHECK(original_track.GetPy() == 0.);
	CHECK(original_track.GetPz() == 0.);
	CHECK(original_track.GetE() == 0.);
}

TEST_CASE("check constructor") {
	HbtTrack original_track(N, Z);
	CHECK(original_track.GetNeutron() == N);
	CHECK(original_track.GetProton() == Z);
	// explicitly set all uninitialized properties
	original_track.SetMass(mass);
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	original_track.SetPxPerNucleon(px);
	original_track.SetPyPerNucleon(py);
	original_track.SetPzPerNucleon(pz);

	auto x = dis(gen), y = dis(gen), z = dis(gen), t = std::abs(dis(gen));
	original_track.SetX(x);
	original_track.SetY(y);
	original_track.SetZ(z);
	original_track.SetTime(t);

	// explicitly call initialize() to update px, py, pz, E
	original_track.Initialize();

	CHECK(original_track.GetMass() == mass);
	CHECK(original_track.GetPxPerNucleon() == px);
	CHECK(original_track.GetPyPerNucleon() == py);
	CHECK(original_track.GetPzPerNucleon() == pz);
	CHECK(original_track.GetPx() == px * (N + Z));
	CHECK(original_track.GetPy() == py * (N + Z));
	CHECK(original_track.GetPz() == pz * (N + Z));
	CHECK(original_track.GetE() >= mass);
	CHECK(original_track.GetX() == x);
	CHECK(original_track.GetY() == y);
	CHECK(original_track.GetZ() == z);
	CHECK(original_track.GetTime() == t);
}

TEST_CASE("check full constructor") {
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	HbtTrack original_track(N, Z, mass, px, py, pz);
	CHECK(original_track.GetNeutron() == N);
	CHECK(original_track.GetProton() == Z);
	CHECK(original_track.GetMass() == mass);
	CHECK(original_track.GetPxPerNucleon() == px);
	CHECK(original_track.GetPyPerNucleon() == py);
	CHECK(original_track.GetPzPerNucleon() == pz);
	// do not have to explicitly call initialize() because it is called in the constructor
	CHECK(original_track.GetPx() == px * (N + Z));
	CHECK(original_track.GetPy() == py * (N + Z));
	CHECK(original_track.GetPz() == pz * (N + Z));
	CHECK(original_track.GetE() >= mass);

	SUBCASE("check copy constructor") {
		HbtTrack track_copy(original_track);
		CHECK(track_copy.GetNeutron() == N);
		CHECK(track_copy.GetProton() == Z);

		CHECK(track_copy.GetMass() == mass);
		CHECK(track_copy.GetPxPerNucleon() == px);
		CHECK(track_copy.GetPyPerNucleon() == py);
		CHECK(track_copy.GetPzPerNucleon() == pz);
		CHECK(track_copy.GetPx() == px * (N + Z));
		CHECK(track_copy.GetPy() == py * (N + Z));
		CHECK(track_copy.GetPz() == pz * (N + Z));
		CHECK(track_copy.GetE() >= mass);

		CHECK(track_copy.GetX() == 0.);
		CHECK(track_copy.GetY() == 0.);
		CHECK(track_copy.GetZ() == 0.);
		CHECK(track_copy.GetTime() == 0.);
	}

	SUBCASE("check move constructor") {
		HbtTrack track_copy(original_track);
		HbtTrack track_move(std::move(track_copy));
		CHECK(track_move.GetNeutron() == N);
		CHECK(track_move.GetProton() == Z);

		CHECK(track_move.GetMass() == mass);
		CHECK(track_move.GetPxPerNucleon() == px);
		CHECK(track_move.GetPyPerNucleon() == py);
		CHECK(track_move.GetPzPerNucleon() == pz);
		CHECK(track_move.GetPx() == px * (N + Z));
		CHECK(track_move.GetPy() == py * (N + Z));
		CHECK(track_move.GetPz() == pz * (N + Z));
		CHECK(track_move.GetE() >= mass);

		CHECK(track_move.GetX() == 0.);
		CHECK(track_move.GetY() == 0.);
		CHECK(track_move.GetZ() == 0.);
		CHECK(track_move.GetTime() == 0.);
	}

	SUBCASE("check copy assignment") {
		HbtTrack track_copy = original_track;
		CHECK(track_copy.GetNeutron() == N);
		CHECK(track_copy.GetProton() == Z);

		CHECK(track_copy.GetMass() == mass);
		CHECK(track_copy.GetPxPerNucleon() == px);
		CHECK(track_copy.GetPyPerNucleon() == py);
		CHECK(track_copy.GetPzPerNucleon() == pz);
		CHECK(track_copy.GetPx() == px * (N + Z));
		CHECK(track_copy.GetPy() == py * (N + Z));
		CHECK(track_copy.GetPz() == pz * (N + Z));
		CHECK(track_copy.GetE() >= mass);

		CHECK(track_copy.GetX() == 0.);
		CHECK(track_copy.GetY() == 0.);
		CHECK(track_copy.GetZ() == 0.);
		CHECK(track_copy.GetTime() == 0.);
	}

	SUBCASE("check move assignment") {
		HbtTrack track_copy = original_track;
		HbtTrack track_move = std::move(track_copy);
		CHECK(track_move.GetNeutron() == N);
		CHECK(track_move.GetProton() == Z);

		CHECK(track_move.GetMass() == mass);
		CHECK(track_move.GetPxPerNucleon() == px);
		CHECK(track_move.GetPyPerNucleon() == py);
		CHECK(track_move.GetPzPerNucleon() == pz);
		CHECK(track_move.GetPx() == px * (N + Z));
		CHECK(track_move.GetPy() == py * (N + Z));
		CHECK(track_move.GetPz() == pz * (N + Z));
		CHECK(track_move.GetE() >= mass);

		CHECK(track_move.GetX() == 0.);
		CHECK(track_move.GetY() == 0.);
		CHECK(track_move.GetZ() == 0.);
		CHECK(track_move.GetTime() == 0.);
	}
}

TEST_CASE("check constructor from std::array") {
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	std::array<double, 3> mom = {px, py, pz};
	std::array<double, 4> spacetime = {0., 0., 0., 0.};
	HbtTrack original_track(N, Z, mass, mom, spacetime);

	CHECK(original_track.GetNeutron() == N);
	CHECK(original_track.GetProton() == Z);
	CHECK(original_track.GetMass() == mass);
	CHECK(original_track.GetPxPerNucleon() == px);
	CHECK(original_track.GetPyPerNucleon() == py);
	CHECK(original_track.GetPzPerNucleon() == pz);
	CHECK(original_track.GetPx() == px * (N + Z));
	CHECK(original_track.GetPy() == py * (N + Z));
	CHECK(original_track.GetPz() == pz * (N + Z));
	CHECK(original_track.GetE() >= mass);
}

TEST_CASE("check constructor from std::vector") {
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	std::vector<double> mom = {px, py, pz};
	std::vector<double> spacetime = {0., 0., 0., 0.};
	HbtTrack original_track(N, Z, mass, mom, spacetime);

	CHECK(original_track.GetNeutron() == N);
	CHECK(original_track.GetProton() == Z);
	CHECK(original_track.GetMass() == mass);
	CHECK(original_track.GetPxPerNucleon() == px);
	CHECK(original_track.GetPyPerNucleon() == py);
	CHECK(original_track.GetPzPerNucleon() == pz);
	CHECK(original_track.GetPx() == px * (N + Z));
	CHECK(original_track.GetPy() == py * (N + Z));
	CHECK(original_track.GetPz() == pz * (N + Z));
	CHECK(original_track.GetE() >= mass);
}

TEST_CASE("check constructor from std::initializer_list") {
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	std::initializer_list<double> mom = {px, py, pz};
	std::initializer_list<double> spacetime = {0., 0., 0., 0.};
	HbtTrack original_track(N, Z, mass, mom, spacetime);

	CHECK(original_track.GetNeutron() == N);
	CHECK(original_track.GetProton() == Z);
	CHECK(original_track.GetMass() == mass);
	CHECK(original_track.GetPxPerNucleon() == px);
	CHECK(original_track.GetPyPerNucleon() == py);
	CHECK(original_track.GetPzPerNucleon() == pz);
	CHECK(original_track.GetPx() == px * (N + Z));
	CHECK(original_track.GetPy() == py * (N + Z));
	CHECK(original_track.GetPz() == pz * (N + Z));
	CHECK(original_track.GetE() >= mass);
}

TEST_CASE("check = operator") {
	HbtTrack original_track(N, Z);
	original_track.SetMass(mass);
	auto px = dis(gen), py = dis(gen), pz = dis(gen);
	original_track.SetPxPerNucleon(px);
	original_track.SetPyPerNucleon(py);
	original_track.SetPzPerNucleon(pz);

	auto x = dis(gen), y = dis(gen), z = dis(gen), t = std::abs(dis(gen));
	original_track.SetX(x);
	original_track.SetY(y);
	original_track.SetZ(z);
	original_track.SetTime(t);

	// explicitly call initialize() to update px, py, pz, E
	original_track.Initialize();

	HbtTrack track_copy = original_track;
	CHECK(track_copy.GetNeutron() == N);
	CHECK(track_copy.GetProton() == Z);

	CHECK(track_copy.GetMass() == mass);
	CHECK(track_copy.GetPxPerNucleon() == px);
	CHECK(track_copy.GetPyPerNucleon() == py);
	CHECK(track_copy.GetPzPerNucleon() == pz);
	CHECK(track_copy.GetPx() == px * (N + Z));
	CHECK(track_copy.GetPy() == py * (N + Z));
	CHECK(track_copy.GetPz() == pz * (N + Z));
	CHECK(track_copy.GetE() >= mass);

	CHECK(track_copy.GetX() == x);
	CHECK(track_copy.GetY() == y);
	CHECK(track_copy.GetZ() == z);
	CHECK(track_copy.GetTime() == t);
}