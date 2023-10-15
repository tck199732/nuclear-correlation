#include "custom_event_cut.hpp"
custom_event_cut::custom_event_cut()
{
    nevents_passed = 0;
    nevents_failed = 0;
    multiplicity[0] = 1;
    multiplicity[1] = 80;
}

void custom_event_cut::set_multiplicity(const unsigned int &vmin, const unsigned int &vmax)
{
    this->multiplicity = {vmin, vmax};
}

void custom_event_cut::set_impact_parameter(const double &vmin, const double &vmax)
{
    this->impact_parameter = {vmin, vmax};
}

bool custom_event_cut::pass(const event *event)
{
    unsigned int multiplicity = event->get_multiplicity();
    double impact_parameter = event->get_impact_parameter();
    bool accepted = (
        multiplicity >= this->multiplicity[0] && 
        multiplicity <= this->multiplicity[1] &&
        impact_parameter >= this->impact_parameter[0] &&
        impact_parameter <= this->impact_parameter[1]
    );
    accepted ? this->nevents_passed++ : this->nevents_failed++;
    return accepted;
}
