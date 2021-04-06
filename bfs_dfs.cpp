#include<bits/stdc++.h>
using namespace std;
bool visited[100];

void dfs(vector<int> graph[], int N, int src){
    cout << src << " ";
    visited[src] = true;
    for(int adj_node : graph[src]){
        if(!visited[adj_node]){
            dfs(graph,N,adj_node);
        }
    }
}
void dfs_iter(vector<int> graph[], int N,int src){
    stack<int> s;
    vector<bool> visited(N,false);
    s.push(src);
    visited[src] = true;
    while(!s.empty()){
        int curr_node = s.top();
        s.pop();
        cout << curr_node << " ";
        for(int adj_node : graph[curr_node]){
            if(!visited[adj_node]){
                s.push(adj_node);
                visited[adj_node] = true;
            }
        }
    }
    cout << "\n";
}

void bfs(vector<int> graph[] ,int N, int src){
    queue<int> q;
    vector<bool> visited(N,false);
    q.push(src);
    visited[src] = true;
    while(!q.empty()){
        int curr_node = q.front();
        q.pop();
        cout << curr_node <<" ";
        for(int adj_node:graph[curr_node]){
            if(!visited[adj_node]){
                q.push(adj_node);
                visited[adj_node] = true;
            }
        }
    }
    cout <<"\n";
}

void print(vector<int> tree[],int N){
    for(int i =0;i<N;i++){
        cout << i <<" => ";
        for(int adj_node : tree[i])
            cout <<  adj_node << ",";
        cout << "\n";
    }
}
int main(){
    int N,node;
    cout << "Enter No of Nodes => \n";
    cin >> N;
    vector<int> graph[N];
    for(int i=0;i<N;i++){
        while(true){
            cin >> node;
            if(node == -1)
                break;
            graph[i].push_back(node);
        }
    }
    print(graph,N);
    dfs_iter(graph,N,0);
    dfs(graph,N,0);
    return 0;
}
