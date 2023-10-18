#ifndef base_cut_hpp
#define base_cut_hpp

#include "monitor.hpp"
#include "event.hpp"
#include "track.hpp"
#include "pair.hpp"
class base_cut {
    public:
    base_cut();
    base_cut(const base_cut &);
    virtual ~base_cut();

    void fill_monitor(const event *evt, bool pass);
    void fill_monitor(const track *trk, bool pass);
    void fill_monitor(const pair *pr, bool pass);

    void set_passed_monitor(monitor *mon) { this->passed_monitor = mon; }
    void set_failed_monitor(monitor *mon) { this->failed_monitor = mon; }

    monitor* get_passed_monitor() const { return this->passed_monitor; }
    monitor* get_failed_monitor() const { return this->failed_monitor; }

private:
    monitor *passed_monitor;
    monitor *failed_monitor;
};

#endif
