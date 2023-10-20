#include "physics.hpp"

physics::four_vector::four_vector(const four_vector &other) {
	this->p0 = other.p0;
	this->p1 = other.p1;
	this->p2 = other.p2;
	this->p3 = other.p3;
}

physics::four_vector &physics::four_vector::operator=(const four_vector &other) {
	this->p0 = other.p0;
	this->p1 = other.p1;
	this->p2 = other.p2;
	this->p3 = other.p3;
	return *this;
}

physics::four_vector &physics::four_vector::operator+=(const four_vector &other) {
	this->p0 += other.p0;
	this->p1 += other.p1;
	this->p2 += other.p2;
	this->p3 += other.p3;
	return *this;
}

physics::four_vector &physics::four_vector::operator-=(const four_vector &other) {
	this->p0 -= other.p0;
	this->p1 -= other.p1;
	this->p2 -= other.p2;
	this->p3 -= other.p3;
	return *this;
}

physics::four_vector &physics::four_vector::operator*=(const double &scalar) {
	this->p0 *= scalar;
	this->p1 *= scalar;
	this->p2 *= scalar;
	this->p3 *= scalar;
	return *this;
}

physics::four_vector &physics::four_vector::operator/=(const double &scalar) {
	this->p0 /= scalar;
	this->p1 /= scalar;
	this->p2 /= scalar;
	this->p3 /= scalar;
	return *this;
}

physics::four_vector physics::four_vector::operator+(const four_vector &other) const {
	return four_vector(*this) += other;
}

physics::four_vector physics::four_vector::operator-(const four_vector &other) const {
	return four_vector(*this) -= other;
}

physics::four_vector physics::four_vector::operator*(const double &scalar) const {
	return four_vector(*this) *= scalar;
}

physics::four_vector physics::four_vector::operator/(const double &scalar) const {
	return four_vector(*this) /= scalar;
}

void physics::four_vector::boost(const double &beta_x, const double &beta_y, const double &beta_z) {
	double beta = std::sqrt(beta_x * beta_x + beta_y * beta_y + beta_z * beta_z);
	double gamma = 1. / std::sqrt(1. - beta * beta);
	auto dot = [](const std::array<double, 3> a, const std::array<double, 3> b) -> double {
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	};
	auto r_dot_beta = dot({this->p1, this->p2, this->p3}, {beta_x, beta_y, beta_z});
	p1 = p1 + (gamma - 1.) * r_dot_beta * beta_x / (beta * beta) + gamma * beta_x * p0;
	p2 = p2 + (gamma - 1.) * r_dot_beta * beta_y / (beta * beta) + gamma * beta_y * p0;
	p3 = p3 + (gamma - 1.) * r_dot_beta * beta_z / (beta * beta) + gamma * beta_z * p0;
	p0 = gamma * (p0 + r_dot_beta);
}

double physics::four_vector::Pt() const { return std::sqrt(p1 * p1 + p2 * p2); }
double physics::four_vector::Mag() const { return std::sqrt(p1 * p1 + p2 * p2 + p3 * p3); }
double physics::four_vector::M() const { return std::sqrt(p0 * p0 - p1 * p1 - p2 * p2 - p3 * p3); }

/******************************CORRELATION FUNCTION ************************************/
double physics::get_minv(const four_vector &first, const four_vector &second) {
	return (first + second).M();
}

double physics::get_qinv(const four_vector &first, const four_vector &second) {
	return (first - second).M();
}

double physics::get_qx(const four_vector &first, const four_vector &second) {
	return (first.Px() * second.M() - second.Px() * first.M()) / (first.M() + second.M());
}

double physics::get_qy(const four_vector &first, const four_vector &second) {
	return (first.Py() * second.M() - second.Py() * first.M()) / (first.M() + second.M());
}

double physics::get_qz(const four_vector &first, const four_vector &second) {
	return (first.Pz() * second.M() - second.Pz() * first.M()) / (first.M() + second.M());
}

// out-side-long coordinate system (Bertsch-Pratt)
// first boost to the frame where the pair Pz = 0 (longitudinal pair rest frame)
// then rotate the transverse plane with an angle \cos\theta = Px / Pt
double physics::get_qout(const four_vector &first, const four_vector &second) {
	auto P = (first + second);
	auto q = (first - second);
	return (q.Px() * P.Px() + q.Py() * P.Py()) / P.Pt();
}

double physics::get_qside(const four_vector &first, const four_vector &second) {
	auto P = (first + second);
	auto q = (first - second);
	return (q.Py() * P.Px() - q.Px() * P.Py()) / P.Pt();
}

double physics::get_qlong(const four_vector &first, const four_vector &second) {
	auto P = (first + second);
	auto q = (first - second);
	q.boost(0, 0, -P.Pz() / P.E());
	return q.Pz();
}