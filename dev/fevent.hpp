#ifndef fevent_hpp
#define fevent_hpp

#include "collection.hpp"
#include "particle.hpp"

class fevent {
public:
	fevent();
	fevent(const fevent &ev);
	~fevent();

	particle_collection *get_first_collection() const { return first_collection; }
	particle_collection *get_second_collection() const { return second_collection; }

private:
	particle_collection *first_collection;
	particle_collection *second_collection;
};
#endif