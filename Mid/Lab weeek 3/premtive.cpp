
#include<bits/stdc++.h>
using namespace std;

struct Process{
    string pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

int main(){
    int n;
    cin >> n;

    vector<Process> p(n);

    for(int i=0;i<n;i++){
        cin >> p[i].pid >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;
    }

    int completed = 0, time = 0;
    int min_rt = INT_MAX;
    int idx = -1;

    vector<string> gantt_pid;
    vector<int> gantt_time;

    gantt_time.push_back(0);

    while(completed < n){

        idx = -1;
        min_rt = INT_MAX;

        for(int i=0;i<n;i++){
            if(p[i].at <= time && p[i].rt > 0){
                if(p[i].rt < min_rt){
                    min_rt = p[i].rt;
                    idx = i;
                }
                else if(p[i].rt == min_rt){
                    if(p[i].at < p[idx].at)
                        idx = i;
                }
            }
        }

        if(idx != -1){

            if(gantt_pid.empty() || gantt_pid.back() != p[idx].pid){
                gantt_pid.push_back(p[idx].pid);
                gantt_time.push_back(time);
            }

            p[idx].rt--;
            time++;

            if(p[idx].rt == 0){
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        }
        else{
            time++;
        }
    }

    gantt_time.push_back(time);

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    float total_wt = 0, total_tat = 0;

    for(int i=0;i<n;i++){
        cout << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    cout << "\nAverage Waiting Time: " << total_wt/n;
    cout << "\nAverage Turnaround Time: " << total_tat/n;

    cout << "\n\nGantt Chart:\n";

    for(int i=0;i<gantt_pid.size();i++)
        cout << "| " << gantt_pid[i] << " ";
    cout << "|\n";

    for(int i=0;i<gantt_time.size();i++)
        cout << gantt_time[i] << "\t";

    cout << endl;

    return 0;
}