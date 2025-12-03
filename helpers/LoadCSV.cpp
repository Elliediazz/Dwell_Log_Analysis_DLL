#include "LoadCSV.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

bool load_dwell_log_data(const string& filename, DwellLog& log) 
{
    // Load/parse CSV FILES
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening: "<< filename << endl;
        return false;
    }

    string line; 

    //REMEBER: skip the header line!!!
    getline(file, line);

    while(getline(file, line)) 
    {
        stringstream ss(line);
        string temp;
        DwellRow row;

        if(!getline(ss, temp, ',')) continue;
        row.time_ms = stod(temp);

        if (!getline(ss, row.fraction_id, ',')) continue;
        
        if(!getline(ss, temp, ',')) continue;
        row.catheter_id = stoi(temp);

        if (!getline(ss, temp, ',')) continue;
        row.dwell_index = stoi(temp);

        if (!getline(ss, temp, ',')) continue;
        row.planned_dwell_s = stod(temp);

        if (!getline(ss, temp, ',')) continue;
        row.delivered_dwell_s = stod(temp);

        if (!getline(ss, temp, ',')) continue;
        row.dose_rate_Gy_per_s = stod(temp);

        if (!getline(ss, row.region_id, ',')) 
        {
            row.region_id = "";
        }

        log.append_data(row);
    }

    return true;
}
