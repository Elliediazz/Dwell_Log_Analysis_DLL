#include <iostream>
#include <iomanip> 
#include "DwellLogData.h"

using namespace std;

// constructor, initialize class variables and pointers here if need.
DwellLog::DwellLog() {
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

// deconstructor,
DwellLog::~DwellLog() { clear(); }

int DwellLog::size() const {
  return size_;
}

void DwellLog::print_table() const {
  DwellNode* cursor = head_;

  if (cursor == NULL){
    cout << "No records availibl\n";
  }

   //Header 
   cout << left
         << setw(12) << "time_ms"
         << setw(12) << "fraction"
         << setw(12) << "catheter"
         << setw(12) << "index"
         << setw(16) << "planned_s"
         << setw(16) << "delivered_s"
         << setw(16) << "dose_rate"
         << setw(10) << "region"
         << "\n";

  cout << string(100, '-') <<"\n";

  while (cursor != NULL) {
    cout << left
    
    << setw(12) << cursor->time_ms
    << setw(12)  << cursor->fraction_id
    << setw(12)  << cursor->catheter_id
    << setw(12)  << cursor->dwell_index
    << setw(16)  << cursor->planned_dwell_s
    << setw(16)  << cursor->delivered_dwell_s
    << setw(16)  << cursor->dose_rate_Gy_per_s
    << setw(10)  << cursor->region_id
    << "\n";

    cursor = cursor->next;
  }
}

DwellNode* DwellLog::init_node(const DwellRow& row) {
  DwellNode* x = new DwellNode;
  x->time_ms = row.time_ms;
  x->fraction_id = row.fraction_id;
  x->catheter_id = row.catheter_id;
  x->dwell_index = row.dwell_index;
  x->planned_dwell_s = row.planned_dwell_s;
  x->delivered_dwell_s = row.delivered_dwell_s;
  x->dose_rate_Gy_per_s = row.dose_rate_Gy_per_s;
  x->region_id = row.region_id;
  x->next = NULL;
  x->prev = NULL;
  return x;
}

void DwellLog::append_data(const DwellRow& row) {
  DwellNode* new_node = init_node(row);
  append(new_node);
}

void DwellLog::append(DwellNode* new_node) {
  if (head_ == NULL){
    head_ = new_node;
    tail_ = new_node;
    new_node->prev = NULL;
    new_node->next = NULL;
    size_ ++;
    return;
  } else {
    tail_->next = new_node;
    new_node->prev = tail_;
    new_node->next = NULL;
    tail_ = new_node;
  }
  size_++;
}

// TODO: InsertData inserts a new node that contains the given data value - Inserting at the end of the list should have the same effect as appending.
void DwellLog::insert_data(int index, const DwellRow& row){
  return;
}

// TODO: This is the same as insert_data, except we're inserting a node, rather than a value. This closely mirrors Append and AppendData.
void DwellLog::insert(int index, DwellNode* new_node){
  return;
}

// TODO: Removes the node indicated by the given index and frees its memory.
void DwellLog::remove(int index){
  return;
}

// TODO: Returns the data associated with a fraction number, false otherwise.
string DwellLog::contains(string fraction) {
  //This will hold code so that the user can input a fraction as a parameter of the contains method and it will return a list of the values in that fraction
  return "";
}

void DwellLog::clear() {
  DwellNode* cursor = head_;
  while (cursor != NULL){
    DwellNode* next = cursor -> next;
    delete cursor;
    cursor = next;
  }
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

DwellNode* DwellLog::head() const {
    return head_;
}

DwellNode* DwellLog::tail() const {
    return tail_;
}
