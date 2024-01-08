#include "CustomEventCut.hpp"
CustomEventCut::CustomEventCut() {
	mPassEvents = 0;
	mFailEvents = 0;
	mMultiplicityRange = {1, INT_MAX};
	mImpactParamRange = {0.0, DBL_MAX};
}

bool CustomEventCut::Pass(const HbtEvent *HbtEvent) {
	auto multi = static_cast<int>(HbtEvent->GetMultiplicity());
	auto b = HbtEvent->GetImpactParameter();
	auto pass = (multi >= mMultiplicityRange[0] && multi <= mMultiplicityRange[1]);
	pass = pass && (b >= mImpactParamRange[0] && b <= mImpactParamRange[1]);

	pass ? mPassEvents++ : mFailEvents++;
	return pass;
}
