#include "main.hpp"

int main(int argc, char *argv[])
{
    manager* man = new manager();
    analysis* anal = new analysis();

    std::string PROJECT_DIR = std::getenv("PROJECT_DIR");
    custom_reader* reader = new custom_reader("tree", (PROJECT_DIR + "/assets/samples/output.root"));
    custom_event_cut* evcut = new custom_event_cut();
    custom_track_cut* trkcut1 = new custom_track_cut();
    custom_track_cut* trkcut2 = new custom_track_cut();
    custom_pair_cut* prcut = new custom_pair_cut();
    custom_correlation* corr = new custom_correlation(50, 0., 200.);

    evcut->set_impact_parameter(0.0, 3.0);
    evcut->set_multiplicity(0, 128);
    trkcut1->set_neutron(1);
    trkcut1->set_proton(1);
    trkcut1->set_transverse_momentum(0, 500);
    trkcut1->set_detector_idx(0);
    
    // if identical particle, second track cut should be set as first track cut
    trkcut2->set_neutron(2);
    trkcut2->set_proton(2);
    trkcut2->set_transverse_momentum(0, 1e5);
    trkcut2->set_detector_idx(0);

    prcut->set_transverse_momentum(0, 1000);

    anal->set_event_cut(evcut);
    anal->set_first_track_cut(trkcut1);
    anal->set_second_track_cut(trkcut2);
    anal->set_pair_cut(prcut);

    anal->add_correlation(corr);
    anal->set_event_mixing_size(40);

    man->add_analysis(anal);
    man->set_reader(reader);
    unsigned int reader_status = 0;
    long nevents_processed = 0;

    while (nevents_processed < 1000000 && reader_status == 0) {
        reader_status = man->process();
        nevents_processed++;
    }

    TFile *outf = new TFile("output.root", "RECREATE");
    corr->Write();
    outf->Write();
    outf->Close();
}

