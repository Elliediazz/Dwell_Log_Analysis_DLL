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
    
    // Load CSV file 
    string input_file;
    cout << "Please enter CSV file:";
    cin >> input_file;

    DwellLog log;

    if (!load_dwell_log_data(input_file, log))
    {
        cout << "Failed to load\n";
        return 0;
    }

    cout << "Successfully loaded dwell predicted log from '" << input_file << "'\n";
    cout << "Loaded events: " << log.size() << "\n";

    Analysis analysis; 

    while (true) 
    {
        cout << " MAIN MENU \n";
        cout << "1) Load a different CSV file\n";
        cout << "2) Print current dwell log\n";
        cout << "3) Clear dwell log data\n";
        cout << "4) Apply Merge Sort\n";
        cout << "5)TODO: Apply LQ Model\n";
        cout << "6)TODO: Compare predicted vs actual logs\n";
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
            cout << "Enter a new CSV file: ";
            string new_file;
            cin >> new_file;

            log.clear();

            if (!load_dwell_log_data(new_file, log)) 
            {
                cout << "Failed to load '" << new_file << "'. Dwell log is now empty.\n";
            } else 
            {
                cout << "Successfully loaded dwell log from '" << new_file << "'\n";
                cout << "Loaded events: " << log.size() << "\n";
                cout << "Dwell Log:\n";
                log.print_table();
            }
        }
        else if(choice == 2) 
        {
            cout << "Current Dwell Log Data - Loaded events:" << log.size() << "\n";
            log.print_table();
        }
        else if(choice == 3) 
        {
            log.clear();
            cout << "Dwell log data has been cleared. Loaded events:" << log.size() << "\n";
        }
        else if(choice == 4) 
        {
            if (log.size() == 0) {
                cout << "Dwell log is empty. Please load a CSV file.\n";
                continue;
            }

            cout << "Select sort mode:\n";
            cout << "  1) Sort by time\n";
            cout << "  2) Sort by catheter_id + dwell_index\n";
            cout << "Enter choice: ";

            int sort_choice;
            cin >> sort_choice;

            if (sort_choice == 1) {
                cout << "Sorting by time\n";
                analysis.sort_by_time(log);
                cout << "Done. Sorted dwell log:\n";
                log.print_table();
            } else if (sort_choice == 2) {
                cout << "Sorting by catheter_id + dwell_index\n";
                analysis.sort_by_catheter_index(log);
                cout << "Done. Sorted dwell log:\n";
                log.print_table();
            } else {
                cout << "Invalid sort choice, please choose mode 1 or mode 2.\n";
            }
        }
        else if(choice == 5) 
        {
            cout << "TODO: Apply LQ Model.\n";
        }
        else if(choice == 6) 
        {
            cout << "TODO: Compare predicted vs actual logs.\n";
        }
        else 
        {
            cout << "Invalid menu option. Please select 1–6 or Q to quit.\n";
        }
    }
    return 0;
}