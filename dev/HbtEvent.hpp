#ifndef HbtEvent_hpp
#define HbtEvent_hpp

#include "HbtCollection.hpp"
#include "HbtProperty.hpp"
#include "HbtTrack.hpp"

class HbtEvent : public HbtProperty {
public:
	HbtEvent();
	HbtEvent(const HbtEvent &ev);
	HbtEvent(HbtEvent &&ev) = default;
	HbtEvent &operator=(const HbtEvent &ev) = default;
	HbtEvent &operator=(HbtEvent &&ev) = default;
	virtual ~HbtEvent();
	HbtTrackCollection *GetTrackCollection() const { return mTrackCollection; }

	void SetMultiplicity(const unsigned int &mult);
	void SetMultiplicity4Pi(const unsigned int &mult);
	void SetImpactParameter(const double &b);

	unsigned int GetMultiplicity() const { return mMultiplicity; }
	unsigned int GetMultiplicity4Pi() const { return mMultiplicity4Pi; }
	double GetImpactParameter() const { return mImpactParameter; }

protected:
	unsigned int mMultiplicity, mMultiplicity4Pi;
	double mImpactParameter;
	HbtTrackCollection *mTrackCollection;
};

inline void HbtEvent::SetMultiplicity(const unsigned int &mult) { mMultiplicity = mult; }

inline void HbtEvent::SetMultiplicity4Pi(const unsigned int &mult) { mMultiplicity4Pi = mult; }

inline void HbtEvent::SetImpactParameter(const double &b) { mImpactParameter = b; }
#endif