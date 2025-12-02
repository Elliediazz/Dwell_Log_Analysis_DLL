#include "DwellLogData.h"

// constructor, initialize class variables and pointers here if need.
DwellLog::DwellLog() {
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

// deconstructor,
DwellLog::~DwellLog() {
    clear();
}

bool DwellLog::empty() const {
    return head_ == NULL;
}

int DwellLog::size() const {
    return size_;
}

DwellNode* DwellLog::init_node(
                    long time_ms,
                    string fraction_id,
                    int catheter_id,
                    int dwell_index,
                    double planned_dwell_s,
                    double delivered_dwell_s,
                    double dose_rate_Gy_per_s,
                    string region_id) {
    DwellNode* n = new DwellNode;
    n->time_ms = time_ms;
    n->fraction_id = fraction_id;
    n->catheter_id = catheter_id;
    n->dwell_index = dwell_index;
    n->planned_dwell_s = planned_dwell_s;
    n->delivered_dwell_s = delivered_dwell_s;
    n->dose_rate_Gy_per_s = dose_rate_Gy_per_s;
    n->region_id = region_id;
    n->next = nullptr;
    n->prev = nullptr;
    return n;
}

void DwellLog::append(DwellNode* new_node) {
  if (head == NULL){
    head_ = new_node;
    tail_ = new_node;
  }else {
    tail_ -> next = new_node;
    new_node -> prev = tail_;
    tail_ = new_node;
  }
  size_ ++;
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

//Redo for Dwell log implementation
string DwellLog::contains(string fraction) {
  // Your code here
  //This will hold code so that the user can input a fraction as a parameter of the contains method and it will return a list of the values in that fraction
}

DwellNode* DwellLog::head() const {
    return head_;
}

DwellNode* DwellLog::tail() const {
    return tail_;
}

//Todo: Sorting 
//Implement mergesort and merge methods
