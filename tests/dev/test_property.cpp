#include "property.hpp"
#include <array>
#include <doctest/doctest.h>
#include <memory>
#include <vector>

TEST_CASE("check setters and getters for normal types") {
	property prop;
	prop.set_property("unsigned integer", 1u);
	prop.set_property("integer", 1);
	prop.set_property("double", 1.0);
	prop.set_property("long", 1L);
	prop.set_property("bool", true);
	prop.set_property("string", static_cast<std::string>("hello world"));
	prop.set_property("const char*", "hello world");
	prop.set_property("vector", std::vector<int>{0, 0, 0});
	prop.set_property("array", std::array<int, 3>{0, 0, 0});

	CHECK(prop.get_property<unsigned int>("unsigned integer") == 1);
	CHECK(prop.get_property<int>("integer") == 1);
	CHECK(prop.get_property<double>("double") == 1.0);
	CHECK(prop.get_property<long>("long") == 1L);
	CHECK(prop.get_property<bool>("bool") == true);
	CHECK(prop.get_property<std::string>("string") == static_cast<std::string>("hello world"));
	CHECK(prop.get_property<const char *>("const char*") == "hello world");
	CHECK(prop.get_property<std::vector<int>>("vector") == std::vector<int>{0, 0, 0});
	CHECK(prop.get_property<std::array<int, 3>>("array") == std::array<int, 3>{0, 0, 0});

	CHECK_THROWS_AS(prop.get_property<int>("double"), std::invalid_argument);
	CHECK_THROWS_AS(prop.get_property<int>("not exist"), std::out_of_range);
}

TEST_CASE("check setters and getters for pointers") {
	property prop;
	auto ptr = new int(1);
	auto unique_ptr = std::make_unique<int>(1);
	auto shared_ptr = std::make_shared<int>(1);
	prop.set_property("int*", ptr);
	prop.set_property("shared_ptr<int>", shared_ptr);

	CHECK(prop.get_property<int *>("int*") == ptr);
	CHECK(prop.get_property<std::shared_ptr<int>>("shared_ptr<int>") == shared_ptr);
	delete ptr;
}

TEST_CASE("check copy constructor") {
	property prop;
	// check usual types
	prop.set_property("unsigned integer", 1u);
	prop.set_property("integer", 1);
	prop.set_property("double", 1.0);
	prop.set_property("long", 1L);
	prop.set_property("bool", true);
	prop.set_property("string", static_cast<std::string>("hello world"));
	prop.set_property("const char*", "hello world");
	prop.set_property("vector", std::vector<int>{0, 0, 0});
	prop.set_property("array", std::array<int, 3>{0, 0, 0});

	// check pointer types
	auto ptr = new int(1);
	auto shared_ptr = std::make_shared<int>(1);
	prop.set_property("int*", ptr);
	prop.set_property("shared_ptr<int>", shared_ptr);

	property prop_copy(prop);
	// check the values
	CHECK(prop_copy.get_property<unsigned int>("unsigned integer") == 1);
	CHECK(prop_copy.get_property<int>("integer") == 1);
	CHECK(prop_copy.get_property<double>("double") == 1.0);
	CHECK(prop_copy.get_property<long>("long") == 1L);
	CHECK(prop_copy.get_property<bool>("bool") == true);
	CHECK(prop_copy.get_property<std::string>("string") == static_cast<std::string>("hello world"));
	CHECK(prop_copy.get_property<const char *>("const char*") == "hello world");
	CHECK(prop_copy.get_property<std::vector<int>>("vector") == std::vector<int>{0, 0, 0});
	CHECK(prop_copy.get_property<std::array<int, 3>>("array") == std::array<int, 3>{0, 0, 0});

	// check the pointers
	CHECK(prop_copy.get_property<int *>("int*") == ptr);
	CHECK(prop_copy.get_property<std::shared_ptr<int>>("shared_ptr<int>") == shared_ptr);
	delete ptr;
}

TEST_CASE("check destructor") {
	property *prop = new property();
	auto ptr = new int(1);
	auto shared_ptr = std::make_shared<int>(1);
	prop->set_property("int*", ptr);
	prop->set_property("shared_ptr<int>", shared_ptr);
	delete prop;

	// check the pointers
	CHECK(*ptr == 1);
	CHECK(*shared_ptr == 1);
	delete ptr;
}