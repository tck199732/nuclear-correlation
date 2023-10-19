#ifndef monitor_hpp
#define monitor_hpp

class event;
class track;
class pair;
class monitor {
public:
	monitor() = default;
	monitor(const monitor &) = default;
	virtual ~monitor() = default;
	virtual void report() = 0;
	virtual void fill(const event *) { ; }
	virtual void fill(const track *) { ; }
	virtual void fill(const pair *) { ; }
};
#endif