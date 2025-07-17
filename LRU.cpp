 #include<bits/stdc++.h>
using namespace std;

void printMemory(vector<int> &memory)
{
    for(auto page : memory)
    {
        cout << page << " ";
    }
    cout << endl;
}

int lru(vector<int> &pages, int frame)
{
    vector<int> memory; // contains the current memory frame contents
    int pageFault = 0;
    unordered_map<int,int> lastUsed; // page -> last used index

    for(int i = 0; i < pages.size(); i++)
    {
        int page = pages[i];
        auto it = find(memory.begin(), memory.end(), page);

        cout << "Accessed: " << page << " -> ";

        if(it == memory.end()) //pf
        {
            pageFault++;
            if(memory.size() < frame)//accommodate
            {
                memory.push_back(page);
            }
            else
            {
                //find lru of current memory contents
                int lruIndex = i, lruPage;
                for(int p : memory)
                {
                    if(lastUsed[p] < lruIndex)
                    {
                        lruIndex = lastUsed[p];
                        lruPage = p;
                    }
                }
                replace(memory.begin(), memory.end(), lruPage, page);
            }
            printMemory(memory);
            cout << "Result: Page Fault ✅\n";
        }
        else // Page Hit
        {
            printMemory(memory);
            cout << "Result: Hit ❌\n";
        }

        lastUsed[page] = i;
    }
    return pageFault;
}

int main()
{
    int n;
    cout << "Enter Page Reference String Size: ";
    cin >> n;

    vector<int> rs(n);
    cout << "Enter the Page Reference String (space-separated): ";
    for(int i = 0; i < n; i++)
    {
        cin >> rs[i];
    }

    int frame;
    cout << "Enter number of frames: ";
    cin >> frame;

  
    int pageFault = lru(rs, frame);
    cout<<endl;
    cout << "Total Page Faults: " << pageFault << endl;

    return 0;
}
