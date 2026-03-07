#include<bits/stdc++.h>
using namespace std;

struct Process {
    string pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    bool completed;
};

int main() {
    int n;
    cin >> n;

    vector<Process> p(n);

    for(int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
        p[i].completed = false;
    }

    int completed = 0, time = 0;

    vector<string> gantt_pid;
    vector<int> gantt_time;

    gantt_time.push_back(0);

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

            gantt_pid.push_back(p[idx].pid);

            time += p[idx].bt;

            gantt_time.push_back(time);

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].completed = true;
            completed++;

        }
        else {
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

    cout << "\n\nGantt Chart:\n";

    for(int i = 0; i < gantt_pid.size(); i++)
        cout << "| " << gantt_pid[i] << " ";

    cout << "|\n";

    for(int i = 0; i < gantt_time.size(); i++)
        cout << gantt_time[i] << "\t";

    cout << endl;

    return 0;
}
