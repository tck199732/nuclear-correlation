#include "custom_event_cut.hpp"
custom_event_cut::custom_event_cut() {
	nevents_passed = 0;
	nevents_failed = 0;
	this->multiplicity_range = {1, INT_MAX};
	this->impact_parameter_range = {0.0, DBL_MAX};
}

bool custom_event_cut::pass(const event *event) {
	auto multiplicity = static_cast<int>(event->get_multiplicity());
	auto impact_parameter = event->get_impact_parameter();

	auto accepted = (multiplicity >= this->multiplicity_range[0] && multiplicity <= this->multiplicity_range[1]);

	accepted = accepted && (impact_parameter >= this->impact_parameter_range[0] &&
							impact_parameter <= this->impact_parameter_range[1]);

	accepted ? this->nevents_passed++ : this->nevents_failed++;
	return accepted;
}
