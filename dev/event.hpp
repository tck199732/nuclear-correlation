#ifndef event_hpp
#define event_hpp

#include "collection.hpp"
#include "track.hpp"

class event {
public:
	event();
	event(const event &ev);
	virtual ~event();

	track_collection *get_track_collection() const { return tracks; }

	void set_multiplicity(const unsigned int &mult) { multiplicity = mult; }
	void set_impact_parameter(const double &b) { impact_parameter = b; }

	unsigned int get_multiplicity() const { return multiplicity; }
	double get_impact_parameter() const { return impact_parameter; }

private:
	unsigned int multiplicity;
	double impact_parameter;
	track_collection *tracks;
};
#endif