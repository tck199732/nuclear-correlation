#ifndef fevent_hpp
#define fevent_hpp

#include "collection.hpp"
#include "track.hpp"

class fevent {
public:
	fevent();
	fevent(const fevent &ev);
	~fevent();

	track_collection *get_first_collection() const { return first_collection; }
	track_collection *get_second_collection() const { return second_collection; }

private:
	track_collection *first_collection;
	track_collection *second_collection;
};
#endif