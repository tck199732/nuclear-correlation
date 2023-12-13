#ifndef monitor_hpp
#define monitor_hpp

class event;
class track;
class monitor {
public:
	monitor() = default;
	monitor(const monitor &) = default;
	virtual ~monitor() = default;
	virtual void report() = 0;
	virtual void fill(const event *) = 0;
	virtual void fill(const track *) = 0;
	virtual void fill(const track *, const track *) = 0;
};
#endif