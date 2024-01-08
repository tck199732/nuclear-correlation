#include "HbtAnalysis.hpp"
#include <doctest/doctest.h>

// mock classes from other test files
class mock_correlation : public HbtCorrelation {
public:
	mock_correlation() : called_add_real_pair(false), called_add_mixed_pair(false) {}
	mock_correlation(const mock_correlation &other) = default;
	~mock_correlation() = default;
	virtual void FillRealCorrelation(const HbtTrack *track1, const HbtTrack *track2) override { this->called_add_real_pair = true; }
	virtual void FillMixedCorrelation(const HbtTrack *track1, const HbtTrack *track2) override {
		this->called_add_mixed_pair = true;
	}
	bool called_add_real_pair, called_add_mixed_pair;
};

class mock_monitor : public HbtMonitor {
public:
	mock_monitor() : is_event_fill(false), is_track_fill(false), is_pair_fill(false) { ; }
	mock_monitor(const mock_monitor &) = default;
	~mock_monitor() = default;
	void Report() override { ; }
	virtual void Fill(const HbtEvent *) override { this->is_event_fill = true; }
	virtual void Fill(const HbtTrack *) override { this->is_track_fill = true; }
	virtual void Fill(const HbtTrack *track1, const HbtTrack *track2) override { this->is_pair_fill = true; }

	bool is_event_fill;
	bool is_track_fill;
	bool is_pair_fill;
};

class mock_event_cut_ : public HbtEventCut {
public:
	mock_event_cut_() : HbtEventCut() { this->processed_events = 0; }
	mock_event_cut_(const mock_event_cut_ &) = default;
	virtual ~mock_event_cut_(){};
	virtual bool Pass(const HbtEvent *evt) override {
		this->processed_events++;
		return true;
	}
	int processed_events;
};

class mock_track_cut_ : public HbtTrackCut {
public:
	mock_track_cut_() : HbtTrackCut() {
		this->processed_tracks = 0;
		this->N = 0;
		this->Z = 0;
	}
	mock_track_cut_(const mock_track_cut_ &) = default;
	virtual ~mock_track_cut_() = default;
	virtual bool Pass(const HbtTrack *trk) override {
		processed_tracks++;
		return trk->GetNeutron() == this->N && trk->GetProton() == this->Z;
	}
	void setN(int N) { this->N = N; }
	void setZ(int Z) { this->Z = Z; }
	int processed_tracks;
	int N, Z;
};

class mock_pair_cut_ : public HbtPairCut {
public:
	mock_pair_cut_() : HbtPairCut() { this->processed_pairs = 0; }
	mock_pair_cut_(const mock_pair_cut_ &) = default;
	virtual ~mock_pair_cut_() = default;
	virtual bool Pass(const HbtTrack *track1, const HbtTrack *track2) override {
		processed_pairs++;
		return true;
	}
	int processed_pairs;
};

