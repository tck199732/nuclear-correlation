#include "fevent.hpp"

fevent::fevent() {
	this->first_collection = new track_collection();
	this->second_collection = new track_collection();
}

fevent::~fevent() {
	for (auto &ptcl : *(this->first_collection)) {
		delete ptcl;
		ptcl = nullptr;
	}
	this->first_collection->clear();
	delete this->first_collection;
	this->first_collection = nullptr;

	for (auto &ptcl : *(this->second_collection)) {
		delete ptcl;
		ptcl = nullptr;
	}
	this->second_collection->clear();
	delete this->second_collection;
	this->second_collection = nullptr;
}