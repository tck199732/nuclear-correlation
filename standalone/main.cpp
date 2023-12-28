#include "main.hpp"

void add_arguments(int argc, char **argv);
argparse::ArgumentParser program("correlation-benchmark", "1.0");

int main(int argc, char *argv[]) {

	add_arguments(argc, argv);

	auto MyManager = new manager();
	auto MyAnalysis = new analysis();

	// clang-format off
	auto MyReader = new custom_reader(
        program.get<std::string>("--tree_name"),
        program.get<std::vector<std::string>>("--input_files")
	);
	// clang-format on

	// initialize cuts classes
	auto EventCut = new custom_event_cut();
	auto cutDeuteron = new custom_track_cut();
	auto cutAlpha = new custom_track_cut();
	auto RealPairCut = new custom_pair_cut();
	auto MixedPairCut = new custom_pair_cut();

	// initialize monitors classes
	auto EventMonitor = new custom_event_monitor("EventMonitor");
	auto monDeuteron = new custom_track_monitor("monDeuteron");
	auto monAlpha = new custom_track_monitor("monAlpha");
	auto RealPairMonitor = new custom_pair_monitor("RealPairMonitor");
	auto RealPairFailMonitor = new custom_pair_monitor("RealPairFailMonitor");
	auto MixedPairMonitor = new custom_pair_monitor("MixedPairMonitor");
	auto MixedPairFailMonitor = new custom_pair_monitor("MixedPairFailMonitor");

	// sampler for correlation as a funciton of relative momentum
	auto MyCorrelation = new custom_correlation("MyCorrelation", 150, 0., 600.);

	EventCut->set_impact_parameter_range(0, 10);
	EventCut->set_multiplicity_range(1, 128);
	EventCut->set_passed_monitor(EventMonitor);

	cutDeuteron->set_accepted_neutron(1);
	cutDeuteron->set_accepted_proton(1);
	cutDeuteron->set_transverse_velocity_gate(0, 1e5);
	cutDeuteron->set_accepted_efficiency(0, 1e5);
	cutDeuteron->set_passed_monitor(monDeuteron);

	// if identical particle, the second cut should point to the first cut
	cutAlpha->set_accepted_neutron(2);
	cutAlpha->set_accepted_proton(2);
	cutAlpha->set_transverse_velocity_gate(0, DBL_MAX);
	cutAlpha->set_accepted_efficiency(0, DBL_MAX);
	cutAlpha->set_passed_monitor(monAlpha);

	// set monitors for both passing pairs and failing pairs
	RealPairCut->set_consider_detector_effect(true);
	RealPairCut->set_passed_monitor(RealPairMonitor);
	RealPairCut->set_failed_monitor(RealPairFailMonitor);

	MixedPairCut->set_consider_detector_effect(true);
	MixedPairCut->set_passed_monitor(MixedPairMonitor);
	MixedPairCut->set_failed_monitor(MixedPairFailMonitor);

	MyAnalysis->set_event_cut(EventCut);
	MyAnalysis->set_first_track_cut(cutDeuteron);
	MyAnalysis->set_second_track_cut(cutAlpha);
	MyAnalysis->set_real_pair_cut(RealPairCut);
	MyAnalysis->set_mixed_pair_cut(MixedPairCut);

	MyAnalysis->add_correlation(MyCorrelation);
	// user can set to higher value to increase statistics in denominator
	MyAnalysis->set_event_mixing_size(5);

	MyManager->add_analysis(MyAnalysis);
	MyManager->set_reader(MyReader);

	int reader_status = 0;
	auto reader_entries = MyReader->get_entries();
	auto max_nevents = program.get<int>("--nevents");
	auto nevents = (reader_entries < max_nevents) ? reader_entries : max_nevents;
	long nevents_processed = 0;
	auto progress = 0.d;

	show_console_cursor(false);
	pbar.set_progress(progress);
	auto start = std::chrono::high_resolution_clock::now();
	while (nevents_processed < nevents && reader_status == 0) {
		reader_status = MyManager->process();
		nevents_processed++;
		auto curr_progress = static_cast<double>(nevents_processed) / nevents;
		if (curr_progress - progress > 0.) {
			progress = curr_progress;
			pbar.set_progress(progress * 100.);
		}
	}
	show_console_cursor(true);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	std::cout << "\nTime elapsed: " << duration << " s" << std::endl;

	// saving the results
	TFile *output = new TFile(program.get<std::string>("--output").c_str(), "RECREATE");
	output->cd();

	MyCorrelation->get_numerator()->Write();
	MyCorrelation->get_denominator()->Write();

	// save monitors
	EventMonitor->write();
	monDeuteron->write();
	monAlpha->write();
	RealPairMonitor->write();
	RealPairFailMonitor->write();
	MixedPairMonitor->write();
	MixedPairFailMonitor->write();

	output->Write();
	output->Close();
	return 0;
}

void add_arguments(int argc, char **argv) {

	std::string PROJECT_DIR = std::getenv("PROJECT_DIR");
	auto default_path = PROJECT_DIR + "/assets/samples/benchmark.root";

	program.add_argument("-i", "--input_files")
		.help("a list of input files separated by space")
		.nargs(argparse::nargs_pattern::at_least_one)
		.default_value(std::vector<std::string>({default_path}))
		.required();

	program.add_argument("-t", "--tree_name")
		.help("name of the tree in the input file")
		.default_value(std::string("tree"))
		.required();

	program.add_argument("-n", "--nevents")
		.nargs(1)
		.default_value(INT_MAX)
		.help("number of events to be processed")
		.scan<'i', int>()
		.required();

	program.add_argument("-o", "--output")
		.nargs(1)
		.default_value(std::string("output.root"))
		.help("output file name")
		.required();

	program.add_argument("-d", "--debug").help("debug mode").flag();
	try {
		program.parse_args(argc, argv);
	} catch (const std::runtime_error &err) {
		std::cout << err.what() << std::endl;
		std::cout << program;
		exit(0);
	}
}
