/*
 * binary search tree.cpp
 *
 *  Created on: 11-Sep-2018
 *      Author: indrajeet
 */
#include<bits/stdc++.h>
using namespace std;
template<class T>
struct node{
	T data;
	node *left,*right;
};
template<class T>
class tree{
private:
	node<T> *root;
public:
	tree():root(nullptr){}
	node <T> * getRoot(){
		return root;
	}
	node<T>* createNode(T);
	node<T>* inodersuccesor(node<T>*);
	int height(node<T>*);
	void insert(node<T>*,node<T>*,T);
	void del(node<T> *,node<T>*,T);
	void inorder(node<T>*);
	void preorder(node<T>*);
	void postorder(node<T>*);
};
template<class T>
inline node<T>* tree<T>::createNode(T data){
	node<T> *newNode = new(node<T>);
	newNode-> data=data;
	newNode->left = newNode->right = nullptr;
	return newNode;
}
template<class T>
void tree<T>::inorder(node<T> *rt){
	stack<node<T>*> st;
	bool visited = false;
	if(rt != nullptr){
		do{
			while(!visited && rt->left != nullptr){
				st.push(rt);
				rt = rt->left;
			}
			cout<<rt->data<<" ";
			rt = rt->right;
			visited = false;
			if(rt == nullptr){
				if(st.empty())
					break;
				rt = st.top();
				st.pop();
				visited = true;
			}
		}while(rt);
	}
}
template<class T>
void tree<T>::preorder(node<T> *rt){
	stack<node<T>*>st;
	while(true){
		while(rt){
			cout<<rt->data<<" ";
			st.push(rt);
			rt = rt->left;
		}
		if(st.empty())
			break;
		rt = st.top()->right;
		st.pop();
	}
}
template<class T>
void tree<T>::postorder(node<T> *rt){
	stack<node<T>*> st;
	node<T>* prev = nullptr;
	while(true){
		while(rt && (!prev || rt->right != prev)){
			st.push(rt);
			rt = rt->left;
		}
		if(st.empty())
			break;
		if(st.top()->right==nullptr || st.top()->right == prev){
			prev = st.top();
			cout<<prev->data<<" ";
			st.pop();
		}
		else
			rt = st.top()->right;
	}
}
template<class T>
void tree<T>::insert(node<T>* rt,node<T>* parent,T z){
	node<T> *temp;
	if(root == nullptr)
		root = createNode(z);
	else if(rt == nullptr){
		temp = createNode(z);
		if(parent->data < z)
			parent->right = temp;
		else
			parent->left = temp;
	}
	else if(rt->data<z)
		insert(rt->right,rt,z);

	else
		insert(rt->left,rt,z);
}
template<class T>
void tree<T>::del(node<T> *rt,node<T>* parent,T z){
	if(root == nullptr)
		return;
	if(rt ==  nullptr)
		return;
	else if(rt->data<z)
		del(rt->right,rt,z);
	else if(rt->data>z)
		del(rt->left,rt,z);
	else{
		bool lhs = (rt->left != nullptr && rt->right == nullptr);
		bool rhs = (rt->left == nullptr && rt->right != nullptr);
		if(rt->right == nullptr && rt->left == nullptr){
			if(rt == root)
				root = nullptr;
			else{
				if(parent->data < z)
					parent->right = nullptr;
				else
					parent->left = nullptr;
			}
			delete rt;
			rt = nullptr;
		}
		else if(lhs||rhs){
			if(rt == root)
				root = (rhs?rt->right:rt->left);
			else{
				if(parent->data < z)
					parent->right = (lhs?rt->left:rt->right);
				else
					parent->left = (rhs?rt->right:rt->left);
			}
			delete rt;
			rt = nullptr;
		}
	    else{
	    	node<T> *temp = rt->right;
	    	while(temp->left != nullptr)
	    			temp = temp->left;
	    	int val = temp->data;
	    	del(rt->right,rt,val);
	    	rt->data = val;
	    }
	}
}
int main(){
	tree<int> t;
	string str ="Enter choice :\n"
				"0:Exit\n"
				"1:insert\n"
				"2:delete\n"
				"3:print \n";
	int choice;
	do{
		cout<<str;
		cin>>choice;
		int val;
		switch(choice){
		case 1:
			cout<<"Insert an item"<<endl;
			cin>>val;
			t.insert(t.getRoot(),nullptr,val);
			break;
		case 2:
			cout<<"Enter value to be deleted"<<endl;
			cin>>val;
			t.del(t.getRoot(),nullptr,val);
			break;
		case 3:
			cout<<"inorder-> ";
			t.inorder(t.getRoot());
			cout<<"\npreorder-> ";
			t.preorder(t.getRoot());
			cout<<"\npostorder-> ";
			t.postorder(t.getRoot());
			cout<<endl;
			break;
		default:
			if(choice != 0)
				cout<<"Invalid choice"<<endl;
		}
	}while(choice != 0);
	return 0;
}
