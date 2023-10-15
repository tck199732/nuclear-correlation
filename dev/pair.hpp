#ifndef pair_hpp
#define pair_hpp

#include "particle.hpp"
class pair
{
public:
    pair();
    pair(particle* ptcl1, particle* ptcl2);
    pair(const pair &pr);
    ~pair();

    void set_first_particle(particle* ptcl);
    void set_second_particle(particle* ptcl);
    particle* get_first_particle() const { return first_particle; }
    particle* get_second_particle() const { return second_particle; }

private:
    particle* first_particle;
    particle* second_particle;
};


#endif
