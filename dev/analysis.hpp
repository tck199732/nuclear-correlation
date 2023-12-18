#ifndef analysis_hpp
#define analysis_hpp

#include <algorithm>
#include <deque>
#include <iostream>
#include <string>

#include "collection.hpp"
#include "correlation.hpp"
#include "event.hpp"
#include "event_cut.hpp"
#include "fevent.hpp"
#include "pair_cut.hpp"
#include "reader.hpp"
#include "track.hpp"
#include "track_cut.hpp"

class analysis {
public:
	analysis(const std::string &name = "", const int &mixing_size = 5);
	analysis(const analysis &);
	virtual ~analysis();
	virtual void process(const event *evt);
	// action when the mixing buffer is full
	virtual void clean_mixing_buffer();

	void set_event_mixing_size(const unsigned int &size);
	void set_event_cut(event_cut *cut);
	void set_first_track_cut(track_cut *cut);
	void set_second_track_cut(track_cut *cut);
	void set_real_pair_cut(pair_cut *cut);
	void set_mixed_pair_cut(pair_cut *cut);
	void add_correlation(correlation *corr);

	unsigned int get_event_mixing_size() const { return event_mixing_size; }
	event_cut *get_event_cut() const { return evt_cut; }
	track_cut *get_first_track_cut() const { return first_track_cut; }
	track_cut *get_second_track_cut() const { return second_track_cut; }
	pair_cut *get_real_pair_cut() const { return real_pair_cut; }
	pair_cut *get_mixed_pair_cut() const { return mixed_pair_cut; }
	correlation *get_correlation(const unsigned int &index) const { return correlations->at(index); }

protected:
	std::string name;
	unsigned int event_mixing_size;

	event_cut *evt_cut;
	track_cut *first_track_cut;
	track_cut *second_track_cut;
	pair_cut *real_pair_cut;
	pair_cut *mixed_pair_cut;

	correlation_collection *correlations;
	fevent_collection *event_mixing_buffer;

	fevent *preprocess(const event *evt);
	void fill_particles(track_cut *&cut, track_collection *&src, track_collection *&des);
	void fill_real_correlation(track_collection *first, track_collection *second = 0);
	void fill_mixed_correlation(track_collection *first, track_collection *second);

	bool is_identical_particle() { return (first_track_cut == second_track_cut); }
	bool is_buffer_full() { return event_mixing_buffer->size() == event_mixing_size; }
};

inline void analysis::set_event_mixing_size(const unsigned int &size) { event_mixing_size = size; }

inline void analysis::set_event_cut(event_cut *cut) { evt_cut = cut; }

inline void analysis::set_first_track_cut(track_cut *cut) { first_track_cut = cut; }

inline void analysis::set_second_track_cut(track_cut *cut) { second_track_cut = cut; }

inline void analysis::set_real_pair_cut(pair_cut *cut) { real_pair_cut = cut; }

inline void analysis::set_mixed_pair_cut(pair_cut *cut) { mixed_pair_cut = cut; }

inline void analysis::add_correlation(correlation *corr) { correlations->push_back(corr); }

#endif
