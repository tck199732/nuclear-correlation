#include "CustomCorrelation.hpp"

CustomCorrelation::CustomCorrelation(const std::string &mName) :
	mName(mName),
	mNumerator(nullptr),
	mDenominator(nullptr) {}

CustomCorrelation::CustomCorrelation(
	const std::string &mName, const int &bins, const double &vmin, const double &vmax
) :
	mName(mName) {

	mNumerator = new TH1D((mName + "Num").c_str(), "", bins, vmin, vmax);
	mDenominator = new TH1D((mName + "Den").c_str(), "", bins, vmin, vmax);
	mNumerator->Sumw2();
	mDenominator->Sumw2();
	mNumerator->SetDirectory(0);
	mDenominator->SetDirectory(0);
}

CustomCorrelation::CustomCorrelation(const CustomCorrelation &other) {
	mName = other.mName;
	mNumerator = (TH1D *)other.mNumerator->Clone((other.mName + "Num").c_str());
	mDenominator = (TH1D *)other.mDenominator->Clone((other.mName + "Den").c_str());
}

CustomCorrelation::~CustomCorrelation() {
	if (mNumerator) {
		delete mNumerator;
	}
	if (mDenominator) {
		delete mDenominator;
	}
}

double CustomCorrelation::CalcRelativeMomentum(const HbtTrack *track1, const HbtTrack *track2) {
	auto px1 = track1->GetPx(), px2 = track2->GetPx();
	auto py1 = track1->GetPy(), py2 = track2->GetPy();
	auto pz1 = track1->GetPz(), pz2 = track2->GetPz();
	auto e1 = track1->GetE(), e2 = track2->GetE();

	auto p1 = physics::four_vector(px1, py1, pz1, e1);
	auto p2 = physics::four_vector(px2, py2, pz2, e2);

	auto P = p1 + p2;
	auto q = physics::relative_four_vector(p1, p2);
	q.boost(P.beta_x(), P.beta_y(), P.beta_z());
	return q.Mag();
}

void CustomCorrelation::FillRealCorrelation(const HbtTrack *track1, const HbtTrack *track2) {
	mNumerator->Fill(CalcRelativeMomentum(track1, track2), 1.);
}

void CustomCorrelation::FillMixedCorrelation(const HbtTrack *track1, const HbtTrack *track2) {
	mDenominator->Fill(CalcRelativeMomentum(track1, track2), 1.);
}
