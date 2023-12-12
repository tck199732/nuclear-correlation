#ifndef physics_hpp
#define physics_hpp

#include <array>
#include <cmath>
#include <stdexcept>

namespace physics {
class four_vector {
public:
	four_vector() = default;
	four_vector(const double &x, const double &y, const double &z, const double &t);

	template <typename T> four_vector(const T &vec) {

		// clang-format off
		static_assert(
            std::is_same_v<typename T::value_type, double> || 
            std::is_same_v<typename T::value_type, float>,
			"Input type must be std::array or std::vector of double or float."
        );
		// clang-format on

		if (vec.size() != 4) {
			throw std::invalid_argument("Input array or vector must have 4 elements.");
		}

		this->p1 = static_cast<double>(vec[0]);
		this->p2 = static_cast<double>(vec[1]);
		this->p3 = static_cast<double>(vec[2]);
		this->p0 = static_cast<double>(vec[3]);
	}
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

	void set_px(const double &v) { this->p1 = v; }
	void set_py(const double &v) { this->p2 = v; }
	void set_pz(const double &v) { this->p3 = v; }
	void set_e(const double &v) { this->p0 = v; }

	double Px() const { return this->p1; }
	double Py() const { return this->p2; }
	double Pz() const { return this->p3; }
	double E() const { return this->p0; }

	double x() const { return this->p1; }
	double y() const { return this->p2; }
	double z() const { return this->p3; }
	double t() const { return this->p0; }

	double Pt() const;
	double Mag() const;
	double M() const;
	double M2() const;

	double beta_x() const { return -this->p1 / this->p0; }
	double beta_y() const { return -this->p2 / this->p0; }
	double beta_z() const { return -this->p3 / this->p0; }
	double gamma() const { return this->p0 / this->M(); }

	bool spacelike() const { return this->M() < 0; }
	bool timelike() const { return this->M() > 0; }
	bool lightlike() const { return this->M() == 0; }

private:
	double p0, p1, p2, p3;
};

bool operator==(const four_vector &first, const four_vector &second);
bool operator!=(const four_vector &first, const four_vector &second);
physics::four_vector relative_four_vector(const physics::four_vector &first, const physics::four_vector &second);
/**
 * @brief Return the x-component of the relative 3-vector given two four-vectors.
 */
double get_qx(const four_vector &first, const four_vector &second);
/**
 * @brief Return the y-component of the relative 3-vector given two four-vectors.
 */
double get_qy(const four_vector &first, const four_vector &second);
/**
 * @brief Return the z-component of the relative 3-vector given two four-vectors.
 */
double get_qz(const four_vector &first, const four_vector &second);

// first boost to the frame where the pair Pz = 0 (longitudinal pair rest frame)
// then rotate the transverse plane with an angle \cos\theta = Px / Pt

/**
 * @brief Return the out-component of the relative 3-vector given two four-vectors.
 * @details The vector is defined in the Bertsch-Pratt coordinate system. The relative 4-vector `q`
 * is first boosted to LCMS frame where the pair `Pz = 0`, then rotated the transverse plane with an
 * angle `\cos\theta = Px / Pt`.
 */
double get_qout(const four_vector &first, const four_vector &second);
/**
 * @brief Return the side-component of the relative 3-vector given two four-vectors.
 * @details See `get_qout` for details.
 */
double get_qside(const four_vector &first, const four_vector &second);
/**
 * @brief Return the long-component of the relative 3-vector given two four-vectors.
 * @details See `get_qout` for details.
 */
double get_qlong(const four_vector &first, const four_vector &second);

/**
 * @brief Return the invariant mass of the pair given two four-vectors.
 */
double get_minv(const four_vector &first, const four_vector &second);
/**
 * @brief Return the invariant mass of the relative 4-vector.
 */
double get_qinv(const four_vector &first, const four_vector &second);

}; // namespace physics
#endif