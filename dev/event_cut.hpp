#ifndef event_cut_hpp
#define event_cut_hpp

class event;
class event_cut
{
public:
    event_cut(){};
    event_cut(const event_cut &);
    virtual ~event_cut(){};
    virtual bool pass(const event *event) = 0;
};
#endif
