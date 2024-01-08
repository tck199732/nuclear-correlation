#include "Cuts/CustomEventMonitor.hpp"

CustomEventMonitor::CustomEventMonitor(const std::string &name) : name(name) {
	this->h1_impact_parameter = new TH1D((this->name + "_h1_impact_parameter").c_str(), "", 60., 0., 3.);
	this->h1_impact_parameter->Sumw2();
	this->h1_impact_parameter->SetDirectory(0);
}

CustomEventMonitor::~CustomEventMonitor() { delete h1_impact_parameter; }

void CustomEventMonitor::Fill(const HbtEvent *evt) {
	this->h1_impact_parameter->Fill(evt->GetImpactParameter());
	return;
}

void CustomEventMonitor::Write() {
	this->h1_impact_parameter->Write();
	return;
}
