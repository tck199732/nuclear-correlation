#include "cuts/custom_track_monitor.hpp"

custom_track_monitor::custom_track_monitor(const std::string &name) : name(name) {
	this->h1_transverse_velocity = new TH1D((this->name + "_h1_transverse_velocity").c_str(), "", 30, 0, 600);
	this->h1_transverse_velocity->Sumw2();
	this->h1_transverse_velocity->SetDirectory(0);

	h2_kinergy_theta = new TH2D((this->name + "_h2_kinergy_theta").c_str(), "", 50, 0, 150, 80, 40, 100);
	h2_kinergy_theta->Sumw2();
	h2_kinergy_theta->SetDirectory(0);
}

custom_track_monitor::~custom_track_monitor() {
	delete h1_transverse_velocity;
	delete h2_kinergy_theta;
}

void custom_track_monitor::fill(const track *trk) {
	auto A = trk->get_N() + trk->get_Z();
	auto px_ = trk->get_px_per_nucleon();
	auto py_ = trk->get_py_per_nucleon();
	auto pz_ = trk->get_pz_per_nucleon();
	auto pT_ = std::sqrt(px_ * px_ + py_ * py_);

	auto mass = trk->get_mass();
	auto energy = trk->get_E();
	auto kinergy = (energy - mass) / A;
	double theta_lab = std::atan2(pT_, pz_) * TMath::RadToDeg();

	this->h1_transverse_velocity->Fill(pT_);
	this->h2_kinergy_theta->Fill(kinergy, theta_lab);
	return;
}

void custom_track_monitor::write() {
	this->h1_transverse_velocity->Write();
	this->h2_kinergy_theta->Write();
}
