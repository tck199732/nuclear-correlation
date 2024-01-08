#ifndef HbtAnalysis_hpp
#define HbtAnalysis_hpp

#include <algorithm>
#include <deque>
#include <iostream>
#include <random>
#include <string>

#include "HbtCollection.hpp"
#include "HbtCorrelation.hpp"
#include "HbtEvent.hpp"
#include "HbtEventCut.hpp"
#include "HbtPairCut.hpp"
#include "HbtReader.hpp"
#include "HbtTempEvent.hpp"
#include "HbtTrack.hpp"
#include "HbtTrackCut.hpp"

class HbtAnalysis {
public:
	HbtAnalysis(const std::string &name = "", const int &mixing_size = 5);
	HbtAnalysis(const HbtAnalysis &);
	virtual ~HbtAnalysis();
	virtual void Process(const HbtEvent *evt);

	void SetEventMixingSize(const unsigned int &size);
	void SetEventCut(HbtEventCut *cut);
	void SetFirstTrackCut(HbtTrackCut *cut);
	void SetSecTrackCut(HbtTrackCut *cut);
	void SetRealPairCut(HbtPairCut *cut);
	void SetMixedPairCut(HbtPairCut *cut);
	void AddCorrelation(HbtCorrelation *corr);

	unsigned int GetEventMixingSize() const { return mEventMixingSize; }
	HbtEventCut *GetEventCut() const { return mEventCut; }
	HbtTrackCut *GetFirstTrackCut() const { return mFirstTrackCut; }
	HbtTrackCut *GetSecTrackCut() const { return mSecTrackCut; }
	HbtPairCut *GetRealPairCut() const { return mRealPairCut; }
	HbtPairCut *GetMixedPairCut() const { return mMixedPairCut; }
	HbtCorrelation *GetCorrelation(const unsigned int &index) const { return mCorrelationFunctions->at(index); }

protected:
	HbtTempEvent *PreProcess(const HbtEvent *evt);
	virtual void ClearMixingBuffer(); // action when the mixing buffer is full
	void SelectParticles(
		HbtTrackCut *&cut, HbtTrackCollection *&src, HbtTrackCollection *&des
	); // select passed tracks from src and Fill them into des
	void FillRealCorrelation(HbtTrackCollection *track1, HbtTrackCollection *track2 = 0);
	void FillMixedCorrelation(HbtTrackCollection *track1, HbtTrackCollection *track2);

	bool IsIdenticalAnalysis() const;
	bool IsMixingBufferFull() const;

	std::string mName;
	unsigned int mEventMixingSize;

	HbtEventCut *mEventCut;
	HbtTrackCut *mFirstTrackCut;
	HbtTrackCut *mSecTrackCut;
	HbtPairCut *mRealPairCut;
	HbtPairCut *mMixedPairCut;

	HbtCorrelationCollection *mCorrelationFunctions;
	HbtTempEventCollection *mMixingBuffer;
};

inline void HbtAnalysis::SetEventMixingSize(const unsigned int &size) { mEventMixingSize = size; }

inline void HbtAnalysis::SetEventCut(HbtEventCut *cut) { mEventCut = cut; }

inline void HbtAnalysis::SetFirstTrackCut(HbtTrackCut *cut) { mFirstTrackCut = cut; }

inline void HbtAnalysis::SetSecTrackCut(HbtTrackCut *cut) { mSecTrackCut = cut; }

inline void HbtAnalysis::SetRealPairCut(HbtPairCut *cut) { mRealPairCut = cut; }

inline void HbtAnalysis::SetMixedPairCut(HbtPairCut *cut) { mMixedPairCut = cut; }

inline void HbtAnalysis::AddCorrelation(HbtCorrelation *corr) { mCorrelationFunctions->push_back(corr); }

inline bool HbtAnalysis::IsIdenticalAnalysis() const { return mFirstTrackCut == mSecTrackCut; }

inline bool HbtAnalysis::IsMixingBufferFull() const {
	return mMixingBuffer->size() == static_cast<size_t>(mEventMixingSize);
}
#endif
