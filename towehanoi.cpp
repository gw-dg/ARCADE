#include <bits/stdc++.h>
using namespace std;

// display function
void dispRod(vector<stack<int>> &rods)
{
    cout << "\033[2J\033[1;1H";
    for (int i = 0; i < rods.size(); i++)
    {
        cout << i + 1 << " row: ";
        stack<int> temp = rods[i];
        vector<int> elements;

        while (!temp.empty())
        {
            elements.push_back(temp.top());
            temp.pop();
        }

        for (int j = elements.size() - 1; j >= 0; j--)
        {
            cout << elements[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isWin(stack<int> s, int n)
{
    if (s.size() != n)
        return false;
    int i = 1;
    while (!s.empty())
    {
        if (s.top() != i)
        {
            return false;
        }
        s.pop();
        i++;
    }
    return true;
}

void playTowerOfHanoi(int n)
{
    vector<stack<int>> rods(3); // 3 rods

    // first rod is initialized with disks
    for (int i = n; i >= 1; i--)
    {
        rods[0].push(i);
    }

    while (true)
    {
        dispRod(rods);

        if (isWin(rods[2], n))
        {
            cout << "Congratulations! You've solved the Tower of Hanoi.\n";
            break;
        }
        int from, to;
        cout << "Enter the rod to move from (1-3): ";
        cin >> from;
        cout << "Enter the rod to move to (1-3): ";
        cin >> to;

        if (from < 1 || from > 3 || to < 1 || to > 3 || from == to)
        {
            cout << "Invalid input. Please enter valid rod numbers.\n";
            continue;
        }

        // Adjusted for zero-based indexing
        from -= 1;
        to -= 1;

        // move validation
        if (rods[from].empty())
        {
            cout << "Invalid move: Source rod is empty.\n";
            continue;
        }

        if (!rods[to].empty() && rods[to].top() < rods[from].top())
        {
            cout << "Invalid move: Cannot place a larger disk on top of a smaller disk.\n";
            continue;
        }
        rods[to].push(rods[from].top());
        rods[from].pop();
    }
}

void gameStartTowerOfHanoi()
{
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;

    playTowerOfHanoi(n);
}
