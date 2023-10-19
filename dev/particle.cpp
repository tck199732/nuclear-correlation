#include "particle.hpp"

particle::particle(const unsigned &N, const unsigned &Z, const double &px, const double &py,
				   const double &pz, const double &E, const double &x, const double &y,
				   const double &z, const double &t) {
	this->N = N;
	this->Z = Z;
	this->px = px;
	this->py = py;
	this->pz = pz;
	this->E = E;
	this->x = x;
	this->y = y;
	this->z = z;
	this->t = t;
	this->trk = nullptr;
}

particle::particle(const particle &ptcl) {
	this->N = ptcl.N;
	this->Z = ptcl.Z;
	this->px = ptcl.px;
	this->py = ptcl.py;
	this->pz = ptcl.pz;
	this->E = ptcl.E;
	this->x = ptcl.x;
	this->y = ptcl.y;
	this->z = ptcl.z;
	this->t = ptcl.t;

	if (ptcl.trk != nullptr) {
		this->trk = new track(*ptcl.trk);
	} else {
		this->trk = nullptr;
	}
}

particle::particle(const track *trk) {
	this->N = trk->get_neutron();
	this->Z = trk->get_proton();
	unsigned int a = this->N + this->Z;
	this->px = trk->get_vx() * a;
	this->py = trk->get_vy() * a;
	this->pz = trk->get_vz() * a;
	this->E =
		std::sqrt(pow(trk->get_mass(), 2) + pow(this->px, 2) + pow(this->py, 2) + pow(this->pz, 2));

	this->x = trk->get_x();
	this->y = trk->get_y();
	this->z = trk->get_z();
	this->t = trk->get_t();
	this->trk = new track(*trk);
}

particle::~particle() {
	if (this->trk)
		delete this->trk;
}