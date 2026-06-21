
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
    vector<int> lastUsed(frames, -1);

    int timer = 0;
    int pageFaults = 0;

    cout << "\nPage\tFrames\t\t\tStatus\n";

    for (int page : pages) {
        bool hit = false;
        int replaced = -1;

        // Check hit
        for (int i = 0; i < frames; i++) {
            if (frame[i] == page) {
                hit = true;
                lastUsed[i] = timer++;
                break;
            }
        }

        if (!hit) {
            int pos = -1;

            // Empty frame
            for (int i = 0; i < frames; i++) {
                if (frame[i] == -1) {
                    pos = i;
                    break;
                }
            }

            // Find LRU page
            if (pos == -1) {
                pos = 0;
                for (int i = 1; i < frames; i++) {
                    if (lastUsed[i] < lastUsed[pos])
                        pos = i;
                }
                replaced = frame[pos];
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


/*

4
15
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2

*/




