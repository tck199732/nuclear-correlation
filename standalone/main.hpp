// dev library
#include "analysis.hpp"
#include "manager.hpp"

// custom library
#include "correlations/custom_correlation.hpp"
#include "cuts/custom_event_cut.hpp"
#include "cuts/custom_event_monitor.hpp"
#include "cuts/custom_pair_cut.hpp"
#include "cuts/custom_pair_monitor.hpp"
#include "cuts/custom_track_cut.hpp"
#include "cuts/custom_track_monitor.hpp"
#include "readers/custom_reader.hpp"

// external library
#include "argparse/argparse.hpp"
#include "indicators/block_progress_bar.hpp"
#include "indicators/cursor_control.hpp"
#include <indicators/progress_bar.hpp>
using namespace indicators;

BlockProgressBar pbar{option::BarWidth{80}, option::Start{"["}, option::End{"]"},
					  option::ForegroundColor{Color::white},
					  option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}};
