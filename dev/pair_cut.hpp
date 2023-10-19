
#ifndef pair_cut_hpp
#define pair_cut_hpp

#include "base_cut.hpp"
class pair_cut : public base_cut
{
public:
    pair_cut() = default;
    pair_cut(const pair_cut &) = default;
    virtual ~pair_cut() = default;
    virtual bool pass(const pair *pair) = 0;
};

#endif