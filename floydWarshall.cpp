#include<bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> Matrix;

void takeInput(Matrix &M,int n){
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			cin>>M[i][j];
			if(M[i][j] == -1)
				M[i][j] = INT_MAX;
		}
}

void printMatrix(Matrix &M){
	for(auto row:M){	
		for(auto w:row)
			cout<<w<<" ";
		cout<<"\n";
	} 
}

void floydWarshall(Matrix &M,int n){
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(M[i][k]!=INT_MAX && M[k][j]!=INT_MAX)
					M[i][j] = min(M[i][j],M[i][k]+M[k][j]);
			}
		}		
	}
}

int main(){
	int n;
	cin>>n;
	Matrix M(n,vector<int>(n,INT_MAX));
	takeInput(M,n);
	printMatrix(M);
	floydWarshall(M,n);
	printMatrix(M);
	return 0;
}
