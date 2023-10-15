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
    auto a1 = first->get_N() + first->get_Z();
    auto a2 = second->get_N() + second->get_Z();

    std::array<double, 4> p1 = {first->get_px(), first->get_py(), first->get_pz(), first->get_e()};
    std::array<double, 4> p2 = {second->get_px(), second->get_py(), second->get_pz(), second->get_e()};
    std::array<double, 4> x1 = {first->get_x(), first->get_y(), first->get_z(), first->get_t()};
    std::array<double, 4> x2 = {second->get_x(), second->get_y(), second->get_z(), second->get_t()};

    for (int idim = 0; idim < 4; idim++)
    {
        p1[idim] /= a1;
        p2[idim] /= a2;
    }
    std::array<double, 3> prel = {p1[0] - p2[0], p1[1] - p2[1], p1[2] - p2[2]};
    double q = std::sqrt(prel[0] * prel[0] + prel[1] * prel[1] + prel[2] * prel[2]);
    this->numerator->Fill(q);
}

void custom_correlation::add_mixed_pair(const pair *pr)
{
    auto first = pr->get_first_particle();
    auto second = pr->get_second_particle();
    auto a1 = first->get_N() + first->get_Z();
    auto a2 = second->get_N() + second->get_Z();

    std::array<double, 4> p1 = {first->get_px(), first->get_py(), first->get_pz(), first->get_e()};
    std::array<double, 4> p2 = {second->get_px(), second->get_py(), second->get_pz(), second->get_e()};
    std::array<double, 4> x1 = {first->get_x(), first->get_y(), first->get_z(), first->get_t()};
    std::array<double, 4> x2 = {second->get_x(), second->get_y(), second->get_z(), second->get_t()};

    for (int idim = 0; idim < 4; idim++)
    {
        p1[idim] /= a1;
        p2[idim] /= a2;
    }
    std::array<double, 3> prel = {p1[0] - p2[0], p1[1] - p2[1], p1[2] - p2[2]};
    double q = std::sqrt(prel[0] * prel[0] + prel[1] * prel[1] + prel[2] * prel[2]);
    this->denominator->Fill(q);
}
