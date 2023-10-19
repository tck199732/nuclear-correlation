#include "cuts/custom_pair_monitor.hpp"

custom_pair_monitor::custom_pair_monitor(const std::string &name) {
	this->name = name;
	this->h1_transverse_velocity = new TH1D("h1_transverse_velocity", "", 30, 0, 600);
	this->h1_transverse_velocity->Sumw2();
	this->h1_transverse_velocity->SetDirectory(0);
}

custom_pair_monitor::~custom_pair_monitor() { delete h1_transverse_velocity; }

void custom_pair_monitor::fill(const pair *pr) {
	auto first = pr->get_first_particle()->get_track();
	auto second = pr->get_second_particle()->get_track();
	double vx = first->get_vx() + second->get_vx();
	double vy = first->get_vy() + second->get_vy();
	this->h1_transverse_velocity->Fill(std::sqrt(vx * vx + vy * vy));
}

void custom_pair_monitor::write() { this->h1_transverse_velocity->Write(); }
