#ifndef HbtMonitor_hpp
#define HbtMonitor_hpp

class HbtEvent;
class HbtTrack;
class HbtMonitor {
public:
	HbtMonitor() = default;
	HbtMonitor(const HbtMonitor &) = default;
	virtual ~HbtMonitor() = default;
	virtual void Report() = 0;
	virtual void Fill(const HbtEvent *) = 0;
	virtual void Fill(const HbtTrack *) = 0;
	virtual void Fill(const HbtTrack *, const HbtTrack *) = 0;
};
#endif