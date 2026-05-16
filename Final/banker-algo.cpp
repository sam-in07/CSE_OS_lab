
#include <iostream>
using namespace std;

int main() {
    int process, resource;
    cout << "Enter number of processes: ";
    cin >> process;
   cout << "Enter number of resources: ";
    cin >> resource;
    int allocation[10][10];
    int maximum[10][10];
    int remaining[10][10];
    int available[10];
    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < process; i++) {
        for (int j = 0; j < resource; j++) {
            cin >> allocation[i][j];
        }
    }
    cout << "\nEnter Maximum Matrix:\n";
    for (int i = 0; i < process; i++) {
        for (int j = 0; j < resource; j++) {
            cin >> maximum[i][j];
        }
    }
    cout << "\nEnter Available Resources:\n";
    for (int i = 0; i < resource; i++) {
        cin >> available[i];
    }

    for (int i = 0; i < process; i++) {
        for (int j = 0; j < resource; j++) {
            remaining[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
    cout << "\nRemaining Matrix:\n";
    for (int i = 0; i < process; i++) {
        for (int j = 0; j < resource; j++) {
            cout << remaining[i][j] << " ";
        }
        cout << endl;
    }
    bool finished[10] = {false};
    int safeSequence[10];
    int count = 0;
    while (count < process) {
        bool found = false;
        for (int i = 0; i < process; i++) {
            if (!finished[i]) {

                bool possible = true;

                for (int j = 0; j < resource; j++) {

                    if (remaining[i][j] > available[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {

                    for (int j = 0; j < resource; j++) {
                        available[j] += allocation[i][j];
                    }

                    safeSequence[count] = i;
                    count++;
                    finished[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is NOT in safe state.\n";
            return 0;
        }
    }

    cout << "\nSystem is in SAFE state.\n";

    cout << "Safe Sequence: ";

    for (int i = 0; i < process; i++) {

        cout << "P" << safeSequence[i];

        if (i != process - 1)
            cout << " -> ";
    }

    cout << endl;

    return 0;
}




/*
Enter number of processes: 5
Enter number of resources: 3

Enter Allocation Matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

Enter Maximum Matrix:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

Enter Available Resources:
3 3 2

Need Matrix:
7 4 3
1 2 2
6 0 0
0 1 1
4 3 1





*/
