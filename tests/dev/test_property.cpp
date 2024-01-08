#include "HbtProperty.hpp"
#include <array>
#include <doctest/doctest.h>
#include <memory>
#include <vector>

TEST_CASE("check setters and getters for normal types") {
	HbtProperty prop;
	prop.SetProperty("unsigned integer", 1u);
	prop.SetProperty("integer", 1);
	prop.SetProperty("double", 1.0);
	prop.SetProperty("long", 1L);
	prop.SetProperty("bool", true);
	prop.SetProperty("string", static_cast<std::string>("hello world"));
	prop.SetProperty("const char*", "hello world");
	prop.SetProperty("vector", std::vector<int>{0, 0, 0});
	prop.SetProperty("array", std::array<int, 3>{0, 0, 0});

	CHECK(prop.GetProperty<unsigned int>("unsigned integer") == 1);
	CHECK(prop.GetProperty<int>("integer") == 1);
	CHECK(prop.GetProperty<double>("double") == 1.0);
	CHECK(prop.GetProperty<long>("long") == 1L);
	CHECK(prop.GetProperty<bool>("bool") == true);
	CHECK(prop.GetProperty<std::string>("string") == static_cast<std::string>("hello world"));
	CHECK(prop.GetProperty<const char *>("const char*") == "hello world");
	CHECK(prop.GetProperty<std::vector<int>>("vector") == std::vector<int>{0, 0, 0});
	CHECK(prop.GetProperty<std::array<int, 3>>("array") == std::array<int, 3>{0, 0, 0});

	CHECK_THROWS_AS(prop.GetProperty<int>("double"), std::invalid_argument);
	CHECK_THROWS_AS(prop.GetProperty<int>("not exist"), std::out_of_range);
}

TEST_CASE("check setters and getters for pointers") {
	HbtProperty prop;
	auto ptr = new int(1);
	auto unique_ptr = std::make_unique<int>(1);
	auto shared_ptr = std::make_shared<int>(1);
	prop.SetProperty("int*", ptr);
	prop.SetProperty("shared_ptr<int>", shared_ptr);

	CHECK(prop.GetProperty<int *>("int*") == ptr);
	CHECK(prop.GetProperty<std::shared_ptr<int>>("shared_ptr<int>") == shared_ptr);
	delete ptr;
}

TEST_CASE("check copy constructor") {
	HbtProperty prop;
	// check usual types
	prop.SetProperty("unsigned integer", 1u);
	prop.SetProperty("integer", 1);
	prop.SetProperty("double", 1.0);
	prop.SetProperty("long", 1L);
	prop.SetProperty("bool", true);
	prop.SetProperty("string", static_cast<std::string>("hello world"));
	prop.SetProperty("const char*", "hello world");
	prop.SetProperty("vector", std::vector<int>{0, 0, 0});
	prop.SetProperty("array", std::array<int, 3>{0, 0, 0});

	// check pointer types
	auto ptr = new int(1);
	auto shared_ptr = std::make_shared<int>(1);
	prop.SetProperty("int*", ptr);
	prop.SetProperty("shared_ptr<int>", shared_ptr);

	HbtProperty prop_copy(prop);
	// check the values
	CHECK(prop_copy.GetProperty<unsigned int>("unsigned integer") == 1);
	CHECK(prop_copy.GetProperty<int>("integer") == 1);
	CHECK(prop_copy.GetProperty<double>("double") == 1.0);
	CHECK(prop_copy.GetProperty<long>("long") == 1L);
	CHECK(prop_copy.GetProperty<bool>("bool") == true);
	CHECK(prop_copy.GetProperty<std::string>("string") == static_cast<std::string>("hello world"));
	CHECK(prop_copy.GetProperty<const char *>("const char*") == "hello world");
	CHECK(prop_copy.GetProperty<std::vector<int>>("vector") == std::vector<int>{0, 0, 0});
	CHECK(prop_copy.GetProperty<std::array<int, 3>>("array") == std::array<int, 3>{0, 0, 0});

	// check the pointers
	CHECK(prop_copy.GetProperty<int *>("int*") == ptr);
	CHECK(prop_copy.GetProperty<std::shared_ptr<int>>("shared_ptr<int>") == shared_ptr);
	delete ptr;
}

TEST_CASE("check destructor") {
	HbtProperty *prop = new HbtProperty();
	auto ptr = new int(1);
	auto shared_ptr = std::make_shared<int>(1);
	prop->SetProperty("int*", ptr);
	prop->SetProperty("shared_ptr<int>", shared_ptr);
	delete prop;

	// check the pointers
	CHECK(*ptr == 1);
	CHECK(*shared_ptr == 1);
	delete ptr;
}