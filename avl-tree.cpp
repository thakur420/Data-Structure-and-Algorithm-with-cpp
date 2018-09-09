/*
 * avl-tree.cpp
 *
 *  Created on: 06-Sep-2018
 *      Author: indrajeet
 */
#include<bits/stdc++.h>
using namespace std;
template<class T>
struct node{
	T data;
	int bf;
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
	node<T>* ll_rotate(node<T>*);
	node<T>* rr_rotate(node<T>*);
	node<T>* inodersuccesor(node<T>*);
	int height(node<T>*);
	void insert(node<T>*,node<T>*,T);
	void cal_bf(node<T>*,node<T>*);
	void inorder(node<T>*);
	void del(node<T> *,node<T>*,T);
};
template<class T>
inline node<T>* tree<T>::createNode(T data){
	node<T> *newNode = new(node<T>);
	newNode-> data=data;
	newNode->bf =0;
	newNode->left = newNode->right = nullptr;
	return newNode;
}
template<class T>
void tree<T>::inorder(node<T> *rt){
	if(rt != nullptr){
		inorder(rt->left);
		cout<<"("<<rt->data<<","<<rt->bf<<")"<<" ";
		inorder(rt->right);
	}
}
template<class T>
int tree<T>::height(node<T> *rt){
	if(rt == nullptr)
		return -1;
	return 1+max(height(rt->left),height(rt->right));
}
template<class T>
node<T>* tree<T>::rr_rotate(node<T> *rt){
	if(rt == root)
		root = root->left;
	node<T> *lr = rt->left->right,*new_node = rt->left;
	rt->left->right = rt;
	rt->left = lr;
	return new_node;
}
template<class T>
node<T>* tree<T>::ll_rotate(node<T> *rt){
	if(rt == root)
		root = root->right;
	node<T> *rl = rt->right->left,*new_node = rt->right;
	rt->right->left = rt;
	rt->right = rl;
	return new_node;
}
template<class T>
void tree<T>::cal_bf(node<T> *rt,node<T>* parent){
	node<T>* temp = nullptr;
	rt->bf=height(rt->left)-height(rt->right);
	if(rt->bf < -1){
		if(rt->right->bf > 0){
			temp = rr_rotate(rt->right);
			rt->right = temp;
		}
		temp = ll_rotate(rt);
	}
	else if(rt->bf > 1){
		if(rt->left->bf < 0){
			temp = ll_rotate(rt->left);
			rt->left = temp;
		}
		temp = rr_rotate(rt);
	}
	if(parent != nullptr && temp != nullptr){
		if(parent->data < temp->data)
			parent->right = temp;
		else
			parent->left = temp;
	}
	if(temp != nullptr){
		if(temp->left != nullptr)
			temp->left->bf = height(temp->left->left)-height(temp->left->right);
		if(temp->right != nullptr)
			temp->right->bf = height(temp->right->left)-height(temp->right->right);
		temp->bf = height(temp->left)-height(temp->right);
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
	if(rt != nullptr)
		cal_bf(rt,parent);
}
template<class T>
node<T>* tree<T>::inodersuccesor(node<T> *rt){
	while(rt->left != nullptr)
		rt = rt->left;
	return rt;
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
	    	node<T> *temp = inodersuccesor(rt->right);
	    	int val = temp->data;
	    	del(rt->right,rt,val);
	    	rt->data = val;
	    }
	}
	if(rt != nullptr)
		cal_bf(rt,parent);
}
int main(){
	tree<int> t;
	string str ="Enter choice :\n"
				"0:Exit\n"
				"1:insert\n"
				"2:delete\n"
				"3:print\n";
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
			t.inorder(t.getRoot());
			cout<<endl;
			break;
		default:
			if(choice != 0)
				cout<<"Invalid choice"<<endl;
		}
	}while(choice != 0);
	return 0;
}


