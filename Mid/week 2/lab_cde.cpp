#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int start;
    int completion;
};


bool compareArrival(Process a, Process b) {
    return a.arrival < b.arrival;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for(int i = 0; i < n; i++) {
        cout << "Enter Process ID, Arrival Time and Burst Time for process " << i+1 << ": ";
        cin >> p[i].pid >> p[i].arrival >> p[i].burst;
    }


    sort(p.begin(), p.end(), compareArrival);

    int currentTime = 0;

    for(int i = 0; i < n; i++) {
        if(currentTime < p[i].arrival)
            currentTime = p[i].arrival;

        p[i].start = currentTime;
        p[i].completion = p[i].start + p[i].burst;
        currentTime = p[i].completion;
    }

    
    cout << "\nGantt Chart:\n";

    cout << " ";
    for(int i = 0; i < n; i++) {
        cout << "-------";
    }
    cout << endl << "|";

    for(int i = 0; i < n; i++) {
        cout << "  P" << p[i].pid << "  |";
    }

    cout << endl << " ";
    for(int i = 0; i < n; i++) {
        cout << "-------";
    }

    cout << endl;

    
    cout << p[0].start;
    for(int i = 0; i < n; i++) {
        cout << "      " << p[i].completion;
    }

    cout << endl;

    return 0;
}