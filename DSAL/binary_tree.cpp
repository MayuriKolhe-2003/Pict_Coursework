#include <iostream>
#include <string>
#define size 20
using namespace std;

//-------------STACK CLASS-----------------------//
template <class T>
class Stack
{
	private:
		int top;
		T st[size];
     public:
        Stack()
        {
        	top=-1;
        }
        void push(T i);
        T pop();
        bool isEmpty()
        {
        	if(top==-1)
        	{
        		return 1;
        	}
        	return 0;
        }
        bool isFull()
        {
           if(top==size -1)
           {
          		return 1;
           }
           return 0;
        }
        friend class binary_tree;

};
template <class T>
void Stack<T>::push(T i)
{
      st[++top] = i;
}

template <class T>
T Stack<T>::pop()
{
      return st[top--];
}

//-------------NODE CLASS--------------------//
class node
{
	int data;
	node *left,*right;
public :


	node()
	{
		data = 0;
		left = right = NULL;
	}
	node(int x)
	{
		data = x;
		left = right = NULL;
	}
	friend class binary_tree;
};


//-------------BINARY TREE CLASS-------------//
class binary_tree
{
	node *root;
public:

	binary_tree()
	{
		root = NULL;
		cout<<"Tree created..\n";
	}
	node* getRoot(){return root;}
	void setRoot(node* r){root = r; }

	node* R_create();
	void I_create();
	void R_inorder(node* r);
	void R_preorder(node* r);
	void R_postorder(node* r);

	void I_inorder();
	void I_preorder();
	void I_postorder();


};

node* binary_tree::R_create()
{
	int n;
	node* t;
	cout<<"\nEnter data or -1 : ";
	cin>>n;
	if(n==-1)
	{
		return NULL;
	}
	t = new node(n);
	cout<<"\nEnter left child of: "<<t->data;
		t->left = R_create();
	cout<<"\nEnter right child of: "<<t->data;
		t->right = R_create();

	return t;
}
void binary_tree::I_create()
{
	node *t,*p;
	int n;
	Stack <node*> st;
	cout<<"\nEnter root: ";
	cin>>n;
	t = new node(n);
	setRoot(t);
	st.push(getRoot());

	while(!st.isEmpty())
	{
		p = st.pop();
		cout<<"\nEnter left child of "<<p->data;
		cin>>n;
		if(n!=-1)
		{
			t = new node(n);
			p->left = t;
			st.push(t);
		}
		cout<<"\nEnter right child of "<<p->data;
		cin>>n;
		if(n!=-1)
		{
			t = new node(n);
			p->right = t;
			st.push(t);
		}
	}

}

void binary_tree::R_inorder(node* r)
{
	if(r==NULL)
	{
		return;
	}
	R_inorder(r->left);
	cout<<r->data<< "\t";
	R_inorder(r->right);
}
void binary_tree::R_preorder(node* r)
{
	if(r==NULL)
	{
		return;
	}
	cout<<r->data<< "\t";
	R_preorder(r->left);
	R_preorder(r->right);
}
void binary_tree::R_postorder(node* r)
{
	if(r==NULL)
	{
		return;
	}
	R_postorder(r->left);
	R_postorder(r->right);
	cout<<r->data<< "\t";
}

void binary_tree::I_inorder()
{
	cout<<"\nInorder Traversal : \n";
	Stack <node*> st;
	node* temp;
	temp = getRoot();

	while(!st.isEmpty() || temp!=NULL)
	{
		if(temp!=NULL)
		{
			st.push(temp);
			temp = temp->left;
		}else{
			temp = st.pop();
			cout<<temp->data<<"\t";
			temp = temp->right;
		}
	}
}
void binary_tree::I_preorder()
{
	cout<<"\nPreorder Traversal : \n";
	Stack <node*> st;
	node* temp;
	temp = getRoot();

	/*while(!st.isEmpty() || temp!=NULL)
	{
		if(temp!=NULL)
		{
			cout<<temp->data<<"\t";
			st.push(temp);
			temp = temp->left;
		}else{
			temp = st.pop();
			temp = temp->right;
		}
	}*/
	st.push(temp);
	while(!st.isEmpty() || temp!=NULL)
	{
		temp = st.pop();
		cout<<temp->data<<"\t";
		if(temp->right != NULL)
		{
			st.push(temp->right);
		}
		if(temp->left != NULL)
		{
			st.push(temp->left);
		}

	}
}
void binary_tree::I_postorder()
{

}


int main ()
{
		Stack <node *> s1;
		binary_tree b1;
		b1.I_create();

		b1.R_inorder(b1.getRoot());
		//b1.I_preorder();

}
