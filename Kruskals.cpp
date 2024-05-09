#include <bits/stdc++.h>
using namespace std;

class graph{
    int n;
    vector<vector<int>> g;
public:

    graph(int x){
        n = x;
        g = vector<vector<int>>(2000,vector<int>(2000,0));
    }

    void addEdge(int a, int b, int cost){
        g[a][b] = cost;
        g[b][a] = cost;
    }

    bool dfs(vector<vector<int>>&graph, vector<bool>&vis, int parent, int curr){
        vis[curr] = true;
        for(int i=0;i<n;i++){
            if(graph[curr][i] > 0){
                if(vis[i]){
                    if(i != parent) return true;
                }
                else{
                    if(dfs(graph,vis,curr,i))
                        return true;
                }
            }
        }
        return false;
    }

    bool checkCycle(vector<vector<int>> &graph){
        vector<bool> vis(n,false);
        for(int i=0;i<n;i++){
            if(!vis[i]){
                if(dfs(graph,vis,-1,i)){
                    return true;
                }
            }
        }
        return false;
    }

    void kruskals(int start){
        vector<vector<int>> temp = g;
        vector<vector<int>> adjKrusks(n,vector<int>(n,0));
        int taken_edges = 0;
        vector<bool> visited(n, false);
        int cost = 0;
        while (taken_edges != n-1){
            int mini_edge = INT_MAX;
            int vertex_i = -1;
            int vertex_j = -1;
            for(int i=0;i<n;i++){
                for(int j=i+1;j<n;j++){
                    if(!visited[i] && !visited[j] && temp[i][j] != -1 && temp[i][j] != 0){
                        if(mini_edge > temp[i][j]){
                            mini_edge = temp[i][j];
                            vertex_i = i;
                            vertex_j = j;
                        }
                    }
                }
            }
            adjKrusks[vertex_i][vertex_j] = adjKrusks[vertex_j][vertex_i] = mini_edge;
            temp[vertex_i][vertex_j] = temp[vertex_j][vertex_i] = -1;
            if(checkCycle(adjKrusks)){
                adjKrusks[vertex_i][vertex_j] = adjKrusks[vertex_j][vertex_i] = 0;
            }
            else{
                taken_edges++;
                cost += adjKrusks[vertex_i][vertex_j];
            }
        }
        cout << "COST = " << cost << endl;
        cout << "DISPLAYING THE ADJACENCY MATRIX OF THE MST" << endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout << adjKrusks[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    graph g(9);
    g.addEdge(0,1,4);
    g.addEdge(0,7,8);
    g.addEdge(1,2,8);
    g.addEdge(1,7,11);
    g.addEdge(2,8,2);
    g.addEdge(2,3,7);
    g.addEdge(7,8,7);
    g.addEdge(7,6,1);
    g.addEdge(8,6,6);
    g.addEdge(2,5,4);
    g.addEdge(6,5,2);
    g.addEdge(3,5,14);
    g.addEdge(3,4,9);
    g.addEdge(5,4,10);
    g.kruskals(0);
    return 0;
}