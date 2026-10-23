#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdexcept>
using namespace std;

// Here is where I leave the declaration of some of the variables.
// Most of tese variables are not mine, they are just the variables I found in the original code you gave us.
struct Delivery {
    string farmer;
    double kg;
    char grade;
};

vector<double> morningWeights = {
    45.5, 80.0, 12.0, -3.0, 66.5, 20.0, 31.0, 95.0, 50.0, 18.5, 0.0, 72.0
};

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
};  

struct RawRecord {
    string id;
    string kg;       
    char grade;
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

vector<int> board = {0, 0, 0, 1, 0, 0, 4, 1, 0, 0, 2, 2, 0, 1, 5, 0, 0};

// The function you called "helper"...
void printBoard(const vector<int> &b) {
    for (int i = 1; i <= 16; i++) cout << b[i] << " ";
    cout << "\n";
}

//Function to find farmer on Q3
int findFarmer(const vector<Delivery> &log, string name) {
    for (int i = 0; i < log.size(); i++) {
        if (log[i].farmer == name) {
            return i;
        }
    }

    return -1;
}

double payment(double kg, char grade);
//End of variable declarations and stuff, for now

int main() {
    // WORKED EXAMPLE
    int gradeACount = 0;
    Delivery heaviest = logbook[0];

    for (Delivery d : logbook) {
        if (d.grade == 'A') {
            gradeACount++;
        }
        if (d.kg > heaviest.kg) {
            heaviest = d;
        }
    }

    cout << "I removed the worked example outputs... don't be surprised to not see it.\n "; 

    // Q1
    cout << "=== Q1 ===\n";
    double total = 0;
    int validCount = 0;
    double heaviestWeight = morningWeights[0];
    int heaviestPosition = 0;
    int currentRun = 0;
    int longestRun = 0;

    for (int i = 0; i < (morningWeights.size()); i++) {
        double weight = morningWeights[i];
        total += weight;
        if (weight > heaviestWeight) {
            heaviestWeight = weight;
            heaviestPosition = i;
        }

        if (weight > 0 && weight <= 80) {
            validCount++;
            currentRun++;

            if (currentRun > longestRun) {
                longestRun = currentRun;
            }
        } else {
            currentRun = 0;
        }
    }

    cout << "Total: " << total << " kg\n";
    cout << "Valid: " << validCount << " of " << morningWeights.size() << "\n";
    cout << "Heaviest: " << heaviestWeight
         << " kg at position " << heaviestPosition << "\n";
    cout << "Longest valid run: " << longestRun << "\n\n";

    // Q2 — Grade summary solution stuff....
    cout << "=== Q2 ===\n";

    char grades[] = {'A', 'B', 'C'};
    int gradeCounts[3] = {0, 0, 0};
    double gradeTotals[3] = {0, 0, 0};

    for (Delivery d : logbook) {
        for (int i = 0; i < 3; i++) {
            if (d.grade == grades[i]) {
                gradeCounts[i]++;
                gradeTotals[i] += d.kg;
            }
        }
    }

    int bestGradeIndex = 0;
    double bestAverage = -1;

    for (int i = 0; i < 3; i++) {
        double average = 0;

        if (gradeCounts[i] > 0) {
            average = gradeTotals[i] / gradeCounts[i];
        }

        cout << "Grade " << grades[i] << ": "<< gradeCounts[i] << " deliveries, "<< gradeTotals[i] << " kg total, "<< average << " kg average\n";

        if (gradeCounts[i] > 0 && average > bestAverage) {
            bestAverage = average;
            bestGradeIndex = i;
        }
    }

    cout << "Best average: grade " << grades[bestGradeIndex] << "\n\n";

    // Q3 — WHO IS WHO
    cout << "=== Q3 ===\n";

    cout << "findFarmer(Isanda) = " << findFarmer(logbook, "Isanda") << "\n";
    cout << "findFarmer(Mukamana) = " << findFarmer(logbook, "Mukamana") << "\n";

    vector<string> farmers;
    vector<int> farmerCounts;
    vector<double> farmerTotals;

    for (Delivery d : logbook) {
        int index = -1;

        for (int i = 0; i < (farmers.size()); i++) {
            if (farmers[i] == d.farmer) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            farmers.push_back(d.farmer);
            farmerCounts.push_back(0);
            farmerTotals.push_back(0);
            index = (farmers.size()) - 1;
        }

        farmerCounts[index]++;
        farmerTotals[index] += d.kg;
    }

    int mostDeliveriesIndex = 0;
    int mostKgIndex = 0;

    for (int i = 1; i < 
        (farmers.size()); i++) {
        if (farmerCounts[i] > farmerCounts[mostDeliveriesIndex]) {
            mostDeliveriesIndex = i;
        }
        if (farmerTotals[i] > farmerTotals[mostKgIndex]) {
            mostKgIndex = i;
        }
    }

    cout << "Most deliveries: " << farmers[mostDeliveriesIndex]
         << " (" << farmerCounts[mostDeliveriesIndex] << ")\n";
    cout << "Most kg: " << farmers[mostKgIndex]
         << " (" << farmerTotals[mostKgIndex] << " kg)\n\n";

    // Q4 — PAYMENT RUN WITH A DAILY CAP
    cout << "=== Q4 ===\n";

    double totalPaid = 0;
    const double DAILY_CAP = 100000;

    for (Delivery d : logbook) {
        double amount = payment(d.kg, d.grade);
        bool halved = totalPaid > DAILY_CAP;

        if (halved) {
            amount /= 2;
        }

        cout << d.farmer << " " << d.kg << " kg grade " << d.grade
             << " -> " << amount;

        if (halved) {
            cout << "  (halved)";
        }

        cout << "\n";
        totalPaid += amount;
    }

    cout << "Total paid: " << totalPaid << "\n\n";

    // Q5 — THE VALIDATION REPORT
    cout << "=== Q5 ===\n";

    int accepted = 0;
    int rejected = 0;

    for (RawRecord r : rawRecords) {
        string reason = "";

        // Rule 1: F followed by exactly three digits.
        if (r.id.size() != 4 || r.id[0] != 'F' ||
            !isdigit(static_cast<unsigned char>(r.id[1])) ||
            !isdigit(static_cast<unsigned char>(r.id[2])) ||
            !isdigit(static_cast<unsigned char>(r.id[3]))) {
            reason = "bad id";
        }

        // Rule 2: weight must be present, numeric, > 0 and <= 80.
        else if (r.kg.empty()) {
            reason = "weight missing";
        } else {
            try {
                size_t charsUsed = 0;
                double kgValue = stod(r.kg, &charsUsed);

                if (charsUsed != r.kg.size()) {
                    reason = "weight not a number";
                } else if (kgValue <= 0 || kgValue > 80) {
                    reason = "weight out of range";
                }
            } catch (const invalid_argument &) {
                reason = "weight not a number";
            } catch (const out_of_range &) {
                reason = "weight not a number";
            }
        }

        // Rule 3: grade must be A, B or C (case-insensitive).
        if (reason.empty()) {
            char grade = static_cast<char>(
                toupper(static_cast<unsigned char>(r.grade))
            );

            if (grade != 'A' && grade != 'B' && grade != 'C') {
                reason = "unknown grade";
            }
        }

        if (reason.empty()) {
            cout << r.id << " ACCEPT\n";
            accepted++;
        } else {
            cout << r.id << " REJECT - " << reason << "\n";
            rejected++;
        }
    }

    cout << accepted << " accepted, " << rejected << " rejected\n\n";

    // Q6 — IGISORO: A FULL TURN
    cout << "=== Q6 ===\n";

    vector<int> finalBoard = board;
    int currentPit = 6;
    int seeds = finalBoard[currentPit];
    finalBoard[currentPit] = 0;
    int laps = 0;

    while (seeds > 0) {
        laps++;

        while (seeds > 0) {
            currentPit = (currentPit % 16) + 1;
            finalBoard[currentPit]++;
            seeds--;
        }

        // If the last pit now contains exactly one seed, it was empty
        // before the seed landed, so the turn ends.
        if (finalBoard[currentPit] == 1) {
            break;
        }

        // Relay: pick up all seeds from the pit where the last seed landed.
        seeds = finalBoard[currentPit];
        finalBoard[currentPit] = 0;
    }

    cout << "Final board: ";
    printBoard(finalBoard);
    cout << "Landed in pit " << currentPit << " after "
         << laps << " laps\n\n";

    // Q7 — SORT THE LOGBOOK (optional stretch)
    cout << "=== Q7 ===\n";

    vector<Delivery> sortedLog = logbook;

    sort(sortedLog.begin(), sortedLog.end(),
         [](const Delivery &a, const Delivery &b) {
             return a.kg > b.kg;
         });

    cout << "Heaviest first: ";
    for (Delivery d : sortedLog) {
        cout << d.farmer << "(" << d.kg << ") ";
    }
    cout << "\n";

    sortedLog = logbook;
    sort(sortedLog.begin(), sortedLog.end(),
         [](const Delivery &a, const Delivery &b) {
             return a.farmer < b.farmer;
         });

    cout << "Alphabetical: ";
    for (Delivery d : sortedLog) {
        cout << d.farmer << " ";
    }
    cout << "\n";

    sortedLog = logbook;
    sort(sortedLog.begin(), sortedLog.end(),
         [](const Delivery &a, const Delivery &b) {
             if (a.grade != b.grade) {
                 return a.grade < b.grade;
             }
             return a.kg > b.kg;
         });

    cout << "Grade then weight: ";
    for (Delivery d : sortedLog) {
        cout << d.grade << d.farmer << "(" << d.kg << ") ";
    }
    cout << "\n\n";

    // Q8 — SPOTTING DOUBLE-ENTRIES (optional stretch)
    cout << "=== Q8 ===\n";

    cout << "Adjacent: ";
    for (int i = 0; i < static_cast<int>(logbook.size()) - 1; i++) {
        if (logbook[i].farmer == logbook[i + 1].farmer &&
            logbook[i].kg == logbook[i + 1].kg) {
            cout << logbook[i].farmer << "(" << logbook[i].kg << ") ";
        }
    }
    cout << "\n";

    cout << "Anywhere: ";
    for (int i = 0; i < static_cast<int>(logbook.size()); i++) {
        for (int j = i + 1; j < static_cast<int>(logbook.size()); j++) {
            if (logbook[i].farmer == logbook[j].farmer &&
                logbook[i].kg == logbook[j].kg) {
                cout << logbook[i].farmer << "(" << logbook[i].kg
                     << ") at " << i << " and " << j << "  ";
            }
        }
    }
    cout << "\n";

    return 0;
}

// Q3: return the position of the first delivery by this farmer,
// or -1 if the farmer is not in the log at all.
int findFarmer(const vector<Delivery> &log, string name) {
    for (int i = 0; i < static_cast<int>(log.size()); i++) {
        if (log[i].farmer == name) {
            return i;
        }
    }

    return -1;
}

// Q4: what one delivery earns, before any cap is applied.
// Grade A pays 10% above the rate, B pays the rate,
// anything else pays 20% below it. The rate is 450.
double payment(double kg, char grade) {
    const double rate = 450;

    if (grade == 'A') {
        return kg * rate * 1.10;
    } else if (grade == 'B') {
        return kg * rate;
    } else {
        return kg * rate * 0.80;
    }
}
