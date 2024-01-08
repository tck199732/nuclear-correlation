#ifndef CustomEventCut_hpp
#define CustomEventCut_hpp

#include <array>
#include <cfloat>
#include <climits>
#include <string>

#include "HbtEvent.hpp"
#include "HbtEventCut.hpp"

class CustomEventCut : public HbtEventCut {
public:
	CustomEventCut();
	CustomEventCut(const CustomEventCut &);
	virtual bool Pass(const HbtEvent *) override;

	void SetMultiplicityRange(const int &vmin, const int &vmax);
	void SetImpactParamRange(const double &vmin, const double &vmax);

	std::array<int, 2> GetMultiplicityRange() const { return mMultiplicityRange; }
	std::array<double, 2> GetImpactParamRange() const { return mImpactParamRange; }

	long GetPassEvents() const { return mPassEvents; }
	long GetFailEvents() const { return mFailEvents; }

private:
	std::array<int, 2> mMultiplicityRange;
	std::array<double, 2> mImpactParamRange;
	long mPassEvents, mFailEvents;
};

inline void CustomEventCut::SetMultiplicityRange(const int &vmin, const int &vmax) {
	mMultiplicityRange = {vmin, vmax};
}

inline void CustomEventCut::SetImpactParamRange(const double &vmin, const double &vmax) {
	mImpactParamRange = {vmin, vmax};
}

#endif