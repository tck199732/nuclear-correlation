#ifndef collection_hpp
#define collection_hpp

#include <deque>
#include <vector>

class fevent;
class track;
class correlation;
class analysis;
class monitor;
class base_cut;

typedef std::deque<fevent *> fevent_collection;
typedef std::vector<track *> track_collection;
typedef std::vector<analysis *> analysis_collection;
typedef std::vector<correlation *> correlation_collection;
typedef std::vector<monitor *> monitor_collection;
typedef std::vector<base_cut *> cut_collection;

#endif
