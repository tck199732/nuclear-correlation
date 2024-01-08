#ifndef HbtManager_hpp
#define HbtManager_hpp

#include "HbtAnalysis.hpp"
#include "HbtReader.hpp"

class HbtManager {
public:
	HbtManager();
	virtual ~HbtManager();
	int Process();

	void SetReader(HbtReader *HbtReader) { mReader = HbtReader; }
	void AddAnalysis(HbtAnalysis *anal) { mAnalysisCollection->push_back(anal); }

	HbtReader *GetReader() const { return mReader; }
	HbtAnalysisCollection *GetAnalysisCollection() const { return mAnalysisCollection; }

protected:
	HbtReader *mReader;
	HbtAnalysisCollection *mAnalysisCollection;
};

#endif