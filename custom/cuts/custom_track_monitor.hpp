#ifndef custom_track_monitor_hpp
#define custom_track_monitor_hpp

#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "track.hpp"
#include "monitor.hpp"
class custom_track_monitor : public monitor
{
public:
    custom_track_monitor(const std::string &name = "");
    virtual ~custom_track_monitor();
    virtual void fill(const track *evt);
    virtual void report() { ; }
    void write();

private:
    std::string name;
    TH1D *h1_transverse_velocity;
    TH2D *h2_kinergy_theta;
};

#endif