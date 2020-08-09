#include<bits/stdc++.h>
#include "disjoint_set_union.h"
using namespace std;
using namespace DSU;

void UnionFind::make_set(int n){
	for(int i=0;i<n;i++){
		par[i] = i;
		size[i] = 1;
	}
}

int UnionFind::find_set(int a){
	if(a == par[a])
		return a;
	return par[a] = find_set(par[a]);
}

void UnionFind::union_set(int a,int b){
	int p = find_set(a);
	int q = find_set(b);
	if(p == q)
		return ;
	
	if(size[p]<size[q]){
		par[p] = q;
		size[q] += size[p];
	}
	else{
		par[q] = p;
		size[p] += size[q];
	}
}

