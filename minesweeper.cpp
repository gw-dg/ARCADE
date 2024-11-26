
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Directions
const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

class Minesweeper
{
private:
    vector<vector<char>> board; // Actual board with mines ('*') and numbers
    vector<vector<bool>> revealed;
    int rows, cols, mines;

    bool isValid(int x, int y)
    {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }

    // Function to calculate adjacent mines
    int countAdjacentMines(int x, int y)
    {
        int count = 0;
        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (isValid(nx, ny) && board[nx][ny] == '*')
                count++;
        }
        return count;
    }

    // Function to place mines randomly on the board
    void placeMines()
    {
        int placedMines = 0;
        while (placedMines < mines)
        {
            int x = rand() % rows;
            int y = rand() % cols;
            if (board[x][y] != '*')
            {
                board[x][y] = '*';
                placedMines++;
            }
        }
    }

    // Function to initialize the board
    void initializeBoard()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (board[i][j] != '*')
                {
                    int count = countAdjacentMines(i, j);
                    board[i][j] = (count > 0) ? (count + '0') : ' ';
                }
            }
        }
    }

    // Recursive function to reveal cells
    void reveal(int x, int y)
    {
        if (!isValid(x, y) || revealed[x][y] || board[x][y] == '*')
            return;

        revealed[x][y] = true;

        if (board[x][y] == ' ')
        {
            for (int i = 0; i < 8; i++)
            {
                reveal(x + dx[i], y + dy[i]);
            }
        }
    }

    // Function to print the current state of the board
    void printBoard(bool showMines = false)
    {
        cout << "\033[2J\033[1;1H";
        cout << "   ";
        for (int i = 0; i < cols; i++)
            cout << i << " ";
        cout << endl;

        for (int i = 0; i < rows; i++)
        {
            cout << i << "  ";
            for (int j = 0; j < cols; j++)
            {
                if (showMines)
                {
                    cout << board[i][j] << " ";
                }
                else
                {
                    if (revealed[i][j])
                        cout << board[i][j] << " ";
                    else
                        cout << ". ";
                }
            }
            cout << endl;
        }
    }

public:
    Minesweeper(int r, int c, int m) : rows(r), cols(c), mines(m)
    {
        srand(time(0)); // Seed random generator once
        board = vector<vector<char>>(rows, vector<char>(cols, ' '));
        revealed = vector<vector<bool>>(rows, vector<bool>(cols, false));
        placeMines();
        initializeBoard();
    }

    void play()
    {
        int x, y;
        while (true)
        {
            printBoard();
            cout << "Enter cell to reveal (row and column): ";
            cin >> x >> y;

            if (!isValid(x, y))
            {
                cout << "Invalid cell. Try again.\n";
                continue;
            }

            if (board[x][y] == '*')
            {
                cout << "Game Over! You hit a mine.\n";
                printBoard(true);
                break;
            }

            reveal(x, y);

            // Check if all non-mine cells are revealed
            int revealedCount = 0;
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (revealed[i][j])
                        revealedCount++;
                }
            }

            if (revealedCount == rows * cols - mines)
            {
                cout << "Congratulations! You won the game.\n";
                printBoard(true);
                break;
            }
        }
    }
};

void gameStartMinesweeper()
{
    int rows = 5, cols = 5, mines = 5;
    cout << "Welcome to Minesweeper!\n";
    Minesweeper game(rows, cols, mines);
    game.play();
}
