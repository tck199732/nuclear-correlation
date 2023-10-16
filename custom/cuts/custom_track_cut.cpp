#include "custom_track_cut.hpp"

custom_track_cut::custom_track_cut()
{
    ntracks_passed = 0;
    ntracks_failed = 0;
    N = 0;
    Z = 0;
    transverse_momentum = {0., DBL_MAX};
    detector_idx = 0;
}

custom_track_cut::custom_track_cut(const custom_track_cut &cut)
{
    ntracks_passed = cut.ntracks_passed;
    ntracks_failed = cut.ntracks_failed;
    N = cut.N;
    Z = cut.Z;
    transverse_momentum = cut.transverse_momentum;
    detector_idx = cut.detector_idx;
}

bool custom_track_cut::pass(const track *trk)
{   
    double pt = std::sqrt(trk->get_vx() * trk->get_vx() + trk->get_vy() * trk->get_vy());
    unsigned int idx;
    try {
        idx = trk->get_uint_property("detector-index");
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << e.what() << std::endl;
        std::abort();
    }
    
    bool accepted = (
        trk->get_neutron() == this->N && 
        trk->get_proton() == this->Z &&
        pt >= this->transverse_momentum[0] &&
        pt <= this->transverse_momentum[1] &&
        detector_idx == idx
    );

    accepted ? ntracks_passed++ : ntracks_failed++;
    return accepted;
}