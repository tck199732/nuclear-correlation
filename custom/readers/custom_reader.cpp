#include "custom_reader.hpp"
custom_reader::custom_reader(const std::string& tree_name, const std::string& filename) : reader()
{
    chain = new TChain(tree_name.c_str(), "");
    chain->AddFile(filename.c_str());
    this->set_branches(chain);
    current_event_index = 0;
}

custom_reader::custom_reader(const custom_reader &reader)
{
    chain = 0;
}

custom_reader::~custom_reader()
{
    delete chain;
}

event *custom_reader::return_event()
{
    event *evt = 0;
    try
    {
        evt = read();
    }
    catch (std::exception &e)
    {
        return 0;
    }
    if (!evt) this->status = 1;
    return evt;
}

event *custom_reader::read()
{
    chain->GetEntry(current_event_index);
    event *evt = new event();

    evt->set_multiplicity(branches.multi);
    evt->set_impact_parameter(branches.b);
    track_collection *tracks = evt->get_track_collection();

    for (int j = 0; j < branches.multi; j++)
    {
        double mass = this->nucleon_mass * (branches.N[j] + branches.Z[j]);
        track *trk= new track(
            branches.N[j],
            branches.Z[j],
            branches.vx[j],
            branches.vy[j],
            branches.vz[j],
            mass,
            0, 0, 0, 0
        );
        trk->set_property("detector-index", 0);
        tracks->push_back(trk);
    }
    current_event_index += 1;
    return evt;
}

void custom_reader::set_branches(TChain*& chain)
{
    chain->SetMakeClass(1);
    chain->SetBranchStatus("*", 0);

    chain->SetBranchAddress("multi", &branches.multi);
    chain->SetBranchAddress("b", &branches.b);
    chain->SetBranchAddress("N", &branches.N[0]);
    chain->SetBranchAddress("Z", &branches.Z[0]);
    chain->SetBranchAddress("vx", &branches.vx[0]);
    chain->SetBranchAddress("vy", &branches.vy[0]);
    chain->SetBranchAddress("vz", &branches.vz[0]);

    chain->SetMakeClass(1);
    chain->SetBranchStatus("*", false);
    chain->SetBranchStatus("multi", true);
    chain->SetBranchStatus("b", true);
    chain->SetBranchStatus("N", true);
    chain->SetBranchStatus("Z", true);
    chain->SetBranchStatus("vx", true);
    chain->SetBranchStatus("vy", true);
    chain->SetBranchStatus("vz", true);
}
