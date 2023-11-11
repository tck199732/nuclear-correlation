#include "analysis.hpp"
analysis::analysis() {
	event_mixing_size = 5;
	evt_cut = nullptr;
	first_track_cut = nullptr;
	second_track_cut = nullptr;
	real_pr_cut = nullptr;
	mixed_pr_cut = nullptr;
	correlations = new correlation_collection();
	event_mixing_buffer = new fevent_collection();
}

analysis::analysis(const analysis &anal) {
	this->event_mixing_size = anal.event_mixing_size;
	this->evt_cut = 0;
	this->first_track_cut = 0;
	this->second_track_cut = 0;
	this->real_pr_cut = 0;
	this->mixed_pr_cut = 0;
	this->correlations = 0;
	this->event_mixing_buffer = 0;
}

analysis::~analysis() {
	if (evt_cut) {
		delete evt_cut;
	}
	if (is_identical_particle()) {
		second_track_cut = nullptr;
	}
	if (first_track_cut) {
		delete first_track_cut;
		first_track_cut = nullptr;
	}
	if (second_track_cut) {
		delete second_track_cut;
		second_track_cut = nullptr;
	}
	if (real_pr_cut) {
		delete real_pr_cut;
		real_pr_cut = nullptr;
	}
	if (mixed_pr_cut) {
		delete mixed_pr_cut;
		mixed_pr_cut = nullptr;
	}
	if (correlations) {
		for (auto &corr : *correlations) {
			delete corr;
		}
		delete correlations;
		correlations = nullptr;
	}
	if (event_mixing_buffer) {
		for (auto &fevt : *event_mixing_buffer) {
			delete fevt;
		}
		delete event_mixing_buffer;
		event_mixing_buffer = nullptr;
	}
}

fevent *analysis::preprocess(const event *evt) {
	auto fevt = new fevent();
	auto tracks = evt->get_track_collection();
	auto first_collection = fevt->get_first_collection();
	fill_particles(first_track_cut, tracks, first_collection);
	if (!is_identical_particle()) {
		auto second_collection = fevt->get_second_collection();
		fill_particles(second_track_cut, tracks, second_collection);
	}
	return fevt;
}

void analysis::process(const event *evt) {
	// event will be passed if event_cut == nullptr
	if (this->evt_cut) {
		bool is_passed_event = this->evt_cut->pass(evt);
		this->evt_cut->fill_monitor(evt, is_passed_event);
		if (!is_passed_event) {
			return;
		}
	}

	// retain only the passed particles
	fevent *fevt = preprocess(evt);

	// determine if the event should be processed
	auto first_size = fevt->get_first_collection()->size();
	auto second_size = fevt->get_second_collection()->size();
	auto reject_condition1 = is_identical_particle() && first_size < 2;
	auto reject_condition2 = !is_identical_particle() && (first_size == 0 || second_size == 0);
	if (reject_condition1 || reject_condition2) {
		delete fevt;
		return;
	}

	auto first_collection = fevt->get_first_collection();
	auto second_collection = is_identical_particle() ? nullptr : fevt->get_second_collection();
	fill_real_correlation(first_collection, second_collection);

	for (auto fevt_mix : *event_mixing_buffer) {
		if (is_identical_particle()) {
			auto first_collection = fevt->get_first_collection();
			auto second_collection = fevt_mix->get_first_collection();
			fill_mixed_correlation(first_collection, second_collection);

		} else {
			auto first_collection = fevt->get_first_collection();
			auto second_collection = fevt_mix->get_first_collection();
			fill_mixed_correlation(first_collection, second_collection);
			fill_mixed_correlation(second_collection, first_collection);
		}
	}
	if (is_buffer_full()) {
		event_mixing_buffer->pop_front();
		event_mixing_buffer->push_back(fevt);
	} else {
		event_mixing_buffer->push_back(fevt);
	}
}

void analysis::fill_real_correlation(particle_collection *first, particle_collection *second) {
	pair *pr = new pair();
	auto start_outer = first->begin();
	auto end_outer = first->end();
	particle_collection::iterator start_inner;
	particle_collection::iterator end_inner;

	if (!second) {
		end_inner = first->end();
		end_outer--;

	} else {
		start_inner = second->begin();
		end_inner = second->end();
	}

	for (auto &iptcl = start_outer; iptcl != end_outer; iptcl++) {
		if (!second) {
			start_inner = iptcl;
			start_inner++;
		}
		for (auto &jptcl = start_inner; jptcl != end_inner; jptcl++) {

			pr->set_first_particle(*iptcl);
			pr->set_second_particle(*jptcl);

			bool is_passed_pair = true;
			if (real_pr_cut) {
				is_passed_pair = real_pr_cut->pass(pr);
				real_pr_cut->fill_monitor(pr, is_passed_pair);
			}
			if (is_passed_pair) {
				for (auto &corr : *correlations) {
					corr->add_real_pair(pr);
				}
			}
		}
	}
	delete pr;
}

void analysis::fill_mixed_correlation(particle_collection *first, particle_collection *second) {
	pair *pr = new pair();
	for (auto &iptcl : *first) {
		for (auto &jptcl : *second) {
			pr->set_first_particle(iptcl);
			pr->set_second_particle(jptcl);

			bool is_passed_pair = true;
			if (mixed_pr_cut) {
				is_passed_pair = mixed_pr_cut->pass(pr);
				mixed_pr_cut->fill_monitor(pr, is_passed_pair);
			}
			if (is_passed_pair) {
				for (auto &corr : *correlations) {
					corr->add_mixed_pair(pr);
				}
			}
		}
	}
	delete pr;
}

void analysis::fill_particles(track_cut *cut, track_collection *src, particle_collection *des) {
	for (auto &trk : *src) {
		if (cut) {
			bool is_passed_track = cut->pass(trk);
			cut->fill_monitor(trk, is_passed_track);
			if (is_passed_track)
				des->push_back(new particle(trk));
		} else {
			des->push_back(new particle(trk));
		}
	}
	return;
}

correlation *analysis::get_correlation(const unsigned int &index) const {
	if (index >= correlations->size()) {
		return nullptr;
	}
	return (*correlations)[index];
}