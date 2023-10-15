#ifndef track_cut_hpp
#define track_cut_hpp

class track;
class track_cut 
{
public:
    track_cut() {};
    track_cut(const track_cut &);
    virtual ~track_cut(){};
    virtual bool pass(const track *trk) = 0;
};

#endif