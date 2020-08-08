#include<bits/stdc++.h>
using namespace std;

class UnionFind{
	private:
		vector<int> par,size;
	public:
		UnionFind(int n):par(n),size(n){}
		void make_set(int);
		int find_set(int);
		void union_set(int,int);
};
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
int main(){
	int choice,n;
	cin>>n;
	UnionFind set(n); 
	string str ="Enter choice :\n"
				"0:Exit\n"
				"1:make_set\n"
				"2:find_set\n"
				"3:union\n";
	
	do{
		cout<<str;
		cin>>choice;
		int a,b;
		switch(choice){
		case 1:
			set.make_set(n);
			break;
		case 2:
			cout<<"Enter element a"<<endl;
			cin>>a;
			cout<<set.find_set(a)<<"\n";
			break;
		case 3:
			cout<<"Enter element a,b"<<endl;
			cin>>a>>b;
			set.union_set(a,b);
			break;
		default:
			if(choice != 0)
				cout<<"Invalid choice"<<endl;
		}
	}while(choice != 0);
	return 0;
}
