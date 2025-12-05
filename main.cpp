#include <fstream>
#include <sstream>
#include <iostream>

#include "LoadCSV.h"
#include "DwellLogData.h"
#include "Analysis.h"

using namespace std;

int main () 
{
    cout << "Dwell Log Analysis\n";
    
    // Load CSV file - predicted log initially 
    string input_file;
    cout << "Please enter CSV file for the predicted dwell log:";
    cin >> input_file;

    DwellLog predicted_log;

    if (!load_dwell_log_data(input_file, predicted_log))
    {
        cout << "Failed to load\n";
        return 0;
    }

    cout << "Successfully loaded predicted dwell log from '" << input_file << "'\n";
    cout << "Loaded events: " << predicted_log.size() << "\n";

    DwellLog actual_log;
    bool actual_log_loaded = false;

    Analysis analysis; 

    while (true) 
    {
        cout << " MAIN MENU \n";
        cout << "1) Load a different CSV file\n";
        cout << "2) Print current predicted dwell log\n";
        cout << "3) Clear dwell log data\n";
        cout << "4) Apply Merge Sort\n";
        cout << "5) Apply LQ Model\n";
        cout << "6) Compare predicted vs actual logs\n";
        cout << "Q) Quit\n";
        cout << "Enter menu selection (Q to quit): ";


        string process_choice;
        cin >> process_choice;
        
        if ( process_choice == "Q" || process_choice == "q")
        {
            cout << "Quitting..." << endl;
            return 0;
        }

        int choice = stoi(process_choice); 

        cout << choice << " selected \n";

        // string output_file;
        // cout << "Please Enter output file:";
        // cin >> output_file;

        if(choice == 1) 
        {
            cout << "Enter a new predicted dwell log CSV file: ";
            string new_file;
            cin >> new_file;

            predicted_log.clear();

            if (!load_dwell_log_data(new_file, predicted_log)) 
            {
                cout << "Failed to load '" << new_file << "'. Pedicted Dwell log is empty.\n";
            } else 
            {
                cout << "Successfully loaded predicted dwell log from '" << new_file << "'\n";
                cout << "Loaded events: " << predicted_log.size() << "\n";
                cout << "Dwell Log:\n";
                predicted_log.print_table();
            }
        }
        else if(choice == 2) 
        {
            cout << "Current predicted Dwell Log Data - Loaded events:" << predicted_log.size() << "\n";
            predicted_log.print_table();
        }
        else if(choice == 3) 
        {
            predicted_log.clear();
            cout << "predicted dwell log data has been cleared. Loaded events:" << predicted_log.size() << "\n";
        }
        else if(choice == 4) 
        {
            if (predicted_log.size() == 0) {
                cout << "predicted dwell log is empty. Please load a CSV file.\n";
                continue;
            }

            cout << "Select sort mode:\n";
            cout << "  1) Sort by time\n";
            cout << "  2) Sort by catheter_id + dwell_index\n";
            cout << "Enter choice: ";

            int sort_choice;
            cin >> sort_choice;

            if (sort_choice == 1) {
                cout << "Sorting predicted dwell log by time\n";
                analysis.sort_by_time(predicted_log);
                cout << "Done. Sorted dwell log:\n";
                predicted_log.print_table();
            } else if (sort_choice == 2) {
                cout << "Sorting by catheter_id + dwell_index\n";
                analysis.sort_by_catheter_index(predicted_log);
                cout << "Sorted dwell log:\n";
                predicted_log.print_table();
            } else {
                cout << "Invalid sort choice, please choose mode 1 or mode 2.\n";
            }
        }
        else if(choice == 5) 
        {
            if (predicted_log.size() == 0) {
                cout << "predicted dwell log is empty. Please load a CSV file.\n";
                continue;
            }

            double alpha, beta;
            cout << "Enter alpha (example: 0.25): ";
            cin >> alpha;
            cout << "Enter beta (example: 0.03): ";
            cin >> beta;

            cout << "\n Running LQ analysis on predicted dwell log \n";
            analysis.apply_lq_to_log(predicted_log, alpha, beta);

            cout << "\n LQ summary:\n";
            analysis.print_analysis(cout);

            cout << "Would you like to save this LQ summary to a file? (y/n): ";
            char save_choice;
            cin >> save_choice;

            if (save_choice == 'y' || save_choice == 'Y') {
                string output_file;
                cout << "Enter output filename (ex: lq_summary.txt): ";
                cin >> output_file;

                ofstream ofs(output_file);
                if (!ofs.is_open()) {
                    cout << "Error: could not open '" << output_file << "' for writing.\n";
                } else {
                    analysis.print_analysis(ofs);
                    cout << "LQ summary written to '" << output_file << "'.\n";
                }
            }

        }
        else if(choice == 6) 
        {
            if (predicted_log.size() == 0) {
                cout << "predicted dwell log is empty. Please load a CSV file.\n";
                continue;
            }

            // If actual log has not been loaded yet, upload now5
            if (!actual_log_loaded || actual_log.size() == 0) {
                cout << "No actual dwell log loaded, Please enter CSV file for actual dwell log:\n";
                string actual_file;
                cin >> actual_file;

                actual_log.clear();

                if (!load_dwell_log_data(actual_file, actual_log)) {
                    cout << "Failed to load actual dwell log from '" << actual_file << "'.\n";
                    actual_log_loaded = false;
                    continue;
                } else {
                    actual_log_loaded = true;
                    cout << "Successfully loaded actual dwell log from '" 
                         << actual_file << "'\n";
                    cout << "Loaded events: " << actual_log.size() << "\n";
                }
            }

            cout << "Sorting both predicted and actual logs by catheter_id + dwell_index: before comparison \n";
            analysis.sort_by_catheter_index(predicted_log);
            analysis.sort_by_catheter_index(actual_log);

            cout << "\nRunning comparison of predicted vs actual dwell logs \n\n";
            analysis.compare_predicted_actual(predicted_log, actual_log);

            cout << "\nWould you like to save this comparison to a file? (y/n): ";
            char save_choice;
            cin >> save_choice;

            if (save_choice == 'y' || save_choice == 'Y') {
                string output_file;
                cout << "Enter output filename (ex: comparison_report.txt): ";
                cin >> output_file;

                ofstream ofs(output_file);
                if (!ofs.is_open()) {
                    cout << "Error: could not open '" << output_file << "' for writing.\n";
                } else {
                    analysis.compare_predicted_actual(predicted_log, actual_log, ofs);
                    cout << "Comparison report can be found in: '" << output_file << "'.\n";
                }
            }
        }
        else 
        {
            cout << "Invalid menu option. Please select 1–6 or Q to quit.\n";
        }
    }
    return 0;
}