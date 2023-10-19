#include "custom_event.hpp"

custom_event::custom_event() : event() {
	this->trigger_condition = "";
	this->trigger = -DBL_MAX;
}

custom_event::custom_event(const custom_event &ev) : event(ev) {
	this->trigger_condition = ev.trigger_condition;
	this->trigger = ev.trigger;
}

custom_event::~custom_event() {}