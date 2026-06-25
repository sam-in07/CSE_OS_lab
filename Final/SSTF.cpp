#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n, head;
    cout << "Enter number of requests: ";
    cin >> n;
    vector<int> requests(n);
    vector<bool> visited(n, false);
    cout << "Enter request queue: ";
    for (int i = 0; i < n; i++)
        cin >> requests[i];
    cout << "Enter initial head position: ";
    cin >> head;
    int totalSeek = 0;
    cout << "\nOrder of Service:\n";
    cout << head;
    for (int i = 0; i < n; i++) {
        int minDist = 1000000;
        int index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int dist = abs(head - requests[j]);

                if (dist < minDist) {
                    minDist = dist;
                    index = j;
                }
            }
        }
        visited[index] = true;
        totalSeek += minDist;
        head = requests[index];

        cout << " -> " << head;
    }
    cout << "\n\nTotal Seek Time = " << totalSeek << endl;
    cout << "Average Seek Time = "
         << (float)totalSeek / n << endl;
    return 0;
}