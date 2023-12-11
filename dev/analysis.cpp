#include "analysis.hpp"
analysis::analysis(const std::string &name, const int &mixing_size) : name(name), event_mixing_size(mixing_size) {
	this->evt_cut = nullptr;
	this->first_track_cut = nullptr;
	this->second_track_cut = nullptr;
	this->real_pair_cut = nullptr;
	this->mixed_pair_cut = nullptr;
	this->correlations = new correlation_collection();
	this->event_mixing_buffer = new fevent_collection();
}

analysis::analysis(const analysis &other) {
	this->event_mixing_size = other.event_mixing_size;
	this->evt_cut = other.evt_cut;
	this->first_track_cut = other.first_track_cut;
	this->second_track_cut = other.second_track_cut;
	this->real_pair_cut = other.real_pair_cut;
	this->mixed_pair_cut = other.mixed_pair_cut;
	this->correlations = other.correlations;
	this->event_mixing_buffer = other.event_mixing_buffer;
}

analysis::~analysis() {
	if (this->evt_cut) {
		delete this->evt_cut;
	}
	if (this->first_track_cut) {
		delete this->first_track_cut;
	}
	if (this->second_track_cut) {
		delete this->second_track_cut;
	}
	if (this->real_pair_cut) {
		delete this->real_pair_cut;
	}
	if (this->mixed_pair_cut) {
		delete this->mixed_pair_cut;
	}

	for (auto &corr : *(this->correlations)) {
		delete corr;
	}
	this->correlations->clear();
	delete this->correlations;

	for (auto &fevt : *(this->event_mixing_buffer)) {
		delete fevt;
	}
	this->event_mixing_buffer->clear();
	delete this->event_mixing_buffer;
}

void analysis::process(event *&evt) {
	// event will be passed if event_cut == nullptr
	bool pass = this->evt_cut ? this->evt_cut->pass(evt) : true;
	if (this->evt_cut) {
		this->evt_cut->fill_monitor(evt, pass);
	}
	if (!pass) {
		return;
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

void analysis::fill_real_correlation(track_collection *&first, track_collection *&second) {
	auto start_outer = first->begin();
	auto end_outer = first->end();
	track_collection::iterator start_inner;
	track_collection::iterator end_inner;

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
			auto pr = std::make_pair(*iptcl, *jptcl);
			bool is_passed_pair = true;
			if (real_pair_cut) {
				is_passed_pair = real_pair_cut->pass(pr);
				real_pair_cut->fill_monitor(pr, is_passed_pair);
			}
			if (is_passed_pair) {
				for (auto &corr : *correlations) {
					corr->add_real_pair(pr);
				}
			}
		}
	}
}

void analysis::fill_mixed_correlation(track_collection *&first, track_collection *&second) {

	for (auto &iptcl : *first) {
		for (auto &jptcl : *second) {
			auto pr = std::make_pair(iptcl, jptcl);
			bool pass = this->mixed_pair_cut ? this->mixed_pair_cut->pass(pr) : true;

			if (this->mixed_pair_cut) {
				this->mixed_pair_cut->fill_monitor(pr, pass);
			}
			if (!pass) {
				continue;
			}
			for (auto &corr : *(this->correlations)) {
				corr->add_mixed_pair(pr);
			}
		}
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

void analysis::fill_particles(track_cut *&cut, track_collection *&src, track_collection *&des) {
	// pre-clean the destination collection
	for (auto &des_track : *des) {
		if (des_track) {
			delete des_track;
		}
	}
	// fill particles into the destination collection and monitors
	for (auto &src_track : *src) {
		bool pass = cut != nullptr ? cut->pass(src_track) : true;
		if (cut) {
			cut->fill_monitor(src_track, pass);
		}
		if (pass) {
			des->push_back(new track(*src_track));
		}
	}
	return;
}
