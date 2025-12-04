#ifndef DWELLLOGDATA_H_
#define DWELLLOGDATA_H_

#include <string>

using namespace std;

struct DwellNode 
{
  double time_ms;
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

struct DwellRow 
{
  double time_ms;
  string fraction_id;
  int catheter_id;
  int dwell_index;
  double planned_dwell_s;
  double delivered_dwell_s;
  double dose_rate_Gy_per_s;
  string region_id;
};

class DwellLog {
public:
  // Constructor. Initialize class variables and pointers here if need. Initially set top pointer to null.
  DwellLog();

  // Deconstructor. Can probably leave this empty because we use bare pointers (node*), and you must reclaim heap memory immediately when that memory is no longer used.
  ~DwellLog();

  int size() const;
  void print_table() const;


  //Initialize a new DwellNode on the heap with given data
  DwellNode* init_node(const DwellRow& row);

  // Append adds the data points to the end of the list.
  void append_data(const DwellRow& row);

  // Append is the same as AppendData, except we're adding a node, rather than a value.
  void append(DwellNode* new_node);

  // TODO: InsertData inserts a new node that contains the given data value - Inserting at the end of the list should have the same effect as appending.
  void insert_data(int index, const DwellRow& row);

  // TODO: This is the same as insert_data, except we're inserting a node, rather than a value. This closely mirrors Append and AppendData.
  void insert(int index, DwellNode* new_node);

  // TODO: Removes the node indicated by the given index and frees its memory.
  void remove(int index);

  // TODO: Returns the data associated with a fraction number,
  // false otherwise.
  string contains(string fraction);

  void clear();

  // For traversal
  DwellNode* head() const;
  DwellNode* tail() const;

  //sorting externally
  void rebuild_from_head(DwellNode* new_head);

private:
  DwellNode* head_;
  DwellNode* tail_;
  int size_;
};

#endif