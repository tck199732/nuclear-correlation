#ifndef custom_pair_cut_hpp
#define custom_pair_cut_hpp

#include <array>
#include <cfloat>

#include "pair.hpp"
#include "pair_cut.hpp"

class custom_pair_cut : public pair_cut {
public:
	custom_pair_cut();
	custom_pair_cut(const custom_pair_cut &cut);
	virtual bool pass(const pair *pr) override;

	void set_kT_gate(const double &vmin, const double &vmax);
	void set_consider_detector_effect(const bool &v);

	bool get_consider_detector_index() const { return this->is_consider_detector_effect; }
	std::array<double, 2> get_kT_gate() const { return this->kT_gate; }

	long get_npairs_passed() const { return this->npairs_passed; }
	long get_npairs_failed() const { return this->npairs_failed; }

private:
	long npairs_passed, npairs_failed;
	bool is_consider_detector_effect;
	std::array<double, 2> kT_gate;
};

inline void custom_pair_cut::set_kT_gate(const double &vmin, const double &vmax) {
	this->kT_gate = {vmin, vmax};
}

inline void custom_pair_cut::set_consider_detector_effect(const bool &v) {
	this->is_consider_detector_effect = v;
}

#endif
