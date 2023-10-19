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
    virtual bool pass(const pair *pr) override;

    void set_transverse_velocity_gate(const double &vmin, const double &vmax) { this->transverse_velocity_gate = {vmin, vmax}; }
    void set_consider_detector_index(const bool &v) { this->is_consider_detector_index = v; }

    bool get_consider_detector_index() const { return this->is_consider_detector_index; }
    std::array<double, 2> get_transverse_velocity_gate() const { return this->transverse_velocity_gate; }

    long get_npairs_passed() const { return this->npairs_passed; }
    long get_npairs_failed() const { return this->npairs_failed; }
private:
    long npairs_passed;
    long npairs_failed;

    bool is_consider_detector_index;
    std::array<double, 2> transverse_velocity_gate;
};

#endif
