#include "custom_pair_cut.hpp"

custom_pair_cut::custom_pair_cut()
{
    npairs_passed = 0;
    npairs_failed = 0;
    transverse_momentum = {0.0, DBL_MAX};
}

custom_pair_cut::custom_pair_cut(const custom_pair_cut &cut)
{
    npairs_passed = cut.npairs_passed;
    npairs_failed = cut.npairs_failed;
    transverse_momentum = cut.transverse_momentum;
}

bool custom_pair_cut::pass(const pair *pr)
{   
    auto first = pr->get_first_particle();
    auto second = pr->get_second_particle();
    auto px = first->get_px() + second->get_px();
    auto py = first->get_py() + second->get_py();
    auto kt = std::sqrt(px * px + py * py);
    bool accepted = (kt >= transverse_momentum[0] && kt <= transverse_momentum[1]);
    accepted ? npairs_passed++ : npairs_failed++;
    return accepted;
}
