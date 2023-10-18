#ifndef event_cut_hpp
#define event_cut_hpp

#include "base_cut.hpp"
class event_cut : public base_cut
{
public:
    event_cut() = default;
    event_cut(const event_cut &) = default;
    virtual ~event_cut() = default;
    virtual bool pass(const event *event) = 0;
};
#endif
