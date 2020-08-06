#include<bits/stdc++.h>
using namespace std;

struct edge {
	int a,b,w;
};
void print(auto &v){
	for(auto i:v)
		cout<<i<<" ";
	cout<<"\n";
}

bool bf(vector<edge> &G,vector<int> &d,vector<int> &p,int n,int m,int src){
	d[src] = 0;
	bool flag = 0;
	for(int i=0;i<n;i++){
		flag = 0;
		for(int j = 0;j < m;j++){
			if(d[G[j].a]<INT_MAX && d[G[j].b]>d[G[j].a]+G[j].w){
				d[G[j].b] = min(d[G[j].b],d[G[j].a]+G[j].w);
				p[G[j].b] = G[j].a;
				flag = 1;
			}
		}
		if(!flag) break;
	}
	return flag;
}

int main(){
	int noEdge,noVer,src;
	cin>>noVer>>noEdge;
	vector<edge> G(noEdge);
	vector<int> dist(noVer,INT_MAX),par(noVer,-1);
	for(int i=0;i<noEdge;i++)
		cin>>G[i].a>>G[i].b>>G[i].w;
	cin>>src;
	bool isNegCycle = bf(G,dist,par,noVer,noEdge,src);
	if(isNegCycle)
		cout<<"Negative Cycle Found\n";
	else{
		print(dist);
		print(par);
	}
}
