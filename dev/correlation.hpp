#ifndef correlation_hpp
#define correlation_hpp

#include "track.hpp"
class correlation {
public:
	correlation() = default;
	correlation(const correlation &corr) = default;
	virtual ~correlation() = default;
	virtual void add_real_pair(const std::pair<track *, track *> &pr) = 0;
	virtual void add_mixed_pair(const std::pair<track *, track *> &pr) = 0;
};
#endif
