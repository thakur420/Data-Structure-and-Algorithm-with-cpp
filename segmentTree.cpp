#include <iostream>
#include<vector>
using namespace std;
class SegmentTree{
	vector<int> segTree;
	int size;
public:
	SegmentTree(vector<int> &arr){
		this->size = 4 * arr.size();
		segTree.resize(this->size);
		buildST(arr,0,arr.size()-1,0);
	}
	void buildST(vector<int> &arr,int s,int e,int idx){
		if(s == e){
			segTree[idx] = arr[s];
			return;
		}
		int mid  = (s + e ) / 2;
		buildST(arr,s,mid,2*idx+1);
		buildST(arr,mid+1,e,2*idx+2);
		segTree[idx] = segTree[2*idx + 1] + segTree[2*idx + 2];
		return;
	}
	int getrangeSumQ(int qL,int qR,int segS,int segE,int segIdx){
		if(qL <= segS && qR >= segE){
			return segTree[segIdx];
		}
		if(qL > segE || qR < segS)
			return 0;
		
		int mid = (segS + segE) / 2;
		
		return getrangeSumQ(qL,qR,segS,mid,2*segIdx+1) + getrangeSumQ(qL,qR,mid+1,segE,2*segIdx+2);
	}
	
	void updateQ(int segS,int segE,int val,int idx,int segIdx){
		if(segS > idx || segE < idx){
			return ;
		}
		if(segS == segE){
			segTree[segIdx] = val;
			return;	
		}
		int mid = (segS + segE) / 2;
		
		if(idx > mid){
			updateQ(mid+1,segE,val,idx,2*segIdx+2);
		}else{
			updateQ(segS,mid,val,idx,2*segIdx+1);
		}
		
		segTree[segIdx] = segTree[2*segIdx+1] + segTree[2*segIdx+2];
	}
	void printSegTree(){
		for(int node : segTree){
			cout << node <<" ";
		}
		cout <<"\n";
	}
};


int main() {
	vector<int> arr = {1,3,5,7,9,11};
	SegmentTree segTree(arr);
	segTree.printSegTree();
	int n = 6;
	cout << segTree.getrangeSumQ(2,4,0,n-1,0) << "\n";
	cout << segTree.getrangeSumQ(0,3,0,n-1,0) << "\n";
	segTree.updateQ(0,n-1,5,1,0);
	cout << segTree.getrangeSumQ(0,3,0,n-1,0) << "\n";
	return 0;
}
