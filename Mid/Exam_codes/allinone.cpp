#include <iostream>
#include <queue>
#include <climits>
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

// -------- SJF --------
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

// -------- SRTF --------
void srtf(Process p[], int n)
{
    int complete = 0, time = 0;

    while (complete < n)
    {
        int idx = -1, min_rt = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].rt > 0 && p[i].rt < min_rt)
            {
                min_rt = p[i].rt;
                idx = i;
            }
        }

        if (idx == -1)
        {
            time++;
            continue;
        }

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0)
        {
            complete++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }

    printTable(p, n);
}

// -------- Round Robin --------
void roundRobin(Process p[], int n, int tq)
{
    queue<int> q;
    bool visited[n] = {false};

    int time = 0, complete = 0;

    while (complete < n)
    {

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && !visited[i])
            {
                q.push(i);
                visited[i] = true;
            }
        }

        if (q.empty())
        {
            time++;
            continue;
        }

        int i = q.front();
        q.pop();

        int exec = min(tq, p[i].rt);
        p[i].rt -= exec;
        time += exec;

        for (int j = 0; j < n; j++)
        {
            if (p[j].at <= time && !visited[j])
            {
                q.push(j);
                visited[j] = true;
            }
        }

        if (p[i].rt > 0)
            q.push(i);
        else
        {
            complete++;
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
        }
    }

    printTable(p, n);
}

void priorityRoundRobin(Process p[], int n, int tq)
{

    int time = 0, complete = 0;
    bool visited[n] = {false};

    string ganttPID[200];
    int ganttTime[200];
    int g = 0;

    ganttTime[g++] = 0;

    while (complete < n)
    {

        // Find highest priority (lowest number)
        int best_pr = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].rt > 0)
            {
                best_pr = min(best_pr, p[i].pr);
            }
        }

        if (best_pr == INT_MAX)
        {
            time++;
            continue;
        }

        queue<int> q;

        // Add same priority processes
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].rt > 0 &&
                p[i].pr == best_pr && !visited[i])
            {

                q.push(i);
                visited[i] = true;
            }
        }

        while (!q.empty())
        {

            int i = q.front();
            q.pop();

            ganttPID[g - 1] = p[i].pid;

            int exec = min(tq, p[i].rt);

            p[i].rt -= exec;
            time += exec;

            ganttTime[g] = time;
            g++;

            // Add new arrivals with same priority
            for (int j = 0; j < n; j++)
            {
                if (p[j].at <= time && p[j].rt > 0 &&
                    p[j].pr == best_pr && !visited[j])
                {

                    q.push(j);
                    visited[j] = true;
                }
            }

            if (p[i].rt > 0)
                q.push(i);
            else
            {
                complete++;

                p[i].ct = time;
                p[i].tat = p[i].ct - p[i].at;
                p[i].wt = p[i].tat - p[i].bt;
            }
        }

        // Reset visited for next round
        for (int i = 0; i < n; i++)
        {
            if (p[i].rt > 0)
                visited[i] = false;
        }
    }

    // -------- GANTT --------
    cout << "\nGantt Chart:\n| ";
    for (int i = 0; i < g - 1; i++)
    {
        cout << ganttPID[i] << " | ";
    }

    cout << "\n0\t";
    for (int i = 1; i < g; i++)
    {
        cout << ganttTime[i] << "\t";
    }

    // -------- TABLE --------
    float total_wt = 0, total_tat = 0;

    cout << "\n\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++)
    {

        cout << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].pr << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    cout << "\nAverage Waiting Time: " << total_wt / n << endl;
    cout << "Average Turnaround Time: " << total_tat / n << endl;
}

// -------- MAIN --------
int main()
{
    cout << "1.FCFS\n2.SJF\n3.SRTF\n4.Round Robin\n5.Priority + Round Robin\n";

    int choice;
    cin >> choice;

    int n;
    cin >> n;

    Process p[n];

    // -------- INPUT BASED ON CHOICE --------

    if (choice == 5)
    {
        cout << "Enter PID AT BT Priority:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> p[i].pid >> p[i].at >> p[i].bt >> p[i].pr;
            p[i].rt = p[i].bt;
        }
    }
    else
    {
        cout << "Enter PID AT BT:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> p[i].pid >> p[i].at >> p[i].bt;
            p[i].rt = p[i].bt;
        }
    }

    // -------- CALL FUNCTIONS --------

    if (choice == 1)
        fcfs(p, n);

    else if (choice == 2)
        sjf(p, n);

    else if (choice == 3)
        srtf(p, n);

    else if (choice == 4)
    {
        int tq;
        // cout << "Enter Time Quantum: ";
        cin >> tq;
        roundRobin(p, n, tq);
    }

    else if (choice == 5)
    {
        int tq;
        cin >> tq; // direct input, no message
        priorityRoundRobin(p, n, tq);
    }

    else
        cout << "Invalid Choice";

    return 0;
}

/*
5
4
P1 0 10 2
P2 1 15 1
P3 2 13 3
P4 3 11 2
2


4
4
P1 0 8
P2 1 4
P3 2 9
P4 3 5
2

2
4
P1 0 8
P2 1 4
P3 2 9
P4 3 5


1
4
P1 0 8
P2 1 4
P3 2 9
P4 3 5



*/