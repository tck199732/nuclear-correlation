#include "particle.hpp"
#include "track.hpp"
#include <doctest/doctest.h>
#include <random>

TEST_CASE("particle constructor") {

	// set up data for construction of particle
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> momentum_dist(-100., 100.);
	std::uniform_real_distribution<double> space_dist(-1., 1.);
	std::uniform_real_distribution<double> time_dist(0., 1000.);
	std::array<double, 3> momentum = {momentum_dist(gen), momentum_dist(gen), momentum_dist(gen)};
	std::array<double, 3> pos = {space_dist(gen), space_dist(gen), space_dist(gen)};
	auto time = time_dist(gen);
	std::array<double, 4> spacetime = {pos[0], pos[1], pos[2], time};

	// initialize particle(track) of proton at rest at random spacetime & momentum
	track trk(0, 1, 938.7830734813572, momentum, spacetime);
	particle p(&trk);

	// check the particle is initialized correctly
	CHECK(p.get_N() == 0);
	CHECK(p.get_Z() == 1);
	CHECK(p.get_px() == momentum[0]);
	CHECK(p.get_py() == momentum[1]);
	CHECK(p.get_pz() == momentum[2]);

	// check the energy is calculated correctly
	auto erg = std::sqrt(std::pow(trk.get_mass(), 2) + std::pow(p.get_px(), 2) +
						 std::pow(p.get_py(), 2) + std::pow(p.get_pz(), 2));
	CHECK(p.get_e() == doctest::Approx(erg));

	// check the spacetime is initialized correctly
	CHECK(p.get_x() == pos[0]);
	CHECK(p.get_y() == pos[1]);
	CHECK(p.get_z() == pos[2]);
	CHECK(p.get_t() == time);

	// check if track is copied with copy constructor
	auto ptr_to_track = p.get_track();
	CHECK(ptr_to_track != &trk);
}