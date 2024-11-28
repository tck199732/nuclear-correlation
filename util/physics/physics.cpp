#include "physics.hpp"

physics::four_vector::four_vector(const double &x, const double &y, const double &z, const double &t) {
	p0 = t;
	p1 = x;
	p2 = y;
	p3 = z;
}

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

bool physics::operator==(const four_vector &track1, const four_vector &track2) {
	return track1.x() == track2.x() && track1.y() == track2.y() && track1.z() == track2.z() && track1.t() == track2.t();
}
bool physics::operator!=(const four_vector &track1, const four_vector &track2) { return !(track1 == track2); }

void physics::four_vector::boost(const double &beta_x, const double &beta_y, const double &beta_z) {
	double beta = std::sqrt(beta_x * beta_x + beta_y * beta_y + beta_z * beta_z);
	double gamma = 1. / std::sqrt(1. - beta * beta);
	auto dot = [](const std::array<double, 3> a, const std::array<double, 3> b) -> double {
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	};
	auto r_dot_beta = dot({this->p1, this->p2, this->p3}, {beta_x, beta_y, beta_z});

	auto dp1 = beta_x != 0 ? (gamma - 1.) * r_dot_beta * beta_x / (beta * beta) + gamma * beta_x * p0 : 0.;
	auto dp2 = beta_y != 0 ? (gamma - 1.) * r_dot_beta * beta_y / (beta * beta) + gamma * beta_y * p0 : 0.;
	auto dp3 = beta_z != 0 ? (gamma - 1.) * r_dot_beta * beta_z / (beta * beta) + gamma * beta_z * p0 : 0.;

	this->p1 += dp1;
	this->p2 += dp2;
	this->p3 += dp3;
	p0 = gamma * (p0 + r_dot_beta);
}

double physics::four_vector::Pt() const { return std::sqrt(p1 * p1 + p2 * p2); }
double physics::four_vector::Mag() const { return std::sqrt(p1 * p1 + p2 * p2 + p3 * p3); }
double physics::four_vector::M() const { return std::sqrt(p0 * p0 - p1 * p1 - p2 * p2 - p3 * p3); }
double physics::four_vector::M2() const { return p0 * p0 - p1 * p1 - p2 * p2 - p3 * p3; }
double physics::four_vector::Rapidity() const { return 0.5 * std::log((p0 + p3) / (p0 - p3)); }

/******************************CORRELATION FUNCTION ************************************/
double physics::get_minv(const four_vector &track1, const four_vector &track2) { return (track1 + track2).M(); }

double physics::get_qinv(const four_vector &track1, const four_vector &track2) {
	auto qinv2 = (track1 - track2).M2();
	return qinv2 > 0 ? std::sqrt(qinv2) : -std::sqrt(-qinv2);
}

physics::four_vector physics::relative_four_vector(const four_vector &track1, const four_vector &track2) {
	if (track1.M() <= 0 || track2.M() <= 0) {
		std::cout << "track1.M() = " << track1.M() << std::endl;
		std::cout << "track2.M() = " << track2.M() << std::endl;
		throw std::runtime_error("Negative mass in relative_four_vector");
	}
	return (track1 * track2.M() - track2 * track1.M()) / (track1.M() + track2.M());
}

double physics::get_qx(const four_vector &track1, const four_vector &track2) {
	return physics::relative_four_vector(track1, track2).Px();
}

double physics::get_qy(const four_vector &track1, const four_vector &track2) {
	return physics::relative_four_vector(track1, track2).Py();
}

double physics::get_qz(const four_vector &track1, const four_vector &track2) {
	return physics::relative_four_vector(track1, track2).Pz();
}

double physics::get_qout(const four_vector &track1, const four_vector &track2) {
	auto P = track1 + track2;
	auto q = track1 - track2;
	return (q.Px() * P.Px() + q.Py() * P.Py()) / P.Pt();
}

double physics::get_qside(const four_vector &track1, const four_vector &track2) {
	auto P = track1 + track2;
	auto q = track1 - track2;
	return (q.Py() * P.Px() - q.Px() * P.Py()) / P.Pt();
}

double physics::get_qlong(const four_vector &track1, const four_vector &track2) {
	auto P = track1 + track2;
	auto q = track1 - track2;
	q.boost(0, 0, -P.Pz() / P.E());
	return q.Pz();
}

double physics::get_relative_angle(const four_vector &track1, const four_vector &track2, bool degree) {
	auto dot = [](const std::array<double, 3> a, const std::array<double, 3> b) -> double {
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	};
	auto a = std::array<double, 3>{track1.Px(), track1.Py(), track1.Pz()};
	auto b = std::array<double, 3>{track2.Px(), track2.Py(), track2.Pz()};
	auto deg = degree ? 180. / M_PI : 1.;
	return std::acos(dot(a, b) / (track1.Mag() * track2.Mag())) * deg;
}

physics::four_vector physics::get_boosted_vector(
	const physics::four_vector &track, const double &beta_x, const double &beta_y, const double &beta_z
) {
	auto p = track;
	p.boost(beta_x, beta_y, beta_z);
	return p;
}