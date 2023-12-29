#ifndef custom_event_cut_hpp
#define custom_event_cut_hpp

#include <array>
#include <cfloat>
#include <climits>
#include <string>

#include "event.hpp"
#include "event_cut.hpp"

class custom_event_cut : public event_cut {
public:
	custom_event_cut();
	custom_event_cut(const custom_event_cut &);
	virtual bool pass(const event *) override;

	void set_multiplicity_range(const int &vmin, const int &vmax);
	void set_impact_parameter_range(const double &vmin, const double &vmax);

	std::array<int, 2> get_accepted_multiplicity() const { return multiplicity_range; }
	std::array<double, 2> get_accepted_impact_parameter() const { return impact_parameter_range; }

	long get_nevents_passed() { return nevents_passed; }
	long get_nevents_failed() { return nevents_failed; }

private:
	std::array<int, 2> multiplicity_range;
	std::array<double, 2> impact_parameter_range;
	long nevents_passed, nevents_failed;
};

inline void custom_event_cut::set_multiplicity_range(const int &vmin, const int &vmax) {
	this->multiplicity_range = {vmin, vmax};
}

inline void custom_event_cut::set_impact_parameter_range(const double &vmin, const double &vmax) {
	this->impact_parameter_range = {vmin, vmax};
}

#endif