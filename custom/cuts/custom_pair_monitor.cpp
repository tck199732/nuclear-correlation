#include "cuts/custom_pair_monitor.hpp"

custom_pair_monitor::custom_pair_monitor(const std::string &name) : name(name) {
	this->h1_kT = new TH1D((this->name + "_h1_kT").c_str(), "", 50, 0, 1000);
	this->h1_kT->Sumw2();
	this->h1_kT->SetDirectory(0);
}

custom_pair_monitor::~custom_pair_monitor() { delete h1_kT; }

void custom_pair_monitor::fill(const track *first, const track *second) {
	auto eff = first->get_efficiency() * second->get_efficiency();
	double px_ = first->get_px_per_nucleon() + second->get_px_per_nucleon();
	double py_ = first->get_py_per_nucleon() + second->get_py_per_nucleon();
	this->h1_kT->Fill(std::sqrt(px_ * px_ + py_ * py_), 1. / eff);
}

void custom_pair_monitor::write() {
	this->h1_kT->Write();
	return;
}
