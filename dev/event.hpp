#ifndef event_hpp
#define event_hpp

#include "collection.hpp"
#include "property.hpp"
#include "track.hpp"

class event : public property {
public:
	event();
	event(const event &ev);
	event(event &&ev) = default;
	event &operator=(const event &ev) = default;
	event &operator=(event &&ev) = default;
	virtual ~event();
	track_collection *get_track_collection() const { return this->tracks; }

	void set_multiplicity(const unsigned int &mult);
	void set_impact_parameter(const double &b);

	unsigned int get_multiplicity() const { return this->multiplicity; }
	double get_impact_parameter() const { return this->impact_parameter; }

private:
	unsigned int multiplicity;
	double impact_parameter;
	track_collection *tracks;
};

inline void event::set_multiplicity(const unsigned int &mult) { this->multiplicity = mult; }
inline void event::set_impact_parameter(const double &b) { this->impact_parameter = b; }
#endif