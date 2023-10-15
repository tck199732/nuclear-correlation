#include "fevent.hpp"

fevent::fevent() {
    first_collection = new particle_collection();
    second_collection = new particle_collection();
}

fevent::fevent(const fevent &evt) {
    this->first_collection = new particle_collection();
    this->second_collection = new particle_collection();

    for (auto& ptcl : *evt.first_collection)
    {
        this->first_collection->push_back(ptcl);
    }
    for (auto& ptcl : *evt.second_collection)
    {
        this->second_collection->push_back(ptcl);
    }

    delete first_collection;
    delete second_collection;
}

fevent::~fevent() {
    for (auto& ptcl : *first_collection) delete ptcl;
    for (auto& ptcl : *second_collection) delete ptcl;
    first_collection->clear();
    second_collection->clear();
    delete first_collection;
    delete second_collection;
}