#include "custom_pair_cut.hpp"

custom_pair_cut::custom_pair_cut() : npairs_passed(0), npairs_failed(0) {
	this->kT_gate = {0.0, DBL_MAX};
	this->is_consider_detector_effect = false;
}

custom_pair_cut::custom_pair_cut(const custom_pair_cut &cut) {
	npairs_passed = cut.npairs_passed;
	npairs_failed = cut.npairs_failed;
	kT_gate = cut.kT_gate;
	is_consider_detector_effect = cut.is_consider_detector_effect;
}

bool custom_pair_cut::pass(const pair *pr) {
	// kinematic cut obtained from the particle class
	auto first = pr->get_first_particle();
	auto second = pr->get_second_particle();
	// extract information stored in the `track` level
	auto first_track = first->get_track();
	auto second_track = second->get_track();

	auto a1 = first_track->get_neutron() + first_track->get_proton();
	auto a2 = second_track->get_neutron() + second_track->get_proton();
	auto vx = first->get_px() / a1 + second->get_px() / a2;
	auto vy = first->get_py() / a1 + second->get_py() / a2;
	auto kt = std::sqrt(vx * vx + vy * vy);
	bool accepted = (kt >= this->kT_gate[0] && kt <= this->kT_gate[1]);

	if (this->is_consider_detector_effect) {
		// throw if
		// 1. name is not found in the std::map
		// 2. type is incorrect
		auto detID_1 = first_track->get_property<int>("detector_index");
		auto detID_2 = second_track->get_property<int>("detector_index");

		// reject if pair comes from the same detector
		accepted = accepted && (detID_1 != detID_2);
	}
	accepted ? npairs_passed++ : npairs_failed++;
	return accepted;
}
