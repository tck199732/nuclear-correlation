#ifndef custom_event_hpp
#define custom_event_hpp

#include "event.hpp"
#include <cfloat>
#include <string>

class custom_event : public event {
public:
	custom_event();
	custom_event(const custom_event &);
	virtual ~custom_event();

	void set_trigger_condition(const std::string &v) { this->trigger_condition = v; }
	void set_trigger(const double &v) { this->trigger = v; }

	std::string get_trigger_condition() const { return this->trigger_condition; }
	double get_trigger() const { return this->trigger; }

private:
	std::string trigger_condition;
	double trigger;
};
#endif