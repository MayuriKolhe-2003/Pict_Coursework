///avl insertion and deletion

#include <iostream>
#include <queue>

using namespace std;

class node{
    int key;
    string value;
    int height = 1;
    node *left;
    node *right;
    
    public:
    node(){
        key = 0;
        value = "";
        height = 1;
        left = nullptr;
        right = nullptr;
    }
    node(int k,string v){
        key = k ;
        value = v;
        height = 1;
        left = nullptr ;
        right = nullptr;
    }
    friend class avl;
};

class avl{
    node *root;
    public:
    avl(){
        root = nullptr;
    }
    node *getRoot(){
        return root;
    }
    int getHeight(node *t){
        if(t == nullptr){
            return 0;
        }
        return t->height;
    }
    int getBalanceFactor(node *t){
        if(t == nullptr){
            return 0;
        }
        return (getHeight(t->left) - getHeight(t->right));
    }
    void updateHeight(node *t){
        int hl = getHeight(t->left);
        int hr = getHeight(t->right);
        t->height = 1 + max(hl,hr);
    }
    
    node *LLRotation(node *t)
    {
        node *newnode = t->left ;
        t->left = newnode->right;
        newnode->right = t;
        
        updateHeight(t);
        updateHeight(newnode);
        
        cout<<"[LL]"<<endl;
        return newnode;
    }
    node* RRRotation(node *t)
    {
        node *newnode = t->right;
        t->right = newnode->left;
        newnode->left = t;
        
        updateHeight(t);
        updateHeight(newnode);
        
        std::cout << "[RR]" << std::endl;
        return newnode;
    }
    node* LRRotation(node *t)
    {
        t->left = RRRotation(t->left);
        return LLRotation(t);
        std::cout << "[LR]" << std::endl;
    }
    node* RLRotation(node *t)
    {
        t->right = LLRotation(t->right);
        return RRRotation(t);
        std::cout << "[RL]" << std::endl;
    }
    
    node* balance(node *t){
        if(getBalanceFactor(t) == 2){
            if(getBalanceFactor(t->left) < 0){
                std::cout << "call(lr_)" << std::endl;
                t = LRRotation(t);
            }else{
                std::cout << " call ll" << std::endl;
                t = LLRotation(t);
            }
        }
        else if(getBalanceFactor(t)==-2){
            if(getBalanceFactor(t->right)>0){
                std::cout << "call rl" << std::endl;
                t = RLRotation(t);
            }else{
                std::cout << "call rr" << std::endl;
                t = RRRotation(t);
            }
        }
        updateHeight(t);
        return t;
    }
    
    void inorder(node* t){
        if(t == nullptr){
            return;
        }
        inorder(t->left);
        std::cout << t->key << " ";
        inorder(t->right);
    }
    
    node* insert(node* curr ,int key,string value)
    {
        if(curr == nullptr){
            node *newnode = new node(key,value);
            return newnode;
        }
        if(curr->key < key){
            curr->right = insert(curr->right,key,value);
        }else if(curr->key > key){
            curr->left = insert(curr->left , key,value);
        }else{
            curr->value = value;
            return curr;
        }
        return balance(curr);
    }
    
    
    void insert_data(int key,string value){
        root = insert(root , key,value);
    }
    
    void bfs()
    {
        queue<node*> q ;
        node *t;
        q.push(root);
        while(!q.empty()){
            t = q.front();
            q.pop();
            cout<<t->key << "|" << getBalanceFactor(t)<< "|"<<" ";
            
            if(t->left != nullptr){
                q.push(t->left);
            }
            if(t->right != nullptr){
                q.push(t->right);
            }
        }
        cout<<endl;
    }
    
    node* findminValnode(node*t)
    {
        if(t==nullptr || t->left==nullptr){
            return t;
        }
        return findminValnode(t->left);
    }
    
    node* deleteNode(node* curr , int key)
    {
        if(curr == nullptr){
            return nullptr;
        }
        if(key < curr->key)
        {
            curr->left = deleteNode(curr->left , key);
        }else if(key > curr->key){
            curr->right = deleteNode(curr->right , key);
        }else{
            if(curr->left == nullptr || curr->right == nullptr){
                node *temp;
                temp = curr->left ? curr->left : curr->right;
                if(temp == nullptr){
                    temp = curr;
                    curr = nullptr;
                }else{
                    *curr = *temp;
                }
                delete(temp);
            }else{
                node *temp;
                temp = findminValnode(curr->right);
                curr->key = temp->key;
                curr->value = temp->value;
                curr->right = deleteNode(curr->right , temp->key);
            }
        }
        
        if(curr == nullptr){
            return nullptr;
        }
        return balance(curr);
    }
    
    void delete_ele(int key){
        root = deleteNode(root,key);
    }
};

int main()
{
    avl tree;
    tree.insert_data(20,"a");
    tree.insert_data(10,"b");
    tree.insert_data(30,"c");
    tree.insert_data(15,"c");
    tree.insert_data(11,"c");
    tree.insert_data(12,"c");
    tree.insert_data(14,"c");
    //tree.inorder(tree.getRoot());
    tree.bfs();
    
    tree.delete_ele(14);
    tree.bfs();
    
     tree.delete_ele(11);
    tree.bfs();

    return 0;
}
