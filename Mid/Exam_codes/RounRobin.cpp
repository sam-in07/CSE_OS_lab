#include <bits/stdc++.h>
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
    cin >> tq;

    Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;
    }

    queue<int> q;

    int time = 0;
    int complete = 0;
    bool visited[n] = {false};

    string ganttPID[200];
    int ganttTime[200];
    int g = 0;

    ganttTime[g++] = 0;

    while (complete < n) {

        // Add arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }

        if (q.empty()) {
            time++;
            continue;
        }

        int i = q.front();
        q.pop();

        ganttPID[g-1] = p[i].pid;

        int execTime;

        if (p[i].rt > tq)
            execTime = tq;
        else
            execTime = p[i].rt;

        p[i].rt -= execTime;
        time += execTime;

        ganttTime[g] = time;
        g++;

        // Add newly arrived processes
        for (int j = 0; j < n; j++) {
            if (p[j].at <= time && !visited[j]) {
                q.push(j);
                visited[j] = true;
            }
        }

        if (p[i].rt > 0) {
            q.push(i);
        }
        else {
            complete++;

            p[i].ct = time;

            p[i].tat =
                p[i].ct - p[i].at;

            p[i].wt =
                p[i].tat - p[i].bt;
        }
    }

    // -------- Gantt Chart --------

    cout << "\nGantt Chart:\n";

    cout << "| ";

    for (int i = 0; i < g-1; i++) {
        cout << ganttPID[i] << " | ";
    }

    cout << "\n0\t";

    for (int i = 1; i < g; i++) {
        cout << ganttTime[i] << "\t";
    }

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
2
P1 0 8
P2 1 4
P3 2 9
P4 3 5
*/