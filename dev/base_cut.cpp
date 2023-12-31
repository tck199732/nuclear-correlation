#include "base_cut.hpp"

base_cut::base_cut() {
	this->passed_monitor = nullptr;
	this->failed_monitor = nullptr;
}

base_cut::base_cut(const base_cut &cut) {
	this->passed_monitor = cut.passed_monitor;
	this->failed_monitor = cut.failed_monitor;
}

base_cut::~base_cut() {
	if (this->passed_monitor != nullptr) {
		delete this->passed_monitor;
	}
	if (this->failed_monitor != nullptr) {
		delete this->failed_monitor;
	}
}

void base_cut::fill_monitor(const event *evt, bool pass) {
	if (pass && this->passed_monitor != nullptr) {
		this->passed_monitor->fill(evt);
	} else if (!pass && this->failed_monitor != nullptr) {
		this->failed_monitor->fill(evt);
	}
}

void base_cut::fill_monitor(const track *trk, bool pass) {
	if (pass && this->passed_monitor != nullptr) {
		this->passed_monitor->fill(trk);
	} else if (!pass && this->failed_monitor != nullptr) {
		this->failed_monitor->fill(trk);
	}
}

void base_cut::fill_monitor(const track *first, const track *second, bool pass) {
	if (pass && this->passed_monitor != nullptr) {
		this->passed_monitor->fill(first, second);
	} else if (!pass && this->failed_monitor != nullptr) {
		this->failed_monitor->fill(first, second);
	}
}
