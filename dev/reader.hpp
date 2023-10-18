#ifndef reader_hpp
#define reader_hpp

class event;
class reader
{
public:
    reader() = default;
    virtual ~reader() = default;
    virtual event *return_event() = 0;
    unsigned int  get_status() const {return status;}

protected:
    unsigned int status;
};

#endif