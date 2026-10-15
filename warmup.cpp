// =====================================================================
//  C++ WARM-UP  ·  African Olympiad Academy
//
//  The question descriptions are in README.md. Read them there.
//  This file holds the data, one worked example, and your answers.
//
//  BUILD AND RUN:   g++ -std=c++17 -Wall -o run warmup.cpp && ./run
//            or:    ./run.sh
//
//  Work on ONE question at a time. Write it, run it, check the output
//  against the README, commit it, move on.
// =====================================================================

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
#include <unordered_map>
#include <algorithm>
using namespace std;

/**
 * THE RECORD
 * One delivery: who brought it, how much, and what grade it was given.
 */
struct Delivery {
    string farmer;
    double kg;
    char   grade;
};


/**
 * THE DATA
 * Do not change these. Every expected answer in the README comes from exactly this data.
 */

// Q1 — one morning's weights, in the order they were weighed
vector<double> morningWeights = {
    45.5, 80.0, 12.0, -3.0, 66.5, 20.0, 31.0, 95.0, 50.0, 18.5, 0.0, 72.0
};

// Q2, Q3, Q4, Q7, Q8 — the day's logbook
vector<Delivery> logbook = {
    {"Keza",    45.5, 'A'},
    {"Bonu",    80.0, 'B'},
    {"Isanda",  20.0, 'A'},
    {"Keza",    12.0, 'C'},
    {"Onyinye", 66.5, 'B'},
    {"Karimi",  31.0, 'A'},
    {"Karimi",  31.0, 'A'},
    {"Keza",    18.5, 'B'},
    {"Bonu",    50.0, 'C'},
    {"Isanda",  20.0, 'A'},
    {"Onyinye", 72.0, 'A'}
};   // yes, one of these rows is in here twice. Q8 is about that.

// Q5 — records as the volunteers typed them, before any checking. Several of these are wrong. That is the point.
struct RawRecord {
    string id;
    string kg;        // text, because a volunteer can type anything
    char   grade;
};

vector<RawRecord> rawRecords = {
    {"F012", "45.5",  'A'},
    {"F7",   "20",    'A'},
    {"F033", "heavy", 'B'},
    {"F021", "0",     'C'},
    {"F044", "80",    'b'},
    {"F055", "",      'A'},
    {"F066", "31.5",  'D'},
    {"F077", "92",    'B'}
};

// Q6 — an Igisoro board. 16 pits, in sowing order.
//      Position 0 is unused so that board[1] really is pit 1.
vector<int> board = {0, 0, 0, 1, 0, 0, 4, 1, 0, 0, 2, 2, 0, 1, 5, 0, 0};


// ---------------------------------------------------------------------
//  A HELPER YOU MAY FIND USEFUL
// ---------------------------------------------------------------------
void printBoard(const vector<int> &b) {
    for (int i = 1; i <= 16; i++) cout << b[i] << " ";
    cout << "\n";
}


