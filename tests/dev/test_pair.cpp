#include "pair.hpp"
#include "particle.hpp"
#include <doctest/doctest.h>
#include <random>

class mock_particle : public particle {
public:
	mock_particle() : particle() {}
	mock_particle(const mock_particle &ptcl) : particle(ptcl) {}
};

TEST_CASE("check implementation") {
	// check default constructor
	auto original_pair = new pair();
	CHECK(original_pair->get_first_particle() == nullptr);
	CHECK(original_pair->get_second_particle() == nullptr);

	// check setters
	auto *ptcl1 = new mock_particle();
	auto *ptcl2 = new mock_particle();
	original_pair->set_first_particle(ptcl1);
	original_pair->set_second_particle(ptcl2);

	// check copy constructor
	pair copied_pair(*original_pair);
	// check if the copy constructor does not copy the address
	CHECK(copied_pair.get_first_particle() != ptcl1);
	CHECK(copied_pair.get_second_particle() != ptcl2);

	// check destructor
	delete original_pair;
	// check if the destructor does not delete the particles
	CHECK((ptcl1 != nullptr && ptcl2 != nullptr));
}
