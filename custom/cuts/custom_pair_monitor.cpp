#include "cuts/custom_pair_monitor.hpp"

custom_pair_monitor::custom_pair_monitor(const std::string &name) : name(name) {
	this->h1_kT = new TH1D((this->name + "_h1_kT").c_str(), "", 50, 0, 1000);
	this->h1_kT->Sumw2();
	this->h1_kT->SetDirectory(0);
}

custom_pair_monitor::~custom_pair_monitor() { delete h1_kT; }

void custom_pair_monitor::fill(const pair *pr) {
	auto first = pr->get_first_particle()->get_track();
	auto second = pr->get_second_particle()->get_track();
	double vx = first->get_vx() + second->get_vx();
	double vy = first->get_vy() + second->get_vy();
	this->h1_kT->Fill(std::sqrt(vx * vx + vy * vy));
}

void custom_pair_monitor::write() { this->h1_kT->Write(); }
