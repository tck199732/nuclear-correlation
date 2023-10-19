#include "pair.hpp"

pair::pair() {
	first_particle = 0;
	second_particle = 0;
}

pair::pair(particle *ptcl1, particle *ptcl2) {
	first_particle = ptcl1;
	second_particle = ptcl2;
}

pair::pair(const pair &pr) {
	this->first_particle = new particle(*pr.first_particle);
	this->second_particle = new particle(*pr.second_particle);
}

pair::~pair() {
	// do not delete the particles, they are owned by the track collection
}

void pair::set_first_particle(particle *ptcl) { first_particle = ptcl; }

void pair::set_second_particle(particle *ptcl) { second_particle = ptcl; }
