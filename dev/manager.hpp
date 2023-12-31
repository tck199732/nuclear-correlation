#ifndef manager_hpp
#define manager_hpp

#include "analysis.hpp"
#include "reader.hpp"
class manager {
public:
	manager();
	virtual ~manager();
	int process();

	void set_reader(reader *reader) { event_reader = reader; }
	void add_analysis(analysis *anal) { analyses->push_back(anal); }

	reader *get_reader() const { return event_reader; }
	analysis_collection *get_analyses() const { return analyses; }

protected:
	reader *event_reader;
	analysis_collection *analyses;
};

#endif