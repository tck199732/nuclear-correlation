#include "event.hpp"

event::event() {
    tracks = new track_collection();
}

event::event(const event &evt) {

    this->multiplicity = evt.multiplicity;
    this->impact_parameter = evt.impact_parameter;

    this->tracks = new track_collection();

    for (auto& trk : *evt.tracks)
    {
        this->tracks->push_back(new track(*trk));
    }
}

event::~event() {
    
    for (auto& trk : *tracks) delete trk;
    tracks->clear();
    delete tracks;
}