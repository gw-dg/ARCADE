#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
void sleep(int milliseconds)
{
    Sleep(milliseconds);
}
// Initialize the board
char board[10][10] = {{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
                      {'1', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', '|'},
                      {'2', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', '|'},
                      {'3', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', '|'},
                      {'4', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                      {'5', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
                      {'6', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', '|'},
                      {'7', ' ', 'x', ' ', 'x', ' ', 'x', ' ', 'x', '|'},
                      {'8', 'x', ' ', 'x', ' ', 'x', ' ', 'x', ' ', '|'},
                      {'9', '-', '-', '-', '-', '-', '-', '-', '-', '-'}};

// Function to display the board
void dispBoard(char board[][10])
{
    cout << "\033[2J\033[1;1H"; // Clear screen and move cursor to top-left

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

class CheckersAI
{
public:
    // Get all valid moves for a player
    vector<pair<pair<int, int>, pair<int, int>>> getAllValidMoves(char board[][10], char player)
    {
        vector<pair<pair<int, int>, pair<int, int>>> moves;
        for (int i = 1; i <= 8; i++)
        {
            for (int j = 1; j <= 8; j++)
            {
                if (board[i][j] == player || board[i][j] == toupper(player))
                {
                    bool isKing = (board[i][j] == toupper(player));

                    // Determine valid movement directions based on piece type
                    vector<int> rowDirections;
                    if (isKing)
                    {
                        rowDirections = {-1, 1}; // Kings can move both directions
                    }
                    else if (player == 'o')
                    {
                        rowDirections = {1}; // 'o' moves down only
                    }
                    else
                    {                         // player == 'x'
                        rowDirections = {-1}; // 'x' moves up only
                    }

                    // Check moves in allowed directions
                    for (int di : rowDirections)
                    {
                        for (int dj : {-1, 1})
                        { // Always check both diagonal columns
                            // Check regular moves
                            int ni = i + di, nj = j + dj;
                            if (ni >= 1 && ni <= 8 && nj >= 1 && nj <= 8 && board[ni][nj] == ' ')
                            {
                                moves.push_back({{i, j}, {ni, nj}});
                            }

                            // Check capture moves
                            ni = i + 2 * di;
                            nj = j + 2 * dj;
                            int midRow = i + di;
                            int midCol = j + dj;

                            if (ni >= 1 && ni <= 8 && nj >= 1 && nj <= 8 &&
                                board[ni][nj] == ' ' &&
                                (board[midRow][midCol] == (player == 'o' ? 'x' : 'o') ||
                                 board[midRow][midCol] == (player == 'o' ? 'X' : 'O')))
                            {
                                moves.push_back({{i, j}, {ni, nj}});
                            }
                        }
                    }
                }
            }
        }
        return moves;
    }

    // Other methods remain the same
    int evaluateBoard(char board[][10], char player)
    {
        int score = 0;
        for (int i = 1; i <= 8; i++)
        {
            for (int j = 1; j <= 8; j++)
            {
                if (board[i][j] == 'o')
                    score += 10;
                else if (board[i][j] == 'O')
                    score += 20;
                else if (board[i][j] == 'x')
                    score -= 10;
                else if (board[i][j] == 'X')
                    score -= 20;

                // Add positional bonuses
                if (board[i][j] == 'o' || board[i][j] == 'O')
                {
                    score += i; // Reward forward progression for 'o'
                }
                else if (board[i][j] == 'x' || board[i][j] == 'X')
                {
                    score -= (9 - i); // Reward forward progression for 'x'
                }
            }
        }
        return (player == 'o') ? score : -score;
    }

    int minimax(char board[][10], int depth, bool maximizingPlayer, char player)
    {
        if (depth == 0)
        {
            return evaluateBoard(board, player);
        }

        vector<pair<pair<int, int>, pair<int, int>>> allMoves =
            getAllValidMoves(board, maximizingPlayer ? player : (player == 'o' ? 'x' : 'o'));

        if (allMoves.empty())
        {
            return evaluateBoard(board, player);
        }

        int bestValue = maximizingPlayer ? INT_MIN : INT_MAX;

        for (auto move : allMoves)
        {
            char tempBoard[10][10];
            memcpy(tempBoard, board, sizeof(char) * 10 * 10);
            applyMove(tempBoard, move.first.first, move.first.second,
                      move.second.first, move.second.second);

            int value = minimax(tempBoard, depth - 1, !maximizingPlayer, player);

            if (maximizingPlayer)
            {
                bestValue = max(bestValue, value);
            }
            else
            {
                bestValue = min(bestValue, value);
            }
        }

        return bestValue;
    }

    pair<pair<int, int>, pair<int, int>> findBestMove(char board[][10], char player, int depth)
    {
        int bestValue = INT_MIN;
        pair<pair<int, int>, pair<int, int>> bestMove = {{-1, -1}, {-1, -1}};
        vector<pair<pair<int, int>, pair<int, int>>> allMoves = getAllValidMoves(board, player);

        for (auto move : allMoves)
        {
            char tempBoard[10][10];
            memcpy(tempBoard, board, sizeof(char) * 10 * 10);
            applyMove(tempBoard, move.first.first, move.first.second,
                      move.second.first, move.second.second);

            int moveValue = minimax(tempBoard, depth - 1, false, player);

            if (moveValue > bestValue)
            {
                bestValue = moveValue;
                bestMove = move;
            }
        }

        return bestMove;
    }

    void applyMove(char board[][10], int srcRow, int srcCol, int dstRow, int dstCol)
    {
        char piece = board[srcRow][srcCol];
        board[dstRow][dstCol] = piece;
        board[srcRow][srcCol] = ' ';

        if (abs(dstRow - srcRow) == 2)
        {
            int midRow = (srcRow + dstRow) / 2;
            int midCol = (srcCol + dstCol) / 2;
            board[midRow][midCol] = ' ';
        }

        // King promotion
        if (piece == 'o' && dstRow == 8)
            board[dstRow][dstCol] = 'O';
        else if (piece == 'x' && dstRow == 1)
            board[dstRow][dstCol] = 'X';
    }
};

// Function to validate and make a move
bool Move(int srcRow, int srcCol, int dstRow, int dstCol, char player, bool isKing, char board[][10])
{
    // Ensure source and destination are within bounds
    if (!(srcRow >= 1 && srcRow <= 8 && srcCol >= 1 && srcCol <= 8 &&
          dstRow >= 1 && dstRow <= 8 && dstCol >= 1 && dstCol <= 8))
    {
        cout << "Move out of bounds. Please try again.\n";
        return false;
    }

    // Ensure the source contains the correct player's piece
    if (board[srcRow][srcCol] != player && board[srcRow][srcCol] != toupper(player))
    {
        cout << "Source does not contain your piece. Please try again.\n";
        return false;
    }

    // Ensure the destination is empty
    if (board[dstRow][dstCol] != ' ')
    {
        cout << "Destination is not empty. Please try again.\n";
        return false;
    }

    // Movement rules for Player 'o'
    if (player == 'o')
    {
        if (isKing)
        {
            // King: Can move diagonally in any direction by 1 step
            if (abs(dstRow - srcRow) == 1 && abs(dstCol - srcCol) == 1)
            {
                board[dstRow][dstCol] = 'O';
                board[srcRow][srcCol] = ' ';
                return true;
            }
        }
        else
        {
            // Regular piece: Can only move diagonally forward
            if (dstRow - srcRow == 1 && abs(dstCol - srcCol) == 1)
            {
                board[dstRow][dstCol] = 'o';
                board[srcRow][srcCol] = ' ';
                return true;
            }
            // Capture logic for 'o'
            if (dstRow - srcRow == 2 && abs(dstCol - srcCol) == 2)
            {
                int midRow = (srcRow + dstRow) / 2;
                int midCol = (srcCol + dstCol) / 2;
                if (board[midRow][midCol] == 'x' || board[midRow][midCol] == 'X')
                {
                    board[midRow][midCol] = ' ';
                    board[dstRow][dstCol] = 'o';
                    board[srcRow][srcCol] = ' ';
                    return true;
                }
            }
        }
    }

    // Movement rules for Player 'x'
    if (player == 'x')
    {
        if (isKing)
        {
            // King: Can move diagonally in any direction by 1 step
            if (abs(dstRow - srcRow) == 1 && abs(dstCol - srcCol) == 1)
            {
                board[dstRow][dstCol] = 'X';
                board[srcRow][srcCol] = ' ';
                return true;
            }
        }
        else
        {
            // Regular piece: Can only move diagonally forward
            if (srcRow - dstRow == 1 && abs(dstCol - srcCol) == 1)
            {
                board[dstRow][dstCol] = 'x';
                board[srcRow][srcCol] = ' ';
                return true;
            }
            // Capture logic for 'x'
            if (srcRow - dstRow == 2 && abs(dstCol - srcCol) == 2)
            {
                int midRow = (srcRow + dstRow) / 2;
                int midCol = (srcCol + dstCol) / 2;
                if (board[midRow][midCol] == 'o' || board[midRow][midCol] == 'O')
                {
                    board[midRow][midCol] = ' ';
                    board[dstRow][dstCol] = 'x';
                    board[srcRow][srcCol] = ' ';
                    return true;
                }
            }
        }
    }

    cout << "Invalid move. Please try again.\n";
    return false;
}

void gameStartCheckers()
{
    CheckersAI ai;
    dispBoard(board);

    while (true)
    {
        char player;
        int srcRow, srcCol, dstRow, dstCol;

        // Alternate turns between players 'o' and 'x'
        static int turn = 0;
        player = (turn % 2 == 0) ? 'o' : 'x';

        if (player == 'x')
        {
            // AI's turn
            cout << "AI is thinking...\n";
            sleep(100);
            auto move = ai.findBestMove(board, player, 3); // Depth 3 for Minimax
            if (move.first.first == -1)
            {
                cout << "No valid moves left. Game over.\n";
                break;
            }
            ai.applyMove(board, move.first.first, move.first.second, move.second.first, move.second.second);
        }
        else
        {
            // Player's turn
            // cout << "Player " << player << "'s turn.\n";
            // cout << "Enter source row and column: ";
            // cin >> srcRow >> srcCol;
            // cout << "Enter destination row and column: ";
            // cin >> dstRow >> dstCol;
            cout << "AI is thinking...\n";
            sleep(100);
            auto move = ai.findBestMove(board, player, 3); // Depth 3 for Minimax
            if (move.first.first == -1)
            {
                cout << "No valid moves left. Game over.\n";
                break;
            }
            ai.applyMove(board, move.first.first, move.first.second, move.second.first, move.second.second);
            // bool isKing = (board[srcRow][srcCol] == toupper(player));
            // if (!Move(srcRow, srcCol, dstRow, dstCol, player, isKing, board))
            //     continue;
        }

        dispBoard(board);
        turn++; // Switch turns
    }

    // return 0;
}
