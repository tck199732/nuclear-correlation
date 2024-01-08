#include "Cuts/CustomPairMonitor.hpp"

CustomPairMonitor::CustomPairMonitor(const std::string &name) : name(name) {
	this->h1_kT = new TH1D((this->name + "_h1_kT").c_str(), "", 50, 0, 1000);
	this->h1_kT->Sumw2();
	this->h1_kT->SetDirectory(0);
}

CustomPairMonitor::~CustomPairMonitor() { delete h1_kT; }

void CustomPairMonitor::Fill(const HbtTrack *track1, const HbtTrack *track2) {
	auto eff = track1->GetEfficiency() * track2->GetEfficiency();
	double px_ = track1->GetPxPerNucleon() + track2->GetPxPerNucleon();
	double py_ = track1->GetPyPerNucleon() + track2->GetPyPerNucleon();
	this->h1_kT->Fill(std::sqrt(px_ * px_ + py_ * py_), 1. / eff);
}

void CustomPairMonitor::Write() {
	this->h1_kT->Write();
	return;
}
