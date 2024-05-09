#include <bits/stdc++.h>
using namespace std;

int heuristic(vector<vector<int>>& curr, vector<vector<int>>&final, int level)
{
    int count = 0;
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            if (curr[i][j] != final[i][j])
                count++;
        }
    }
    return count+level;
}

int nrow[4] = {0,1,-1,0};
int ncol[4] = {1,0,0,-1};

int main()
{
    vector<vector<int>> start(3,vector<int>(3,0));
    vector<vector<int>> end(3,vector<int>(3,0));
    cout << "Enter the initital state: ";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin >> start[i][j];
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin >> end[i][j];
        }
    }
    cout << "Printing the initial state" << endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout << start[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Printing the final state" << endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout << end[i][j] << " ";
        }
        cout << endl;
    }
    priority_queue<pair<int,pair<int,vector<vector<int>>>>, vector<pair<int,pair<int,vector<vector<int>>>>>, greater<pair<int,pair<int,vector<vector<int>>>>>> pq;
    pq.push({heuristic(start,end,0),{0,start}});

    int c = 0;
    while (!pq.empty() && c <= 1000)
    {
        int level = pq.top().second.first;
        int heuris = pq.top().first - level;
        vector<vector<int>> state = pq.top().second.second;

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                cout << state[i][j] << " ";
            }
            cout << endl;
        }

        cout << "level = " << level << endl;
        cout << "heuristic = " << heuris << endl;

        if(state == end)
        {
            cout << "Goal state reached\n";
            break;
        }
        pq.pop();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(state[i][j] == -1){
                    for(int k=0;k<4;k++){
                        int nr = i + nrow[k];
                        int nc = j + ncol[k];
                        if(nr >= 0 && nc >= 0 && nr < 3 && nc < 3){
                            vector<vector<int>> temp = state;
                            swap(temp[i][j],temp[nr][nc]);
                            pq.push({heuristic(temp,end,level+1),{level+1,temp}});
                        }
                    }
                }
            }
        }
        c++;
    }
    if(c>1000){
        cout << "No solutions exist." << endl;
    }
    return 0;
}