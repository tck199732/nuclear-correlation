#include "HbtTrack.hpp"

HbtTrack::HbtTrack() :
	mNeutron(0),
	mProton(0),
	mMass(0.),
	mPxPerNucleon(0.),
	mPyPerNucleon(0.),
	mPzPerNucleon(0.),
	mX(0.),
	mY(0.),
	mZ(0.),
	mT(0.),
	mEfficiency(1.) {
	Initialize();
}

HbtTrack::HbtTrack(const unsigned int &N, const unsigned int &Z) : mNeutron(N), mProton(Z) {
	mMass = 0.;
	mPxPerNucleon = 0.;
	mPyPerNucleon = 0.;
	mPzPerNucleon = 0.;
	mX = 0.;
	mY = 0.;
	mZ = 0.;
	mT = 0.;
	mEfficiency = 1.;
	Initialize();
}

HbtTrack::HbtTrack(
	const unsigned int &N, const unsigned int &Z, const double &mass, const double &px_, const double &py_,
	const double &pz_, const double &x, const double &y, const double &z, const double &t
) :
	mNeutron(N),
	mProton(Z),
	mMass(mass),
	mPxPerNucleon(px_),
	mPyPerNucleon(py_),
	mPzPerNucleon(pz_),
	mX(x),
	mY(y),
	mZ(z),
	mT(t),
	mEfficiency(1.) {
	Initialize();
}

HbtTrack::HbtTrack(
	const unsigned int &N, const unsigned int &Z, const double &mass, const std::array<double, 3> &p_,
	const std::array<double, 4> &x_
) :
	mNeutron(N),
	mProton(Z),
	mMass(mass),
	mPxPerNucleon(p_[0]),
	mPyPerNucleon(p_[1]),
	mPzPerNucleon(p_[2]),
	mX(x_[0]),
	mY(x_[1]),
	mZ(x_[2]),
	mT(x_[3]),
	mEfficiency(1.) {
	Initialize();
}

HbtTrack::HbtTrack(
	const unsigned int &N, const unsigned int &Z, const double &mass, const std::vector<double> &p_,
	const std::vector<double> &x_
) :
	mNeutron(N),
	mProton(Z),
	mMass(mass),
	mEfficiency(1.) {
	assert(p_.size() == 3);
	mPxPerNucleon = p_[0];
	mPyPerNucleon = p_[1];
	mPzPerNucleon = p_[2];

	assert(x_.size() == 4);
	mX = x_[0];
	mY = x_[1];
	mZ = x_[2];
	mT = x_[3];

	Initialize();
}

HbtTrack::HbtTrack(
	const unsigned int &N, const unsigned int &Z, const double &mass, const std::initializer_list<double> &p_,
	const std::initializer_list<double> &x_
) :
	mNeutron(N),
	mProton(Z),
	mMass(mass),
	mEfficiency(1.) {

	assert(p_.size() == 3);
	mPxPerNucleon = *(p_.begin());
	mPyPerNucleon = *(p_.begin() + 1);
	mPzPerNucleon = *(p_.begin() + 2);

	assert(x_.size() == 4);

	mX = *(x_.begin());
	mY = *(x_.begin() + 1);
	mZ = *(x_.begin() + 2);
	mT = *(x_.begin() + 3);

	Initialize();
}

HbtTrack::HbtTrack(const HbtTrack &HbtTrack) :
	mNeutron(HbtTrack.mNeutron),
	mProton(HbtTrack.mProton),
	mMass(HbtTrack.mMass),
	mPxPerNucleon(HbtTrack.mPxPerNucleon),
	mPyPerNucleon(HbtTrack.mPyPerNucleon),
	mPzPerNucleon(HbtTrack.mPzPerNucleon),
	mX(HbtTrack.mX),
	mY(HbtTrack.mY),
	mZ(HbtTrack.mZ),
	mT(HbtTrack.mT),
	mEfficiency(HbtTrack.mEfficiency) {
	// note : shallow-copy if a pointer object is in the map
	mProperties = HbtTrack.mProperties;
	// recalculate the four momentum
	Initialize();
}

HbtTrack &HbtTrack::operator=(const HbtTrack &HbtTrack) {
	if (this != &HbtTrack) {
		mNeutron = HbtTrack.mNeutron;
		mProton = HbtTrack.mProton;
		mMass = HbtTrack.mMass;
		mPxPerNucleon = HbtTrack.mPxPerNucleon;
		mPyPerNucleon = HbtTrack.mPyPerNucleon;
		mPzPerNucleon = HbtTrack.mPzPerNucleon;
		mX = HbtTrack.mX;
		mY = HbtTrack.mY;
		mZ = HbtTrack.mZ;
		mT = HbtTrack.mT;
		mEfficiency = HbtTrack.mEfficiency;

		// note : shallow-copy if a pointer object is in the map
		mProperties = HbtTrack.mProperties;
		// recalculate the four momentum
		Initialize();
	}
	return *this;
}

void HbtTrack::Initialize() {
	auto nucleons = mNeutron + mProton;
	mPx = mPxPerNucleon * nucleons;
	mPy = mPyPerNucleon * nucleons;
	mPz = mPzPerNucleon * nucleons;
	mE = std::sqrt(mMass * mMass + mPx * mPx + mPy * mPy + mPz * mPz);
	return;
}