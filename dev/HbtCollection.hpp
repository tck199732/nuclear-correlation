#ifndef HbtCollection_hpp
#define HbtCollection_hpp

#include <deque>
#include <vector>

class HbtTempEvent;
class HbtTrack;
class HbtCorrelation;
class HbtAnalysis;
class HbtMonitor;
class HbtBaseCut;

typedef std::deque<HbtTempEvent *> HbtTempEventCollection;
typedef std::vector<HbtTrack *> HbtTrackCollection;
typedef std::vector<HbtAnalysis *> HbtAnalysisCollection;
typedef std::vector<HbtCorrelation *> HbtCorrelationCollection;
typedef std::vector<HbtMonitor *> HbtMonitorCollection;
typedef std::vector<HbtBaseCut *> HbtCutCollection;

#endif
