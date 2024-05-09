#include <bits/stdc++.h>
using namespace std;

bool isSafe(int row, int col, vector<vector<int>>&board, int n){
    // check upper column
    for(int i=0;i<row;i++){
        if(board[i][col] == 1) return false;
    }
    // check upper left diagonal
    for(int i=row,j=col;i>=0&&j>=0;i--,j--){
        if(board[i][j]==1) return false;
    }
    // check upper right diagonal
    for(int i=row,j=col;i>=0&&j<n;i--,j++){
        if(board[i][j]==1) return false;
    }
    return true;
}

void solve(int row, vector<vector<int>>&board, vector<vector<vector<int>>>&answers, int n){
    if(row == n){
        answers.push_back(board);
        return;
    }
    for(int col = 0; col < n; col++){
        if(isSafe(row, col, board, n)){
            board[row][col] = 1;
            solve(row+1,board,answers,n);
            board[row][col] = 0;
        }
    }
}

void disp(vector<vector<int>> &temp){
    cout << "-----------------------------------------------------------------\n";
    for(int i=0;i<temp.size();i++){
        for(int j=0;j<temp[i].size();j++){
            if(temp[i][j] == 0){
                cout << ". ";
            }
            else{
                cout << "Q "; 
            }
        }
        cout << endl;
    }
    cout << "-----------------------------------------------------------------\n";
}

void back(int n)
{
    vector<vector<int>> board(n, vector<int>(n,0));
    vector<vector<vector<int>>> answers;
    solve(0,board,answers,n);
    for(int i=0;i<answers.size();i++){
        disp(answers[i]);
    }
}

class BranchAndBound{
    int n;
    vector<bool> rows;
    vector<bool> diagonalLeft;
    vector<bool> diagonalRight;
    vector<vector<vector<int>>> answers;
public:
    
    BranchAndBound(int x){
        n = x;
        rows = vector<bool>(n,false);
        diagonalLeft = vector<bool>(2*n-1,false);
        diagonalRight = vector<bool>(2*n-1,false);
    }

    void helper(int row, vector<vector<int>>& board){
        if(row == n){
            answers.push_back(board);
            return;
        }
        for(int col=0;col<n;col++){
            if(!rows[col] && !diagonalLeft[row+col] && !diagonalRight[row-col+n-1]){
                rows[col] = true;
                diagonalLeft[row+col] = true;
                diagonalRight[row-col+n-1] = true;
                board[row][col] = 1;
                helper(row+1,board);
                rows[col] = false;
                diagonalLeft[row+col] = false;
                diagonalRight[row-col+n-1] = false;
                board[row][col] = 0;
            }
        }
    }

    void solve(){
        vector<vector<int>> board(n,vector<int>(n,0));
        helper(0,board);
        for(int i=0;i<answers.size();i++){
            disp(answers[i]);
        }
    }

};

int main()
{
    int n;
    cout << ">> Enter the value of n: ";
    cin >> n;
    if(n == 1){
        cout << "1" << endl;return 0;
    }
    if(n<=3){
        cout << "Solution not possible\n";
        return 0;
    }
    int type;
    cout << "1. Backtracking\n2. Branch and Bound.\n";
    cin >> type;
    if(type == 1){
        back(n);
    }
    else{
        BranchAndBound obj(n);
        obj.solve();
    }
    return 0;
}