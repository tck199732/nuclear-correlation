#include "Cuts/CustomTrackMonitor.hpp"

CustomTrackCutMonitor::CustomTrackCutMonitor(const std::string &name) : name(name) {
	this->h1_transverse_velocity = new TH1D((this->name + "_h1_transverse_velocity").c_str(), "", 30, 0, 600);
	this->h1_transverse_velocity->Sumw2();
	this->h1_transverse_velocity->SetDirectory(0);

	h2_kinergy_theta = new TH2D((this->name + "_h2_kinergy_theta").c_str(), "", 50, 0, 150, 80, 40, 100);
	h2_kinergy_theta->Sumw2();
	h2_kinergy_theta->SetDirectory(0);
}

CustomTrackCutMonitor::~CustomTrackCutMonitor() {
	delete h1_transverse_velocity;
	delete h2_kinergy_theta;
}

void CustomTrackCutMonitor::Fill(const HbtTrack *trk) {
	auto A = trk->GetNeutron() + trk->GetProton();
	auto px_ = trk->GetPxPerNucleon();
	auto py_ = trk->GetPyPerNucleon();
	auto pz_ = trk->GetPzPerNucleon();
	auto pT_ = std::sqrt(px_ * px_ + py_ * py_);

	auto mass = trk->GetMass();
	auto energy = trk->GetE();
	auto kinergy = (energy - mass) / A;
	double theta_lab = std::atan2(pT_, pz_) * TMath::RadToDeg();
	this->h1_transverse_velocity->Fill(pT_);
	this->h2_kinergy_theta->Fill(kinergy, theta_lab);
	return;
}

void CustomTrackCutMonitor::Write() {
	this->h1_transverse_velocity->Write();
	this->h2_kinergy_theta->Write();
}
