# Radaiation Therapy Treatment Log Analysis using a Doubly Linked List and Merge Sort

## Description and Background: 
As someone who’s interested in getting into Medical Physics and eventually doing research within the medical physics/radiobiology space, I wanted to pick a project that felt practical and connected to real-world applications. I decided to implement a doubly linked list and use it to handle and alalyze a dataset that mimics a dwell log. The primary purpose of a dwell log is to make sure treatment delivery is precise and accurate. Since administering radiation is a specific to a patient and cannot be generalized, we have to plan the exact points where the high activity source will stop and how long it stays there for each patient. Each stop becomes a dwell point, and the time spent there is the dwell time, which tells us how long the source remains at that position, to deliver a precise dose of radiation. The importance of a dwell log is echoed when thinking about how any error can cause significant dose discrepancies, and potentially under treat the target tissue or accidentally overdose healthy tissue. A dwell log helps ensure the treatment machine actually delivers the correct dosage as prescribed. My goal is to incorporate a mock version of this into my project. To do so I asked AI to create a mock data set using the following data points: 

- Time
- Fraction ID (Session ID)
- Catheter ID
- Dwell Index
- Planned Dwell
- Delivered Dwell
- Dose Rate (How fast radiation is bing delivered in GY/Seconds)
- Region ID (Location on the body). 

I then plan to use this data to feed it into a Linear Quadratic Model which will quantify how many cells are killed after radiation is delivered to the indicated area by using the following equation: 

S=e^(-aD-bD^2)

Where:

    S= The Surviving fraction 

    D= The Dose 

    a and b are constants 

The Linear component (aD) represents the cell death from a single tract of radiation creating a lethal lesion, this damage is directly proportional to the dose. According to Fiveable.me's 'Radiobiology Unit 6 Guide' The Linear Quadratic (LQ) model is widely used in radiotherapy treatment planning to optimize dose fractionation and predict tumor control probability (TCP) and normal tissue complication probability (NTCP)

The Quadratic component (bD^2) represents the cell death from two independent radiation tracts causing seperate lesions when they interact with each other, they create a lethal lesion. This is proportional to the square of the dose.

The Fraction is the models key insight, which is that the Quadratic Component is dependent on the time between doses. If there is enough time between fractions (or sessions) a cell can repair a lesion from the first track before a second track can interact witth it, reducing the number of cells killed compare to a single high dose and shows why multiple smaller fractions is often more effcetice as opposed to a sigle high dose.

## Implementation
Using a Doubly linked list (DLL) allows for easier analysis as each node as it contains two pointers, one pointer references the next node in the sequence, while the other references the previous node. This allows traversal both forward and backward making comparisons like; detecting duplicate events, checking out of order dwell indicies, checking time stamp differences and verifying catheter position consitency, things that can can be easily implemented with a DLL. A DLL also makes merge sorting easier as it can split the list in half intuitively. 

## Time/Space Comlexity
When it comes to a doubly linked list, the time complexity remains 0(n) for searching and taversal as you would need to potentially traverse through the entire list to find a value. 
Merge sort however, has a complexity of 0(n log 2n), where N is the size of the linked list.

## Advantages
A doubly linked list works really well for this project because it lets me easily move forward and backward through the dwell log. That’s especially helpful when I need to compare two events, check neighboring dwell indices, or detect out-of-order entries. It also works naturally with merge sort making the implementations more straightforward.

## Disadvantages
One of the downfalls of using a DLL is the extra memory that is needed to store both the next and prev pointers in addition to the actual data.
A disadvantage for using Merge Sort vs another sorting algorith is that it is more complex to implement compared to simpler algorithms, and it always runs in O(n log n) even if it is mostly sorted.

## My Goal:
1. Create two mock dwell log datasets in CSV format for a hypothetical patient where one is a predicted dwell log generated from the treatment plan, and one is the 'actual' dwell log representing what was delivered during treatment.

    - These files serve as the primary input for testing the program.

2. Build a console-based frontend that allows the user to upload either the predicted or actual dwell log and choose which analysis or processing methods to run.
    - The Frontend will allow the user to sort, analyze, and evaluate the dwell log data.

3. Once the user has upload the dwell log, the program will create a doubly linked list of the dwell events to organize the data 


4. After the data is organized in a DLL the program will perform computational analysis using a Linear–Quadratic (LQ) model to estimate cell surviving fraction and evaluate the biological effectiveness of the delivered dose. It will also be able to apply merge sort to; detect dwell time discrepancies, evaluate dwell time per catheter, identify out-of-order dwell indices, detect duplicate or irregular events

    - This provides insight into how accurately the treatment was delivered compared to the plan.

5. The frontend will then generate a summarized report of the results so the user can visually compare planned vs. delivered dwell logs and understand how these differences impact predicted cell survival based on the LQ model.

## Doubly Linked List Invariants:
1. The 'next' pointer of the tail node must be NULL.
2. The 'prev' pointer of the head node must be NULL.
3. If the list is empty, both head and tail must be NULL.
4. If the list contains exactly one node, that node's 'prev' and 'next' must both be NULL.

## File Structure
### helpers: 
This folder holds the loading logic used to read both the predicted dwell log and the actual dwell log from CSV files. Its job is to take raw files and convert them into data structures the rest of the program can use.

### include: 
This folder contains the mock data and any header files that need to be shared between components.

### src: 
The source folder hold the actual logic implementation. The DwellLogData files implement the doubly linked list data structure and related operations for storing dwell log events. While the Analysis files implement the Linear–Quadratic (LQ) model logic and any additional analysis functions like the dose calculations, discrepancy checks, etc.

### tests: 
This folder holds the unit tests for the data structure, CSV loading, and analysis logic. It’s used to verify that the implementation behaves as expected and handles edge cases correctly.

### main.cpp: 
The main file acts as the “frontend” of the application. It provides the console-based user interface, lets the user choose input files, triggers the analysis, and displays results based on the logic implemented in the src files.

## How to run the app locally
1. Go to build directory by using: cd build
2. Clear existing files and subdirs in build dir by rm -r *
3. Run cmake ..
4. Run make
4. To run the app: ./dwell_log_app
5. When prompted "Please enter CSV file for the predicted dwell log" enter the following: ../include/predicted_dwell_log.csv
    You should get a message stating the number of records that were loaded
6. This wil display the menu options
    MAIN MENU
    1) Load a different CSV file
    2) Print current predicted dwell log
    3) Clear dwell log data
    4) Apply Merge Sort
    5) Apply LQ Model
    6) Compare predicted vs actual logs
    Q) Quit

     If you select 5: You will be prompted with "No actual dwell log loaded, Please enter CSV file for actual dwell log:" enter the following: ../include/actual_dwell_log.csv
7. You will be prompted to enter output file names in steps 5 and 6 if you choose. If not there are example files in the build folder displaying example outputs. They are labeled: comparison_report.txt and lq_summary.txt

## Final Project Video
https://drive.google.com/file/d/1WywuR6JpSgc9jg3xr4KtMV86tJBl_Kwe/view?usp=sharing


## Sources: 

https://iopscience.iop.org/article/10.1088/1361-6560/aaf26a/pdf 

https://www.youtube.com/watch?v=9KDrRaXVuK0 

https://aapm.onlinelibrary.wiley.com/doi/epdf/10.1002/mp.17062 

https://interviewkickstart.com/blogs/learn/merge-sort-for-linked-list 

https://www.sarthaks.com/3596791/how-does-merge-sort-work-on-a-doubly-linked-list