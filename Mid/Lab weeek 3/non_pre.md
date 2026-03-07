I will explain the **SJF (Shortest Job First) Non-Preemptive C++ code step by step** so you can easily understand it for **OS lab or exams**.

---

# 1. Header Files

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
```

### Explanation

* `iostream` → used for **input/output (cin, cout)**
* `vector` → used to store **multiple processes dynamically**
* `algorithm` → used for algorithms (not heavily used here but commonly included)
* `using namespace std;` → so we don’t need to write `std::`

---

# 2. Structure for Process

```cpp
struct Process {
    string pid;
    int at; 
    int bt; 
    int ct; 
    int tat; 
    int wt; 
    bool completed;
};
```

### Explanation

We create a **structure (struct)** to store all information about a process.

| Variable    | Meaning                    |
| ----------- | -------------------------- |
| `pid`       | Process ID                 |
| `at`        | Arrival Time               |
| `bt`        | Burst Time                 |
| `ct`        | Completion Time            |
| `tat`       | Turnaround Time            |
| `wt`        | Waiting Time               |
| `completed` | Checks if process finished |

---

# 3. Start of Main Function

```cpp
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
```

### Explanation

* `n` = number of processes
* User enters how many processes will be scheduled.

Example:

```
4
```

---

# 4. Create Process List

```cpp
vector<Process> p(n);
```

### Explanation

* Creates a **vector (array-like structure)** of `Process`
* Stores all process information.

Example memory:

| PID | AT | BT |
| --- | -- | -- |
| P1  | 0  | 8  |
| P2  | 1  | 4  |
| P3  | 2  | 9  |
| P4  | 3  | 5  |

---

# 5. Input Process Information

```cpp
for(int i = 0; i < n; i++) {
    cout << "Enter Process ID, Arrival Time, Burst Time: ";
    cin >> p[i].pid >> p[i].at >> p[i].bt;
    p[i].completed = false;
}
```

### Explanation

Loop runs **n times** to take process data.

Example input:

```
P1 0 8
P2 1 4
P3 2 9
P4 3 5
```

`completed = false`
→ means the process has **not executed yet**.

---

# 6. Initialize Variables

```cpp
int completed = 0, time = 0;
```

### Explanation

| Variable    | Meaning                      |
| ----------- | ---------------------------- |
| `completed` | number of finished processes |
| `time`      | current CPU time             |

---

# 7. Main Scheduling Loop

```cpp
while(completed < n)
```

### Explanation

Loop runs until **all processes are completed**.

Example:

```
completed = 0
n = 4
```

Loop continues until `completed = 4`.

---

# 8. Find Shortest Burst Process

```cpp
int idx = -1;
int min_bt = 1e9;
```

### Explanation

| Variable | Meaning                   |
| -------- | ------------------------- |
| `idx`    | index of selected process |
| `min_bt` | minimum burst time        |

`1e9` means **very large number**.

---

# 9. Check All Processes

```cpp
for(int i = 0; i < n; i++) {
    if(p[i].at <= time && !p[i].completed)
```

### Explanation

Process will run **only if**:

1. Arrival time ≤ current time
2. Process is not completed

---

# 10. Select Shortest Job

```cpp
if(p[i].bt < min_bt) {
    min_bt = p[i].bt;
    idx = i;
}
```

### Explanation

Among arrived processes choose the one with **minimum burst time**.

Example at time = 8

Available processes:

| Process | Burst |
| ------- | ----- |
| P2      | 4     |
| P3      | 9     |
| P4      | 5     |

Shortest → **P2**

---

# 11. Tie Breaking

```cpp
else if(p[i].bt == min_bt) {
    if(p[i].at < p[idx].at) {
        idx = i;
    }
}
```

### Explanation

If **two burst times are same**, choose the process with **earlier arrival time**.

---

# 12. Execute the Process

```cpp
if(idx != -1) {
    time += p[idx].bt;
```

### Explanation

CPU runs that process.

Example:

```
time = 8
burst = 4
new time = 12
```

---

# 13. Calculate Completion Time

```cpp
p[idx].ct = time;
```

Formula:

```
Completion Time = current time
```

---

# 14. Calculate Turnaround Time

```cpp
p[idx].tat = p[idx].ct - p[idx].at;
```

Formula:

```
TAT = CT - AT
```

Example:

```
CT = 12
AT = 1
TAT = 11
```

---

# 15. Calculate Waiting Time

```cpp
p[idx].wt = p[idx].tat - p[idx].bt;
```

Formula:

```
WT = TAT - BT
```

Example:

```
TAT = 11
BT = 4
WT = 7
```

---

# 16. Mark Process Completed

```cpp
p[idx].completed = true;
completed++;
```

Explanation:

* Mark process as **finished**
* Increase completed counter

---

# 17. If No Process Arrived

```cpp
else {
    time++;
}
```

Explanation:

If CPU is **idle**, time moves forward.

---

# 18. Print Result Table

```cpp
cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
```

Output format:

| PID | AT | BT | CT | TAT | WT |

---

# 19. Calculate Average Times

```cpp
float total_wt = 0, total_tat = 0;
```

Loop adds all waiting and turnaround times.

---

# 20. Print Average

```cpp
cout << "\nAverage Waiting Time: " << total_wt / n;
cout << "\nAverage Turnaround Time: " << total_tat / n;
```

Formula:

```
Average WT = total WT / n
Average TAT = total TAT / n
```

---

# 21. Execution Order for Your Example

Input:

| Process | AT | BT |
| ------- | -- | -- |
| P1      | 0  | 8  |
| P2      | 1  | 4  |
| P3      | 2  | 9  |
| P4      | 3  | 5  |

Execution:

```
0 ----8   P1
8 ----12  P2
12---17   P4
17---26   P3
```

Gantt Chart:

```
| P1 | P2 | P4 | P3 |
0    8    12   17   26
```

---

✅ If you want, I can also show:

* **Even simpler SJF code (best for exams)**
* **How to write SJF Non-Preemptive in under 30 lines**
* **Step-by-step dry run table (teachers often ask this)**.
