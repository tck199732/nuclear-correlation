#ifndef CustomPairMonitor_hpp
#define CustomPairMonitor_hpp

#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "HbtMonitor.hpp"
#include "HbtTrack.hpp"

class CustomPairMonitor : public HbtMonitor {
public:
	CustomPairMonitor(const std::string &name = "");
	virtual ~CustomPairMonitor();

	virtual void Report() override { ; }
	virtual void Fill(const HbtEvent *) override { ; }
	virtual void Fill(const HbtTrack *) override { ; }
	virtual void Fill(const HbtTrack *track1, const HbtTrack *track2) override;

	void Write();
	TH1D *get_h1_kT() const { return this->h1_kT; }

private:
	std::string name;
	TH1D *h1_kT;
};

#endif