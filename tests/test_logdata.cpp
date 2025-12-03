#include "../src/DwellLogData.h"
#include "../helpers/LoadCSV.h"
#include <cassert>
#include <iostream>

using namespace std;

//Write unit tests for Dwell Log (Review Linked List Test)
    //Append/Init
    //Clear
    //TODO: Sort by Time
    //TODO: Sort by Catheter/
    
void test_append() 
{
    DwellLog log;
    //Test Data
    DwellRow r = {110, "F001", 1, 0, 7.0, 6.8, 0.10, "TUMOR"};
    log.append_data(r);

    assert(log.size() == 1);
    assert(log.head()->time_ms == 110);
    assert(log.head() == log.tail());
}

void test_clear() 
{
    DwellLog log;
    //Test Data
    log.append_data({110, "F001", 1, 0, 7, 6.8, 0.1, "TUMOR"});
    log.append_data({210, "F001", 1, 1, 6.5, 6.6, 0.1, "TUMOR"});

    log.clear();

    assert(log.size() == 0);
    assert(log.head() == NULL);
    assert(log.tail() == NULL);
}

//Write unit tests for CSV File load
void test_load_csv() 
{
    DwellLog log;
    bool ok = load_dwell_log_data("../include/test_data.csv", log);

    //cout << "*****DEBUGGER*****: log.size() = " << log.size() << endl;
    assert(ok == true);
    assert(log.size() == 10);
}

//TODO: Write unit tests for LQ Model analysis functions
    //TBD on specifics: ****NOTE AS FUNCTIONS ARE WRITTEN****

int main() {
    cout << "Running tests\n";

    test_append();
    test_clear();
    test_load_csv();

    cout << "Tests passed sucessfully!\n";
    return 0;
}