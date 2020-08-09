#ifndef DISJOINT_SET_UNION_H
#define DISJOINT_SET_UNION_H
#include<bits/stdc++.h>
using namespace std;

namespace DSU{
	
	class UnionFind{
		private:
			vector<int> par,size;
		public:
			UnionFind(int n):par(n),size(n){}
			void make_set(int);
			int find_set(int);
			void union_set(int,int);
	};
}

#endif
