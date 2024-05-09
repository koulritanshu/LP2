#include <bits/stdc++.h>
using namespace std;

class graph{
    map<int,vector<int>> g;
    int n;
public:
    graph(){
    }
    graph(int x){
        n = x;
    }
    void addEdge(int a, int b){
        g[a].push_back(b);
        g[b].push_back(a);
    }
    void dfs(int startNode, int level, vector<bool>&vis){
        vis[startNode] = true;
        cout << "{ " << startNode << " , " << level << " } " << endl;
        for(auto &i: g[startNode]){
            if(!vis[i]){
                vis[i] = true;
                dfs(i,level+1,vis);
            }
        }
    }
    void bfs(int startNode){
        vector<bool> vis(n, false);
        queue <pair<int,int>> qp;
        qp.push({startNode,0});
        vis[startNode] = true;
        while(!qp.empty()){
            int node = qp.front().first;
            int level = qp.front().second;
            qp.pop();
            cout << " { " << node << " , " << level << " } " << endl;
            for(auto &i : g[node]){
                if(!vis[i]){
                    vis[i] = true;
                    qp.push({i,level+1});
                }
            }
        }
    }
};

int main()
{
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    int x;
    cin >> x;
    graph g(n);
    while(x--){
        int a,b;
        cout << "Enter a, b";
        cin >> a >> b;
        g.addEdge(a,b);
    }
    cout << "\n-----------------------------------------------------------\n";
    vector<bool> vis(n,false);
    g.dfs(0,0,vis);
    cout << "\n-----------------------------------------------------------\n";
    g.bfs(0);
    return 0;
}