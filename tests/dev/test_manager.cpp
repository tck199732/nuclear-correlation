#include "HbtManager.hpp"
#include <doctest/doctest.h>

class derived_reader : public HbtReader {
public:
	derived_reader() {}
	~derived_reader() {}
	HbtEvent *ReturnHbtEvent() { return new HbtEvent(); }
};

class mock_analysis : public HbtAnalysis {
public:
	mock_analysis() : HbtAnalysis() {}
	~mock_analysis() {}
	void Process(HbtEvent *evt) {}
};

TEST_CASE("check HbtManager constructor") {
	// create a HbtManager object
	HbtManager mgr;
	// check that the HbtEvent HbtReader and HbtAnalysis HbtCollection are initialized
	CHECK(mgr.get_reader() == nullptr);
	CHECK(mgr.get_analyses() != nullptr);
	CHECK(mgr.get_analyses()->size() == 0);
}

TEST_CASE("check SetReader method") {
	// create a HbtManager object
	HbtManager mgr;
	// create a HbtReader object
	auto event_reader = new derived_reader();
	// set the HbtReader object in the HbtManager
	mgr.SetReader(event_reader);
	// check that the HbtReader object is set correctly
	CHECK(mgr.get_reader() == event_reader);
}

TEST_CASE("check AddAnalysis method") {
	// create a HbtManager object
	HbtManager mgr;
	// create an HbtAnalysis object
	auto anal = new HbtAnalysis();
	// add the HbtAnalysis object to the HbtManager
	mgr.AddAnalysis(anal);
	// check that the HbtAnalysis object is added correctly
	CHECK(mgr.get_analyses()->size() == 1);
	CHECK(mgr.get_analyses()->at(0) == anal);
}

TEST_CASE("check Process method") {
	// create a HbtManager object
	HbtManager mgr;
	// create a HbtReader object
	auto event_reader = new derived_reader();
	// set the HbtReader object in the HbtManager
	mgr.SetReader(event_reader);
	// create an HbtAnalysis object
	auto anal = new mock_analysis();
	// add the HbtAnalysis object to the HbtManager
	mgr.add_analysis(anal);
	// call the Process method
	int result = mgr.Process();
	// check that the Process method returns 0
	CHECK(result == 0);
}