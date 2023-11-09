#include "event.hpp"
#include "reader.hpp"
#include <doctest/doctest.h>
#include <memory>

class mock_reader : public reader {
public:
	mock_reader(event *evt) : event_ptr(evt) {}
	event *return_event() override { return event_ptr; }

private:
	event *event_ptr;
};

class mock_event : public event {
public:
	mock_event() : event() {}
	mock_event(const mock_event &ev) : event(ev) {}
	~mock_event() override = default;
};

TEST_CASE("check initialization of reader") {
	// create a mock event
	auto evt = std::make_shared<mock_event>();
	// create a mock reader with the event
	auto mreader = std::make_shared<mock_reader>(evt.get());
	// check the reader status is 0
	CHECK(mreader->get_status() == 0);
}