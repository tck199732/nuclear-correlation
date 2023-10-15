#ifndef correlation_hpp
#define correlation_hpp

class pair;
class correlation
{
public:
    correlation() { ; }
    correlation(const correlation &corr) { ; }
    virtual ~correlation() { ; }    
    virtual void add_real_pair(const pair* pr)  = 0;
    virtual void add_mixed_pair(const pair* pr) = 0;
};
#endif

 
 