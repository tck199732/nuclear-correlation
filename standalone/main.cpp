#include "main.hpp"

int main(int argc, char *argv[]) {
	manager *man = new manager();
	analysis *anal = new analysis();

	std::string PROJECT_DIR = std::getenv("PROJECT_DIR");
	custom_reader *reader =
		new custom_reader("tree", (PROJECT_DIR + "/assets/samples/output.root"));

	custom_event_cut *evcut = new custom_event_cut();
	custom_track_cut *trkcut1 = new custom_track_cut();
	custom_track_cut *trkcut2 = new custom_track_cut();
	custom_pair_cut *real_prcut = new custom_pair_cut();
	custom_pair_cut *mixed_prcut = new custom_pair_cut();

	custom_event_monitor *event_monitor = new custom_event_monitor("event_monitor");
	custom_track_monitor *first_track_monitor = new custom_track_monitor("first_track_monitor");
	custom_track_monitor *second_track_monitor = new custom_track_monitor("second_track_monitor");
	custom_pair_monitor *real_pair_monitor = new custom_pair_monitor("real_pair_monitor");
	custom_pair_monitor *mixed_pair_monitor = new custom_pair_monitor("mixed_pair_monitor");

	custom_correlation *corr = new custom_correlation("my_correlation", 50, 0., 200.);

	evcut->set_accepted_impact_parameter(0, 1e5);
	evcut->set_accepted_multiplicity(0, 128);
	evcut->set_accepted_trigger_condition("");
	evcut->set_accepted_trigger_value(0, 1e5);
	evcut->set_passed_monitor(event_monitor);

	trkcut1->set_accepted_neutron(1);
	trkcut1->set_accepted_proton(1);
	trkcut1->set_transverse_velocity_gate(0, 1e5);
	trkcut1->set_accepted_efficiency(0, 1e5);
	trkcut1->set_passed_monitor(first_track_monitor);

	// if identical particle, second track cut should be set as first track cut
	trkcut2->set_accepted_neutron(2);
	trkcut2->set_accepted_proton(2);
	trkcut2->set_transverse_velocity_gate(0, 1e5);
	trkcut2->set_accepted_efficiency(0, 1e5);
	trkcut2->set_passed_monitor(second_track_monitor);

	real_prcut->set_transverse_velocity_gate(0, 1e5);
	real_prcut->set_consider_detector_index(1);
	real_prcut->set_passed_monitor(real_pair_monitor);
	mixed_prcut->set_transverse_velocity_gate(0, 1e5);
	mixed_prcut->set_consider_detector_index(1);
	mixed_prcut->set_passed_monitor(mixed_pair_monitor);

	anal->set_event_cut(evcut);
	anal->set_first_track_cut(trkcut1);
	anal->set_second_track_cut(trkcut2);
	anal->set_real_pair_cut(real_prcut);
	anal->set_mixed_pair_cut(real_prcut);

	anal->add_correlation(corr);
	anal->set_event_mixing_size(40);

	man->add_analysis(anal);
	man->set_reader(reader);
	unsigned int reader_status = 0;
	long nevents_processed = 0;

	while (nevents_processed < 1000000 && reader_status == 0) {
		reader_status = man->process();
		if (nevents_processed % 10000 == 0)
			std::cout << nevents_processed << std::endl;
		nevents_processed++;
	}

	TFile *outf = new TFile("output.root", "RECREATE");
	corr->write();
	outf->Write();
	outf->Close();

	TFile *event_monitor_outf = new TFile("event_monitor.root", "RECREATE");
	event_monitor_outf->cd();
	event_monitor->write();
	event_monitor_outf->Write();
	event_monitor_outf->Close();

	TFile *first_track_monitor_outf = new TFile("first_track_monitor.root", "RECREATE");
	first_track_monitor_outf->cd();
	first_track_monitor->write();
	first_track_monitor_outf->Write();
	first_track_monitor_outf->Close();

	TFile *second_track_monitor_outf = new TFile("second_track_monitor.root", "RECREATE");
	second_track_monitor_outf->cd();
	second_track_monitor->write();
	second_track_monitor_outf->Write();
	second_track_monitor_outf->Close();

	TFile *real_pair_monitor_outf = new TFile("real_pair_monitor.root", "RECREATE");
	real_pair_monitor_outf->cd();
	real_pair_monitor->write();
	real_pair_monitor_outf->Write();
	real_pair_monitor_outf->Close();
}
