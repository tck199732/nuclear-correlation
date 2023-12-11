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

bool custom_pair_cut::pass(const std::pair<track *, track *> &pr) {
	// kinematic cut obtained from the particle class
	auto [ptcl1, ptcl2] = pr;

	auto px_ = ptcl1->get_px_per_nucleon() + ptcl2->get_px_per_nucleon();
	auto py_ = ptcl1->get_py_per_nucleon() + ptcl2->get_py_per_nucleon();
	auto kT = std::sqrt(px_ * px_ + py_ * py_);
	bool accepted = (kT >= this->kT_gate[0] && kT <= this->kT_gate[1]);

	if (this->is_consider_detector_effect) {
		// throw if
		// 1. name is not found in the std::map
		// 2. type is incorrect
		auto detID_1 = ptcl1->get_property<int>("detector_index");
		auto detID_2 = ptcl2->get_property<int>("detector_index");

		// reject if pair comes from the same detector
		accepted = accepted && (detID_1 != detID_2);
	}
	accepted ? npairs_passed++ : npairs_failed++;
	return accepted;
}
