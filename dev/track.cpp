#include "track.hpp"

track::track(const unsigned int &N, const unsigned int &Z, const double &vx, const double &vy,
			 const double &vz, const double &mass, const double &x, const double &y,
			 const double &z, const double &t) {
	this->N = N;
	this->Z = Z;
	this->vx = vx;
	this->vy = vy;
	this->vz = vz;
	this->mass = mass;
	this->x = x;
	this->y = y;
	this->z = z;
	this->t = t;
}

track::track(const unsigned int &N, const unsigned int &Z, const double &mass,
			 const std::array<double, 3> &v, const std::array<double, 4> &x) {
	this->N = N;
	this->Z = Z;
	this->vx = v[0];
	this->vy = v[1];
	this->vz = v[2];
	this->mass = mass;
	this->x = x[0];
	this->y = x[1];
	this->z = x[2];
	this->t = x[3];
}

track::track(const track &track) {
	this->N = track.N;
	this->Z = track.Z;
	this->mass = track.mass;
	this->vx = track.vx;
	this->vy = track.vy;
	this->vz = track.vz;
	this->x = track.x;
	this->y = track.y;
	this->z = track.z;
	this->t = track.t;
	// note : shallow-copy if a pointer object is in the map
	this->properties = track.properties;
}
