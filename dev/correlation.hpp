#ifndef correlation_hpp
#define correlation_hpp

class pair;
class correlation
{
public:
    correlation() = default;
    correlation(const correlation &corr) = default;
    virtual ~correlation() = default;
    virtual void add_real_pair(const pair* pr)  = 0;
    virtual void add_mixed_pair(const pair* pr) = 0;
};
#endif

 
 