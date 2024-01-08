#ifndef CustomTrackMonitor_hpp
#define CustomTrackMonitor_hpp

#include "HbtMonitor.hpp"
#include "HbtTrack.hpp"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"

class CustomTrackCutMonitor : public HbtMonitor {
public:
	CustomTrackCutMonitor(const std::string &name = "");
	virtual ~CustomTrackCutMonitor();
	virtual void Report() override { ; }

	virtual void Fill(const HbtEvent *) override { ; }
	virtual void Fill(const HbtTrack *trk) override;
	virtual void Fill(const HbtTrack *track1, const HbtTrack *track2) override { ; }
	void Write();
	TH1D *get_h1_transverse_velocity() const { return this->h1_transverse_velocity; }
	TH2D *get_h2_kinergy_theta() const { return this->h2_kinergy_theta; }

private:
	std::string name;
	TH1D *h1_transverse_velocity;
	TH2D *h2_kinergy_theta;
};

#endif