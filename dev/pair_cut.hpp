
#ifndef pair_cut_hpp
#define pair_cut_hpp

class pair;
class pair_cut {
public:
    pair_cut(){};
    pair_cut(const pair_cut &);
    virtual ~pair_cut(){};
    virtual bool pass(const pair *pair) = 0;
};

#endif