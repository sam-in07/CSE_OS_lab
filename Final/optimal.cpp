#include <iostream>
#include <vector>
using namespace std;
int main() {
    int frames, n;
     cout << "Enter number of frames: ";
    cin >> frames;
     cout << "Enter number of pages: ";
    cin >> n;
    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++)
        cin >> pages[i];
    vector<int> frame(frames, -1);
    int pageFaults = 0;
    cout << "\nPage\tFrames\t\t\tStatus\n";
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool hit = false;
        int replaced = -1;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                hit = true;
                break;
            }
        }
        if (!hit) {
            int pos = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }
              if (pos == -1) {
                int farthest = -1;

                for (int j = 0; j < frames; j++) {
                    int nextUse = n; // Assume page won't be used again

                    for (int k = i + 1; k < n; k++) {
                        if (pages[k] == frame[j]) {
                            nextUse = k;
                            break;
                        }
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        pos = j;
                    }
                }
                replaced = frame[pos];
            }
            frame[pos] = page;
            pageFaults++;
        }
        cout << page << "\t";
        for (int x : frame) {
            if (x == -1)
                cout << "- ";
            else
                cout << x << " ";
        }
        if (hit)
            cout << "\tHit";
        else {
            cout << "\tFault";
            if (replaced != -1)
                cout << " (" << replaced << " replaced)";
        }
        cout << endl;
    }
    cout << "\nTotal Page Faults = " << pageFaults << endl;
    return 0;
}