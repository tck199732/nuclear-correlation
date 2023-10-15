#ifndef custom_correlation_hpp
#define custom_correlation_hpp

#include <string>
#include <stdexcept>
#include "TH1D.h"

#include "correlation.hpp"
#include "pair.hpp"

class custom_correlation : public correlation
{
public:
    custom_correlation();
    custom_correlation(const int &bins, const double &vmin, const double &vmax);
    custom_correlation(const correlation &other);
    ~custom_correlation();

    virtual void add_real_pair(const pair *) ;
    virtual void add_mixed_pair(const pair *) ;

    TH1D *get_numerator(){ return numerator; }
    TH1D *get_denominator(){ return denominator; }

    void set_numerator(const std::string& name, const std::string& title, const int& bins, const double& vmin, const double& vmax);
    void set_denominator(const std::string& name, const std::string& title, const int& bins, const double& vmin, const double& vmax);
    void Write();

private:
    TH1D *numerator;
    TH1D *denominator;
};

#endif
