#ifndef ANALYSIS_H_
#define ANALYSIS_H_

#include "DwellLogData.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Analysis {
public:
    Analysis();
    ~Analysis();

    //LQ Model Calculation
    double compute_cell_survival_rate(double dose_Gy, double a, double b);
    
    //Apply to Dwell Log
    void apply_lq_to_log(const DwellLog& log, double a, double b);
    
    //Compare predicted vs Actual
    void compare_predicted_actual(const DwellLog& predicted, const DwellLog& actual, ostream& os = cout);

    //Print analysis to a seperate file (Add Graph is time allows)
    void print_analysis(ostream& os = cout);

    //APPLY MERGESORT
    void sort_by_time(DwellLog& log);
    void sort_by_catheter_index(DwellLog& log);

    //Merge Sort
    //mode 1: Sort by Time
    //mode 2: Sort by Catheter and Index
    DwellNode* mergesort(DwellNode* start, int mode);

    // merge is the helper function for mergesort.
    DwellNode* merge(DwellNode* a, DwellNode* b, int mode);

private:
    struct LQSummary {
        string fraction_id;
        int catheter;
        int dwell_index;
        double dose;
        double survival;
    };
    vector<LQSummary> summarys_;
};

#endif