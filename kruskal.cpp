#include<bits/stdc++.h>
#include "disjoint_set_union.h"

using namespace std;
using namespace DSU;

struct Edge{
	int u,v,W;
	bool operator<(Edge const& e){
		return W < e.W;
	}
};

void printEdge(vector<pair<int,int>> &E){
	for(auto e:E)
		cout<<e.first<<","<<e.second<<"\n";
}

void kruskal(vector<Edge> &G,vector<pair<int,int>> &mstEdge,int &mstVal,int v){
	UnionFind set(v);
	set.make_set(v);
	
	sort(G.begin(),G.end());
	for(Edge e:G){
		if(set.find_set(e.u)!=set.find_set(e.v)){
			mstVal += e.W;
			mstEdge.push_back({e.u,e.v});
			set.union_set(e.u,e.v);
		}
	}
}

int main(){
	int v,e,mstVal=0;
	cin>>v>>e;
	vector<Edge> G(e);
	vector<pair<int,int>> mstEdge;
	
	for(int i=0;i<e;i++)
		cin>>G[i].u>>G[i].v>>G[i].W;
	
	kruskal(G,mstEdge,mstVal,v);	
	printEdge(mstEdge);
	cout<<"MSTVAL => "<<mstVal<<"\n";
	return 0;
}
