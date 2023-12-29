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

	virtual void report() override { ; }
	virtual void fill(const event *) override { ; }
	virtual void fill(const track *) override { ; }
	virtual void fill(const track *first, const track *second) override;

	void write();
	TH1D *get_h1_kT() const { return this->h1_kT; }

private:
	std::string name;
	TH1D *h1_kT;
};

#endif