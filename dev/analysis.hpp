#ifndef analysis_hpp
#define analysis_hpp

#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <string>

#include "collection.hpp"
#include "correlation.hpp"
#include "event.hpp"
#include "event_cut.hpp"
#include "fevent.hpp"
#include "pair.hpp"
#include "pair_cut.hpp"
#include "particle.hpp"
#include "reader.hpp"
#include "track.hpp"
#include "track_cut.hpp"

class analysis {
public:
	analysis();
	analysis(const analysis &);
	virtual ~analysis();

	fevent *preprocess(const event *evt);
	virtual void process(const event *evt);
	void fill_real_pair_correlation(particle_collection *first, particle_collection *second = 0);
	void fill_mixed_pair_correlation(particle_collection *first, particle_collection *second);

	void set_event_mixing_size(const unsigned int &size) { event_mixing_size = size; }
	void set_event_cut(event_cut *cut) { evt_cut = cut; }
	void set_first_track_cut(track_cut *cut) { first_track_cut = cut; }
	void set_second_track_cut(track_cut *cut) { second_track_cut = cut; }
	void set_real_pair_cut(pair_cut *cut) { real_pr_cut = cut; }
	void set_mixed_pair_cut(pair_cut *cut) { mixed_pr_cut = cut; }
	void add_correlation(correlation *corr) { correlations->push_back(corr); }

	unsigned int get_event_mixing_size() const { return event_mixing_size; }
	event_cut *get_event_cut() const { return evt_cut; }
	track_cut *get_first_track_cut() const { return first_track_cut; }
	track_cut *get_second_track_cut() const { return second_track_cut; }
	pair_cut *get_real_pair_cut() const { return real_pr_cut; }
	pair_cut *get_mixed_pair_cut() const { return mixed_pr_cut; }
	correlation *get_correlation(const unsigned int &index) const;

protected:
	bool is_identical;
	unsigned int event_mixing_size;

	event_cut *evt_cut;
	track_cut *first_track_cut;
	track_cut *second_track_cut;
	pair_cut *real_pr_cut;
	pair_cut *mixed_pr_cut;

	correlation_collection *correlations;
	fevent_collection *event_mixing_buffer;

	bool check_identical() {
		return (first_track_cut == second_track_cut) && first_track_cut != nullptr;
	}
	bool is_buffer_full() { return event_mixing_buffer->size() == event_mixing_size; }
};

#endif
