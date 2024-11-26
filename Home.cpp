#include <bits/stdc++.h>
#include "cross.cpp"
#include "checkers.cpp"
#include "towehanoi.cpp"
#include "minesweeper.cpp"
#include "guess.cpp"
#include "sudoku_solver.cpp"
using namespace std;

// Function declarations
void playCrossword();
void playCheckers();
void playGuess();
void playMinesweeper();
void playSudokuSolver();
void playTowerOfHanoi();

void playCheckers()
{
    gameStartCheckers();
}

void playGuess()
{
    gameStartGuess();
}

void playMinesweeper()
{
    gameStartMinesweeper();
}

void playSudokuSolver()
{
    gameStartSudoku();
}

void playTowerOfHanoi()
{
    gameStartTowerOfHanoi();
}

void playCrossword()
{
    gameStartCrossword();
}
void displayMenu()
{
    cout << "\033[2J\033[1;1H";
    cout << "Welcome to ARCADE! Select a game to play:\n";
    cout << "1. Checkers\n";
    cout << "2. 20 Questions\n";
    cout << "3. Minesweeper\n";
    cout << "4. Sudoku Solver\n";
    cout << "5. Tower of Hanoi\n";
    cout << "6. Crossword\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    int choice;
    while (true)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            playCheckers();
            break;
        case 2:
            playGuess();
            break;
        case 3:
            playMinesweeper();
            break;
        case 4:
            playSudokuSolver();
            break;
        case 5:
            playTowerOfHanoi();
            break;
        case 6:
            playCrossword();
            break;
        case 7:
            cout << "Thank you for playing ARCADE. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
