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
    bool done[n];

    // Input
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
        done[i] = false;
    }

    int completed = 0, time = 0;

    string ganttPID[100];
    int ganttTime[100];
    int g = 0;

    ganttTime[g++] = 0;

    while (completed < n) {

        int idx = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++) {

            if (p[i].at <= time && !done[i]) {

                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx != -1) {

            ganttPID[g-1] = p[idx].pid;

            time += p[idx].bt;

            ganttTime[g] = time;
            g++;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            done[idx] = true;
            completed++;

        } 
        else {
            time++;
        }
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n";

    for (int i = 0; i < g-1; i++) {
        cout << "| " << ganttPID[i] << " ";
    }
    cout << "|\n";

    for (int i = 0; i < g; i++) {
        cout << ganttTime[i] << "\t";
    }

    float total_wt = 0, total_tat = 0;

    // Table Output
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