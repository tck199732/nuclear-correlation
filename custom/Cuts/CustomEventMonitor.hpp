#ifndef CustomEventMonitor_hpp
#define CustomEventMonitor_hpp

#include "HbtEvent.hpp"
#include "HbtMonitor.hpp"
#include "TH1D.h"
class CustomEventMonitor : public HbtMonitor {
public:
	CustomEventMonitor(const std::string &name = "");
	virtual ~CustomEventMonitor();
	virtual void Report() override { ; }
	virtual void Fill(const HbtEvent *evt) override;
	virtual void Fill(const HbtTrack *) override { ; }
	virtual void Fill(const HbtTrack *, const HbtTrack *) override { ; }
	void Write();
	TH1D *get_h1_imapct_parameter() const { return this->h1_impact_parameter; }

private:
	std::string name;
	TH1D *h1_impact_parameter;
};

#endif
