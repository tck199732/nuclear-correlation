#ifndef custom_pair_monitor_hpp
#define custom_pair_monitor_hpp

#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "monitor.hpp"
#include "track.hpp"

class custom_pair_monitor : public monitor {
public:
	custom_pair_monitor(const std::string &name = "");
	virtual ~custom_pair_monitor();
	virtual void fill(const std::pair<track *, track *> &pr);
	virtual void report() { ; }
	void write();

private:
	std::string name;
	TH1D *h1_kT;
};

#endif