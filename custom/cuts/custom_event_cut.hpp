#ifndef custom_event_cut_hpp
#define custom_event_cut_hpp

#include <array>
#include <cfloat>
#include <string>

#include "custom_event.hpp"
#include "event.hpp"
#include "event_cut.hpp"

class custom_event_cut : public event_cut {
public:
	custom_event_cut();
	custom_event_cut(const custom_event_cut &);
	virtual bool pass(const event *) override;
	bool pass(const custom_event *event);

	void set_accepted_multiplicity(const unsigned int &vmin, const unsigned int &vmax);
	void set_accepted_impact_parameter(const double &vmin, const double &vmax);
	void set_accepted_trigger_condition(const std::string &v) {
		this->accepted_trigger_condition = v;
	}
	void set_accepted_trigger_value(const double &vmin, const double &vmax) {
		this->accepted_trigger_value = {vmin, vmax};
	}

	std::array<unsigned int, 2> get_accepted_multiplicity() const { return accepted_multiplicity; }
	std::array<double, 2> get_accepted_impact_parameter() const {
		return accepted_impact_parameter;
	}
	std::string get_accepted_trigger_condition() const { return accepted_trigger_condition; }
	std::array<double, 2> get_accepted_trigger_value() const { return accepted_trigger_value; }

	long get_nevents_passed() { return nevents_passed; }
	long get_nevents_failed() { return nevents_failed; }

private:
	std::array<unsigned int, 2> accepted_multiplicity;
	std::array<double, 2> accepted_impact_parameter;
	std::string accepted_trigger_condition;
	std::array<double, 2> accepted_trigger_value;
	long nevents_passed;
	long nevents_failed;
};
#endif