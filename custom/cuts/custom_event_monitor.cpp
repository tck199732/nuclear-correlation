#include "cuts/custom_event_monitor.hpp"

custom_event_monitor::custom_event_monitor(const std::string &name) : name(name) {
	this->h1_impact_parameter = new TH1D((this->name + "_h1_impact_parameter").c_str(), "", 60., 0., 3.);
	this->h1_impact_parameter->Sumw2();
	this->h1_impact_parameter->SetDirectory(0);
}

custom_event_monitor::~custom_event_monitor() { delete h1_impact_parameter; }

void custom_event_monitor::fill(const event *evt) {
	this->h1_impact_parameter->Fill(evt->get_impact_parameter());
	return;
}

void custom_event_monitor::write() {
	this->h1_impact_parameter->Write();
	return;
}
