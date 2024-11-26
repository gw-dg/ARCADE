#include <bits/stdc++.h>
using namespace std;

const int GRID_SIZE = 16;
char grid[GRID_SIZE][GRID_SIZE] = {
    {' ', ' ', ' ', ' ', ' ', 'H', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', 'C', ' ', 'A', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', 'A', 'P', 'P', 'L', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', 'T', ' ', 'P', ' ', 'L', 'O', 'R', 'D', 'S', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', 'Y', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'H', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', 'B', 'A', 'N', 'A', 'N', 'A', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'N', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', 'G', 'U', 'I', 'T', 'A', 'R', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', 'L', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', 'A', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', 'G', 'A', 'R', 'L', 'A', 'N', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
char crossword[GRID_SIZE][GRID_SIZE] = {
    {' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', '_', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', '_', '_', '_', '_', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', '_', ' ', '_', ' ', '_', '_', '_', '_', '_', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', '_', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
string words[] = {
    "apple", "cat", "happy", "guitar", "elephant", "banana", "island", "garland", "lords"};
string hints[] = {
    "A fruit that keeps the doctor away",     // apple
    "A small animal, often a pet",            // cat
    "Feeling joy or contentment",             // happy
    "A musical instrument with strings",      // guitar
    "A large mammal with a trunk",            // elephant
    "A yellow fruit, often seen in bunches",  // banana
    "A place surrounded by water",            // island
    "A type of flower or a decorative plant", // garland
    "A title for a noble or ruler"            // lords
};

class node
{
public:
    string word;
    string hint;
    bool wordFound;
    node *next;

    node(string w, string h) : word(w), hint(h), wordFound(false), next(nullptr) {}
};

class HashMap
{
private:
    static const int TABLE_SIZE = 26;
    node *table[TABLE_SIZE];

public:
    HashMap()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            table[i] = nullptr;
        }
    }

    // Polynomial hash function
    // hash(s) = (s0 * p ^ 0 + s1 * p ^ 1 + s2 * p ^ 2 + ... + sn - 1 * p ^ (n - 1)) % m
    // int hashFunction(string word)
    // {
    //     const int p = 31;  // Base, a small prime number
    //     const int m = 100; // number of slots

    //     long long hashValue = 0;
    //     long long power = 1;

    //     for (char c : word)
    //     {
    //         hashValue = (hashValue + (c - 'a' + 1) * power) % m;
    //         power = (power * p) % m;
    //     }

    //     return hashValue % m;
    // }
    int hashFunction(string word)
    {
        const int prime = 31;
        long long hashValue = 0;

        for (char c : word)
        {
            hashValue = (hashValue * prime + (c - 'a' + 1)) % TABLE_SIZE;
        }

        return hashValue;
    }

    void insert(string word, string hint)
    {
        int index = hashFunction(word);
        node *newNode = new node(word, hint);

        newNode->next = table[index];
        table[index] = newNode;
    }

    bool search(string word)
    {
        int index = hashFunction(word);
        node *current = table[index];
        while (current)
        {
            if (current->word == word)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void markWordFound(string word)
    {
        int index = hashFunction(word);
        node *current = table[index];
        while (current)
        {
            if (current->word == word)
            {
                current->wordFound = true;
                return;
            }
            current = current->next;
        }
    }

    bool getHint(string word)
    {
        int index = hashFunction(word);
        node *current = table[index];
        while (current)
        {
            if (current->word == word)
            {
                return current->wordFound;
            }
            current = current->next;
        }
        return false;
    }
};

void displayCross(char grid[][GRID_SIZE], HashMap &hs)
{
    cout << "\033[2J\033[1;1H";
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";
    cout << "Hints : \n";
    for (int i = 0; i < 9; i++)
    {
        if (!hs.getHint(words[i]))
        {
            cout << hints[i] << "\n";
        }
    }
}

bool wordExists(string input, string words[])
{

    for (int i = 0; i < 9; i++)
    {
        if (words[i] == input)
            return true;
    }
    return false;
}

bool isWin(char (&crossword)[GRID_SIZE][GRID_SIZE], char (&grid)[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] != crossword[i][j])
                return false;
        }
    }
    return true;
}

void placeWord(string input, char (&crossword)[GRID_SIZE][GRID_SIZE], char (&grid)[GRID_SIZE][GRID_SIZE], HashMap &hs)
{
    string wordFound = "";
    bool isWordFound = false;
    int endIndexRow = -1, colIndex = -1;
    // checking words vertically
    for (int i = 0; i < GRID_SIZE; i++)
    {

        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[j][i] != ' ')
            {
                wordFound.push_back(towlower(grid[j][i]));
            }
            else
            {
                if (wordFound == input)
                {
                    isWordFound = true;
                    endIndexRow = j;
                    break;
                }
                else
                {
                    wordFound = "";
                }
            }
        }
        if (isWordFound)
        {
            hs.markWordFound(input);
            // cout << wordFound << "\n";
            int k = input.size(), j = endIndexRow;
            while (k >= 0)
            {
                crossword[j][i] = grid[j][i];
                j--;
                k--;
            }
            return;
        }
    }

    wordFound = "";
    isWordFound = false;
    int endIndexCol = -1, rowIndex = -1;
    // check word horizontally
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] != ' ')
            {
                wordFound.push_back(towlower(grid[i][j]));
            }
            else
            {
                if (wordFound == input)
                {
                    isWordFound = true;
                    endIndexCol = j;
                    break;
                }
                else
                {
                    wordFound = "";
                }
            }
        }
        if (isWordFound)
        {
            hs.markWordFound(input);
            int k = input.size(), j = endIndexCol;
            while (k >= 0)
            {
                crossword[i][j] = grid[i][j];
                j--;
                k--;
            }
            return;
        }
    }
}

void gameStartCrossword()
{
    HashMap hs;
    for (int i = 0; i < 9; i++)
    {
        hs.insert(words[i], hints[i]);
    }
    while (1)
    {
        displayCross(crossword, hs);
        string input;
        cout << "Enter a word : ";
        cin >> input;
        if (hs.search(input))
        {
            placeWord(input, crossword, grid, hs);
        }
        else
            cout << "Enter a correct word!";
        if (isWin(crossword, grid))
        {
            displayCross(crossword, hs);
            cout << "YOU WIN!!!\n";
            break;
        }
    }
}