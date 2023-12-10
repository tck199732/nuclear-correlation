#include "cuts/custom_track_monitor.hpp"

custom_track_monitor::custom_track_monitor(const std::string &name) : name(name) {

	this->h1_transverse_velocity =
		new TH1D((this->name + "_h1_transverse_velocity").c_str(), "", 30, 0, 600);
	this->h1_transverse_velocity->Sumw2();
	this->h1_transverse_velocity->SetDirectory(0);

	h2_kinergy_theta =
		new TH2D((this->name + "_h2_kinergy_theta").c_str(), "", 50, 0, 200, 120, 20, 80);
	h2_kinergy_theta->Sumw2();
	h2_kinergy_theta->SetDirectory(0);
}

custom_track_monitor::~custom_track_monitor() {
	delete h1_transverse_velocity;
	delete h2_kinergy_theta;
}

void custom_track_monitor::fill(const track *trk) {
	int a = trk->get_neutron() + trk->get_proton();
	double vx = trk->get_vx(), vy = trk->get_vy(), vz = trk->get_vz();
	double vt = std::sqrt(vx * vx + vy * vy);
	double px = vx * a, py = vy * a, pz = vz * a;
	double mass = trk->get_mass();
	double kinergy = (1. / a) * (std::sqrt(px * px + py * py + pz * pz + mass * mass) - mass);
	double theta_lab = std::atan2(vt, vz) * TMath::RadToDeg();
	this->h1_transverse_velocity->Fill(vt);
	this->h2_kinergy_theta->Fill(kinergy, theta_lab);
	return;
}

void custom_track_monitor::write() {
	this->h1_transverse_velocity->Write();
	this->h2_kinergy_theta->Write();
}
