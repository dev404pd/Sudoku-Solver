#include <bits/stdc++.h>
using namespace std;

#define N 9  // Sudoku size

// Function to print the Sudoku board
void printBoard(vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Check if placing num at board[row][col] is valid
bool isSafe(vector<vector<int>> &board, int row, int col, int num) {
    // Row check
    for (int x = 0; x < N; x++)
        if (board[row][x] == num) return false;

    // Column check
    for (int x = 0; x < N; x++)
        if (board[x][col] == num) return false;

    // 3x3 subgrid check
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + startRow][j + startCol] == num) return false;

    return true;
}

// Backtracking solver
bool solveSudoku(vector<vector<int>> &board, int row = 0, int col = 0) {
    if (row == N - 1 && col == N) return true;
    if (col == N) { row++; col = 0; }
    if (board[row][col] != 0) return solveSudoku(board, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board, row, col + 1)) return true;
            board[row][col] = 0; // backtrack
        }
    }
    return false;
}

int main() {
    vector<vector<int>> board = {
    {5,3,0,0,7,0,0,0,0},
    {6,0,0,1,9,5,0,0,0},
    {0,9,8,0,0,0,0,6,0},
    {8,0,0,0,6,0,0,0,3},
    {4,0,0,8,0,3,0,0,1},
    {7,0,0,0,2,0,0,0,6},
    {0,6,0,0,0,0,2,8,0},
    {0,0,0,4,1,9,0,0,5},
    {0,0,0,0,8,0,0,7,9}
};

    if (solveSudoku(board))
        printBoard(board);
    else
        cout << "No solution exists" << endl;

    return 0;
}