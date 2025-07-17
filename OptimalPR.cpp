 #include <bits/stdc++.h>
using namespace std;

void printMemory(vector<int> &memory)
{
    for (auto page : memory)
    {
        cout << page << " ";
    }
    cout << endl;
}

int optimal(vector<int> &pages, int frameSize)
{
    vector<int> memory;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); ++i)
    {
        int page = pages[i];
        auto it = find(memory.begin(), memory.end(), page);

        cout << "Accessed: " << page << " -> ";

        if (it == memory.end()) // Page fault
        {
            pageFaults++;

            if (memory.size() < frameSize)
            {
                memory.push_back(page);
            }
            else
            {
                // Find the page in memory with the farthest next use
                int indexToReplace = -1;
                int farthestNextUse = -1;

                for (int j = 0; j < memory.size(); ++j)
                {
                    int nextUse = INT_MAX;

                    for (int k = i + 1; k < pages.size(); ++k)
                    {
                        if (pages[k] == memory[j])
                        {
                            nextUse = k;
                            break;
                        }
                    }

                    if (nextUse > farthestNextUse)
                    {
                        farthestNextUse = nextUse;
                        indexToReplace = j;
                    }
                }

                memory[indexToReplace] = page;
            }

            printMemory(memory);
            cout << "Result: Page Fault ✅\n";
        }
        else // Page hit
        {
            printMemory(memory);
            cout << "Result: Hit ❌\n";
        }
    }

    return pageFaults;
}

int main()
{
    int n;
    cout << "Enter Page Reference String Size: ";
    cin >> n;

    vector<int> rs(n);
    cout << "Enter the Page Reference String (space-separated): ";
    for (int i = 0; i < n; i++)
    {
        cin >> rs[i];
    }

    int frame;
    cout << "Enter number of frames: ";
    cin >> frame;

    cout << "\n--- Optimal Page Replacement Simulation ---\n";
    int pageFaults = optimal(rs, frame);
    cout << "\nTotal Page Faults: " << pageFaults << endl;

    return 0;
}
