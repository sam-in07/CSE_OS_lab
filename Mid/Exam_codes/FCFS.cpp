#include <iostream>
using namespace std;

struct Process {
    string pid;
    int at, bt;
    int ct, tat, wt;
};

int main() {

    int n;
    cin >> n;

    Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
    }

    // Sort by Arrival Time (simple FCFS rule)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                swap(p[i], p[j]);
            }
        }
    }

    int time = 0;

    string ganttPID[100];
    int ganttTime[100];
    int g = 0;

    ganttTime[g++] = 0;

    for (int i = 0; i < n; i++) {

        if (time < p[i].at)
            time = p[i].at;

        ganttPID[i] = p[i].pid;

        time += p[i].bt;

        ganttTime[g] = time;
        g++;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n";

    cout << "| ";
    for (int i = 0; i < n; i++) {
        cout << ganttPID[i] << " | ";
    }
    cout << "\n";

    for (int i = 0; i < g; i++) {
        cout << ganttTime[i] << "\t";
    }

    // Table
    float total_wt = 0, total_tat = 0;

    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {

        cout << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    cout << "\nAverage Waiting Time: "
         << total_wt / n << endl;

    cout << "Average Turnaround Time: "
         << total_tat / n << endl;

    return 0;
}

/*
4
P1 0 8
P2 1 4
P3 2 9
P4 3 5

*/