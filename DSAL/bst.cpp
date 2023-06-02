#include <iostream>
using namespace std;

class node {
public:
	int data;
	node *left, *right;

	node() {
		data = 0;
		left = right = NULL;
	}
	node(int x) {
		data = x;
		left = right = NULL;
	}
	friend class BST;
};

class BST {
	node *root;
public:

	BST() {
		root = NULL;
		cout << "Tree created..\n";
	}
	node* getRoot() {
		return root;
	}
	void insert(int x);
	void inorder(node *r);
	void preorder(node *r);
	void postorder(node *r);
	int search(int x, node *&curr, node *&parent);
	void remove(int x);
	void min();
	void max();
	int height(node *t);
	node* swap(node *t);
};

int BST::search(int x, node *&curr, node *&parent) {
	int count = 0;
	while (curr != NULL) {
		count++;
		if (curr->data == x) {
			return count;
		} else {
			parent = curr;
			if (curr->data > x) {
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}
	}
	if(curr == NULL)
	{
		return 0;
	}
}

void BST::insert(int x) {
	node *newnode = new node(x);
	node *curr = root;
	node *parent = NULL;
	int sflag;

	if (root == NULL) {
		root = newnode;
	} else {
		sflag = search(x, curr, parent);
		if (curr == NULL) {
			if (parent->data > x) {
				parent->left = newnode;
				cout << "Inserted at left [Parent " << parent->data << "]";
			} else {
				parent->right = newnode;
				cout << "Inserted at right [Parent " << parent->data << "]";
			}
		} else {
			cout << "Duplicate Data\n";
		}
	}

}

void BST::remove(int x) {
	node *parent = NULL;
	node *child;
	node *curr = root;

	if (root == NULL) {
		cout << "Tree is empty..\n";
	}
	int sflag = search(x, curr, parent);

//if x is having both left and right child
	if (curr->left != NULL && curr->right != NULL) {
		node *cs = curr->right;
		parent = curr;
		while (cs->left != NULL) {
			parent = cs;
			cs = cs->left;
		}
		curr->data = cs->data;
		curr = cs;

	}
//having  no child(leaf node)
	if (curr->left == NULL && curr->right == NULL) {
		child = NULL;
	}
//having  only left
	if (curr->left != NULL && curr->right == NULL) {
		child = curr->left;
	}
//having  only right
	if (curr->left == NULL && curr->right != NULL) {
		child = curr->right;
	}
	if (parent != NULL) {
		if (curr == parent->left) {
			parent->left = child;
		} else {
			parent->right = child;
		}
	} else {
		root = child;
	}
	cout << "Element deleted : " << x;
	cout << "\nRoot is : " << root->data;
	free(curr);
}

void BST::inorder(node *r) {
	if (r == NULL) {
		return;
	}
	inorder(r->left);
	cout << r->data << "\t";
	inorder(r->right);
}
void BST::preorder(node *r) {
	if (r == NULL) {
		return;
	}
	cout << r->data << "\t";
	inorder(r->left);
	inorder(r->right);
}
void BST::postorder(node *r) {
	if (r == NULL) {
		return;
	}
	inorder(r->left);
	inorder(r->right);
	cout << r->data << "\t";
}
void BST::min() {
	node *t = root;
	while (t->left != NULL) {
		t = t->left;
	}
	cout << "Minimum element : " << t->data;
}
void BST::max() {
	node *t = root;
	while (t->right != NULL) {
		t = t->right;
	}
	cout << "Maximum element : " << t->data;
}

int BST::height(node *t) {
	int l, r;
	if (t == NULL) {
		return 0;
	}
	if (t->left == NULL && t->right == NULL) {
		return 0;
	}
	l = height(t->left);
	r = height(t->right);
	return (l > r) ? l + 1 : r + 1;
}
node* BST::swap(node *t) {
	node *p;
	if (t != NULL) {
		p = t->left;
		t->left = swap(t->right);
		t->right = swap(p);
	}
	return t;
}

int main() {
	cout << "!!!BINAARY SEARCH TREE!!!" << endl; // prints !!!Hello World!!!
	BST tree1;

	int c = 1, ch, n, s;

	while (c) {
		cout
				<< "\n1.Insert 2.Inorder 3.Preorder 4.Postorder 5.Search 6.Delete\n"
						"7.Minimum 8.Maximum 9.Height 10.Swap 11.Nodes in longest Path\n";
		cin >> ch;
		switch (ch) {
		case 1:
			cout << "Enter element : ";
			cin >> n;
			tree1.insert(n);
			break;
		case 2:
			tree1.inorder(tree1.getRoot());
			break;
		case 3:
			tree1.preorder(tree1.getRoot());
			break;
		case 4:
			tree1.postorder(tree1.getRoot());
			break;
		case 5:
			cout << "Enter element to search : ";
			cin >> n;
			node *p = NULL;
			node *curr = tree1.getRoot();
			s = tree1.search(n, curr, p);
			if (s == 0) {
				cout << "Element NOT found.\n";
			} else {
				cout << "Element found in " << s << " comparisons.\n";
			}
			break;
		case 6:
			cout << "Enter element to remove : ";
			cin >> n;
			tree1.remove(n);
			break;
		case 7:
			tree1.min();
			break;
		case 8:
			tree1.max();
			break;
		case 9:
			s = tree1.height(tree1.getRoot());
			cout << "Height of Tree : " << s;
			break;
		case 10:
			tree1.swap(tree1.getRoot());
			break;
		case 11:
			s = tree1.height(tree1.getRoot());
			cout << "Number of nodes in longest path : " << s + 1;
			break;

		default:
			exit(0);

		}

	}
