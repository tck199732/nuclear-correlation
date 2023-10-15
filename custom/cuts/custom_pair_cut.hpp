#ifndef custom_pair_cut_hpp
#define custom_pair_cut_hpp

#include <array>
#include <cfloat>

#include "pair.hpp"
#include "pair_cut.hpp"

class custom_pair_cut : public pair_cut
{
public:
    custom_pair_cut();
    custom_pair_cut(const custom_pair_cut & cut);
    bool pass(const pair *pr);
    void set_transverse_momentum(const double &vmin, const double &vmax) { transverse_momentum = {vmin, vmax}; }

private:
    long npairs_passed;
    long npairs_failed;
    std::array<double, 2> transverse_momentum;
};

#endif
