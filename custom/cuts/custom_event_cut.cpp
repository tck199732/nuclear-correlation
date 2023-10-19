#include "custom_event_cut.hpp"
custom_event_cut::custom_event_cut() {
	nevents_passed = 0;
	nevents_failed = 0;
	accepted_multiplicity[0] = 1;
	accepted_multiplicity[1] = 80;
	accepted_impact_parameter[0] = 0.0;
	accepted_impact_parameter[1] = DBL_MAX;
}

void custom_event_cut::set_accepted_multiplicity(const unsigned int &vmin,
												 const unsigned int &vmax) {
	this->accepted_multiplicity = {vmin, vmax};
}

void custom_event_cut::set_accepted_impact_parameter(const double &vmin, const double &vmax) {
	this->accepted_impact_parameter = {vmin, vmax};
}

bool custom_event_cut::pass(const event *event) {
	auto cev = dynamic_cast<const custom_event *>(event);
	if (!cev)
		throw std::bad_cast();
	return this->pass(cev);
}

bool custom_event_cut::pass(const custom_event *event) {
	unsigned int multiplicity = event->get_multiplicity();
	double impact_parameter = event->get_impact_parameter();
	std::string trigger_condition = event->get_trigger_condition();
	double trigger = event->get_trigger();

	bool accepted = (multiplicity >= this->accepted_multiplicity[0] &&
					 multiplicity <= this->accepted_multiplicity[1]);
	accepted = accepted && (impact_parameter >= this->accepted_impact_parameter[0] &&
							impact_parameter <= this->accepted_impact_parameter[1]);
	accepted = accepted && (trigger_condition == this->accepted_trigger_condition);
	accepted = accepted && (trigger >= this->accepted_trigger_value[0] &&
							trigger <= this->accepted_trigger_value[1]);
	accepted ? this->nevents_passed++ : this->nevents_failed++;
	return accepted;
}
