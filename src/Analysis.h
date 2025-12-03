#ifndef ANALYSIS_H__
#define ANALYSIS_H__
 
#include "DwellLogData.h"
#include <string>

using namespace std;

class Analysis {
public:
    Analysis();
    ~Analysis();

    //TODO: LQ Model Calculation

    //TODO: Apply to Dwell Log

    //TODO: Compare predicted vs Actual

    //TODO: Print analysis (Add Graph is time allows)

    //TODO: APPLY MERGESORT
    void sortByTime();
    void sortByCatheterAndIndex();

    //Merge Sort
    //mode 1: Sort by Time
    //mode 2: Sort by Catheter and Index
    void mergesort(DwellNode* start, int mode);

    // merge is the helper function for mergesort.
    void merge(DwellNode* a, DwellNode* b, int mode);

};

#endif