#include <bits/stdc++.h>
using namespace std;

#define N 9  // Sudoku size

// Check if placing num at board[row][column] is valid
bool isSafe(vector<vector<int>> &board, int row, int column, int num) {
    // Row check
    for (int x = 0; x < N; x++)
        if (board[row][x] == num) return false;

    // columnumn check
    for (int x = 0; x < N; x++)
        if (board[x][column] == num) return false;

    // 3x3 subgrid check
    int startRow = row - row % 3, startcolumn = column - column % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + startRow][j + startcolumn] == num) return false;

    return true;
}

// Backtracking solver
bool solveSudoku(vector<vector<int>> &board, int row = 0, int column = 0) {
    if (row ==  N) 
        return true;
    if (column == N) 
        return solveSudoku(board, row+1, 0);
    if (board[row][column] != 0) 
        return solveSudoku(board, row, column + 1);

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, column, num)) {
            board[row][column] = num;
            if (solveSudoku(board, row, column + 1)) return true;
            board[row][column] = 0; // backtrack
        }
    }
    return false;
}

// Function to print the Sudoku board
void printBoard(vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
            if((j+1)%3==0)
                cout<<" ";
        }
        cout<<endl;
        if((i+1)%3 ==0 && i<N-1 )
            cout<<endl;
       
    }
}


//Generate a board filled with solved sudoku
vector<vector<int>> generateboard()
{
    vector<vector<int>> board(N,vector<int>(N,0));
    solveSudoku(board);
    return board;
}

//empty cell randomly to generate solvable sudoku
void boardtoplay(vector<vector<int>> &board, int blanks)
{
    srand(time(0));
    while(blanks>0)
    {
        int row = rand()%N;
        int column = rand()%N;
        if(board[row][column] != 0)
        {
            board[row][column] = 0;
            blanks--;
        }
    }
}




int main() {
    int n;
    cout << "Enter level of game\n";
    cout<<" 1. Easy \n 2. Medium \n 3. Hard\n";
    cin>>n;

    vector<vector<int>> board = generateboard();

    cout << "Generated board (solved):\n";
    printBoard(board);
    if(n==1)
    {
        cout << "\nPuzzle for user:\n";
        boardtoplay(board,25);
        printBoard(board);
    }
    else if(n==2)
    {
        cout << "\nPuzzle for user:\n";
        boardtoplay(board,40);
        printBoard(board);
    }
    else if(n==3)
    {
        cout << "\nPuzzle for user:\n";
        boardtoplay(board,55);
        printBoard(board);
    }
    return 0;
}