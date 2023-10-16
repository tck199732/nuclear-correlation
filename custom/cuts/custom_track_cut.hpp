#ifndef custom_track_cut_hpp
#define custom_track_cut_hpp

#include "track_cut.hpp"
#include "track.hpp"
#include "custom_track.hpp"

#include <iostream>
#include <array>
#include <cfloat>
#include <climits>
#include <cmath>

class custom_track_cut : public track_cut
{
public:
    custom_track_cut();
    custom_track_cut(const custom_track_cut &);
    virtual bool pass(const track *trk) override;
    bool pass(const custom_track *ctrk);

    void set_accepted_neutron(const unsigned int &N) { this->accepted_neutron = N; }
    void set_accepted_proton(const unsigned int &Z) { this->accepted_proton = Z; }
    void set_transverse_momentum(const double &vmin, const double &vmax) { this->transverse_momentum = {vmin, vmax}; }
    void set_accepted_detector_idx(const unsigned int &idx) { this->accepted_detector_idx = idx; }
    void set_accepted_efficiency(const double &vmin, const double &vmax) { this->accepted_efficiency = {vmin, vmax}; }

    unsigned int get_accepted_neutron() const { return this->accepted_neutron; }
    unsigned int get_accepted_proton() const { return this->accepted_proton; }
    int get_accepted_detector_idx() const { return this->accepted_detector_idx; }
    std::array<double, 2> get_transverse_momentum() const { return this->transverse_momentum; }
    std::array<double, 2> get_accepted_efficiency() const { return this->accepted_efficiency; }

    long get_ntracks_passed() const { return ntracks_passed; }
    long get_ntracks_failed() const { return ntracks_failed; }

private:
    unsigned int accepted_neutron, accepted_proton;
    std::array<double, 2> transverse_momentum;
    int accepted_detector_idx;
    std::array<double, 2> accepted_efficiency;
    long ntracks_passed;
    long ntracks_failed;
};
#endif