int main() {

    // =================================================================
    //  WORKED EXAMPLE  ·  not a question
    //
    //  This is the house style: walk the data once, keep what you need
    //  as you go, print at the end. Read it before you start Q1.
    //
    //  It answers: how many deliveries were grade A, and what was the
    //  heaviest single delivery in the whole logbook?
    // =================================================================


 int findFarmer(const vector<Delivery> &log, string name);
    int gradeACount = 0;
    Delivery heaviest = logbook[0];        // start from a REAL entry,
                                           // never from a made-up 0
    for (Delivery d : logbook) {
        if (d.grade == 'A') {
            gradeACount++;
        }
        if (d.kg > heaviest.kg) {
            heaviest = d;                  // keep the WHOLE record,
        }                                  // not just the number
    }

    cout << "=== Worked example ===\n";
    cout << "Grade A deliveries: " << gradeACount << "\n";
    cout << "Heaviest: " << heaviest.farmer << " with "
         << heaviest.kg << " kg\n\n";


    // =================================================================
    //  Q1  ·  THE WEIGHING SESSION          (see README)
    //  Uses: morningWeights
    // =================================================================

    cout << "=== Q1 ===\n";
    double total = 0.0;
    int valids = 0;
    double maxWeight = morningWeights[0];
    int heaviestpos = 0;
    int thisrun = 0;
    int longestrun = 0;

    for (int i = 0; i < morningWeights.size(); i++) {
        total += morningWeights[i];

        if (morningWeights[i] > 0 && morningWeights[i] <= 80) {
            valids++;
            thisrun++;
            if(i == morningWeights.size() - 1){
                if(thisrun > longestrun){
                longestrun = thisrun;
            }
            }
        }else{
            if(thisrun > longestrun){
                longestrun = thisrun;
            }
            thisrun = 0;
        }

        if (morningWeights[i] > maxWeight) {
            maxWeight = morningWeights[i];
            heaviestpos = i;
        }
    }

    if (thisrun > longestrun) {
        longestrun = thisrun;
    }

    cout << "Total: " << total << "\n";
    cout << "Valid: " << valids << " of " << morningWeights.size() << "\n";
    cout << "Heaviest: " << maxWeight << "kg at position " << heaviestpos << "\n";
    cout << "Longest valid run: " << longestrun << "\n";


    // =================================================================
    //  Q2  ·  GRADE SUMMARY                 (see README)
    //  Uses: logbook
    // =================================================================

    cout << "=== Q2 ===\n";
    int gradeAcount = 0;
    int gradeAtotal = 0;
    int gradeAavg = 0;
    int gradeBcount = 0;
    int gradeBtotal = 0;
    int gradeBavg = 0;
    int gradeCcount = 0;
    int gradeCtotal = 0;
    int gradeCavg = 0;
    for (int i = 0; i < logbook.size(); i++)
    {
        switch (logbook[i].grade)
        {
        case 'A':
            gradeAcount++;
            gradeAtotal += logbook[i].kg;
            break;
        case 'B':
            gradeBcount++;
            gradeBtotal += logbook[i].kg;
            break;
        case 'C':
            gradeCcount++;
            gradeCtotal += logbook[i].kg;
            break;
        }
    }
    if (gradeAcount > 0) {
        gradeAavg = gradeAtotal / gradeAcount;
    }
    if (gradeBcount > 0) {
        gradeBavg = gradeBtotal / gradeBcount;
    }
    if (gradeCcount > 0) {
        gradeCavg = gradeCtotal / gradeCcount;
    }
    cout << "Grade A: " << gradeAcount << " deliveries, " << gradeAtotal << " kg total, " << gradeAavg << " kg average" << '\n';
    cout << "Grade B: " << gradeBcount << " deliveries, " << gradeBtotal << " kg total, " << gradeBavg << " kg average" << '\n';
    cout << "Grade C: " << gradeCcount << " deliveries, " << gradeAtotal << " kg total, " << gradeAavg << " kg average" << '\n';
    int bestavg = max(gradeAavg,max(gradeBavg,gradeCavg));
    cout << "Best average: " << bestavg;
    cout << "\n";


    // =================================================================
    //  Q3  ·  WHO IS WHO                    (see README)
    //  Uses: logbook, and the findFarmer function you write below main
    // =================================================================

    cout << "=== Q3 ===\n";
    cout << "findFarmer(Isanda) = " << findFarmer(logbook,"Isanda") << endl;
    cout << "findFarmer(Mukamana) = " << findFarmer(logbook,"Mukamana") << endl;
    unordered_map<string,int> deliveryCounts;
    unordered_map<string,double> deliverytotalKGS;
    for(int i = 0; i < logbook.size();i++){
        deliveryCounts[logbook[i].farmer]++;
        deliverytotalKGS[logbook[i].farmer] += logbook[i].kg;
    }
    string topdeliveries = "";
    int maxdelivcount = 0;
    for (const auto& [deliverer, count] : deliveryCounts) {
        if (count > maxdelivcount) {
            maxdelivcount = count;
            topdeliveries = deliverer;
        }
    }
    cout << "Most deliveries: " << topdeliveries << "(" << maxdelivcount << ")"  << endl;
    string topdelivweightowner = "";
    int maxdelivweight = 0;
    for (const auto& [deliverer, weight] : deliverytotalKGS) {
        if (weight > maxdelivweight) {
            maxdelivweight = weight;
            topdelivweightowner = deliverer;
        }
    }
    cout << "Most kg: " << topdelivweightowner << " (" << maxdelivweight << ")" << endl;

    cout << "\n";


    // =================================================================
    //  Q4  ·  PAYMENT RUN WITH A DAILY CAP  (see README)
    //  Uses: logbook, and the payment function you write below main
    // =================================================================

    cout << "=== Q4 ===\n";





    cout << "\n";


    // =================================================================
    //  Q5  ·  THE VALIDATION REPORT         (see README)
    //  Uses: rawRecords
    // =================================================================

    cout << "=== Q5 ===\n";





    cout << "\n";

    // =================================================================
    //  Q6  ·  IGISORO: A FULL TURN          (see README)
    //  Uses: board
    // =================================================================

    cout << "=== Q6 ===\n";



    
    // =================================================================
    //  STRETCH  ·  optional
    // =================================================================

    // =================================================================
    //  Q7  ·  SORT THE LOGBOOK              (see README)
    //  Uses: logbook
    // =================================================================

    // cout << "=== Q7 ===\n";





    // =================================================================
    //  Q8  ·  SPOTTING DOUBLE-ENTRIES       (see README)
    //  Uses: logbook
    // =================================================================

    // cout << "=== Q8 ===\n";





    return 0;
}


// =====================================================================
//  FUNCTIONS YOU WRITE
//
//  C++ reads a file top to bottom, so a function must be DECLARED above
//  the place that calls it. These two are declared here at the bottom,
//  which main() cannot see — so move them ABOVE main(), or leave a
//  one-line declaration up there. Working that out is part of Q3.
// =====================================================================

// Q3:  return the position of the first delivery by this farmer,
//      or -1 if the farmer is not in the log at all.

 int findFarmer(const vector<Delivery> &log, string name) {
    int n = log.size();
    int found = -1;
    for (int i = 0; i < n; i++)
    {
        if(log[i].farmer == name){
            found = i;
            break;
        }
    }
    return found;
    
 }


// Q4:  what one delivery earns, before any cap is applied.
//      Grade A pays 10% above the rate, B pays the rate,
//      anything else pays 20% below it. The rate is 450.
//
// double payment(double kg, char grade) {
//
// }

