#ifndef HbtReader_hpp
#define HbtReader_hpp

class HbtEvent;
class HbtReader {
public:
	HbtReader() = default;
	HbtReader(const HbtReader &r) = default;
	HbtReader(HbtReader &&r) = default;
	HbtReader &operator=(const HbtReader &r) = default;
	virtual ~HbtReader() = default;
	virtual HbtEvent *ReturnHbtEvent() = 0;
	unsigned int GetStatus() const { return mStatus; }

protected:
	// mStatus = 0: success; user should define other mStatus ID.
	unsigned int mStatus = 0;
};

#endif