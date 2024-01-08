#include "HbtEvent.hpp"
#include "HbtReader.hpp"
#include <doctest/doctest.h>
#include <memory>

class derived_reader : public HbtReader {
public:
	derived_reader() {}
	~derived_reader() {}
	HbtEvent *ReturnHbtEvent() { return new HbtEvent(); }
};

TEST_CASE("HbtReader default constructor") {
	auto rdr = std::make_unique<derived_reader>();
	CHECK(rdr->GetStatus() == 0);
}

TEST_CASE("read HbtEvent") {
	auto rdr = std::make_unique<derived_reader>();
	auto evt = rdr->ReturnHbtEvent();
	CHECK(evt != nullptr);
}
