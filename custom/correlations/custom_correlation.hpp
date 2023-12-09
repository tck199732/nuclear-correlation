#ifndef custom_correlation_hpp
#define custom_correlation_hpp

#include "TH1D.h"
#include "correlation.hpp"
#include "pair.hpp"
#include "physics/physics.hpp"
#include <stdexcept>
#include <string>

class custom_correlation : public correlation {
public:
	custom_correlation(const std::string &name = "");
	custom_correlation(const std::string &name, const int &bins, const double &vmin,
					   const double &vmax);
	custom_correlation(const custom_correlation &other);
	~custom_correlation();

	virtual void add_real_pair(const pair *);
	virtual void add_mixed_pair(const pair *);

	TH1D *get_numerator() const { return numerator; }
	TH1D *get_denominator() const { return denominator; }

private:
	std::string name;
	TH1D *numerator;
	TH1D *denominator;
	double calculate_relative_momentum(const pair *pr);
};

#endif
