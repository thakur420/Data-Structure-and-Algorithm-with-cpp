/*
 * singly linked list
 *
 *  Created on: 13-Jul-2018
 *      Author: indrajeet
 */
#include <iostream>
#include <string>
using namespace std;
template<class T>
struct node{
	T data;
	node *nextnodeptr;
};
template<class T>
class list{
private:
	node<T> *headptr=nullptr;
public:
	list(node<T> *headptr=nullptr):headptr(headptr){}
	node<T> *createNode(T,node<T> *);
	void prepend(T);
	void append(T);
	void addafter(T,T);
	void addbefore(T,T);
	T findPosition(T,bool);
	void sortlist(bool);
	void delbeg();
	void delnode(T);
	void reverse();
	void print();
};
template<class T>
inline node<T>* list<T>::createNode(T data,node<T>* nextptr){
	node<T> *newNode = new(node<T>);
	newNode-> data=data;
	newNode-> nextnodeptr=nextptr;
	return newNode;
}
template<class T>
void list<T>::prepend(T data){
	node<T> *newNode = createNode(data,headptr);
	headptr=newNode;
}
template<class T>
void list<T>::append(T data){
	node<T> *iter = headptr;
	while(iter!=nullptr && iter->nextnodeptr!=nullptr)
		iter = iter->nextnodeptr;
	node<T> *newNode = createNode(data,nullptr);
	if(iter == nullptr)
		headptr = newNode;
	else
		iter->nextnodeptr=newNode;
}
template<class T>
void list<T>::addafter(T positionValue,T data){
	node<T> *iter = headptr;
	while(iter!=nullptr && iter->data!=positionValue)
		iter = iter->nextnodeptr;
	if(iter==nullptr)
		cout << "Value not found" <<endl;
	else{
		node<T> *newNode = createNode(data,iter->nextnodeptr);
		iter->nextnodeptr = newNode;
	}
}
template<class T>
void list<T>::addbefore(T positionValue,T data){
	node<T> *iter = headptr,*prev=nullptr;
	while(iter!=nullptr && iter->data!=positionValue){
		prev=iter;
		iter = iter->nextnodeptr;
	}
	if(iter==nullptr)
		cout << "Value not found" <<endl;
	else if(prev==nullptr)
		prepend(data);
	else{
		node<T> *newNode = createNode(data,iter);
		prev->nextnodeptr = newNode;
	}
}
template<class T>
T list<T>::findPosition(T data,bool ascending){
	node<T> *iter=headptr;
	while(iter!=nullptr)
		if(ascending==true && data > iter->data)
			iter = iter->nextnodeptr;
		else if(ascending==false && data < iter->data)
			iter = iter->nextnodeptr;
		else
			return iter->data;
}
template<class T>
void list<T>::sortlist(bool ascending){
	node<T> *iter = headptr;
	while(iter!=nullptr && iter->nextnodeptr!=nullptr){
		if(ascending==true && iter->data < iter->nextnodeptr->data)
			iter=iter->nextnodeptr;
		else if(ascending==false && iter->data > iter->nextnodeptr->data)
			iter=iter->nextnodeptr;
		else{
			T temp =iter->nextnodeptr->data;
			delnode(temp);
			addbefore(findPosition(temp,ascending),temp);
		}
	}
}
template<class T>
void list<T>::delbeg(){
	if(headptr == nullptr){
		cout << "list is empty" <<endl;
		return ;
	}
	node<T> *temp=headptr;
	headptr=headptr->nextnodeptr;
	delete temp;
}
template<class T>
void list<T>::delnode(T data){
	node<T> *iter = headptr,*prev=nullptr;
	while(iter!=nullptr && data != iter->data){
		prev = iter;
		iter=iter->nextnodeptr;
	}
	if(iter == nullptr)
		cout << "Value not found" <<endl;
	else{
		prev->nextnodeptr = iter->nextnodeptr;
		delete iter;
	}
}
template<class T>
void list<T>::reverse(){
	node<T> *iter=headptr;
	while(iter!=nullptr && iter->nextnodeptr!=nullptr){
		T temp = iter->nextnodeptr->data;
		delnode(temp);
		prepend(temp);
	}
}
template<class T>
void list<T>::print(){
	node<T> *iter = headptr;
	while(iter!=nullptr){
		cout << iter->data <<" " ;
		iter = iter->nextnodeptr;
	}
}
int main(void) {
	list<char> l;
	string str ="Enter choice :\n"
				"0:Exit\n"
				"1:Add in beginning\n"
				"2:Add in last\n"
				"3:Add after\n"
				"4:Add before\n"
				"5:Reverse\n"
				"6:Sort list\n"
				"7:Delete first\n"
				"8:Delete node\n"
				"9:Print list";
	int choice=0;
	do{
		char input;
		int positionValue;
		bool order;
		cout << str << endl;
		cin >> choice;
		switch(choice){
		case 0:
			cout << "terminating the program..."<<endl;
			cout << "program terminated."<<endl;
			break;
		case 1:
			cout <<"insert value"<<endl;
			cin >> input;
			l.prepend(input);
			break;
		case 2:
			cout <<"insert value"<<endl;
			cin >> input;
			l.append(input);
			break;
		case 3:
			cout <<"insert value"<<endl;
			cin >> input;
			cout <<"Enter value after which you want to add new node" <<endl;
			cin >> positionValue;
			l.addafter(positionValue,input);
			break;
		case 4:
			cout <<"insert value"<<endl;
			cin >> input;
			cout <<"Enter value before which you want to add new node" <<endl;
			cin >> positionValue;
			l.addbefore(positionValue,input);
			break;
		case 5:
			l.reverse();
			break;
		case 6:
			cout <<"Enter choice:\n1:Ascending\n2:descending"<<endl;
			cin >> input;
			order = (input==1 ? true : false);
			l.sortlist(order);
			break;
		case 7:
			l.delbeg();
			break;
		case 8:
			cout << "Enter value to be deleted" <<endl;
			cin >> input;
			l.delnode(input);
			break;
		case 9:
			l.print();
			break;
		default :
			cout << "Wrong choice entered" << endl;
		}
	}while(choice!=0);
	return 0;
}
