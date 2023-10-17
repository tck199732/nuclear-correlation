#include "custom_track_cut.hpp"

custom_track_cut::custom_track_cut()
{
    ntracks_passed = 0;
    ntracks_failed = 0;

    accepted_neutron = 0;
    accepted_proton = 0;
    transverse_velocity_gate = {0., DBL_MAX};
}

custom_track_cut::custom_track_cut(const custom_track_cut &cut)
{
    ntracks_passed = cut.ntracks_passed;
    ntracks_failed = cut.ntracks_failed;
    accepted_neutron = cut.accepted_neutron;
    accepted_proton = cut.accepted_proton;
    transverse_velocity_gate = cut.transverse_velocity_gate;
}

bool custom_track_cut::pass(const track *trk) {
    auto ctrk = dynamic_cast<const custom_track *>(trk);
    if (!ctrk) throw std::bad_cast();
    return this->pass(ctrk);
}

bool custom_track_cut::pass(const custom_track *ctrk)
{   
    double pt = std::sqrt(ctrk->get_vx() * ctrk->get_vx() + ctrk->get_vy() * ctrk->get_vy());
    bool accepted = (
        ctrk->get_neutron() == this->accepted_neutron && 
        ctrk->get_proton() == this->accepted_proton &&
        pt >= this->transverse_velocity_gate[0] &&
        pt <= this->transverse_velocity_gate[1] &&
        ctrk->get_efficiency() > this->accepted_efficiency[0] && 
        ctrk->get_efficiency() <= this->accepted_efficiency[1]
    );

    accepted ? ntracks_passed++ : ntracks_failed++;
    return accepted;
}