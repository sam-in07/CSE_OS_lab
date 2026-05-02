#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string pid;
    int at, bt;
    int ct, tat, wt;
};

int main()
{

    int n;
    cin >> n;

    Process p[n];
    bool flag[n];

    // Input
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
        flag[i] = false;
    }

    int completed = 0, time = 0;

    string gPid[100]; // stores process execution order
    int gTim[100];    //stores time points
    int g = 0;

    gTim[g++] = 0;

    while (completed < n)
    {
        //sjfn   minimum burst tim
        int idx = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++)
        {
             //Arrived processes    Not completed 
            if (p[i].at <= time && !flag[i])
            {

                if (p[i].bt < min_bt)
                {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }
        ///if Process Found
        if (idx != -1)
        {
           // Store in Gantt Chart
            gPid[g - 1] = p[idx].pid;
          //Execute Process  non-preemptive, it runs fully
            time += p[idx].bt;

            gTim[g] = time;
            g++;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            flag[idx] = true;
            completed++;
        }
        else
        {
            time++;
        }
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n";

    for (int i = 0; i < g - 1; i++)
    {
        cout << "| " << gPid[i] << " ";
    }
    cout << "|\n";

    for (int i = 0; i < g; i++)
    {
        cout << gTim[i] << "\t";
    }

    float total_wt = 0, total_tat = 0;

    // Table Output
    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";

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