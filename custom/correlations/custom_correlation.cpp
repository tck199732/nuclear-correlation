#include "custom_correlation.hpp"
custom_correlation::custom_correlation(const std::string &name)
	: name(name), numerator(nullptr), denominator(nullptr) {}

custom_correlation::custom_correlation(const std::string &name, const int &bins, const double &vmin,
									   const double &vmax)
	: name(name) {

	this->numerator = new TH1D("num", "", bins, vmin, vmax);
	this->denominator = new TH1D("den", "", bins, vmin, vmax);
	this->numerator->Sumw2();
	this->denominator->Sumw2();
	this->numerator->SetDirectory(0);
	this->denominator->SetDirectory(0);
}
custom_correlation::custom_correlation(const custom_correlation &other) {
	this->name = other.name;
	this->numerator = (TH1D *)other.numerator->Clone((other.name + "_num").c_str());
	this->denominator = (TH1D *)other.denominator->Clone((other.name + "_den").c_str());
}

custom_correlation::~custom_correlation() {
	if (this->numerator) {
		delete numerator;
	}
	if (this->denominator) {
		delete denominator;
	}
}

double custom_correlation::calculate_relative_momentum(const pair *pr) {
	auto first = pr->get_first_particle();
	auto second = pr->get_second_particle();

	auto px1 = first->get_px(), px2 = second->get_px();
	auto py1 = first->get_py(), py2 = second->get_py();
	auto pz1 = first->get_pz(), pz2 = second->get_pz();
	auto e1 = first->get_e(), e2 = second->get_e();

	double qx = physics::get_qx({px1, py1, pz1, e1}, {px2, py2, pz2, e2});
	double qy = physics::get_qy({px1, py1, pz1, e1}, {px2, py2, pz2, e2});
	double qz = physics::get_qz({px1, py1, pz1, e1}, {px2, py2, pz2, e2});
	return std::sqrt(qx * qx + qy * qy + qz * qz);
}

void custom_correlation::add_real_pair(const pair *pr) {
	this->numerator->Fill(this->calculate_relative_momentum(pr), 1.);
	return;
}

void custom_correlation::add_mixed_pair(const pair *pr) {
	this->denominator->Fill(this->calculate_relative_momentum(pr), 1.);
	return;
}
