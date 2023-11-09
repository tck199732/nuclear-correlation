#include "track.hpp"
#include <doctest/doctest.h>

TEST_CASE("check track constructor") {
	// initialize a track of proton
	track original_track(0, 1, 0., 0., 0., 938.7830734813572);
	// check the track is initialized correctly
	CHECK(original_track.get_neutron() == 0);
	CHECK(original_track.get_proton() == 1);
	CHECK(original_track.get_mass() == 938.7830734813572);
	CHECK(original_track.get_vx() == 0.);
	CHECK(original_track.get_vy() == 0.);
	CHECK(original_track.get_vz() == 0.);
	CHECK(original_track.get_x() == 0.);
	CHECK(original_track.get_y() == 0.);
	CHECK(original_track.get_z() == 0.);
	CHECK(original_track.get_t() == 0.);
}

TEST_CASE("check overloaded track constructor") {
	// initialize a track of proton
	track original_track(0, 1, 938.7830734813572, {0., 0., 0.}, {0., 0., 0., 0.});
	// check the track is initialized correctly
	CHECK(original_track.get_neutron() == 0);
	CHECK(original_track.get_proton() == 1);
	CHECK(original_track.get_mass() == 938.7830734813572);
	CHECK(original_track.get_vx() == 0.);
	CHECK(original_track.get_vy() == 0.);
	CHECK(original_track.get_vz() == 0.);
	CHECK(original_track.get_x() == 0.);
	CHECK(original_track.get_y() == 0.);
	CHECK(original_track.get_z() == 0.);
	CHECK(original_track.get_t() == 0.);
}

TEST_CASE("check copy constructor") {
	// initialize a track of proton
	track original_track(0, 1, 938.7830734813572, {0., 0., 0.}, {0., 0., 0., 0.});
	// copy the track
	track copied_track(original_track);
	// check the track is copied correctly
	CHECK(copied_track.get_neutron() == 0);
	CHECK(copied_track.get_proton() == 1);
	CHECK(copied_track.get_mass() == 938.7830734813572);
	CHECK(copied_track.get_vx() == 0.);
	CHECK(copied_track.get_vy() == 0.);
	CHECK(copied_track.get_vz() == 0.);
	CHECK(copied_track.get_x() == 0.);
	CHECK(copied_track.get_y() == 0.);
	CHECK(copied_track.get_z() == 0.);
	CHECK(copied_track.get_t() == 0.);

	// change the copied track to a neutron
	copied_track.set_neutron(1);
	copied_track.set_proton(0);
	copied_track.set_mass(939.5654204759348);
	copied_track.set_vz(200.);

	// check the track is copied correctly
	CHECK(copied_track.get_neutron() == 1);
	CHECK(copied_track.get_proton() == 0);
	CHECK(copied_track.get_mass() == 939.5654204759348);
	CHECK(copied_track.get_vz() == 200.);

	// check the original track is not changed
	CHECK(original_track.get_neutron() == 0);
	CHECK(original_track.get_proton() == 1);
	CHECK(original_track.get_mass() == 938.7830734813572);
	CHECK(original_track.get_vz() == 0.);
}