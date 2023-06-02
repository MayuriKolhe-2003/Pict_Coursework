/*---------------------OBST-------------------------*/

#include <iostream>
using namespace std;

class Node
{
	string data;
	Node *left = NULL;
	Node *right = NULL;

public:
	Node(string x)
	{
		data = x;
		left = right = NULL;
	}
	friend class obst;
};

class obst{
	Node *root;
	int nW;

	float **W,**C,**R;

	public:
	obst(int n)
	{
		root = NULL;
		nW = n;

		W = new float*[nW];
		R = new float*[nW];
		C = new float*[nW];

		for(int i=0;i<=nW;i++)
		{
			W[i] = new float[nW];
			C[i] = new float[nW];
			R[i] = new float[nW];
		}

	}
	Node* getRoot()
	{
	    return root;
	}

	void print()
	{
		for(int i=0;i<=nW;i++)
		{
			for(int j=i;j<=nW;j++)
			{
				cout<<W[i][j] << "|" << C[i][j] <<"|" << R[i][j] <<"\t\t";
			}
			cout<<endl;
		}
	}

	void calculate_wt(float *p,float *q,string *input)
	{
		int k;
		//calculate W,C,R of i-j=0 and i-j=1
		for(int i=0;i<nW;i++)
		{
			W[i][i] = q[i];
			R[i][i] = C[i][i] = 0;

			W[i][i+1] = p[i] + q[i] + q[i+1];
			R[i][i+1] = i+1;
			C[i][i+1] = W[i][i+1];
		}
		W[nW][nW] = q[nW];
		R[nW][nW] = C[nW][nW] = 0;

		//calculate wt and cost of tree having more than one node
	for (int m = 2; m <= nW; ++m){
		// m = row number in calculations matrix
		for (int i=0; i<=nW-m; ++i){
			double Min = 999;

			int j = i + m;
			int k = 0;
			W[i][j] = W[i][j-1] + p[j-1] + q[j];

			// find minimum cost
			// C<i,j> = min(i<k<= j){C<i,k-1> + C<k,j>} + W<i,j>

			for (int x = i+1; x <= j; ++x){
				// find minimum sum
					double sum = C[i][x-1] + C[x][j];
//					cout << "Before:" << Min << endl;
					if (sum < Min){
						Min = sum;
						k = x;
					}
//					cout << "After:" << Min << endl;
			}
			// set cost and root
			C[i][j] = W[i][j] + C[i][k-1] + C[k][j];
			R[i][j] = k;
		}
	}
    root = create_tree(0,nW,R,input);
	}

	Node* create_tree(int i,int j,float** r , string* input)
	{
	    if(i != j)
	    {
	        int k = r[i][j];
	        Node *t = new Node(input[k]);
	        t->left = create_tree(i,k-1,r,input);
	        t->right = create_tree(k,j,r,input);

	        return t;
	    }
	    else
	    {
	        return NULL;
	    }
	}

	void inorder(Node *t)
	{
	    if(t != NULL)
	    {
	        inorder(t->left);
	        cout<<t->data<<"\t";
	        inorder(t->right);
	    }
	}
};


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	obst t(3);
	string input[] = {" ", "A1", "A2", "A3"};
	float p[]= {0.4, 0.1, 0.2};
	float q[] = {0.1, 0.04, 0.09, 0.07};

	t.calculate_wt(p,q,input);
	t.print();
	t.inorder(t.getRoot());

	return 0;
}

