#include "custom_correlation.hpp"
custom_correlation::custom_correlation()
{
    this->numerator = nullptr;
    this->denominator = nullptr;
}

custom_correlation::custom_correlation(const int &bins, const double &vmin, const double &vmax)
{
    this->numerator = new TH1D("num", "", bins, vmin, vmax);
    this->denominator = new TH1D("den", "", bins, vmin, vmax);
    this->numerator->Sumw2();
    this->denominator->Sumw2();
}
custom_correlation::custom_correlation(const correlation &other)
{
    this->numerator = 0;
    this->denominator = 0;
}

custom_correlation::~custom_correlation()
{
    if (this->numerator)
        delete numerator;
    if (this->denominator)
        delete denominator;
}

void custom_correlation::set_numerator(const std::string &name, const std::string &title, const int &bins, const double &vmin, const double &vmax)
{
    if (this->numerator)
    {
        throw std::runtime_error("Numerator already set");
    }
    this->numerator = new TH1D(name.c_str(), title.c_str(), bins, vmin, vmax);
    this->numerator->Sumw2();
}

void custom_correlation::set_denominator(const std::string &name, const std::string &title, const int &bins, const double &vmin, const double &vmax)
{
    if (this->denominator)
    {
        throw std::runtime_error("Denominator already set");
    }
    this->denominator = new TH1D(name.c_str(), title.c_str(), bins, vmin, vmax);
    this->denominator->Sumw2();
}

void custom_correlation::Write()
{
    if (this->numerator)
        this->numerator->Write();
    if (this->denominator)
        this->denominator->Write();
}

void custom_correlation::add_real_pair(const pair *pr)
{
    auto first = pr->get_first_particle();
    auto second = pr->get_second_particle();

    double px1 = first->get_x(), py1 = first->get_y(), pz1 = first->get_z(), e1 = first->get_e();
    double px2 = second->get_x(), py2 = second->get_y(), pz2 = second->get_z(), e2 = second->get_e();
    double mass1 = std::sqrt(e1*e1 - px1*px1 - py1*py1 - pz1*pz1);
    double mass2 = std::sqrt(e2*e2 - px2*px2 - py2*py2 - pz2*pz2);
    
    double px = (mass2 * px1 - mass1 * px2) / (mass1 + mass2);
    double py = (mass2 * py1 - mass1 * py2) / (mass1 + mass2);
    double pz = (mass2 * pz1 - mass1 * pz2) / (mass1 + mass2);
    this->numerator->Fill(std::sqrt(px * px + py * py + pz * pz));
}

void custom_correlation::add_mixed_pair(const pair *pr)
{
    auto first = pr->get_first_particle();
    auto second = pr->get_second_particle();

    double px1 = first->get_x(), py1 = first->get_y(), pz1 = first->get_z(), e1 = first->get_e();
    double px2 = second->get_x(), py2 = second->get_y(), pz2 = second->get_z(), e2 = second->get_e();
    double mass1 = std::sqrt(e1*e1 - px1*px1 - py1*py1 - pz1*pz1);
    double mass2 = std::sqrt(e2*e2 - px2*px2 - py2*py2 - pz2*pz2);
    
    double px = (mass2 * px1 - mass1 * px2) / (mass1 + mass2);
    double py = (mass2 * py1 - mass1 * py2) / (mass1 + mass2);
    double pz = (mass2 * pz1 - mass1 * pz2) / (mass1 + mass2);
    this->denominator->Fill(std::sqrt(px * px + py * py + pz * pz));
}
