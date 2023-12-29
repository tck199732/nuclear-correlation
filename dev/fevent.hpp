#ifndef fevent_hpp
#define fevent_hpp

#include "collection.hpp"
#include "track.hpp"

/**
 * @brief This class is used to store two track collections.
 * Each track collection is a collection of the same type of particles in the same event.
 * Each fevent object will be stored in the event-mixing buffer.
 */
class fevent {
public:
	fevent();
	// do not allow copying
	fevent(const fevent &ev) = delete;
	fevent &operator=(const fevent &ev) = delete;
	~fevent();

	track_collection *get_first_collection() const { return first_collection; }
	track_collection *get_second_collection() const { return second_collection; }

private:
	track_collection *first_collection;
	track_collection *second_collection;
};
#endif