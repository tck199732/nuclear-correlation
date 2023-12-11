#include "event.hpp"

event::event() : multiplicity(0), impact_parameter(0.0) { this->tracks = new track_collection(); }

event::event(const event &evt) {
	this->multiplicity = evt.multiplicity;
	this->impact_parameter = evt.impact_parameter;
	this->tracks = new track_collection();
	// explicitly copy the tracks
	for (auto &trk : *evt.tracks) {
		this->tracks->push_back(new track(*trk));
	}
	this->properties = evt.properties;
}

event::~event() {
	for (auto &trk : *tracks) {
		if (trk != nullptr) {
			delete trk;
		}
	}
	this->tracks->clear();
	delete this->tracks;
}