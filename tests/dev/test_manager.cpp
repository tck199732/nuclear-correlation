#include "manager.hpp"
#include <doctest/doctest.h>

class derived_reader : public reader {
public:
	derived_reader() {}
	~derived_reader() {}
	event *return_event() { return new event(); }
};

class mock_analysis : public analysis {
public:
	mock_analysis() : analysis() {}
	~mock_analysis() {}
	void process(event *evt) {}
};

TEST_CASE("check manager constructor") {
	// create a manager object
	manager mgr;
	// check that the event reader and analysis collection are initialized
	CHECK(mgr.get_reader() == nullptr);
	CHECK(mgr.get_analyses() != nullptr);
	CHECK(mgr.get_analyses()->size() == 0);
}

TEST_CASE("check set_reader method") {
	// create a manager object
	manager mgr;
	// create a reader object
	auto event_reader = new derived_reader();
	// set the reader object in the manager
	mgr.set_reader(event_reader);
	// check that the reader object is set correctly
	CHECK(mgr.get_reader() == event_reader);
}

TEST_CASE("check add_analysis method") {
	// create a manager object
	manager mgr;
	// create an analysis object
	auto anal = new analysis();
	// add the analysis object to the manager
	mgr.add_analysis(anal);
	// check that the analysis object is added correctly
	CHECK(mgr.get_analyses()->size() == 1);
	CHECK(mgr.get_analyses()->at(0) == anal);
}

TEST_CASE("check process method") {
	// create a manager object
	manager mgr;
	// create a reader object
	auto event_reader = new derived_reader();
	// set the reader object in the manager
	mgr.set_reader(event_reader);
	// create an analysis object
	auto anal = new mock_analysis();
	// add the analysis object to the manager
	mgr.add_analysis(anal);
	// call the process method
	int result = mgr.process();
	// check that the process method returns 0
	CHECK(result == 0);
}