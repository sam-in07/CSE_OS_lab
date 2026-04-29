#include <iostream>
#include <climits>
using namespace std;

struct Process {
    string pid;
    int at, bt, rt;
    int ct, tat, wt;
};

int main() {

    int mode;
    cout << "Enter Mode:\n";
    cout << "1.FCFS  2.SJF  3.SRTF  4.RoundRobin\n";
    cin >> mode;

    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    // Input
    cout << "Enter PID AT BT:\n";

    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;
    }

    // ---------------- SRTF ----------------
    if (mode == 3) {

        int complete = 0, time = 0;
        int shortest = -1;

        while (complete < n) {

            int min_rt = INT_MAX;
            shortest = -1;

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

            p[shortest].rt--;
            time++;

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

        // Output Table
        float total_wt = 0, total_tat = 0;

        cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

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
    }

    // -------------- Round Robin --------------
    if (mode == 4) {

        int tq;
        cout << "Enter Time Quantum: ";
        cin >> tq;

        // RR logic can be added here later
        cout << "Round Robin Mode Selected\n";
        cout << "Time Quantum = " << tq << endl;
    }

    return 0;
}