#include <bits/stdc++.h>
using namespace std;
class DisjointSet{
private:
	int size;
	vector<int> par,rank;
public:
	DisjointSet(int size){
		this->size = size;
		par.resize(size);
		rank.resize(size);
	}
	
	void makeSet(){
		for(int i=0;i<size;i++){
			par[i] = i;
			rank[i] = 0;
		}
	}
	
	int findSet(int u){
		if(u == par[u])
			return u;
		return par[u] = findSet(par[u]);
	}
	
	void unionSet(int u,int v){
		int a = findSet(u);
		int b = findSet(v);
		if(a != b){
			if(rank[a]<rank[b])
				swap(a,b);
			par[b] = a;
			if(rank[a] == rank[b])
				rank[a]++;
		}
	}
	void printOutPut(){
		for(int i=0;i<size;i++){
			cout <<"(node=>par,rank) : "<< i <<"=>" <<par[i] <<","<<rank[i]<<"\n";
		}
	}
};

int main() {
	int size = 7;
	DisjointSet set(size);
	set.makeSet();
	set.unionSet(0,1);
	set.unionSet(1,2);
	set.unionSet(3,4);
	set.unionSet(5,6);
	set.unionSet(4,5);
	set.unionSet(1,5);
	set.printOutPut();
	return 0;
}