TEST_CASE("check initialization") {
	auto ana = new HbtAnalysis();
	auto mixing_size = rand() % 10 + 1;
	ana->SetEventMixingSize(mixing_size);
	CHECK(ana->GetEventMixingSize() == mixing_size);

	// objects required for HbtAnalysis
	auto ecut = new mock_event_cut_();
	auto tcut1 = new mock_track_cut_();
	auto pcut_real = new mock_pair_cut_();
	auto pcut_mixed = new mock_pair_cut_();
	auto emonPass = new mock_monitor();
	auto emonFail = new mock_monitor();
	auto tmonPass1 = new mock_monitor();
	auto tmonFail1 = new mock_monitor();
	auto pmonPass_real = new mock_monitor();
	auto pmonFail_real = new mock_monitor();
	auto pmonPass_imag = new mock_monitor();
	auto pmonFail_imag = new mock_monitor();

	// any number of correlations can be added
	auto corr1 = new mock_correlation();
	auto corr2 = new mock_correlation();
	auto corr3 = new mock_correlation();

	ecut->SetPassMonitor(emonPass);
	ecut->SetFailMonitor(emonFail);
	tcut1->SetPassMonitor(tmonPass1);
	tcut1->SetFailMonitor(tmonFail1);
	pcut_real->SetPassMonitor(pmonPass_real);
	pcut_real->SetFailMonitor(pmonFail_real);
	pcut_mixed->SetPassMonitor(pmonPass_imag);
	pcut_mixed->SetFailMonitor(pmonFail_imag);

	ana->SetEventCut(ecut);
	ana->SetFirstTrackCut(tcut1);
	ana->SetRealPairCut(pcut_real);
	ana->SetMixedPairCut(pcut_mixed);

	CHECK(ana->GetEventCut() == ecut);
	CHECK(ana->GetFirstTrackCut() == tcut1);
	CHECK(ana->GetRealPairCut() == pcut_real);
	CHECK(ana->GetMixedPairCut() == pcut_mixed);

	SUBCASE("non-identical HbtAnalysis") {
		auto tcut2 = new mock_track_cut_();
		auto tmonPass2 = new mock_monitor();
		auto tmonFail2 = new mock_monitor();
		tcut2->SetPassMonitor(tmonPass2);
		tcut2->SetFailMonitor(tmonFail2);
		ana->SetSecTrackCut(tcut2);
		CHECK(ana->GetSecTrackCut() == tcut2);
		CHECK(ana->GetFirstTrackCut() != ana->GetSecTrackCut());
	}

	SUBCASE("identical HbtAnalysis") {
		ana->SetSecTrackCut(tcut1);
		CHECK(ana->GetSecTrackCut() == tcut1);
	}

	ana->AddCorrelation(corr1);
	ana->AddCorrelation(corr2);
	ana->AddCorrelation(corr3);
	CHECK(ana->GetCorrelation(0) == corr1);
	CHECK(ana->GetCorrelation(1) == corr2);
	CHECK(ana->GetCorrelation(2) == corr3);

	SUBCASE("check copy constructor") {
		auto ana2 = new HbtAnalysis(*ana);
		CHECK(ana2->GetEventMixingSize() == mixing_size);
		CHECK(ana2->get_event_cut() == ecut);
		CHECK(ana2->GetFirstTrackCut() == tcut1);
		CHECK(ana2->GetRealPairCut() == pcut_real);
		CHECK(ana2->GetMixedPairCut() == pcut_mixed);
		CHECK(ana2->GetCorrelation(0) == corr1);
		CHECK(ana2->GetCorrelation(1) == corr2);
		CHECK(ana2->GetCorrelation(2) == corr3);
	}
	SUBCASE("check destructor") { delete ana; }
}

TEST_CASE("check identical HbtAnalysis") {
	auto ana = new HbtAnalysis();
	auto mixing_size = rand() % 10 + 1;
	ana->SetEventMixingSize(mixing_size);

	// objects required for HbtAnalysis
	auto ecut = new mock_event_cut_();
	auto tcut1 = new mock_track_cut_();
	tcut1->setN(0);
	tcut1->setZ(1);
	auto pcut_real = new mock_pair_cut_();
	auto pcut_mixed = new mock_pair_cut_();

	auto emonPass = new mock_monitor();
	auto emonFail = new mock_monitor();
	auto tmonPass1 = new mock_monitor();
	auto tmonFail1 = new mock_monitor();
	auto pmonPass_real = new mock_monitor();
	auto pmonFail_real = new mock_monitor();
	auto pmonPass_imag = new mock_monitor();
	auto pmonFail_imag = new mock_monitor();

	// any number of correlations can be added
	auto corr1 = new mock_correlation();

	ecut->SetPassMonitor(emonPass);
	ecut->SetFailMonitor(emonFail);
	tcut1->SetPassMonitor(tmonPass1);
	tcut1->SetFailMonitor(tmonFail1);
	pcut_real->SetPassMonitor(pmonPass_real);
	pcut_real->SetFailMonitor(pmonFail_real);
	pcut_mixed->SetPassMonitor(pmonPass_imag);
	pcut_mixed->SetFailMonitor(pmonFail_imag);

	ana->SetEventCut(ecut);
	ana->SetFirstTrackCut(tcut1);
	ana->SetRealPairCut(pcut_real);
	ana->SetMixedPairCut(pcut_mixed);
	ana->SetSecTrackCut(tcut1);
	ana->AddCorrelation(corr1);

	// generate events
	int ntracks = rand() % 10;
	for (int in = 0; in <= mixing_size; in++) {
		auto evt = new HbtEvent();
		auto tcoll = evt->GetTrackCollection();
		for (int _ = 0; _ < ntracks; ++_) {
			auto trk = new HbtTrack(0, 1, 938.272, 0., 0., 0.);
			tcoll->push_back(trk);
		}
		ana->Process(evt);
	}

	CHECK(ecut->processed_events == mixing_size + 1);
	CHECK(tcut1->processed_tracks == ntracks * (mixing_size + 1));
	CHECK(pcut_real->processed_pairs == ntracks * (ntracks - 1) / 2 * (mixing_size + 1));

	CHECK(emonPass->is_event_fill == true);
	CHECK(emonFail->is_event_fill == false);
	CHECK(tmonPass1->is_track_fill == true);
	CHECK(tmonFail1->is_track_fill == false);
	CHECK(pmonPass_real->is_pair_fill == true);
	CHECK(pmonFail_real->is_pair_fill == false);
	CHECK(pmonPass_imag->is_pair_fill == true);
	CHECK(pmonFail_imag->is_pair_fill == false);
	CHECK(corr1->called_add_real_pair == true);
	CHECK(corr1->called_add_mixed_pair == true);
}

