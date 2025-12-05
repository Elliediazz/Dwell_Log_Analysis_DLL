#include "Analysis.h"
#include <iostream>
#include <cmath>

using namespace std;

Analysis::Analysis() {}
Analysis::~Analysis() {}

//LQ Model Calculation S=e^(-aD-bD^2)
double Analysis::compute_cell_survival_rate(double dose_Gy, double a, double b){
    //Edgecase: input is <0
    if (dose_Gy < 0) {
        dose_Gy = 0.0;
    }

    double var = -((a * dose_Gy) + (b* dose_Gy * dose_Gy));
    double S = exp(var);

    //Edgecase: S MUST BE between 0 - 1
    if (S < 0.0){
        S = 0.0;
    }
    if (S > 1.0) {
        S = 1.0;
    }
    return S;
}

//Apply to Dwell Log
void Analysis::apply_lq_to_log(const DwellLog& log, double a, double b){
    
    DwellNode* curr = log.head();

    if (curr == NULL) {
        cout << "LQ Analysis: dwell log is empty, please upload a dwell log to analyze\n";
        return;
    }

    summarys_.clear();

    cout << "LQ Analysis constant values: alpha=" << a << ", beta=" << b << "\n";

    while (curr != NULL) {
        // Calculate the dose
        double dose_Gy = curr->dose_rate_Gy_per_s * curr->delivered_dwell_s;
        double S= compute_cell_survival_rate(dose_Gy, a, b); 

        cout << "  Fraction " << curr->fraction_id
             << ", Catheter " << curr->catheter_id
             << ", DwellIdx " << curr->dwell_index
             << ", Dose ≈ " << dose_Gy << " Gy"
             << ", S(D) = " << S
             << "\n";

        LQSummary summary;
        summary.fraction_id = curr->fraction_id;
        summary.catheter    = curr->catheter_id;
        summary.dwell_index = curr->dwell_index;
        summary.dose        = dose_Gy;
        summary.survival    = S;
        summarys_.push_back(summary);

        curr = curr->next;
    }
}

//Compare predicted vs Actual
void Analysis::compare_predicted_actual(const DwellLog& predicted, const DwellLog& actual, ostream& os){
    DwellNode* p = predicted.head();
    DwellNode* a = actual.head();

    if (p == NULL || a == NULL) {
        os << "Comparison: one or both dwell logs are empty.\n";
        os << "  Predicted size: " << predicted.size()
             << ", Actual size: "    << actual.size() << "\n";
        return;
    }

    //Standarized: Streach goal is to have the user input them 
    const double alpha = 0.25;
    const double beta  = 0.03; 

    os << "Comparing predicted vs actual dwell logs\n";
    os << "Using LQ parameters: alpha = " << alpha
         << ", beta = " << beta << "\n\n";

    //Table Headers 
    os << "Idx | Fraction | Cath | DwellIdx | "
            "t_pred(s) | t_act(s) | delta_t(s) | delta_t(%) | "
            "D_pred(Gy) | D_act(Gy) | delta_D(Gy) | delta_D(%) | "
            "S_pred | S_act | delta_S\n";
    os << "\n";

    int idx = 0;
    double total_pred_dose = 0.0;
    double total_act_dose  = 0.0;

    while (p != NULL && a != NULL) {
        // 1) Dwell time comparison
        double t_pred = p->delivered_dwell_s;
        double t_act  = a->delivered_dwell_s;
        double dt     = t_act - t_pred;
        double dt_pct = (t_pred != 0.0) ? (dt / t_pred) * 100.0 : 0.0;

        // 2) Dose comparison
        double D_pred = p->dose_rate_Gy_per_s * t_pred;
        double D_act  = a->dose_rate_Gy_per_s * t_act;
        double dD     = D_act - D_pred;
        double dD_pct = (D_pred != 0.0) ? (dD / D_pred) * 100.0 : 0.0;

        total_pred_dose += D_pred;
        total_act_dose  += D_act;

        // 3) LQ survival comparison
        double S_pred = compute_cell_survival_rate(D_pred, alpha, beta);
        double S_act  = compute_cell_survival_rate(D_act, alpha, beta);
        double dS     = S_act - S_pred;

        os << idx
             << " | " << p->fraction_id
             << " | " << p->catheter_id
             << " | " << p->dwell_index
             << " | " << t_pred
             << " | " << t_act
             << " | " << dt
             << " | " << dt_pct
             << " | " << D_pred
             << " | " << D_act
             << " | " << dD
             << " | " << dD_pct
             << " | " << S_pred
             << " | " << S_act
             << " | " << dS
             << "\n";

        p = p->next;
        a = a->next;
        ++idx;
    }

    // Edgecase:there is a difference in length of dwell logs
    while (p != NULL) {
        os << "Warning: extra predicted dwell record with no matching actual record at dwellIdx "
             << p->dwell_index << " in catheter " << p->catheter_id << "\n";
        p = p->next;
    }

    while (a != NULL) {
        os << "Warning: extra actual dwell record with no matching predicted record at dwellIdx "
             << a->dwell_index << " in catheter " << a->catheter_id << "\n";
        a = a->next;
    }

    // Summary
    double dD_total     = total_act_dose - total_pred_dose;
    double dD_total_pct = (total_pred_dose != 0.0) ? (dD_total / total_pred_dose) * 100.0: 0.0;

    double S_pred_total = compute_cell_survival_rate(total_pred_dose, alpha, beta);
    double S_act_total  = compute_cell_survival_rate(total_act_dose,  alpha, beta);
    double dS_total     = S_act_total - S_pred_total;

    os << "\n Summary over entire dwell log \n";
    os << "Total predicted dose: " << total_pred_dose << " Gy\n";
    os << "Total actual dose:    " << total_act_dose  << " Gy\n";
    os << "Delta_total:             " << dD_total        << " Gy ("
         << dD_total_pct << " %)\n";
    os << "Total predicted survival S_pred_total: " << S_pred_total << "\n";
    os << "Total actual survival   S_act_total:   " << S_act_total  << "\n";
    os << "Delta_total (S_act - S_pred):            " << dS_total     << "\n";
}

//Print analysis (TODO: Add Graph if time allows)
void Analysis::print_analysis(ostream& os){
    if (summarys_.empty()) {
        os << "No LQ analysis summary available. Please run LQ model first.\n";
        return;
    }

    os << "LQ MODEL SUMMARY \n";

    for (const auto& r : summarys_) {
        os << "Fraction " << r.fraction_id
           << ", Catheter " << r.catheter
           << ", Index " << r.dwell_index
           << " : Dose = " << r.dose 
           << " Gy, Survival = " << r.survival << "\n";
    }

    os << "\n";
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
            return a->catheter_id < b->catheter_id;
        }

        if (a->dwell_index != b->dwell_index){
            return a->dwell_index < b->dwell_index;;
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

//IMPLEMENT MERGSORT
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

//APPLY MERGESORT
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