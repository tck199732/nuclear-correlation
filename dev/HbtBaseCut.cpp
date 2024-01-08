#include "HbtBaseCut.hpp"

HbtBaseCut::HbtBaseCut() {
	this->mPassMonitor = nullptr;
	this->mFailMonitor = nullptr;
}

HbtBaseCut::HbtBaseCut(const HbtBaseCut &cut) {
	this->mPassMonitor = cut.mPassMonitor;
	this->mFailMonitor = cut.mFailMonitor;
}

HbtBaseCut::~HbtBaseCut() {
	if (this->mPassMonitor != nullptr) {
		delete this->mPassMonitor;
	}
	if (this->mFailMonitor != nullptr) {
		delete this->mFailMonitor;
	}
}

void HbtBaseCut::FillMonitor(const HbtEvent *evt, bool Pass) {
	if (Pass && this->mPassMonitor != nullptr) {
		this->mPassMonitor->Fill(evt);
	} else if (!Pass && this->mFailMonitor != nullptr) {
		this->mFailMonitor->Fill(evt);
	}
}

void HbtBaseCut::FillMonitor(const HbtTrack *trk, bool Pass) {
	if (Pass && this->mPassMonitor != nullptr) {
		this->mPassMonitor->Fill(trk);
	} else if (!Pass && this->mFailMonitor != nullptr) {
		this->mFailMonitor->Fill(trk);
	}
}

void HbtBaseCut::FillMonitor(const HbtTrack *track1, const HbtTrack *track2, bool Pass) {
	if (Pass && this->mPassMonitor != nullptr) {
		this->mPassMonitor->Fill(track1, track2);
	} else if (!Pass && this->mFailMonitor != nullptr) {
		this->mFailMonitor->Fill(track1, track2);
	}
}
