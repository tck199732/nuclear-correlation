#include "fevent.hpp"

fevent::fevent() {
	first_collection = new track_collection();
	second_collection = new track_collection();
}

fevent::~fevent() {
	for (auto &ptcl : *first_collection) {
		delete ptcl;
	}
	for (auto &ptcl : *second_collection) {
		delete ptcl;
	}
	first_collection->clear();
	second_collection->clear();
	delete first_collection;
	delete second_collection;
}