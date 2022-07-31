#include <bits/stdc++.h>
using namespace std;
class HeapDS{
private:
	int size;
	vector<pair<int,int>> heap;
	vector<int> mp;
public:
	HeapDS(int size,vector<int> heap){
		this->size = size;
		for(int i = 0; i<size;i++)
			this->heap.push_back({i,heap[i]});
		mp.resize(size);
	}
	bool empty(){
		return (size == 0);
	}
	
	void makeHeap(){
		make_heap(heap.begin(),heap.end(),[&](auto a,auto b){
			return a.second > b.second;
		});
		for(int i=0;i<size;i++)
			mp[i] = heap[i].first;
	}
	
	pair<int,int> extractMin(){
		
		pair<int,int> min = heap[0];
		mp[heap[0].first] = size-1;
		mp[heap[size-1].first] = 0;
		swap(heap[0],heap[size-1]);
		size -= 1;
		heapify(0);
		return min;
	}
	
	void decreaseKey(int key,int val){
		if(heap[mp[key]].second <= val)
			return;
		heap[mp[key]].second = val;
		reBuildHeap(mp[key]);
	}
	
	void reBuildHeap(int key){
		int par = (key-1)/2;
		if(par>=0 && heap[par].second > heap[key].second){
			mp[heap[par].first] = key;
			mp[heap[key].first] = par;
			swap(heap[par],heap[key]);
			reBuildHeap(par);
		}
	}
	void heapify(int rt){
		int lc = 2*rt + 1,rc = 2*rt + 2,smallest = rt;
		if(lc < size && heap[smallest].second > heap[lc].second)
			smallest = lc;
		if(rc < size && heap[smallest].second > heap[rc].second)
			smallest = rc;
		if(smallest != rt){
			mp[heap[rt].first] = smallest;
			mp[heap[smallest].first] = rt;
			swap(heap[rt],heap[smallest]);
			heapify(smallest);
		}
	}
	void printData(){
		for(int i=0;i<size;i++){
			cout <<heap[i].second <<" ";
		}
		cout << "\n";
		for(int idx : mp){
			cout << idx << " ";
		}
		cout <<"\n";
	}
};
int main() {
	// your code goes here
	int n = 9;
	vector<int> heap = {0,99,99,99,99,99,99,99,99};
	HeapDS heapObj(n,heap);
	heapObj.makeHeap();
	heapObj.printData();
	cout <<heapObj.extractMin() <<"\n"; // ==> 0
	heapObj.decreaseKey(1,4);
	heapObj.decreaseKey(7,8);
	cout <<heapObj.extractMin() <<"\n"; // ==> 4
	heapObj.decreaseKey(2,8);
	cout <<heapObj.extractMin() <<"\n"; // ==> 8
	heapObj.decreaseKey(6,1);
	heapObj.decreaseKey(8,7);
	cout <<heapObj.extractMin() <<"\n"; // ==> 1
	heapObj.decreaseKey(5,2);
	heapObj.decreaseKey(8,6);
	cout <<heapObj.extractMin() <<"\n"; // ==> 2
	heapObj.decreaseKey(2,4);
	heapObj.decreaseKey(3,14);
	heapObj.decreaseKey(4,10);
	cout <<heapObj.extractMin() <<"\n"; // ==> 4
	cout <<heapObj.extractMin() <<"\n"; // ==> 6
	cout <<heapObj.extractMin() <<"\n"; // ==> 10
	cout <<heapObj.extractMin() <<"\n"; // ==> 14
	heapObj.printData();
 	return 0;
}
