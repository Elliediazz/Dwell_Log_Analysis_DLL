#ifndef DWELLLOG_H__
#define DWELLLOG_H__
 
#include <string>

using namespace std;

struct DwellNode {
  long time_ms;
  string fraction_id;
  int catheter_id;
  int dwell_index;
  double planned_dwell_s;
  double delivered_dwell_s;
  double dose_rate_Gy_per_s;
  string region_id;

  DwellNode* next; // points to the next node, or NULL if this is the last node.
  DwellNode* prev; // points to the previous node, or NULL if this is the head node.
};



class DwellLog {
public:
  // Constructor. Initialize class variables and pointers here if need. Initially set top pointer to null.
  DwellLog();

  // Deconstructor. Can probably leave this empty because we use bare pointers (node*), and you must reclaim heap memory immediately when that memory is no longer used.
  ~DwellLog();

  bool empty() const;
  int size() const;

  //Create a new DwellNode on the heap with given data
  DwellNode* init_node(
                    long time_ms,
                    string fraction_id,
                    int catheter_id,
                    int dwell_index,
                    double planned_dwell_s,
                    double delivered_dwell_s,
                    double dose_rate_Gy_per_s,
                    string region_id);

  // Append adds the data points to the end of the list.
  void append(DwellNode* new_node);

  void clear();

  // Returns the data associated with a fraction number,
  // false otherwise.
  string contains(string fraction);

  // For traversal
  DwellNode* head() const;
  DwellNode* tail() const;

  void sortByTime();
  void sortByCatheterAndIndex();

  //Merge Sort
  //mode 1: Sort by Time
  //mode 2: Sort by Catheter and Index
  void mergesort(DwellNode* start, int mode);

// merge is the helper function for mergesort.
  void merge(DwellNode* a, DwellNode* b, int mode);

private:
  DwellNode* head_;
  DwellNode* tail_;
  int size_;
};

#endif