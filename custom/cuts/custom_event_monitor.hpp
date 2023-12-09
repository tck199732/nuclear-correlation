#ifndef custom_event_monitor_hpp
#define custom_event_monitor_hpp

#include "TH1D.h"
#include "event.hpp"
#include "monitor.hpp"
class custom_event_monitor : public monitor {
public:
	custom_event_monitor(const std::string &name = "");
	virtual ~custom_event_monitor();
	virtual void fill(const event *evt);
	virtual void report() { ; }
	void write();
	TH1D *get_h1_imapct_parameter() const { return this->h1_impact_parameter; }

private:
	std::string name;
	TH1D *h1_impact_parameter;
};

#endif
