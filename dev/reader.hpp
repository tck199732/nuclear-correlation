#ifndef reader_hpp
#define reader_hpp

class event;
class reader {
public:
	reader() = default;
	reader(const reader &r) = default;
	reader(reader &&r) = default;
	reader &operator=(const reader &r) = default;
	virtual ~reader() = default;
	virtual event *return_event() = 0;
	unsigned int get_status() const { return status; }

protected:
	// status = 0: success; user should define other status ID.
	unsigned int status = 0;
};

#endif