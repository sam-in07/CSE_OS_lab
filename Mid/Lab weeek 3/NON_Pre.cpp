#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    string pid;
    int at; // arrival time
    int bt; // burst time
    int ct; // completion time
    int tat; // turnaround time
    int wt; // waiting time
    bool completed;
};

int main() {
    int n;
   // cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for(int i = 0; i < n; i++) {
      //  cout << "Enter Process ID, Arrival Time, Burst Time: ";
        cin >> p[i].pid >> p[i].at >> p[i].bt;
        p[i].completed = false;
    }

    int completed = 0, time = 0;

    while(completed < n) {
        int idx = -1;
        int min_bt = 1e9;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && !p[i].completed) {
                if(p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
                else if(p[i].bt == min_bt) {
                    if(p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = true;
            completed++;
        } else {
            time++;
        }
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    float total_wt = 0, total_tat = 0;

    for(int i = 0; i < n; i++) {
        cout << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n;

    return 0;
}




/*
4
P1 0 8
P2 1 4
P3 2 9
P4 3 5


*/
