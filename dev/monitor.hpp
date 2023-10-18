#ifndef monitor_hpp
#define monitor_hpp

class event;
class track;
class pair;
class monitor
{
public:
    monitor() = default;
    monitor(const monitor &) = default;
    virtual ~monitor() = default;
    virtual void report() = 0;
    virtual void Fill(const event *) = 0;
    virtual void Fill(const track *) = 0;
    virtual void Fill(const pair *) = 0;
};
#endif