#ifndef analysis_hpp
#define analysis_hpp

#include <string>
#include <algorithm>
#include <deque>
#include <memory>
#include <iostream>

#include "collection.hpp"
#include "fevent.hpp"
#include "event.hpp"
#include "particle.hpp"
#include "track.hpp"
#include "pair.hpp"
#include "reader.hpp"
#include "correlation.hpp"
#include "event_cut.hpp"
#include "track_cut.hpp"
#include "pair_cut.hpp"

class analysis
{
public:
    analysis();
    analysis(const analysis &);
    virtual ~analysis();

    void set_event_mixing_size(const unsigned int &size) { event_mixing_size = size; }
    void set_event_cut(event_cut *cut) { evt_cut = cut; }
    void set_first_track_cut(track_cut *cut) { first_track_cut = cut; }
    void set_second_track_cut(track_cut *cut) { second_track_cut = cut; }
    void set_pair_cut(pair_cut *cut) { pr_cut = cut; }
    void add_correlation(correlation *corr) { correlations->push_back(corr); }

    fevent* preprocess(const event *evt);
    virtual void process(const event *evt);

    void fill_real_pair_correlation(particle_collection* first, particle_collection* second = 0);
    void fill_mixed_pair_correlation(particle_collection* first, particle_collection* second);

protected:
    bool is_identical;
    unsigned int event_mixing_size;

    event_cut* evt_cut;
    track_cut* first_track_cut;
    track_cut* second_track_cut;
    pair_cut* pr_cut;

    correlation_collection *correlations;
    fevent_collection *event_mixing_buffer;

    bool check_identical() {return (first_track_cut == second_track_cut) && first_track_cut != nullptr; }
    bool is_buffer_full() {return event_mixing_buffer->size() == event_mixing_size; }
};

#endif
