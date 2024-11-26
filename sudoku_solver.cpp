#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

#define PUZZLE_SIZE 9
#define EMPTY_VALUE 0

int numberOfSolution = 0;

// Function to print the Sudoku board
void printBoard(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE])
{
    cout << "\033[2J\033[1;1H";
    // std::cout << std::endl;
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            // Print vertical border
            if (j % 3 == 0 && j != 0)
            {
                std::cout << "| ";
            }
            // Print cell value or empty space
            std::cout << (puzzle[i][j] == EMPTY_VALUE ? "." : std::to_string(puzzle[i][j])) << " ";
        }
        std::cout << std::endl;

        // Print horizontal border
        if ((i + 1) % 3 == 0 && i != PUZZLE_SIZE - 1)
        {
            std::cout << "---------------------" << std::endl;
        }
    }
    std::cout << std::endl;
}

// Check if placing a number is safe in a given cell
bool isSafe(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE], int row, int col, int num)
{
    // Check row and column
    for (int x = 0; x < PUZZLE_SIZE; x++)
    {
        if (puzzle[row][x] == num || puzzle[x][col] == num)
        {
            return false;
        }
    }
    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }
    return true;
}

// Recursive function to solve the Sudoku using backtracking
bool solveSudoku(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE])
{
    int row = -1;
    int col = -1;
    bool isEmpty = true;

    // Find the first empty cell (with EMPTY_VALUE)
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            if (puzzle[i][j] == EMPTY_VALUE)
            {
                row = i;
                col = j;
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty)
            break;
    }

    // If there are no empty cells, we've solved the puzzle
    if (isEmpty)
    {
        numberOfSolution++;
        return true;
    }

    // Try placing numbers 1 to 9 in the current empty cell
    for (int num = 1; num <= PUZZLE_SIZE; num++)
    {
        if (isSafe(puzzle, row, col, num))
        {
            puzzle[row][col] = num;

            if (solveSudoku(puzzle))
            {
                if (numberOfSolution > 1)
                    return false; // Stop if more than one solution is found
            }

            // Backtrack if the current number placement doesn't lead to a solution
            puzzle[row][col] = EMPTY_VALUE;
        }
    }

    return false;
}

// Dummy function to fill the puzzle with a complete solution (replace with actual logic)
void fillPuzzle(int (&puzzle)[PUZZLE_SIZE][PUZZLE_SIZE])
{
    int samplePuzzle[PUZZLE_SIZE][PUZZLE_SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    // Copy sample grid to the actual puzzle
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            puzzle[i][j] = samplePuzzle[i][j];
        }
    }

    // Solve the grid to fill all values and use as the starting solution
    solveSudoku(puzzle);
}

// Function to generate a Sudoku puzzle with a given difficulty level
void generatePuzzle(int (&puzzle)[PUZZLE_SIZE][PUZZLE_SIZE], int difficulty = 1)
{
    // Initialize the grid with empty values
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            puzzle[i][j] = EMPTY_VALUE;
        }
    }

    // Fill the puzzle with a complete solution
    fillPuzzle(puzzle);

    // Seed the random number generator
    srand((unsigned)time(0));

    // Start removing elements based on difficulty level
    int attempt = difficulty;
    while (attempt > 0)
    {
        // Select a random cell that is not already empty
        int row = rand() % PUZZLE_SIZE;
        int col = rand() % PUZZLE_SIZE;
        while (puzzle[row][col] == EMPTY_VALUE)
        {
            row = rand() % PUZZLE_SIZE;
            col = rand() % PUZZLE_SIZE;
        }

        // Temporarily remove the cell value
        int backupValue = puzzle[row][col];
        puzzle[row][col] = EMPTY_VALUE;

        // Reset the number of solutions and attempt to solve the puzzle
        numberOfSolution = 0;
        solveSudoku(puzzle);

        // If the number of solutions is not exactly one, restore the value
        if (numberOfSolution != 1)
        {
            puzzle[row][col] = backupValue;
            attempt--;
        }
    }
}

// Function to play with the generated Sudoku puzzle
void playSudoku(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE])
{
    int row, col, num;
    char s;
    while (true)
    {
        std::cout << "Current Sudoku Puzzle:" << std::endl;
        printBoard(puzzle);

        std::cout << "Enter your move (row, column, number) or -1 to quit: ";
        std::cin >> row;

        // Exit condition
        if (row == -1)
            break;
        // Input for column and number
        std::cin >> col >> num;

        // Validate row, column, and number
        if (std::cin.fail() || row < 0 || row >= PUZZLE_SIZE || col < 0 || col >= PUZZLE_SIZE || num < 1 || num > 9)
        {
            std::cout << "Invalid input. Please enter valid values (row 0-8, column 0-8, number 1-9)." << std::endl;
            std::cin.clear();                                                   // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters in the input buffer
            continue;                                                           // Prompt for input again
        }

        // Check if the move is valid
        if (isSafe(puzzle, row, col, num) && puzzle[row][col] == EMPTY_VALUE)
        {
            puzzle[row][col] = num;
            std::cout << "Move accepted." << std::endl;
        }
        else
        {
            std::cout << "Invalid move. The cell is already filled or the number cannot be placed there." << std::endl;
        }
    }
}

void gameStartSudoku()
{
    int puzzle[PUZZLE_SIZE][PUZZLE_SIZE] = {0};
    int difficulty = 10; // Example difficulty level (can be adjusted)
    generatePuzzle(puzzle, difficulty);

    playSudoku(puzzle);
}