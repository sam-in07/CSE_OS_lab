#include <iostream>
#include <climits>
using namespace std;

struct Process {
    string pid;
    int at, bt, rt;
    int ct, tat, wt;
};

int main() {

    int n;
    cin >> n;

    int tq;          // Time Quantum
    cin >> tq;       // <-- NEW INPUT

    Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;
    }

    int complete = 0, time = 0;
    int shortest = -1;
    int min_rt;

    string ganttPID[200];
    int ganttTime[200];
    int g = 0;

    ganttTime[g++] = 0;

    while (complete < n) {

        min_rt = INT_MAX;
        shortest = -1;

        // Find shortest remaining time
        for (int i = 0; i < n; i++) {

            if (p[i].at <= time &&
                p[i].rt > 0 &&
                p[i].rt < min_rt) {

                min_rt = p[i].rt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        // Store process
        ganttPID[g-1] = p[shortest].pid;

        // Run for Time Quantum or remaining time
        int execTime = min(tq, p[shortest].rt);

        p[shortest].rt -= execTime;
        time += execTime;

        ganttTime[g] = time;
        g++;

        if (p[shortest].rt == 0) {

            complete++;

            p[shortest].ct = time;

            p[shortest].tat =
                p[shortest].ct - p[shortest].at;

            p[shortest].wt =
                p[shortest].tat - p[shortest].bt;

            if (p[shortest].wt < 0)
                p[shortest].wt = 0;
        }
    }

    // -------- Gantt Chart --------

    cout << "\nGantt Chart:\n";

    cout << "| " << ganttPID[0] << " ";

    string last = ganttPID[0];

    for (int i = 1; i < g-1; i++) {

        if (ganttPID[i] != last) {

            cout << "| "
                 << ganttPID[i]
                 << " ";

            last = ganttPID[i];
        }
    }

    cout << "|\n";

    cout << "0\t";

    last = ganttPID[0];

    for (int i = 1; i < g-1; i++) {

        if (ganttPID[i] != last) {

            cout << ganttTime[i]
                 << "\t";

            last = ganttPID[i];
        }
    }

    cout << ganttTime[g-1];

    // -------- Table --------

    float total_wt = 0,
          total_tat = 0;

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
3
P1 0 8
P2 1 4
P3 2 9
P4 3 5

4
1
P1 0 8
P2 1 4
P3 2 9
P4 3 5


*/