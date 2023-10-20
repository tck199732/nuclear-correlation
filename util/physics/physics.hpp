#ifndef physics_hpp
#define physics_hpp

#include <array>
#include <cmath>

namespace physics {
class four_vector {
public:
	four_vector(const double &x, const double &y, const double &z, const double &t)
		: p0(t), p1(x), p2(y), p3(z) {}
	four_vector(const four_vector &other);
	~four_vector() = default;
	// operators overloading
	four_vector &operator=(const four_vector &other);
	four_vector &operator+=(const four_vector &other);
	four_vector &operator-=(const four_vector &other);
	four_vector &operator*=(const double &scalar);
	four_vector &operator/=(const double &scalar);
	four_vector operator+(const four_vector &other) const;
	four_vector operator-(const four_vector &other) const;
	four_vector operator*(const double &scalar) const;
	four_vector operator/(const double &scalar) const;

	void boost(const double &beta_x, const double &beta_y, const double &beta_z);

	double Px() const { return this->p1; }
	double Py() const { return this->p2; }
	double Pz() const { return this->p3; }
	double E() const { return this->p0; }

	double Pt() const;
	double Mag() const;
	double M() const;
	double beta_x() const { return -this->p1 / this->p0; }
	double beta_y() const { return -this->p2 / this->p0; }
	double beta_z() const { return -this->p3 / this->p0; }
	double gamma() const { return this->p0 / this->M(); }

private:
	double p0, p1, p2, p3;
};

double get_qx(const four_vector &first, const four_vector &second);
double get_qy(const four_vector &first, const four_vector &second);
double get_qz(const four_vector &first, const four_vector &second);

double get_qout(const four_vector &first, const four_vector &second);
double get_qside(const four_vector &first, const four_vector &second);
double get_qlong(const four_vector &first, const four_vector &second);

double get_minv(const four_vector &first, const four_vector &second);
double get_qinv(const four_vector &first, const four_vector &second);

}; // namespace physics
#endif