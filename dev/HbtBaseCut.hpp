#ifndef HbtBaseCut_hpp
#define HbtBaseCut_hpp

#include "HbtEvent.hpp"
#include "HbtMonitor.hpp"
#include "HbtTrack.hpp"
class HbtBaseCut {
public:
	HbtBaseCut();
	HbtBaseCut(const HbtBaseCut &);
	virtual ~HbtBaseCut();

	// Fill HbtMonitor only if it is not nullptr
	void FillMonitor(const HbtEvent *evt, bool Pass);
	void FillMonitor(const HbtTrack *trk, bool Pass);
	void FillMonitor(const HbtTrack *track1, const HbtTrack *track2, bool Pass);

	void SetPassMonitor(HbtMonitor *mon) { mPassMonitor = mon; }
	void SetFailMonitor(HbtMonitor *mon) { mFailMonitor = mon; }

	HbtMonitor *GetPassMonitor() const { return mPassMonitor; }
	HbtMonitor *GetFailMonitor() const { return mFailMonitor; }

protected:
	HbtMonitor *mPassMonitor;
	HbtMonitor *mFailMonitor;
};

#endif
