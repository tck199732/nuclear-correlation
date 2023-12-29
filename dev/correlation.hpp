#ifndef correlation_hpp
#define correlation_hpp

#include "track.hpp"
class correlation {
public:
	correlation() = default;
	correlation(const correlation &corr) = default;
	correlation(correlation &&corr) = default;
	correlation &operator=(const correlation &corr) = default;
	correlation &operator=(correlation &&corr) = default;
	virtual ~correlation() = default;

	virtual void add_real_pair(const track *, const track *) = 0;
	virtual void add_mixed_pair(const track *, const track *) = 0;
};
#endif
