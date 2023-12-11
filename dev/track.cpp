#include "track.hpp"

track::track() : N(0), Z(0), mass(0.), px_(0.), py_(0.), pz_(0.), x(0.), y(0.), z(0.), t(0.) { this->initalize(); }

track::track(const unsigned int &N, const unsigned int &Z) : N(N), Z(Z) {
	this->mass = 0.;
	this->px_ = 0.;
	this->py_ = 0.;
	this->pz_ = 0.;
	this->x = 0.;
	this->y = 0.;
	this->z = 0.;
	this->t = 0.;
	this->initalize();
}

track::track(
	const unsigned int &N, const unsigned int &Z, const double &mass, const double &px_, const double &py_,
	const double &pz_, const double &x, const double &y, const double &z, const double &t
) :
	N(N),
	Z(Z),
	mass(mass),
	px_(px_),
	py_(py_),
	pz_(pz_),
	x(x),
	y(y),
	z(z),
	t(t) {
	this->initalize();
}

track::track(
	const unsigned int &N, const unsigned int &Z, const double &mass, const std::array<double, 3> &p_,
	const std::array<double, 4> &x_
) :
	N(N),
	Z(Z),
	mass(mass) {
	this->px_ = p_[0];
	this->py_ = p_[1];
	this->pz_ = p_[2];
	this->x = x_[0];
	this->y = x_[1];
	this->z = x_[2];
	this->t = x_[3];
	this->initalize();
}

track::track(
	const unsigned int &N, const unsigned int &Z, const double &mass, const std::vector<double> &p_,
	const std::vector<double> &x_
) :
	N(N),
	Z(Z),
	mass(mass) {

	assert(p_.size() == 3);
	this->px_ = p_[0];
	this->py_ = p_[1];
	this->pz_ = p_[2];

	assert(x_.size() == 4);
	this->x = x_[0];
	this->y = x_[1];
	this->z = x_[2];
	this->t = x_[3];
	this->initalize();
}

track::track(const track &track) :
	N(track.N),
	Z(track.Z),
	mass(track.mass),
	px_(track.px_),
	py_(track.py_),
	pz_(track.pz_),
	x(track.x),
	y(track.y),
	z(track.z),
	t(track.t) {
	// note : shallow-copy if a pointer object is in the map
	this->properties = track.properties;
	// recalculate the four momentum
	this->initalize();
}

void track::initalize() {
	auto nucleons = this->N + this->Z;
	this->px = this->px_ * nucleons;
	this->py = this->py_ * nucleons;
	this->pz = this->pz_ * nucleons;
	this->E = std::sqrt(this->mass * this->mass + this->px * this->px + this->py * this->py + this->pz * this->pz);
	return;
}