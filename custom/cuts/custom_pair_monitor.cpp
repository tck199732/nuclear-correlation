#include "cuts/custom_pair_monitor.hpp"

custom_pair_monitor::custom_pair_monitor(const std::string &name) : name(name) {
	this->h1_kT = new TH1D((this->name + "_h1_kT").c_str(), "", 50, 0, 1000);
	this->h1_kT->Sumw2();
	this->h1_kT->SetDirectory(0);
}

custom_pair_monitor::~custom_pair_monitor() { delete h1_kT; }

void custom_pair_monitor::fill(const std::pair<track *, track *> &pr) {
	auto [ptcl, ptcl2] = pr;
	double px_ = ptcl->get_px_per_nucleon() + ptcl2->get_px_per_nucleon();
	double py_ = ptcl->get_py_per_nucleon() + ptcl2->get_py_per_nucleon();
	this->h1_kT->Fill(std::sqrt(px_ * px_ + py_ * py_));
	return;
}

void custom_pair_monitor::write() {
	this->h1_kT->Write();
	return;
}
