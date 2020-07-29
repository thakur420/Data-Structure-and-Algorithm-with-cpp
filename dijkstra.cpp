#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
typedef long long LL;
typedef vector<int> Arr;
typedef pair<int,int> Pair;
typedef vector<Pair> Adj;
typedef vector<Adj> Graph;
typedef unordered_map<int,int> Map; 

#define F first
#define S second

class Cmp{
public:
    bool operator()(Pair n1,Pair n2) {
        return n1.second>n2.second;
    }
};

void printArr(Graph g){
	for(int i =0;i<(int)g.size();i++){
		cout<<i<<" => ";
		for(auto v:g[i])
			cout<<"("<<v.first<<","<<v.second<<") ";
		cout<<"\n";
	}
}

void printVec(Arr v){
	for(auto i:v)
		cout<<i<<",";
	cout<<"\n";
}

void decrease_key(Adj &heap,Map &mp,int i){	
	while(i > 0){
		int p =  (i-1)/2;
		if(heap[i].S < heap[p].S){
			mp[heap[i].F] = p;
			mp[heap[p].F] = i;
			swap(heap[i],heap[p]);
		}
		i = p;
	}
}

Pair extractMin(Adj &heap,Map &mp){
	Pair curr = heap.front();
	int n = heap.size(),p=0;
	mp[heap[n-1].F] = p;
	mp.erase(curr.F);
	swap(heap[p],heap[n-1]);
	heap.pop_back();
	n -= 1;
	
	while(p < n/2){
		int lc = 2*p+1,rc = 2*p+2,minIndex=p,minVal =heap[p].S; 
		if(lc < n && minVal>heap[lc].S){
			minIndex = lc;
			minVal = heap[p].S;
		}
		if(rc < n && minVal>heap[rc].S){
			minIndex = rc;
			minVal = heap[p].S;
		}
		if(p == minIndex)
			break;
		mp[heap[p].F] = minIndex;
		mp[heap[minIndex].F] = p;
		swap(heap[p],heap[minIndex]);
		p = minIndex;
	}
	return curr;
}

void dj(Graph &g,Arr &dist,Arr &par,int src){
	Map mp;
	Adj minHeap;
	dist[src] = 0;
	
	for(int i=0;i<(int)dist.size();i++)
		minHeap.push_back({i,dist[i]});
	make_heap(minHeap.begin(),minHeap.end(),Cmp());
	
	for(int i=0;i<(int)minHeap.size();i++)
		mp[minHeap[i].F] = i;

	while(!minHeap.empty()){
		Pair curr = extractMin(minHeap,mp);
		dist[curr.F] = curr.S;
		for(auto v:g[curr.F]){
			if(mp.find(v.F) != mp.end() &&(LL)curr.S + v.S < (LL)minHeap[mp[v.F]].S){
				minHeap[mp[v.F]].S = curr.S + v.S;
				par[v.F] = curr.F;
				decrease_key(minHeap,mp,mp[v.F]);
			}
		}
	}
}


int main(){
	Graph g;
	int N,A,V,W,src;
	cout<<"Enter Number of Vertices ...\n";
	cin>>N;
	Arr dist(N,INT_MAX),par(N,-1);
	for(int i=0;i<N;i++){
		cout<<"Enter Number of Adj vertex of "<<i<<"th Vertex\n";
		cin>>A;
		Adj edge;
		cout<<"Enter adj Vertex and Wieght (u,w)\n";
		for(int j=0;j<A;j++){
			cin>>V>>W;
			edge.push_back({V,W});
		}
		g.push_back(edge);
	}
	cin>>src;
	dj(g,dist,par,src);
	cout<<"Your Input Graph\n";
	printArr(g);
	cout<<"Distance from Src\n";
	printVec(dist);
	cout<<"Immediate Parent of Vertex\n";
	printVec(par);
	return 0;
}
