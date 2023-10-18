#include "analysis.hpp"
void fill_particle_collection(track_cut *cut, track_collection *src, particle_collection *des);

analysis::analysis()
{
    is_identical = false;
    event_mixing_size = 5;
    evt_cut = nullptr;
    first_track_cut = nullptr;
    second_track_cut = nullptr;
    real_pr_cut = nullptr;
    mixed_pr_cut = nullptr;
    correlations = new correlation_collection();
    event_mixing_buffer = new fevent_collection();
}

analysis::analysis(const analysis &anal)
{
    this->is_identical = anal.is_identical;
    this->event_mixing_size = anal.event_mixing_size;
    this->evt_cut = 0;
    this->first_track_cut = 0;
    this->second_track_cut = 0;
    this->real_pr_cut = 0;
    this->mixed_pr_cut = 0;
    this->correlations = 0;
    this->event_mixing_buffer = 0;
}

analysis::~analysis()
{
    if (evt_cut != nullptr)
    {
        delete evt_cut;
    }
    if (first_track_cut != nullptr)
    {
        delete first_track_cut;
    }
    if (second_track_cut != nullptr)
    {
        delete second_track_cut;
    }
    if (real_pr_cut != nullptr)
    {
        delete real_pr_cut;
    }
    if (mixed_pr_cut != nullptr)
    {
        delete mixed_pr_cut;
    }

    for (auto corr : *correlations)
    {
        delete corr;
    }
    correlations->clear();
    delete correlations;

    for (auto evt : *event_mixing_buffer)
    {
        delete evt;
    }
    event_mixing_buffer->clear();
    delete event_mixing_buffer;
}

fevent *analysis::preprocess(const event *evt)
{
    fevent *fevt = new fevent();
    fill_particle_collection(first_track_cut, evt->get_track_collection(), fevt->get_first_collection());
    if (!check_identical())
    {
        fill_particle_collection(second_track_cut, evt->get_track_collection(), fevt->get_second_collection());
    }
    return fevt;
}

void analysis::process(const event *evt)
{
    // event will be passed if event_cut == nullptr
    if (this->evt_cut)
    {
        bool is_passed_event = this->evt_cut->pass(evt);
        this->evt_cut->fill_monitor(evt, is_passed_event);
        if (!is_passed_event)
            return;
    }

    // retain only the passed particles
    fevent *fevt = preprocess(evt);

    // determine if the event should be processed
    unsigned int first_size = fevt->get_first_collection()->size();
    unsigned int second_size = fevt->get_second_collection()->size();
    if (check_identical())
    {
        if (first_size < 2)
        {
            delete fevt;
            return;
        }
    }
    else
    {
        if (first_size == 0 || second_size == 0 || first_size + second_size < 2)
        {
            delete fevt;
            return;
        }
    }

    if (check_identical())
    {
        fill_real_pair_correlation(fevt->get_first_collection());
    }
    else
    {
        fill_real_pair_correlation(fevt->get_first_collection(), fevt->get_second_collection());
    }

    for (auto fevt_mix : *event_mixing_buffer)
    {
        if (check_identical())
        {
            fill_mixed_pair_correlation(fevt->get_first_collection(), fevt_mix->get_first_collection());
        }
        else
        {
            fill_mixed_pair_correlation(fevt->get_first_collection(), fevt_mix->get_second_collection());
            fill_mixed_pair_correlation(fevt_mix->get_first_collection(), fevt->get_second_collection());
        }
    }

    if (is_buffer_full())
    {
        event_mixing_buffer->pop_front();
        event_mixing_buffer->push_back(fevt);
    }
    else
    {
        event_mixing_buffer->push_back(fevt);
    }
}

void analysis::fill_real_pair_correlation(particle_collection *first, particle_collection *second)
{
    pair *pr = new pair();
    auto start_outer = first->begin();
    auto end_outer = first->end();
    particle_collection::iterator start_inner;
    particle_collection::iterator end_inner;

    if (!second)
    {
        end_inner = first->end();
        ;
        end_outer--;
    }
    else
    {
        start_inner = second->begin();
        end_inner = second->end();
    }

    for (auto &iptcl = start_outer; iptcl != end_outer; iptcl++)
    {
        for (auto &jptcl = start_inner; jptcl != end_inner; jptcl++)
        {
            pr->set_first_particle(*iptcl);
            pr->set_second_particle(*jptcl);
            // if (real_pr_cut == nullptr || real_pr_cut->pass(pr))
            // {
            //     for (auto &corr : *correlations)
            //     {
            //         corr->add_real_pair(pr);
            //     }
            // }
            bool is_passed_pair = true;
            if (real_pr_cut) {
                is_passed_pair = real_pr_cut->pass(pr);
                real_pr_cut->fill_monitor(pr, is_passed_pair);
            }
            if (is_passed_pair) {
                for (auto &corr : *correlations)
                    corr->add_real_pair(pr);
            }

        }
    }
    delete pr;
}

void analysis::fill_mixed_pair_correlation(particle_collection *first, particle_collection *second)
{
    pair *pr = new pair();
    for (auto &iptcl : *first)
    {
        for (auto &jptcl : *second)
        {
            pr->set_first_particle(iptcl);
            pr->set_second_particle(jptcl);
            // if (mixed_pr_cut == nullptr || mixed_pr_cut->pass(pr))
            // {
            //     for (auto &corr : *correlations)
            //     {
            //         corr->add_mixed_pair(pr);
            //     }
            // }

            bool is_passed_pair = true;
            if (mixed_pr_cut) {
                is_passed_pair = mixed_pr_cut->pass(pr);
                mixed_pr_cut->fill_monitor(pr, is_passed_pair);
            }
            if (is_passed_pair) {
                for (auto &corr : *correlations)
                    corr->add_mixed_pair(pr);
            }
        }
    }
    delete pr;
}

void fill_particle_collection(track_cut *cut, track_collection *src, particle_collection *des)
{
    // for (auto& trk : *src) {
    //     if (cut == nullptr || cut->pass(trk)) {
    //         des->push_back(new particle(trk));
    //     }
    // }

    for (auto &trk : *src)
    {
        if (cut)
        {
            bool is_passed_track = cut->pass(trk);
            cut->fill_monitor(trk, is_passed_track);
            if (is_passed_track)
                des->push_back(new particle(trk));
        }
        else
        {
            des->push_back(new particle(trk));
        }
    }
    return;
}

correlation *analysis::get_correlation(const unsigned int &index) const
{
    if (index >= correlations->size())
    {
        return nullptr;
    }
    return (*correlations)[index];
}