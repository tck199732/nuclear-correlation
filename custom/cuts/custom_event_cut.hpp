#ifndef custom_event_cut_hpp
#define custom_event_cut_hpp

#include <string>
#include <array>

#include "event.hpp"
#include "event_cut.hpp"

class custom_event_cut : public event_cut
{
public:
    custom_event_cut();
    custom_event_cut(const custom_event_cut &);
    bool pass(const event *);
    void set_multiplicity(const unsigned int &vmin, const unsigned int &vmax);
    void set_impact_parameter(const double &vmin, const double &vmax);

    long get_nevents_passed() { return nevents_passed; }
    long get_nevents_failed() { return nevents_failed; }

private:
    std::array<unsigned int, 2> multiplicity;
    std::array<double, 2> impact_parameter;
    long nevents_passed;
    long nevents_failed;
};
#endif