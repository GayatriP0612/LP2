// N Queens Problem

#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>> &board, int row, int col){
    // column check
    int n = board.size();

    for(int i = 0; i< row; i++){
        if(board[i][col] == 1){
            return false;
        }
    }

    //check left diagonal
    for(int i= row, j=col; i>=0 && j >=0; i--, j--){
        if(board[i][j] == 1){
            return false;
        }
    }

    // check right diagonal
    for(int i= row, j=col; i>=0 && j<n; i--, j++){
        if(board[i][j] == 1){
            return false;
        }
    }

    return true;
}

void printBorad(vector<vector<int>> &board){
    int n = board.size();
    for(int i=0; i<n; i++){
        for(int j = 0; j<n; j++){
            cout << (board[i][j] == 1 ? "Q" : "-");
        }
        cout << endl;
    }
}

void NQueens(vector<vector<int>> &board, int row, int &count){
    int n= board.size();
    //already solution
    if(row == n){
        count ++;
        cout << "Solution: "<< count << endl;
        printBorad(board);
        return;
    }

    for(int col = 0; col<n; col++){
        if(isSafe(board, row, col)){
            board[row][col] = 1;
            
            NQueens(board, row+1, count);

            board[row][col] = 0;
        }
    }
}

void bndtNQueens(vector<vector<int>> &board, int row, int &count, vector<bool> &cols, vector<bool> & diag1, vector<bool> &diag2){
    int n = board.size();
    if(row == n){
        count++;
        cout << "Solution: " << count << endl;
        printBorad(board);
        return;
    }

    for(int col=0; col<n; col++){
        if(!cols[col] && !diag1[row - col + n - 1] && !diag2[row + col]){
            board[row][col] = 1;
            cols[col] = true;
            diag1[row - col + n -1] = true;
            diag2[row+col] = true;

            bndtNQueens(board, row+1, count, cols, diag1, diag2);

            board[row][col] = 0;
            cols[col] = false;
            diag1[row - col + n -1] = false;
            diag2[row+col] = false;
        }
    }
}

void solve(int n){
    vector<vector<int>> board(n, vector<int>(n, 0));

    vector<bool> cols(n, false);
    vector<bool> diag1(2*n -1, false);
    vector<bool> diag2(2*n - 1, false);
    int count  = 0; 

    bndtNQueens(board, 0, count, cols, diag1, diag2);

    if(count == 0){
        cout << "No solution found" <<  endl;
    }
}

int main(){
    int n;

    cout <<"Enter no. of queens: ";
    cin >> n;

    // vector<vector<int>> board(n, vector<int>(n, 0));

    // int count = 0;

    // NQueens(board, 0, count);

    // if(count == 0){
    //     cout << "No solution found"<< endl;
    // }
    // return 0;

    solve(n);
}