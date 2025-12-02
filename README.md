# Radaiation Therapy Treatment Log Timeline Reconstrctions using a Doubly Linked List and Merge Sort

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

where:
S= The Surviving fraction 
D= The Dose 
a and b are constants 

The Linear component (aD) represents the cell death from a single tract of radiation creating a lethal lesion, this damage is directly proportional to the dose. acording to fiveable.me's radiobiology unit 6 study guides, the LQ model is widely used in radiotherapy treatment planning to optimize dose fractionation and predict tumor control probability (TCP) and normal tissue complication probability (NTCP)

The Quadratic component (bD^2) represents the cell death from two independent radiation tracts causing seperate lesions when they interact with each other, they create a lethal lesion. This is proportional to the square of the dose.

The Fraction is the models key insight whichis that the Quadratic component is dependent on the time between doses. If there is enough time between fractions (or sessions) a cell can repair a lesion from the first track before a second track can interact witth it, inturn reducing the number of cells killed compare to a single high dose exposure and shows why multiple smaller fractions is ofter perfered and more effcetice as opposed to a sigle high dose

Using a Doubly linked list will allows for easier analysis as each node contains two pointers, one pointer references the next node in the sequence, while the other references the previous node. This allows traversal both forward and backward making comparisons like; detecting duplicate events, checking out of order dwell indicies, comparing planned vs "actual" positions, checking time stamp differences and verifying catheter position consitency things that can can be easily implemented with a DLL. A DLL also makes merge sorting easier as it can split the list in half intuitively. 

## Time/Space Comlexity
When it comes to a doubly linked list, the time complexity remains 0(n) for searching and taversal as you would need to potentially traverse through the entire list to find a value. 
Merge sort however, has a complexity of 0(n log n)

## Advantages
A doubly linked list works really well for this project because it lets me easily move forward and backward through the dwell log. That’s especially helpful when I need to compare two events, check neighboring dwell indices, or detect out-of-order entries. It also pairs naturally with merge sort, since merge sort works efficiently with linked lists by just relinking pointers instead of shifting data around.

## Disadvantages
One of the downfalls of using a DLL is the extra memory that is needed to store both the next and prev pointers in addition to the actual data.
A disadvantage for using Merge Sort vs another sorting algorith is that it is more complex to implement compared to simpler algorithms, and it always runs in O(n log n) even if it is mostly sorted.

## My Goal:
1. Create two mock dwell log datasets for a "patient" in CSV format: one representing the predicted dwell log and one representing the "actual" dwell log "after treatment".

2. Build a front end that can load the predicted dwell log and apply a Linear–Quadratic (LQ) model to estimate how many cells survive after a given radiation dose and how effective that dose is biologically. 

3. Allow the user to adjust the radiation dose in the front end and recompute the LQ model results. (This is FAR more complex but for the purpose of this assigmnet I will have this be a single digit that can be adjusted for comparison)

4. Store each dose scenario and its LQ result in a list, then use merge sort to rank the scenarios based on effectiveness (for example, lowest surviving fraction = most effective dose).

5. Once the patient has “gone through” treatment, the researcher can upload the actual dwell log. The program will then build a doubly linked list of the delivered dwell events and use merge sort to analyze dwell time discrepancies, dwell time per catheter, out of order dwell indices, and duplicate events to help evaluate the quality of the treatment delivery. 

6. The front end will display the data in list form and also plot the results on simple graphs so the researcher can visually compare planned vs actual delivery and the impact on predicted cell survival.

## Doubly Linked List Invariants:
1. The 'next' pointer of the tail node must be NULL.
2. The 'prev' pointer of the head node must be NULL.
3. If the list is empty, both head and tail must be NULL.
4. If the list contains exactly one node, that node's 'prev' and 'next' must both be NULL.


### Sources: 
https://iopscience.iop.org/article/10.1088/1361-6560/aaf26a/pdf 
https://www.youtube.com/watch?v=9KDrRaXVuK0 
https://aapm.onlinelibrary.wiley.com/doi/epdf/10.1002/mp.17062 