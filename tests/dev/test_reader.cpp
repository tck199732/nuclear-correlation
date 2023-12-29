#include "event.hpp"
#include "reader.hpp"
#include <doctest/doctest.h>
#include <memory>

class derived_reader : public reader {
public:
	derived_reader() {}
	~derived_reader() {}
	event *return_event() { return new event(); }
};

TEST_CASE("reader default constructor") {
	auto rdr = std::make_unique<derived_reader>();
	CHECK(rdr->get_status() == 0);
}

TEST_CASE("read event") {
	auto rdr = std::make_unique<derived_reader>();
	auto evt = rdr->return_event();
	CHECK(evt != nullptr);
}
