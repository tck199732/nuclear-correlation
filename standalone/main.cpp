#include "main.hpp"

void add_arguments(int argc, char **argv);
argparse::ArgumentParser program("HbtCorrelation-benchmark", "1.0");

int main(int argc, char *argv[]) {

	add_arguments(argc, argv);

	auto manager = new HbtManager();
	auto anal = new HbtAnalysis("sample analysis", 5);

	// clang-format off
	auto reader = new CustomReader(
        program.get<std::string>("--tree_name"),
        program.get<std::vector<std::string>>("--input_files")
	);
	// clang-format on

	// initialize Cuts classes
	auto EventCut = new CustomEventCut();
	auto cutDeuteron = new CustomTrackCut();
	auto cutAlpha = new CustomTrackCut();
	auto RealPairCut = new CustomPairCut();
	auto MixedPairCut = new CustomPairCut();

	// initialize monitors classes
	auto eventMon = new CustomEventMonitor("eventMon");
	auto DeuteronMon = new CustomTrackCutMonitor("DeuteronMon");
	auto AlphaMon = new CustomTrackCutMonitor("AlphaMon");
	auto RePairMon = new CustomPairMonitor("RePairMon");
	auto RePairFailMon = new CustomPairMonitor("RePairFailMon");
	auto MixPairMon = new CustomPairMonitor("MixPairMon");
	auto MixPairFailMon = new CustomPairMonitor("MixPairFailMon");

	// sampler for HbtCorrelation as a funciton of relative momentum
	auto corr = new CustomCorrelation("corr", 150, 0., 600.);

	EventCut->SetImpactParamRange(0, 10);
	EventCut->SetMultiplicityRange(1, 128);
	EventCut->SetPassMonitor(eventMon);

	cutDeuteron->SetNeutron(1);
	cutDeuteron->SetProton(1);
	cutDeuteron->SetPtransRange(0, 1e5);
	cutDeuteron->SetPassMonitor(DeuteronMon);

	// if identical particle, the track2 cut should point to the track1 cut
	cutAlpha->SetNeutron(2);
	cutAlpha->SetProton(2);
	cutAlpha->SetPtransRange(0, DBL_MAX);
	cutAlpha->SetPassMonitor(AlphaMon);

	// set monitors for both passing pairs and failing pairs
	RealPairCut->SetConsiderDetEffect(true);
	RealPairCut->SetPassMonitor(RePairMon);
	RealPairCut->SetFailMonitor(RePairFailMon);

	MixedPairCut->SetConsiderDetEffect(true);
	MixedPairCut->SetPassMonitor(MixPairMon);
	MixedPairCut->SetFailMonitor(MixPairFailMon);

	anal->SetEventCut(EventCut);
	anal->SetFirstTrackCut(cutDeuteron);
	anal->SetSecTrackCut(cutAlpha);
	anal->SetRealPairCut(RealPairCut);
	anal->SetMixedPairCut(MixedPairCut);

	anal->AddCorrelation(corr);
	// user can set to higher value to increase statistics in mDenominator
	anal->SetEventMixingSize(5);

	manager->AddAnalysis(anal);
	manager->SetReader(reader);

	int reader_status = 0;
	auto reader_entries = reader->GetEntries();
	auto max_nevents = program.get<int>("--nevents");
	auto nevents = (reader_entries < max_nevents) ? reader_entries : max_nevents;
	long nevents_processed = 0;
	auto progress = 0.d;

	show_console_cursor(false);
	pbar.set_progress(progress);
	auto start = std::chrono::high_resolution_clock::now();
	while (nevents_processed < nevents && reader_status == 0) {
		reader_status = manager->Process();
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

	corr->GetNumerator()->Write();
	corr->GetDenominator()->Write();

	// save monitors
	eventMon->Write();
	DeuteronMon->Write();
	AlphaMon->Write();
	RePairMon->Write();
	RePairFailMon->Write();
	MixPairMon->Write();
	MixPairFailMon->Write();

	output->Write();
	output->Close();
	return 0;
}

void add_arguments(int argc, char **argv) {

	std::string PROJECT_DIR = std::getenv("PROJECT_DIR");
	auto default_path = PROJECT_DIR + "/database/samples/benchmark.root";

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
