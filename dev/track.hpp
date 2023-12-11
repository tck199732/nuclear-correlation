#ifndef track_hpp
#define track_hpp

#include <any>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "property.hpp"
class track : public property {
public:
	// default constructor
	track();
	// constructor with N and Z
	track(const unsigned int &N, const unsigned int &Z);
	// constructor with all properties
	track(
		const unsigned int &N, const unsigned int &Z, const double &mass, const double &px_, const double &py_,
		const double &pz_, const double &x = 0., const double &y = 0., const double &z = 0., const double &t = 0.
	);
	// constructor with all properties defined in a std::array
	track(
		const unsigned int &N, const unsigned int &Z, const double &mass, const std::array<double, 3> &p_,
		const std::array<double, 4> &x_ = {0., 0., 0., 0.}
	);
	// constructor with all properties defined in a std::vector
	track(
		const unsigned int &N, const unsigned int &Z, const double &mass, const std::vector<double> &p_,
		const std::vector<double> &x_ = {0., 0., 0., 0.}
	);
	// copy constructor
	track(const track &);
	// move constructor
	track(track &&) = default;
	virtual ~track() { ; }
	void initalize();

	// setters
	void set_N(const unsigned int &N);
	void set_Z(const unsigned int &Z);
	void set_mass(const double &mass);
	void set_px_per_nucleon(const double &px_);
	void set_py_per_nucleon(const double &py_);
	void set_pz_per_nucleon(const double &pz_);
	void set_x(const double &x);
	void set_y(const double &y);
	void set_z(const double &z);
	void set_t(const double &t);

	// getters
	unsigned int get_N() const { return this->N; }
	unsigned int get_Z() const { return this->Z; }
	double get_mass() const { return this->mass; }

	double get_px_per_nucleon() const { return this->px_; }
	double get_py_per_nucleon() const { return this->py_; }
	double get_pz_per_nucleon() const { return this->pz_; }

	double get_x() const { return this->x; }
	double get_y() const { return this->y; }
	double get_z() const { return this->z; }
	double get_t() const { return this->t; }

	double get_px() const { return this->px; }
	double get_py() const { return this->py; }
	double get_pz() const { return this->pz; }
	double get_E() const { return this->E; }

protected:
	// properties set by constructor
	unsigned int N, Z;	  // neutron, proton number
	double mass;		  // rest mass
	double px_, py_, pz_; // momentum per nucleon
	double x, y, z, t;	  // spacetime

	// below are properties to be automatically calculated
	double px, py, pz, E; // four momentum
};

inline void track::set_N(const unsigned int &N) { this->N = N; }

inline void track::set_Z(const unsigned int &Z) { this->Z = Z; }

inline void track::set_mass(const double &mass) { this->mass = mass; }

inline void track::set_px_per_nucleon(const double &px_) { this->px_ = px_; }

inline void track::set_py_per_nucleon(const double &py_) { this->py_ = py_; }

inline void track::set_pz_per_nucleon(const double &pz_) { this->pz_ = pz_; }

inline void track::set_x(const double &x) { this->x = x; }

inline void track::set_y(const double &y) { this->y = y; }

inline void track::set_z(const double &z) { this->z = z; }

inline void track::set_t(const double &t) { this->t = t; }
#endif
