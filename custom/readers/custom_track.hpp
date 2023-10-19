#ifndef custom_track_hpp
#define custom_track_hpp

#include "track.hpp"
#include <climits>
class custom_track : public track {
public:
	custom_track();
	custom_track(const unsigned int &N, const unsigned int &Z, const double &vx, const double &vy,
				 const double &vz, const double &mass, const double &x = 0., const double &y = 0.,
				 const double &z = 0., const double &t = 0., const double &eff = 0.);

	custom_track(const unsigned int &N, const unsigned int &Z, const double &mass,
				 const std::array<double, 3> &v, const std::array<double, 4> &x = {0., 0., 0., 0.},
				 const double &eff = 0.);

	custom_track(const custom_track &);
	~custom_track();

	void set_efficiency(const double &eff) { this->efficiency = eff; }
	double get_efficiency() const { return this->efficiency; }

private:
	double efficiency;
};

#endif