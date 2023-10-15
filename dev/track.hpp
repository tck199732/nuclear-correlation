#ifndef track_hpp
#define track_hpp

#include <array>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

class track
{
public:
    track() { ; }
    track(const unsigned int &N, const unsigned int &Z, const double &vx, const double &vy, const double &vz, const double &mass, const double &x=0., const double &y=0., const double &z=0., const double &t=0.);

    track(const unsigned int &N, const unsigned int &Z, const double &mass, const std::array<double, 3> &v, const std::array<double, 4> &x={0., 0., 0., 0.});
    track(const track &);
    virtual ~track();

    unsigned int get_neutron() const { return this->N; }
    unsigned int get_proton() const { return this->Z; }
    double get_mass() const { return this->mass; }
    double get_vx() const { return this->vx; }
    double get_vy() const { return this->vy; }
    double get_vz() const { return this->vz; }
    double get_x() const { return this->x; }
    double get_y() const { return this->y; }
    double get_z() const { return this->z; }
    double get_t() const { return this->t; }

    void set_neutron(const unsigned int &n) { this->N = n; }
    void set_proton(const unsigned int &z) { this->Z = z; }
    void set_mass(const double &mass) { this->mass = mass; }
    void set_vx(const double &vx) { this->vx = vx; }
    void set_vy(const double &vy) { this->vy = vy; }
    void set_vz(const double &vz) { this->vz = vz; }
    void set_x(const double &x) { this->x = x; }
    void set_y(const double &y) { this->y = y; }
    void set_z(const double &z) { this->z = z; }
    void set_t(const double &t) { this->t = t; }

    void set_uint_property(const std::string &key, const unsigned int &value) { this->uint_properties[key] = value; }
    void set_dbl_property(const std::string &key, const double &value) { this->dbl_properties[key] = value; }
    unsigned int get_uint_property(const std::string &key) const;
    double get_dbl_property(const std::string &key) const;
    std::vector<std::string> get_uint_property_keys() const;
    std::vector<std::string> get_dbl_property_keys() const;

private:
    unsigned int N, Z;
    double mass;
    double vx, vy, vz;
    double x, y, z, t;
    std::map<std::string, unsigned int> uint_properties;
    std::map<std::string, double> dbl_properties;

};

#endif