#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <stack>
#include <queue>

using namespace std;

class node{
	int data;
	bool lbit;
	bool rbit;
	node *left;
	node *right;
public:
	node()
	{
		data = -1;
		left = right = nullptr;
		lbit = rbit = 0;
	}
	node(int d){
		data = d;
		left = right = nullptr;
		lbit = rbit =0;
	}
	friend class tbt;
	
};

class tbt{
    node* root;
    node* head;
    public:
      tbt(){
          root = nullptr;
          head = nullptr;
          std::cout << "cr" << std::endl;
      }
      node* getroot(){
          std::cout << "root : "<<root->data << std::endl;
          return root;
      }
    void setroot(node* r){
        root = r;
    }
    
    bool search(node* &curr, node* &par,int key)
    {
        while(curr != head)
        {
            if(curr->data == key){
                return true;
            }else{
                par = curr;
                if(curr->data > key){
                    curr = curr->left;
                }else{
                    curr = curr->right;
                }
            }
        }
        return false;
    }
    
    void insert(int key)
    {
        if(root == nullptr)
        {
            head = new node();
            root = new node(key);
            head->right = head;
            head->left = root;
            
            root->left = head;
            root->right = head;
            std::cout << "root" << std::endl;
        }
        else
        {
            node *nn = new node(key);
            node *p = root;
            while(1)
            {
                if(p->data > nn->data)
                {
                    if(p->lbit != 0){
                        p = p->left;
                    }else{
                        nn->left = p->left;
                        nn->right = p;
                        p->left = nn;
                        p->lbit = 1;
                        std::cout << "in left :"<<p->data << std::endl;
                        return;
                    }
                    
                }else{
                    if(p->rbit != 0){
                        p = p->right;
                    }else{
                        nn->right = p->right;
                        nn->left = p;
                        p->right = nn;
                        p->rbit = 1;
                        std::cout << "in right :"<<p->data << std::endl;
                        return;
                    }
                }
            }
        }
    }
    
    void inorder()
    {
        node *t = root;
        while(t->lbit != 0){
            t = t->left;
        }
        
        while(t != head)
        {
            cout<<t->data <<" ";
            if(t->rbit != 0){
                t = t->right;
                while(t->lbit != 0){
                    t= t->left;
                }
            }else{
                t = t->right;
            }
        }
    }
    
    void preorder()
    {
        node*t = root;
        while(t != head)
        {
            cout<<t->data <<" ";
            if(t->lbit == 1){
                t = t->left;
            }else if(t->rbit == 1){
                t = t->right;
            }else{
                while(t->rbit != 1 && t!=head){
                    t = t->right;
                }
                if(t != head){
                    t = t->right;
                }
            }
        }
    }
    
    void remove(int key)
    {
        if(root == nullptr){
            std::cout << "empty" << std::endl;
        }else{
            node *curr = root;
            node *par = nullptr;
            bool found = search(curr,par,key);
            if(!found ){
                std::cout << "not" << std::endl;
                return;
            }else{
                //2 child
                if(curr->lbit==1 && curr->rbit==1){
                    node *succ = curr->right;
                    par = curr;
                    while(succ->lbit != 0){
                        par = succ;
                        succ = succ->left;
                    }
                    curr->data = succ->data;
                    curr = succ;
                }
                // leaf nodes both threads
                if(curr->lbit==0 && curr->rbit==0){
                    if(curr == par->left){
                        par->left = curr->left;
                        par->lbit = 0;
                    }
                    else{
                        par->right = curr->right;
                        par->rbit = 0;
                    }
                    delete curr;
                }
                
                //left link and right thread
                if(curr->lbit==1 && curr->rbit==0)
                {
                    node*tmp = curr->left;
                    if(par->left==curr){
                        par->left = tmp;
                    }else{
                        par->right = tmp;
                    }
                    while(tmp->rbit != 0){
                        tmp = tmp->right;
                    }
                    tmp->right = curr->right;
                    delete curr;
                }
                
                //left thread and right link
                if(curr->lbit ==0 && curr->rbit==1)
                {
                    node*tmp = curr->right;
                    if(par->left == curr){
                        par->left = tmp;
                    }
                    else{
                        par->right = tmp;
                    }
                    while(tmp->lbit != 0){
                        tmp = tmp->left;
                    }
                    tmp->left = curr->left;
                    delete curr;
                }
            }
        }
    }
    
   
};

int main()
{
    tbt t;
    t.insert(30);
    t.insert(20);
    t.insert(40);
    t.insert(35);
    t.insert(25);
    t.insert(10);
    
    t.inorder();
    cout<<endl;
    //t.preorder();
    cout<<endl;
    
    t.remove(30);
    t.remove(20);
    t.remove(10);

    t.inorder();
    cout<<endl;
    t.preorder();
    cout<<endl;
    t.getroot();
    

	
	return 0;
}
