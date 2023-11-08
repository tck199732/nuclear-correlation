#include <ame/ame.hpp>
#include <doctest/doctest.h>

TEST_CASE("singleton-test") {
	for (int _ = 0; _ < 100; _++) {
		ame::get_instance();
	}
	CHECK(ame::get_instance()->get_number_of_instances() == 1);
}

TEST_CASE("get-mass-of-existing-element") {
	// ni64 36 28 60480.01762332152
	CHECK(ame::get_instance()->get_mass("ni64") == 60480.01762332152);
	CHECK(ame::get_instance()->get_mass("Ni64") == 60480.01762332152);
	CHECK(ame::get_instance()->get_mass("NI64") == 60480.01762332152);
	CHECK(ame::get_instance()->get_mass("ni64") == 60480.01762332152);
}

TEST_CASE("get-mass-of-non-existing-element") {
	const double mN = 938.918;
	// uranium is a valid element but it can't hold 999 nucleons
	CHECK(ame::get_instance()->get_mass("u999") == std::nullopt);
	// u244 is not found in ame table, but A is less than the maximum allowed.
	// thus handled as unphysical maas
	CHECK(ame::get_instance()->get_mass("u244") == mN * 244);
	// get unphysical u244 mass from N, Z
	CHECK(ame::get_instance()->get_mass(152, 92) == mN * 244);
}

TEST_CASE("get-neutron-proton-numbers-of-existing-element") {
	CHECK(ame::get_instance()->get_neutron_number("ni64") == 36);
	CHECK(ame::get_instance()->get_neutron_number("Ni64") == 36);
	CHECK(ame::get_instance()->get_neutron_number("NI64") == 36);
	CHECK(ame::get_instance()->get_neutron_number("ni64") == 36);

	CHECK(ame::get_instance()->get_proton_number("ni64") == 28);
	CHECK(ame::get_instance()->get_proton_number("Ni64") == 28);
	CHECK(ame::get_instance()->get_proton_number("NI64") == 28);
	CHECK(ame::get_instance()->get_proton_number("ni64") == 28);

	CHECK(ame::get_instance()->get_neutron_proton_number("n") ==
		  ame::get_instance()->get_neutron_proton_number("n1"));
	CHECK(ame::get_instance()->get_neutron_proton_number("p") ==
		  ame::get_instance()->get_neutron_proton_number("h1"));
	CHECK(ame::get_instance()->get_neutron_proton_number("d") ==
		  ame::get_instance()->get_neutron_proton_number("h2"));
	CHECK(ame::get_instance()->get_neutron_proton_number("t") ==
		  ame::get_instance()->get_neutron_proton_number("h3"));
	CHECK(ame::get_instance()->get_neutron_proton_number("3He") ==
		  ame::get_instance()->get_neutron_proton_number("he3"));
	CHECK(ame::get_instance()->get_neutron_proton_number("4He") ==
		  ame::get_instance()->get_neutron_proton_number("he4"));
	CHECK(ame::get_instance()->get_neutron_proton_number("alpha") ==
		  ame::get_instance()->get_neutron_proton_number("he4"));

	CHECK(ame::get_instance()->get_neutron_proton_number("ALPHA") == std::nullopt);
}

TEST_CASE("get-symbol-from-alias") {
	CHECK(ame::get_instance()->get_symbol("n") == "n1");
	CHECK(ame::get_instance()->get_symbol("p") == "h1");
	CHECK(ame::get_instance()->get_symbol("d") == "h2");
	CHECK(ame::get_instance()->get_symbol("t") == "h3");
	CHECK(ame::get_instance()->get_symbol("3He") == "he3");
	CHECK(ame::get_instance()->get_symbol("4He") == "he4");
	CHECK(ame::get_instance()->get_symbol("alpha") == "he4");
	CHECK(ame::get_instance()->get_symbol("ALPHA") == std::nullopt);
}

TEST_CASE("get-symbol-from-NZ") {
	CHECK(ame::get_instance()->get_symbol(0, 1) == "h1");
	CHECK(ame::get_instance()->get_symbol(1, 1) == "h2");
	CHECK(ame::get_instance()->get_symbol(2, 1) == "h3");
	CHECK(ame::get_instance()->get_symbol(1, 2) == "he3");
	CHECK(ame::get_instance()->get_symbol(2, 2) == "he4");
	CHECK(ame::get_instance()->get_symbol(0, 0) == std::nullopt);
}

TEST_CASE("get-maximum-A") { CHECK(ame::get_instance()->get_maximum_mass_number() == 295); }

TEST_CASE("get-mass-from-alias") {
	CHECK(ame::get_instance()->get_mass("n") == ame::get_instance()->get_mass("n1"));
	CHECK(ame::get_instance()->get_mass("p") == ame::get_instance()->get_mass("h1"));
	CHECK(ame::get_instance()->get_mass("d") == ame::get_instance()->get_mass("h2"));
	CHECK(ame::get_instance()->get_mass("t") == ame::get_instance()->get_mass("h3"));
	CHECK(ame::get_instance()->get_mass("3He") == ame::get_instance()->get_mass("he3"));
	CHECK(ame::get_instance()->get_mass("4He") == ame::get_instance()->get_mass("he4"));
	CHECK(ame::get_instance()->get_mass("alpha") == ame::get_instance()->get_mass("he4"));
	CHECK(ame::get_instance()->get_mass("ALPHA") == std::nullopt);
}

TEST_CASE("get-mass-from-NZ") {
	CHECK(ame::get_instance()->get_mass(1, 0) == ame::get_instance()->get_mass("n1"));
	CHECK(ame::get_instance()->get_mass(0, 1) == ame::get_instance()->get_mass("h1"));
	CHECK(ame::get_instance()->get_mass(1, 1) == ame::get_instance()->get_mass("h2"));
	CHECK(ame::get_instance()->get_mass(2, 1) == ame::get_instance()->get_mass("h3"));
	CHECK(ame::get_instance()->get_mass(1, 2) == ame::get_instance()->get_mass("he3"));
	CHECK(ame::get_instance()->get_mass(2, 2) == ame::get_instance()->get_mass("he4"));
	CHECK(ame::get_instance()->get_mass(-1, -1) == std::nullopt);
}
