#include "Analysis.h"
#include <iostream>
#include <cmath>

using namespace std;

Analysis::Analysis() {}
Analysis::~Analysis() {}

//TODO: LQ Model Calculation
double Analysis::compute_cell_survival_rate(double dose_Gy, double a, double b){
    return 0.0;
}

//TODO: Apply to Dwell Log
void Analysis::apply_lq_to_log(const DwellLog& log, double a, double b){
    return;
}

//TODO: Compare predicted vs Actual
void Analysis::compare_predicted_actual(const DwellLog& predicted, const DwellLog& actual){
    return;
}

//TODO: Print analysis (Add Graph is time allows)
void Analysis::print_analysis(ostream& os){
    return;
}


//: Merge Sort - Tortis and Hare Method from source
//*****Merge Sort Helpers*****

DwellNode* getMiddle(DwellNode* head){
    DwellNode* slow = head;
    DwellNode* fast = head->next;

    while (fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; //Slow is the middle point 
}

bool comesBefore(DwellNode* a, DwellNode* b, int mode){
    if (mode ==2 ){
        if (a->catheter_id != b->catheter_id){
            return a->catheter_id < b->dwell_index;
        }

        if (a->dwell_index != b->dwell_index){
            return a->dwell_index < b->dwell_index;
        }
        return a->time_ms <= b->time_ms;
    }else {
        return a -> time_ms <= b->time_ms;
    }
}

DwellNode* Analysis::merge(DwellNode* a, DwellNode* b, int mode){
    DwellNode temp;
    temp.next = NULL;
    temp.prev = NULL;

    DwellNode* tail = &temp;

    while (a != NULL && b != NULL) {
        if (comesBefore(a, b, mode)) {
            tail->next = a;
            a->prev = tail;
            a = a->next;
        } else {
            tail->next = b;
            b->prev = tail;
            b = b->next;
        }
        tail = tail->next;
    }

    while (a != NULL) {
        tail->next = a;
        a->prev = tail;
        tail = a;
        a = a->next;
    }

    while (b != NULL) {
        tail->next = b;
        b->prev = tail;
        tail = b;
        b = b->next;
    }

    DwellNode* new_head = temp.next;
    if (new_head != NULL) {
        new_head->prev = NULL;
    }

    return new_head;
}

//TODO: IMPLEMENT MERGSORT
//mode 1: Sort by Time
//mode 2: Sort by Catheter and Index
DwellNode* Analysis::mergesort(DwellNode* start, int mode){
    if (start == NULL || start->next == NULL) {
        //No need to "sort"
        return start;
    }

    DwellNode* mid = getMiddle(start);
    DwellNode* rightStart = mid->next;

    mid->next = NULL;
    if (rightStart != NULL) {
        rightStart->prev = NULL;
    }

    DwellNode* leftSorted  = mergesort(start, mode);
    DwellNode* rightSorted = mergesort(rightStart, mode);

    return merge(leftSorted, rightSorted, mode);
}

//TODO: APPLY MERGESORT
void Analysis::sort_by_time(DwellLog& log) {
    DwellNode* head = log.head();
    if (head == NULL || head->next == NULL){
        return;
    }

    DwellNode* sorted_head = mergesort(head,1);
    log.rebuild_from_head(sorted_head);
}

void Analysis::sort_by_catheter_index(DwellLog& log) {
    DwellNode* head = log.head();
    if (head == NULL || head->next == NULL){
        return;
    }

    DwellNode* sorted_head = mergesort(head,2);
    log.rebuild_from_head(sorted_head);
}