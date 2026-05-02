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

// -------- FCFS --------
void fcfs(Process p[], int n)
{
    int time = 0;

    for (int i = 0; i < n; i++)
    {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printTable(p, n);
}

int main()
{
    // cout << "1.FCFS";
    // int choice;
    // cin >> choice;

    int n;
    cin >> n;

    Process p[n];

    {
        cout << "Enter PID AT BT:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> p[i].pid >> p[i].at >> p[i].bt;
            p[i].rt = p[i].bt;
        }
    }
    // -------- CALL FUNCTIONS --------

    fcfs(p, n);

    return 0;
}

/*

4
P1 0 8
P2 1 4
P3 2 9
P4 3 5

*/