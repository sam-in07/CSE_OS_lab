#include <iostream>
#include <vector>
using namespace std;

int main() {
    int frames = 4;
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2};

    vector<int> frame(frames, -1);
    vector<int> lastUsed(frames, -1);

    int timer = 0;
    int pageFaults = 0;

    cout << "Page\tFrames\t\t\tStatus\n";

    for (int page : pages) {
        bool hit = false;

        // Check for hit
        for (int i = 0; i < frames; i++) {
            if (frame[i] == page) {
                hit = true;
                lastUsed[i] = timer++;
                break;
            }
        }

        // Page fault
        if (!hit) {
            int pos = -1;

            // Find empty frame
            for (int i = 0; i < frames; i++) {
                if (frame[i] == -1) {
                    pos = i;
                    break;
                }
            }

            // If full, replace LRU page
            if (pos == -1) {
                pos = 0;
                for (int i = 1; i < frames; i++) {
                    if (lastUsed[i] < lastUsed[pos])
                        pos = i;
                }
            }

            frame[pos] = page;
            lastUsed[pos] = timer++;
            pageFaults++;
        }

        cout << page << "\t";
        for (int x : frame) {
            if (x == -1)
                cout << "- ";
            else
                cout << x << " ";
        }
        cout << "\t\t" << (hit ? "Hit" : "Fault") << endl;
    }

    cout << "\nTotal Page Faults = " << pageFaults << endl;

    return 0;
}


