#include "custom_track_cut.hpp"

custom_track_cut::custom_track_cut() {
	ntracks_passed = 0;
	ntracks_failed = 0;
	accepted_neutron = 0;
	accepted_proton = 0;
	transverse_velocity_gate = {0., DBL_MAX};
}

custom_track_cut::custom_track_cut(const custom_track_cut &cut) {
	ntracks_passed = cut.ntracks_passed;
	ntracks_failed = cut.ntracks_failed;
	accepted_neutron = cut.accepted_neutron;
	accepted_proton = cut.accepted_proton;
	transverse_velocity_gate = cut.transverse_velocity_gate;
}

bool custom_track_cut::pass(const track *trk) {
	double px_ = trk->get_px_per_nucleon();
	double py_ = trk->get_py_per_nucleon();
	double pT_ = std::sqrt(px_ * px_ + py_ * py_);
	double efficiency = trk->get_property<double>("efficiency");

	auto is_inside = [](const double &x, const std::array<double, 2> &range) -> bool {
		return (x >= range[0] && x <= range[1]);
	};
	bool accepted = (trk->get_N() == this->accepted_neutron && trk->get_Z() == this->accepted_proton);
	accepted = accepted && is_inside(pT_, this->transverse_velocity_gate);
	accepted = accepted && is_inside(efficiency, this->accepted_efficiency);

	accepted ? ntracks_passed++ : ntracks_failed++;
	return accepted;
}