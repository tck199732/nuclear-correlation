#ifndef custom_track_monitor_hpp
#define custom_track_monitor_hpp

#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "monitor.hpp"
#include "track.hpp"
class custom_track_monitor : public monitor {
public:
	custom_track_monitor(const std::string &name = "");
	virtual ~custom_track_monitor();
	virtual void report() override { ; }

	virtual void fill(const event *) override { ; }
	virtual void fill(const track *trk) override;
	virtual void fill(const std::pair<track *, track *> &) override { ; }
	void write();
	TH1D *get_h1_transverse_velocity() const { return this->h1_transverse_velocity; }
	TH2D *get_h2_kinergy_theta() const { return this->h2_kinergy_theta; }

private:
	std::string name;
	TH1D *h1_transverse_velocity;
	TH2D *h2_kinergy_theta;
};

#endif