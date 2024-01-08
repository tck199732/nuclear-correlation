// dev library
#include "HbtAnalysis.hpp"
#include "HbtManager.hpp"

// custom library
#include "Correlations/CustomCorrelation.hpp"
#include "Cuts/CustomEventCut.hpp"
#include "Cuts/CustomEventMonitor.hpp"
#include "Cuts/CustomPairCut.hpp"
#include "Cuts/CustomPairMonitor.hpp"
#include "Cuts/CustomTrackCut.hpp"
#include "Cuts/CustomTrackMonitor.hpp"
#include "Reader/CustomReader.hpp"

// external library
#include "argparse/argparse.hpp"
#include "indicators/block_progress_bar.hpp"
#include "indicators/cursor_control.hpp"
#include <indicators/progress_bar.hpp>
using namespace indicators;

// std library
#include <chrono>
#include <climits>

BlockProgressBar pbar{
	option::BarWidth{80},
	option::Start{"["},
	option::End{"]"},
	option::ForegroundColor{Color::white},
	option::FontStyles{std::vector<FontStyle>{FontStyle::bold}},
};
