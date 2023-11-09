#include "event.hpp"
#include <doctest/doctest.h>
#include <memory>

TEST_CASE("event copy constructor") {
	// Create an event object to copy
	auto original_event = std::make_shared<event>();
	original_event->set_multiplicity(100);
	original_event->set_impact_parameter(1.0);

	CHECK(original_event->get_multiplicity() == 100);
	CHECK(original_event->get_impact_parameter() == 1.0);

	// Create a copy of the event object
	auto copied_event = std::make_shared<event>(*original_event);
}