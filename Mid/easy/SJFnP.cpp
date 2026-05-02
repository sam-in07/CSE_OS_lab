#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string pid;
    int at, bt, rt, pr;
    int ct, tat, wt;
};

// -------- PRINT FUNCTION --------
void printTable(Process p[], int n)
{
    float total_wt = 0, total_tat = 0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    cout << "\nAverage Waiting Time: " << total_wt / n << endl;
    cout << "Average Turnaround Time: " << total_tat / n << endl;
}

void sjf(Process p[], int n)
{
    bool done[n] = {false};
    int completed = 0, time = 0;

    while (completed < n)
    {
        int idx = -1, min_bt = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && !done[i] && p[i].bt < min_bt)
            {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1)
        {
            time++;
            continue;
        }

        time += p[idx].bt;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        done[idx] = true;
        completed++;
    }

    printTable(p, n);
}

int main()
{

    int n;
    cin >> n;

    Process p[n];

    // -------- INPUT BASED ON CHOICE --------

    {
        cout << "Enter PID AT BT:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> p[i].pid >> p[i].at >> p[i].bt;
            p[i].rt = p[i].bt;
        }
    }

    // -------- CALL FUNCTIONS --------

    sjf(p, n);
    return 0;
}

/*
4
P1 0 8
P2 1 4
P3 2 9
P4 3 5

*/