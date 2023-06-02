#include <iostream>
using namespace std;

class node {
	int data;
	node *right;
	node *left;
	bool rbit, lbit;
	friend class TBT;
public:

	node() {
		data = 0;
		right = left = NULL;
		rbit = lbit = 0;
	}
	node(int x) {
		data = x;
		right = left = NULL;
		rbit = lbit = 0;
	}
};

class TBT {
	node *root;
	node *head;
public:
	TBT() {
		root = NULL;
		head = NULL;
	}
	node* getRoot() {
		return root;
	}
	void Insert(int x);
	void Inorder();
	void Preorder();
	int search(int x, node *&curr, node *&parent);
	void remove(int x);
};

int TBT::search(int x, node *&curr, node *&parent) {
	int count = 0;
	while (curr != head) {
		count++;
		if (curr->data == x) {
			return count;
		} else {
			parent = curr;
			if (curr->data > x) {
				if (curr->lbit == 1) {
					curr = curr->left;
				}
			} else {
				if (curr->rbit == 1) {
					curr = curr->right;
				}
			}
		}
	}
	return count;
}

void TBT::Insert(int x) {
	if (root == NULL) {
//create header node
		head = new node();
		head->right = head;

		root = new node(x);
		root->left = head;
		root->right = head;

		head->left = root;

		cout << "\nInserted at root.";
	} else {
		node *p;
		node *temp = new node(x);
		p = root;

		while (1) {
//insert x at left
			if (p->data > x) {
//p has left link
				if (p->lbit != 0) {
					p = p->left;
				} else {
					temp->left = p->left;
					temp->right = p;
					p->lbit = 1;
					p->left = temp;
					cout << "\nInserted left :" << x << " Parent : [" << p->data
							<< "]";
					return;
				}
			}
//insert at right
			else {
//if p has left link
				if (p->rbit != 0) {
					p = p->right;
				} else {
					temp->right = p->right;
					temp->left = p;
					p->rbit = 1;
					p->right = temp;
					cout << "\nInserted right :" << x << " Parent : ["
							<< p->data << "]";
					return;
				}
			}
		}
	}
}

void TBT::Inorder() {
	cout << "\nInorder Traversal : ";
	if (root == NULL) {
		cout << "\nTree empty...";
		return;
	}
	node *temp;
	temp = root;
//go to extreme left node of tree
	while (temp->lbit != 0) {
		temp = temp->left;
	}
	while (temp != head) {
		cout << temp->data << "\t";
//if temp has a right link goto leftmost node of right subtree
		if (temp->rbit != 0) {
			temp = temp->right;
			while (temp->lbit != 0) {
				temp = temp->left;
			}
		}
//if temp has right thread
		else {
			temp = temp->right;
		}
	}
}

void TBT::Preorder() {
	cout << "\nPreorder Traversal : ";
	if (root == NULL) {
		cout << "\nTree empty...";
		return;
	}
	node *temp;
	temp = root;

//start from printing root
	while (temp != head) {
		cout << temp->data << "\t";
//left is link
		if (temp->lbit == 1) {
			temp = temp->left;
		}
//right is link
		else if (temp->rbit == 1) {
			temp = temp->right;
		} else {
			while (temp->rbit != 1 && temp != head) {
				temp = temp->right;
			}
			if (temp != head) {
				temp = temp->right;
			}
		}

	}

}

void TBT::remove(int x) {
	node *p;
	node *curr;
	node *succ;
	if (root == NULL) {
		cout << "\n Tree is empty...";\
	}
	p = head;
	curr = root;
	search(x, curr, p);
	cout << curr->data;
	cout << p->data;

//if curr has both links
	if (curr->lbit == 1 && curr->rbit == 1) {
		p = curr;
		succ = curr->right;
		while (succ->lbit != 0) {
			p = succ;
			succ = succ->left;
		}
		curr->data = succ->data;
		curr = succ;
	}
//if curr has both threads
	if (curr->lbit == 0 && curr->rbit == 0) {
//if curr is left child of p
		if (p->left == curr) {
			p->left = curr->left;
			p->lbit = 0;
		}
//if curr is right child of p
		if (p->right == curr) {
			p->right = curr->right;
			p->rbit = 0;
		}
	}
//if curr has left link and right thread
	if (curr->lbit == 1 && curr->rbit == 0) {
		node *temp;
		temp = curr->left;
		if (p->left == curr) {
			p->left = temp;
		} else {
			p->right = temp;
		}
//goto rightmost node
		while (temp->rbit == 1) {
			temp = temp->right;
		}
		temp->right = curr->right;
	}

//if curr has left thread and right link
	if (curr->lbit == 0 && curr->rbit == 1) {
		node *temp;
		temp = curr->left;
		if (p->left == curr) {
			p->left = temp;
		} else {
			p->right = temp;
		}
//goto rightmost node
		while (temp->lbit == 1) {
			temp = temp->left;
		}
		temp->left = curr->left;
	}

	cout << "Element deleted : " << x;
	cout << "\nRoot is : " << root->data;
	free(curr);

}

int main() {
	cout << "!!!Threaded Binary Tree!!!" << endl;
	TBT tree;
	int ch, x;
	node *temp = NULL;
	node *curr = tree.getRoot();

	while (1) {
		cout << "\n1.Insert 2.Inorder 3.Preorder 4.Delete ";
		cin >> ch;

		switch (ch) {
		case 1:
			cout << "\nEnter number to insert : ";
			cin >> x;
			tree.Insert(x);
			break;
		case 2:
			tree.Inorder();
			break;
		case 3:
			tree.Preorder();
			break;
		case 4:
			cout << "\nEnter number to remove : ";
			cin >> x;
			tree.remove(x);
			break;

		default:
			exit(0);
		}
	}
	return 0;
}
