#ifndef ANALYSIS_H__
#define ANALYSIS_H__
 
#include <string>
#include "DwellLogData.h"

using namespace std;

bool load_dwell_log_data(const string& filename, DwellLog& log);

#endif