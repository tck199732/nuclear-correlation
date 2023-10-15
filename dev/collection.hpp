#ifndef collection_hpp
#define collection_hpp

#include <vector>
#include <deque>

class fevent;
class event;
class particle;
class track;
class correlation;
class analysis;

typedef std::deque<fevent*> fevent_collection;
typedef std::vector<particle*> particle_collection;
typedef std::vector<track*> track_collection;
typedef std::vector<correlation*> correlation_collection;
typedef std::vector<analysis*> analysis_collection;

#endif
