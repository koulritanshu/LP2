#include <bits/stdc++.h>
using namespace std;

class graph{
    map<int,vector<pair<int,int>>> g;
    int n;
public:
    graph(){}
    graph(int x){n=x;}
    void addEdge(int a, int b, int cost){
        g[a].push_back({b,cost});
        g[b].push_back({a,cost});
    }
    void prims(int start){
        map<int,bool> visited;
        int cost = 0;
        vector<vector<int>> primadj(n,vector<int>(n,0));
        int taken_edges = 0;
        visited[0] = true;
        while(taken_edges != n-1){
            int min_distance = INT_MAX;
            int vertex_i = -1;
            int vertex_j = -1;
            for(auto i:visited){
                int curr_node = i.first;
                // iterate thorugh all the nodes connected to curr_node
                for(auto j:g[curr_node]){
                    int other_node = j.first;
                    int rcost = j.second;
                    if(visited.find(other_node)==visited.end()){
                        if(min_distance > rcost){
                            min_distance = rcost;
                            vertex_i = curr_node;
                            vertex_j = other_node;
                        }
                    }
                }
            }
            if(vertex_i == -1)
                continue;
            taken_edges++;
            cost += min_distance;
            primadj[vertex_i][vertex_j] = primadj[vertex_j][vertex_i] = min_distance;
            visited[vertex_i] = true;
            visited[vertex_j] = true;
        }

        cout << "TOTAL COST = " << cost << endl;
        cout << "DISPLAYING THE ADJACENCY MATRIX" << endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout << primadj[i][j] << " ";
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
    g.prims(0);
    return 0;
}