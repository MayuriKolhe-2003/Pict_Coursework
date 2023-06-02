//============================================================================
// Name        : pr9(avl).cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

class Node {
	int key;
	string value;
	int height=1;
	Node *left;
	Node *right;
public:
	Node() {
		key = -1;
		value = "";
		height = 1;
		left = right = nullptr;
	}
	Node(int k,string v){
		key = k;
		value = v;
		height = 1;
		left = right = nullptr;
	}
	string getValue(){
		return value;
	}
	friend class AVLTree;
};

class AVLTree {
	Node *root = nullptr;
public:
	int getHeight(Node *t) {
		if (t == nullptr) {
			return 0;
		}
		return t->height;
	}
	int getBalanceFactor(Node *t) {
		if (t == nullptr) {
			return 0;
		}
		return getHeight(t->left) - getHeight(t->right);
	}
	void updateHeight(Node *t) {
	    int hl = getHeight(t->left);
	    int hr = getHeight(t->right);
		t->height = 1 + max(hl , hr);
	}

	Node* LLRotation(Node *t) {
		Node *newRoot = t->left;
		t->left = newRoot->right;
		newRoot->right = t;

		// Updating the heights of node and newRoot
		// to in-turn update balance factors of these nodes
		updateHeight(t);
		updateHeight(newRoot);

		cout << "[Performed LL Rotation]" << endl;
		return newRoot;
	}

	Node* RRRotation(Node *t) {
		Node *newRoot = t->right;
		t->right = newRoot->left;
		newRoot->left = t;

		// Updating the heights of node and newRoot
		// to in-turn update balance factors of these nodes
		updateHeight(t);
		updateHeight(newRoot);

		cout << "[Performed RR Rotation]" << endl;
		return newRoot;
	}

	Node* LRRotation(Node *t) {
		t->right = LLRotation(t->right);
		return LLRotation(t);

	}

	Node* RLRotation(Node *t) {
		t->left = RRRotation(t->left);
		return RRRotation(t);
	}

	Node* balance(Node *node) {
		if (getBalanceFactor(node) == 2) {
			// Left subtree has a greater height
			// Possible rotations: LL, LR
		if(getBalanceFactor(node->left)  < 0 ) {
			// For left child, right subtree has greater height. Hence, use LR rotation
			node = LRRotation(node);
		} else {
			// For left child, left subtree has greater height. Hence, use LL rotation
			node = LLRotation(node);
		}
	} else if (getBalanceFactor(node) == -2) {
		// Right subtree has a greater height
		// Possible rotations: RR, RL
	if(getBalanceFactor(node->right) > 0 ) {
		// For left child, right subtree has greater height. Hence, use RL rotation
		node = RLRotation(node);
	} else {
		// For left child, left subtree has greater height. Hence, use RR rotation
		node = RRRotation(node);
	}
}
		updateHeight(node);
		return node;
}

	void inorderRec(Node *t){
		if(t == nullptr){
			return;
		}
		inorderRec(t->left);
		cout<< t->key << "|"<<getBalanceFactor(t)<<"|" << " ";
		inorderRec(t->right);
	}

	Node* insertSubTree(Node *curr,int key,string value){
		if(curr == nullptr){
			Node *newNode = new Node(key , value);
			return newNode;
		}
		if(curr->key > key){
			curr->left = insertSubTree(curr->left , key , value);
		}
		else if(curr->key < key){
			curr->right = insertSubTree(curr->right , key , value);
		}else{
			curr->value = value;
			return curr;
		}
		return balance(curr);
	}

public:
	void insert(int key , string value)
	{
		root = insertSubTree(root , key , value);
	}
	void inorder()
	{
		inorderRec(root);
		cout<<endl;
	}
	Node* search(int key)
	{
		Node* curr = root;
		while(curr != nullptr)
		{
			if(curr->key > key){
				curr = curr->left;
			}
			else if(curr->key < key){
				curr = curr->right;
			}
			else{
				return curr;
			}
		}
		return nullptr;
	}

	void BFS()
	{
		queue <Node*> q;
		q.push(root);
		while(!q.empty()){
			Node* popNode = q.front();
			cout<<popNode->key << " ";
			q.pop();
			if(popNode->left != nullptr){
				q.push(popNode->left);
			}
			if(popNode->right != nullptr){
				q.push(popNode->right);
			}
		}
		cout<<endl;
	}
};

int main() {
cout << "!!!AVL TREE!!!" << endl;
AVLTree tree;
int key;
string value;
int ch;
Node* res;

while(true){

	cout<<"1.Insert(key,value) 2.Inorder 3.search 4.BFS 5.Exit"<<endl;
	cin>>ch;

	switch(ch){
	case 1:
		cout<<"Enter key and Value : ";
		cin>>key>>value;
		tree.insert(key, value);
		break;
	case 2:
		cout<<"Inorder Traversal : "<<endl;
		tree.inorder();
		break;
	case 3:
		cout<<"Enter key to search :";
		cin>>key;
		res = tree.search(key);
		if(res == nullptr){
			cout<<"Key not found"<<endl;
		}else{
			cout<<"Key found Value is :"<<res->getValue()<<endl;
		}
		break;
	case 4:
		cout<<"BFS traversal :"<<endl;
		tree.BFS();
		break;
	case 5:
		exit(0);
	default:
		exit(0);
	}
}

return 0;
}

