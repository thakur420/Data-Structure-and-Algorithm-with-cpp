/*
 * binary tree.cpp
 *
 *  Created on: 11-Sep-2018
 *      Author: indrajeet
 */
#include<bits/stdc++.h>
using namespace std;
struct node{
	int data;
	node *left,*right;
};
class tree{
private:
	node *root;
public:
	tree():root(nullptr){}
	node  *getRoot(){
		return root;
	}
	void setRoot(node *root){
		this->root = root;
	}
	node* createNode(int);
	void bfs(node *);
	void insert(node *,int);
	int findmax(node *);
	bool search(node *,int);
	int size(node *);
	void reversebfs(node *);
	void deltree(node *);
};
node *tree::createNode(int val){
	node *newNode = new(node);
	newNode-> data=val;
	newNode->left = newNode->right = nullptr;
	return newNode;
}
void tree::insert(node *rt,int val){
	if(rt==nullptr)
		root = createNode(val);
	else{
		queue<node*> q;
		q.push(rt);
		while(true){
			rt = q.front();
			q.pop();
			if(rt->left)
				q.push(rt->left);
			else{
				rt->left = createNode(val);
				break;
			}
			if(rt->right)
				q.push(rt->right);
			else{
				rt->right = createNode(val);
				break;
			}
		}
	}
}
int tree::findmax(node *rt){
	if(rt == nullptr)
		return 0;
	if(rt->left == nullptr && rt->right == nullptr)
		return rt->data;
	int lst_max = findmax(rt->left);
	int rst_max = findmax(rt->right);
	return max(rt->data,max(lst_max,rst_max));
}
bool tree::search(node *rt,int target){
	if(rt == nullptr)return false;
	if(rt->data == target)return true;
	bool found = search(rt->left,target);
	if(found)return true;
	else return search(rt->right,target);
}
void tree::bfs(node *rt){
	if(rt != nullptr){
		queue<node *> q;
		q.push(rt);
		while(!q.empty()){
			rt= q.front();
			q.pop();
			cout<<rt->data<<" ";
			if(rt->left)
				q.push(rt->left);
			if(rt->right)
				q.push(rt->right);
		}
	}
}
int tree::size(node *rt){
	if(rt == nullptr)
		return 0;
	return 1+size(rt->left)+size(rt->right);
}
void tree::reversebfs(node *rt){
	queue<node*> q;
	stack<node*> st;
	if(rt != nullptr){
		q.push(rt);
		while(!q.empty()){
			rt = q.front();
			q.pop();
			if(rt->left)
				q.push(rt->left);
			if(rt->right)
				q.push(rt->right);
			st.push(rt);
		}
		while(!st.empty()){
			cout<<st.top()->data<<" ";
			st.pop();
		}
	}
}
void tree::deltree(node *rt){
	if(rt == nullptr)
		return;
	deltree(rt->left);
	deltree(rt->right);
	cout<<"deleting node ..."<<rt->data<<endl;
	delete rt;
	rt = nullptr;
}
int main(){
	tree t;
		string str ="Enter choice :\n"
					"0:Exit\n"
					"1:insert\n"
					"2:delete\n"
					"3:print\n"
					"4:search\n"
					"5:find max\n"
				    "6:size\n"
				    "7:reverse print\n";
		int choice;
		do{
			cout<<str;
			cin>>choice;
			int val;
			switch(choice){
			case 1:
				cout<<"Insert an item"<<endl;
				cin>>val;
				t.insert(t.getRoot(),val);
				break;
			case 2:
				t.deltree(t.getRoot());
				t.setRoot(nullptr);
				break;
			case 3:
				t.bfs(t.getRoot());
				cout<<endl;
				break;
			case 4:
				cout<<"Enter value to be searched"<<endl;
				cin>>val;
				if(t.search(t.getRoot(),val))cout<<"value found"<<endl;
				else cout<<"value not found"<<endl;
				break;
			case 5:
				cout<<t.findmax(t.getRoot())<<endl;
				break;
			case 6:
				cout<<t.size(t.getRoot())<<endl;
				break;
			case 7:
				t.reversebfs(t.getRoot());
				cout<<endl;
				break;
			default:
				if(choice != 0)
					cout<<"Invalid choice"<<endl;
			}
		}while(choice != 0);
		return 0;
}
