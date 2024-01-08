#ifndef CustomReader_hpp
#define CustomReader_hpp

#include <array>
#include <cfloat>
#include <filesystem>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

// root libraries
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

// utlities and base classes
#include "HbtEvent.hpp"
#include "HbtReader.hpp"
#include "HbtTrack.hpp"
#include "ame/ame.hpp"

constexpr int MAX_MULTI = 128;
struct Branches {
	double b;
	std::array<int, MAX_MULTI> N;
	std::array<int, MAX_MULTI> Z;
	// momentum per nucleon
	std::array<double, MAX_MULTI> px;
	std::array<double, MAX_MULTI> py;
	std::array<double, MAX_MULTI> pz;
};

class CustomReader : public HbtReader {
public:
	CustomReader();
	CustomReader(const std::string &mTreeName, const std::vector<std::string> &filenames);
	CustomReader(const CustomReader &HbtReader) = delete;
	~CustomReader();
	HbtEvent *ReturnHbtEvent();
	void SetTreeName(const std::string &mTreeName);
	void SetFileNames(const std::vector<std::string> &filenames);
	void AddFile(const std::string &file_path);

	double GetEntries() const { return mChain->GetEntries(); }
	std::string GetTreeName() const { return mTreeName; }
	std::vector<std::filesystem::path> GetFileNames() const { return mFilePaths; }

private:
	// random generators for making fake detector IDs
	std::random_device mRdnDevice;
	std::mt19937 mGenerator;

	// for reading ROOT files
	TChain *mChain;
	std::string mTreeName;
	std::vector<std::filesystem::path> mFilePaths;
	Branches mBranches;
	long mCurrEventIndex;

	HbtEvent *ReadEvent();
	void SetBranches(TChain *&mChain);
	void BeginEvent();
	void EndEvent();
};

inline void CustomReader::SetTreeName(const std::string &name) { mTreeName = name; }

inline void CustomReader::SetFileNames(const std::vector<std::string> &filenames) { mFilePaths = mFilePaths; }

inline void CustomReader::AddFile(const std::string &file_path) { mFilePaths.push_back(file_path); }

#endif
