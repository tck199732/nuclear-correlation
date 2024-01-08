#include "HbtAnalysis.hpp"
HbtAnalysis::HbtAnalysis(const std::string &name, const int &mixing_size) : mName(name), mEventMixingSize(mixing_size) {
	this->mEventCut = nullptr;
	this->mFirstTrackCut = nullptr;
	this->mSecTrackCut = nullptr;
	this->mRealPairCut = nullptr;
	this->mMixedPairCut = nullptr;
	this->mCorrelationFunctions = new HbtCorrelationCollection();
	this->mMixingBuffer = new HbtTempEventCollection();
}

HbtAnalysis::HbtAnalysis(const HbtAnalysis &other) {
	this->mEventMixingSize = other.mEventMixingSize;
	this->mEventCut = other.mEventCut;
	this->mFirstTrackCut = other.mFirstTrackCut;
	this->mSecTrackCut = other.mSecTrackCut;
	this->mRealPairCut = other.mRealPairCut;
	this->mMixedPairCut = other.mMixedPairCut;
	this->mCorrelationFunctions = other.mCorrelationFunctions;
	this->mMixingBuffer = other.mMixingBuffer;
}

HbtAnalysis::~HbtAnalysis() {
	if (this->mEventCut) {
		delete this->mEventCut;
	}
	if (this->mFirstTrackCut) {
		delete this->mFirstTrackCut;
	}
	if (this->mSecTrackCut) {
		delete this->mSecTrackCut;
	}
	if (this->mRealPairCut) {
		delete this->mRealPairCut;
	}
	if (this->mMixedPairCut) {
		delete this->mMixedPairCut;
	}

	for (auto &corr : *this->mCorrelationFunctions) {
		delete corr;
	}
	this->mCorrelationFunctions->clear();
	delete this->mCorrelationFunctions;

	for (auto &fevt : *this->mMixingBuffer) {
		delete fevt;
	}
	this->mMixingBuffer->clear();
	delete this->mMixingBuffer;
}

void HbtAnalysis::Process(const HbtEvent *evt) {
	bool IsPassEvent = this->mEventCut != nullptr ? this->mEventCut->Pass(evt) : true;
	if (this->mEventCut) {
		this->mEventCut->FillMonitor(evt, IsPassEvent);
	}
	if (IsPassEvent == false) {
		return;
	}

	// retain only the passed particles
	auto fevt = this->PreProcess(evt);

	// determine if the HbtEvent should be processed
	auto mFirstTrackCollection = fevt->GetFirstTrackCollection();
	auto mSecTrackCollection = fevt->GetSecTrackCollection();
	auto first_size = mFirstTrackCollection->size();
	auto second_size = mSecTrackCollection->size();

	// auto reject_condition1 = IsIdenticalAnalysis() && first_size < 2;
	auto reject_condition1 = IsIdenticalAnalysis() && first_size < 1;
	auto reject_condition2 = !IsIdenticalAnalysis() && (first_size == 0 || second_size == 0);
	if (reject_condition1 || reject_condition2) {
		delete fevt;
		return;
	}

	if (IsIdenticalAnalysis()) {
		this->FillRealCorrelation(mFirstTrackCollection);
	} else {
		this->FillRealCorrelation(mFirstTrackCollection, mSecTrackCollection);
	}

	for (auto &storedEvent : *this->mMixingBuffer) {
		if (IsIdenticalAnalysis()) {
			this->FillMixedCorrelation(mFirstTrackCollection, storedEvent->GetFirstTrackCollection());
		} else {
			this->FillMixedCorrelation(mFirstTrackCollection, storedEvent->GetSecTrackCollection());
			this->FillMixedCorrelation(storedEvent->GetFirstTrackCollection(), mSecTrackCollection);
		}
	}

	if (this->IsMixingBufferFull()) {
		this->ClearMixingBuffer(); // delete one HbtTempEvent randomly
	}
	this->mMixingBuffer->push_back(fevt);
}

void HbtAnalysis::FillRealCorrelation(HbtTrackCollection *track1, HbtTrackCollection *track2) {
	auto start_outer = track1->begin();
	auto end_outer = track1->end();
	HbtTrackCollection::iterator start_inner;
	HbtTrackCollection::iterator end_inner;

	if (track2) {
		start_inner = track2->begin();
		end_inner = track2->end();

	} else {
		end_outer--;
		end_inner = track1->end();
	}

	for (HbtTrackCollection::iterator iptcl = start_outer; iptcl != end_outer; iptcl++) {
		if (!track2) {
			start_inner = iptcl;
			start_inner++;
		}
		for (HbtTrackCollection::iterator jptcl = start_inner; jptcl != end_inner; jptcl++) {
			bool is_passed_pair = true;
			if (mRealPairCut) {
				is_passed_pair = mRealPairCut->Pass(*iptcl, *jptcl);
				mRealPairCut->FillMonitor(*iptcl, *jptcl, is_passed_pair);
			}
			if (is_passed_pair) {
				for (auto &corr : *this->mCorrelationFunctions) {
					corr->FillRealCorrelation(*iptcl, *jptcl);
				}
			}
		}
	}
}

void HbtAnalysis::FillMixedCorrelation(HbtTrackCollection *track1, HbtTrackCollection *track2) {

	for (auto &iptcl : *track1) {
		for (auto &jptcl : *track2) {
			bool Pass = this->mMixedPairCut ? this->mMixedPairCut->Pass(iptcl, jptcl) : true;

			if (this->mMixedPairCut) {
				this->mMixedPairCut->FillMonitor(iptcl, jptcl, Pass);
			}
			if (!Pass) {
				continue;
			}
			for (auto &corr : *this->mCorrelationFunctions) {
				corr->FillMixedCorrelation(iptcl, jptcl);
			}
		}
	}
}

HbtTempEvent *HbtAnalysis::PreProcess(const HbtEvent *evt) {
	auto fevt = new HbtTempEvent();
	auto tracks = evt->GetTrackCollection();
	auto mFirstTrackCollection = fevt->GetFirstTrackCollection();
	SelectParticles(mFirstTrackCut, tracks, mFirstTrackCollection);
	if (!IsIdenticalAnalysis()) {
		auto mSecTrackCollection = fevt->GetSecTrackCollection();
		SelectParticles(mSecTrackCut, tracks, mSecTrackCollection);
	}
	return fevt;
}

void HbtAnalysis::SelectParticles(HbtTrackCut *&cut, HbtTrackCollection *&src, HbtTrackCollection *&des) {
	// pre-clean the destination HbtCollection
	for (auto &des_track : *des) {
		if (des_track) {
			delete des_track;
		}
	}
	// Fill particles into the destination HbtCollection and monitors
	for (auto &src_track : *src) {
		bool Pass = cut != nullptr ? cut->Pass(src_track) : true;
		if (cut) {
			cut->FillMonitor(src_track, Pass);
		}
		if (Pass) {
			// do not use move constructor, multiple HbtAnalysis may use the same HbtTrack
			des->push_back(new HbtTrack(*src_track));
		}
	}
	return;
}

void HbtAnalysis::ClearMixingBuffer() {
	// shuffle the buffer so a random HbtEvent is removed
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(mMixingBuffer->begin(), mMixingBuffer->end(), g);
	delete mMixingBuffer->front();
	mMixingBuffer->pop_front();
}