#include "custom_track.hpp"

custom_track::custom_track() : track()
{
    this->detector_index = INT_MAX;
    this->efficiency = 1.;
}

custom_track::custom_track(
    const unsigned int &N, const unsigned int &Z,
    const double &vx, const double &vy, const double &vz, const double &mass,
    const double &x, const double &y, const double &z, const double &t,
    const int &index, const double &eff
    //
    ) : track(N, Z, vx, vy, vz, mass, x, y, z, t)
{
    this->detector_index = index;
    this->efficiency = eff;
}

custom_track::custom_track(
    const unsigned int &N, const unsigned int &Z,
    const double &mass, 
    const std::array<double, 3> &v,
    const std::array<double, 4> &x,
    const int &index, const double &eff
    //
    ) : track(N, Z, mass, v, x)
{
    this->detector_index = index;
    this->efficiency = eff;
}

custom_track::custom_track(const custom_track & ctrk) : track(ctrk) {
    this->detector_index = ctrk.detector_index;
    this->efficiency = ctrk.efficiency;
}
