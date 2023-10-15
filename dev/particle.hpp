#ifndef particle_hpp
#define particle_hpp

#include <array>
#include <cmath>
#include "track.hpp"
class particle
{
public:
    particle(
        const unsigned& N, const unsigned& Z,
        const double& px, const double& py, const double& pz, const double& E,
        const double& x, const double& y, const double& z, const double& t
    );
    particle(const track* trk);
    particle(const particle &ptcl);
    ~particle();

    unsigned int get_N() const { return N; }
    unsigned int get_Z() const { return Z; }
    double get_px() const { return px; }
    double get_py() const { return py; }
    double get_pz() const { return pz; }
    double get_e() const { return E; }
    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_z() const { return z; }
    double get_t() const { return t; }
    track* get_track() const { return trk; }

private:
    track* trk;
    unsigned int N, Z;
    double px, py, pz, E;
    double x, y, z, t;
};

#endif