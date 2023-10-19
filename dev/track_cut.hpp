#ifndef track_cut_hpp
#define track_cut_hpp

#include "base_cut.hpp"
class track_cut : public base_cut
{
public:
    track_cut() = default;
    track_cut(const track_cut &) = default;
    virtual ~track_cut() = default;
    virtual bool pass(const track *trk) = 0;
};

#endif