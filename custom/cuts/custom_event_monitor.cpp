#include "cuts/custom_event_monitor.hpp"

custom_event_monitor::custom_event_monitor(const std::string &name) {
	this->name = name;
	this->h1_multiplicity = new TH1D("h1_multiplicity", "", 20, -0.5, 19.5);
	this->h1_impact_parameter = new TH1D("h1_impact_parameter", "", 100., 0., 1.);
	this->h1_multiplicity->Sumw2();
	this->h1_impact_parameter->Sumw2();
	this->h1_multiplicity->SetDirectory(0);
	this->h1_impact_parameter->SetDirectory(0);
}

custom_event_monitor::~custom_event_monitor() {
	delete h1_multiplicity;
	delete h1_impact_parameter;
}

void custom_event_monitor::fill(const event *evt) {
	this->h1_multiplicity->Fill(evt->get_multiplicity());
	this->h1_impact_parameter->Fill(evt->get_impact_parameter());
}

void custom_event_monitor::write() {
	this->h1_multiplicity->Write();
	this->h1_impact_parameter->Write();
}
