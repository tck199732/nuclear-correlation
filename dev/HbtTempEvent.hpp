#ifndef fevent_hpp
#define fevent_hpp

#include "HbtCollection.hpp"
#include "HbtTrack.hpp"

/**
 * @brief This class is used to store two HbtTrack collections.
 * Each contains one type of particle in the same HbtEvent.
 * Each HbtTempEvent object will be stored in the HbtEvent-mixing buffer.
 */
class HbtTempEvent {
public:
	HbtTempEvent();
	// do not allow copying
	HbtTempEvent(const HbtTempEvent &ev) = delete;
	HbtTempEvent &operator=(const HbtTempEvent &ev) = delete;
	~HbtTempEvent();

	HbtTrackCollection *GetFirstTrackCollection() const { return mFirstTrackCollection; }
	HbtTrackCollection *GetSecTrackCollection() const { return mSecTrackCollection; }

private:
	HbtTrackCollection *mFirstTrackCollection;
	HbtTrackCollection *mSecTrackCollection;
};
#endif