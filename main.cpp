#include <fstream>
#include <sstream>
#include <iostream>

#include "./helpers/LoadCSV.h"
#include "DwellLogData.h"
#include "Analysis.h"

using namespace std;

int main () {
    cout << "Dwell Log Analysis\n";
    
    // Load CSV file 
    string input_file;
    cout << "Please enter CSV file:";
    cin >> input_file;

    DwellLog log;

    if (!load_dwell_log_data(input_file, log)){
        cout << "Failed to load\n";
        return 0;
    }

    cout << "Successfully loaded dwell predicted log from '" << input_file << "'\n";
    cout << "Loaded events: " << log.size() << "\n";
    cout << "Dwell Log:\n";
    log.print_table();


    //Analysis analysis; 
    //DWELL LOG DATA .CPP is done.
    //***NEXT: connect the uploaded file into the data structure***

    //TODO: Display Main Menu & allow user to make a choice
        //Allow the user to exit gracefully

    //TODO: Write methods to handle menu choices
        //Handle Invalid choice
        //Load CSV
        //Apply Mergesort
        //Apply LQ Model
        //Do caparison analysis on the logs

    return 0;
}