#ifndef HbtTrack_hpp
#define HbtTrack_hpp

#include <any>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "HbtProperty.hpp"
class HbtTrack : public HbtProperty {
public:
	// default constructor
	HbtTrack();
	// constructor with N and Z
	HbtTrack(const unsigned int &N, const unsigned int &Z);
	// constructor with all mProperties
	HbtTrack(
		const unsigned int &N, const unsigned int &Z, const double &mass, const double &px_, const double &py_,
		const double &pz_, const double &x = 0., const double &y = 0., const double &z = 0., const double &t = 0.
	);
	// constructor with all mProperties defined in a std::array
	HbtTrack(
		const unsigned int &N, const unsigned int &Z, const double &mass, const std::array<double, 3> &p_,
		const std::array<double, 4> &x_ = {0., 0., 0., 0.}
	);
	// constructor with all mProperties defined in a std::vector
	HbtTrack(
		const unsigned int &N, const unsigned int &Z, const double &mass, const std::vector<double> &p_,
		const std::vector<double> &x_ = {0., 0., 0., 0.}
	);
	// constructor with all mProperties defined in a std::initializer_list
	HbtTrack(
		const unsigned int &N, const unsigned int &Z, const double &mass, const std::initializer_list<double> &p_,
		const std::initializer_list<double> &x_ = {0., 0., 0., 0.}
	);

	// copy constructor
	HbtTrack(const HbtTrack &);
	// move constructor
	HbtTrack(HbtTrack &&) = default;
	// copy assignment
	HbtTrack &operator=(const HbtTrack &);
	// move assignment
	HbtTrack &operator=(HbtTrack &&) = default;

	virtual ~HbtTrack() { ; }
	void Initialize();

	// setters
	void SetNeutron(const unsigned int &N);
	void SetProton(const unsigned int &Z);
	void SetMass(const double &mass);
	void SetPxPerNucleon(const double &px_);
	void SetPyPerNucleon(const double &py_);
	void SetPzPerNucleon(const double &pz_);
	void SetX(const double &x);
	void SetY(const double &y);
	void SetZ(const double &z);
	void SetTime(const double &t);
	void SetEfficiency(const double &eff);

	// getters
	unsigned int GetNeutron() const { return mNeutron; }
	unsigned int GetProton() const { return mProton; }
	double GetMass() const { return mMass; }

	double GetPxPerNucleon() const { return mPxPerNucleon; }
	double GetPyPerNucleon() const { return mPyPerNucleon; }
	double GetPzPerNucleon() const { return mPzPerNucleon; }

	double GetX() const { return mX; }
	double GetY() const { return mY; }
	double GetZ() const { return mZ; }
	double GetTime() const { return mT; }

	double GetPx() const { return mPx; }
	double GetPy() const { return mPy; }
	double GetPz() const { return mPz; }
	double GetE() const { return mE; }

	double GetEfficiency() const { return mEfficiency; }

protected:
	// mProperties set by constructor
	unsigned int mNeutron, mProton;
	double mMass;										// rest mass
	double mPxPerNucleon, mPyPerNucleon, mPzPerNucleon; // three momentum per nucleon
	double mX, mY, mZ, mT;								// four position

	// below are mProperties to be automatically calculated
	double mPx, mPy, mPz, mE; // four momentum

	double mEfficiency;
};

inline void HbtTrack::SetNeutron(const unsigned int &N) { mNeutron = N; }

inline void HbtTrack::SetProton(const unsigned int &Z) { mProton = Z; }
inline void HbtTrack::SetMass(const double &mass) { mMass = mass; }

inline void HbtTrack::SetPxPerNucleon(const double &px_) { mPxPerNucleon = px_; }

inline void HbtTrack::SetPyPerNucleon(const double &py_) { mPyPerNucleon = py_; }

inline void HbtTrack::SetPzPerNucleon(const double &pz_) { mPzPerNucleon = pz_; }

inline void HbtTrack::SetX(const double &x) { mX = x; }

inline void HbtTrack::SetY(const double &y) { mY = y; }

inline void HbtTrack::SetZ(const double &z) { mZ = z; }

inline void HbtTrack::SetTime(const double &t) { mT = t; }

inline void HbtTrack::SetEfficiency(const double &eff) { mEfficiency = eff; }
#endif