TEST_CASE("test non-identical particle") {
	auto ana = new HbtAnalysis();
	auto mixing_size = rand() % 10 + 1;
	ana->SetEventMixingSize(mixing_size);

	// objects required for HbtAnalysis
	auto ecut = new mock_event_cut_();
	auto tcut1 = new mock_track_cut_();
	auto tcut2 = new mock_track_cut_();
	tcut1->setN(0);
	tcut1->setZ(1);
	tcut2->setN(1);
	tcut2->setZ(1);

	auto pcut_real = new mock_pair_cut_();
	auto pcut_mixed = new mock_pair_cut_();

	auto emonPass = new mock_monitor();
	auto emonFail = new mock_monitor();
	auto tmonPass1 = new mock_monitor();
	auto tmonFail1 = new mock_monitor();
	auto tmonPass2 = new mock_monitor();
	auto tmonFail2 = new mock_monitor();
	auto pmonPass_real = new mock_monitor();
	auto pmonFail_real = new mock_monitor();
	auto pmonPass_imag = new mock_monitor();
	auto pmonFail_imag = new mock_monitor();

	// any number of correlations can be added
	auto corr1 = new mock_correlation();

	ecut->SetPassMonitor(emonPass);
	ecut->SetFailMonitor(emonFail);
	tcut1->SetPassMonitor(tmonPass1);
	tcut1->SetFailMonitor(tmonFail1);
	tcut2->SetPassMonitor(tmonPass2);
	tcut2->SetFailMonitor(tmonFail2);
	pcut_real->SetPassMonitor(pmonPass_real);
	pcut_real->SetFailMonitor(pmonFail_real);
	pcut_mixed->SetPassMonitor(pmonPass_imag);
	pcut_mixed->SetFailMonitor(pmonFail_imag);

	ana->SetEventCut(ecut);
	ana->SetFirstTrackCut(tcut1);
	ana->SetRealPairCut(pcut_real);
	ana->SetMixedPairCut(pcut_mixed);
	ana->SetSecTrackCut(tcut2);
	ana->AddCorrelation(corr1);

	// generate events
	int ntracks1 = rand() % 10 + 2;
	int ntracks2 = rand() % 10 + 2;

	for (int in = 0; in <= mixing_size; in++) {
		auto evt = new HbtEvent();
		auto tcoll = evt->GetTrackCollection();
		for (int _ = 0; _ < ntracks1; ++_) {
			auto trk = new HbtTrack(0, 1, 938.272, 0., 0., 0.);
			tcoll->push_back(trk);
		}
		for (int _ = 0; _ < ntracks2; ++_) {
			auto trk = new HbtTrack(1, 1, 1876.124, 0., 0., 0.);
			tcoll->push_back(trk);
		}
		ana->Process(evt);
		delete evt;
	}

	CHECK(ecut->processed_events == mixing_size + 1);
	CHECK(tcut1->processed_tracks == (ntracks1 + ntracks2) * (mixing_size + 1));
	CHECK(tcut2->processed_tracks == (ntracks1 + ntracks2) * (mixing_size + 1));
	CHECK(pcut_real->processed_pairs == ntracks1 * ntracks2 * (mixing_size + 1));
}

TEST_CASE("check behaviour if no cuts are set") {
	auto ana = new HbtAnalysis();
	auto mixing_size = rand() % 10;
	ana->SetEventMixingSize(mixing_size);
	// only correlations are set
	auto corr1 = new mock_correlation();

	// generate events
	int ntracks = rand() % 10 + 2;
	for (int in = 0; in <= mixing_size; in++) {
		auto evt = new HbtEvent();
		auto tcoll = evt->GetTrackCollection();
		for (int _ = 0; _ < ntracks; ++_) {
			auto trk = new HbtTrack(0, 1, 938.272, 0., 0., 0.);
			tcoll->push_back(trk);
		}
		ana->Process(evt);
		delete evt;
	}
}
