#ifndef custom_track_cut_hpp
#define custom_track_cut_hpp

#include "track_cut.hpp"
#include "track.hpp"

#include <iostream>
#include <array>
#include <cfloat>
#include <cmath>

class custom_track_cut : public track_cut
{
public:
    custom_track_cut();
    custom_track_cut(const custom_track_cut &);
    bool pass(const track *trk);
    void set_neutron(const unsigned int & N) { this->N = N; }
    void set_proton(const unsigned int & Z) { this->Z = Z; }
    void set_transverse_momentum(const double & vmin, const double & vmax)
    {
        this->transverse_momentum = {vmin, vmax};
    }
    void set_detector_idx(const unsigned int & idx) { this->detector_idx = idx; }
    
private:
    unsigned int N, Z;
    std::array<double, 2> transverse_momentum;
    unsigned int detector_idx;
    long ntracks_passed;
    long ntracks_failed;
};
#endif