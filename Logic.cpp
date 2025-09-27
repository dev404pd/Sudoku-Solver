#include<bits/stdc++.h>
using namespace std;

#define N 9

//function to print the board
void printBoard(vector<vector<int>> & board)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<<board[i][j]<<" ";

        }
        cout<<endl;
    }
}


//issafe is a function that checks the cell is valid to place the num or not
bool issafe(vector<vector<int>> &board, int row, int column, int num)
{
    //check if that row has same number
    for(int i =0;i<N;i++)
    {
        if(board[row][N]==num)
            return false;
    }
    //check if that column has same number
    for(int i =0;i<N;i++)
    {
        if(board[N][column]==num)
            return false;
    }
    //check the subgrid
    int startrow = row - row%3, startcolumn = column - column%3;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i+startrow][j+startcolumn] == num)
                return false;
        }
    }
    return true;

}

//Function thatsolves and places the number at proper place
//uses backtracking
//here we traverse the board first left to right then top to bottom
//here initializing row and column in call and not in function body
// becoz it will always reset it even when we are recursively calling it
bool solveSudoku(vector<vector<int>> &board,int row =0, int column =0)
{
    //We’re at the end of the last row (row index 8 is the bottom row).
    //And we’ve just moved past the last column (col == 9).
    //this is base case i.e we have traverse entire board
    if(row==N-1 && column == N)
        return true;
    
    //if column reached last point start traversing next row
    if(column == N)
    {
        row++;
        column = 0;
    }

    //if cell is non zero i.e already filled
    //move to next coumn i.e column+1
    if(board[row][column] != 0)
    {
        return solveSudoku(board,row,column+1);
    }

    //if it is zero then 
    //1.check if it safe to place
    //

    for(int num=1;num<=N;num++)
    {
        if(issafe(board, row, column, num))
        {
            board[row][column] = num;
            //recursion till all cells are resolved
            if(solveSudoku(board, row, column+1))
                return true;
            //if it returns falls means it hit the dead end
            //backtrack algo by one step make the row column zero zero

            board[row][column] = 0; 
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
