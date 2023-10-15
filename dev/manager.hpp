#ifndef manager_hpp
#define manager_hpp

#include "reader.hpp"
#include "analysis.hpp"
class manager
{
public:
    manager();
    virtual ~manager();
    void set_reader(reader * reader) { event_reader = reader; }
    void add_analysis(analysis * anal) { analyses->push_back(anal);}
    int process();

private:
    reader *event_reader;
    analysis_collection *analyses;
};

#endif