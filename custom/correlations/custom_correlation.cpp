#include "custom_correlation.hpp"
custom_correlation::custom_correlation(const std::string &name) :
	name(name),
	numerator(nullptr),
	denominator(nullptr) {}

custom_correlation::custom_correlation(
	const std::string &name, const int &bins, const double &vmin, const double &vmax
) :
	name(name) {

	this->numerator = new TH1D((this->name + "_num").c_str(), "", bins, vmin, vmax);
	this->denominator = new TH1D((this->name + "_den").c_str(), "", bins, vmin, vmax);
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

double custom_correlation::calculate_relative_momentum(const std::pair<track *, track *> &pr) {
	auto [ptcl1, ptcl2] = pr;
	auto px1 = ptcl1->get_px(), px2 = ptcl2->get_px();
	auto py1 = ptcl1->get_py(), py2 = ptcl2->get_py();
	auto pz1 = ptcl1->get_pz(), pz2 = ptcl2->get_pz();
	auto e1 = ptcl1->get_E(), e2 = ptcl2->get_E();

	auto p1 = physics::four_vector(px1, py1, pz1, e1);
	auto p2 = physics::four_vector(px2, py2, pz2, e2);

	auto P = p1 + p2;
	auto q = physics::relative_four_vector(p1, p2);
	q.boost(P.beta_x(), P.beta_y(), P.beta_z());
	return q.Mag();
}

void custom_correlation::add_real_pair(const std::pair<track *, track *> &pr) {
	this->numerator->Fill(this->calculate_relative_momentum(pr), 1.);
	return;
}

void custom_correlation::add_mixed_pair(const std::pair<track *, track *> &pr) {
	this->denominator->Fill(this->calculate_relative_momentum(pr), 1.);
	return;
}
