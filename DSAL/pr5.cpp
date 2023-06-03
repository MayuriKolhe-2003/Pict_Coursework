#include <iostream>
using namespace std;

class Node {
	string word;
	string meaning;
	Node *next;
public:
	Node() {
		word = "";
		meaning = "";
		next = NULL;
	}
	Node(string w, string m) {
		word = w;
		meaning = m;
		next = NULL;
	}
	friend class Dictionary;
};

class Dictionary {
	Node **headNodes;
	int tableSize;

public:
	Dictionary() {
		headNodes = NULL;
		tableSize = 0;
	}
	Dictionary(int n) {
		headNodes = new Node*[n];
		tableSize = n;
		for (int i = 0; i < n; i++) {
			headNodes[i] = NULL;
		}
	}
	int HashFunction(string w) {
		int c = 0;
		for (int i = 0; i < w.length(); i++) {
			c = c + (int(w[i]) * i * i);
		}
		return (c % tableSize);
	}
	void display() {
		for (int i = 0; i < tableSize; i++) {
			cout << "[" << i << "] ";
			Node *temp = headNodes[i];
			while (temp != NULL) {
				cout << temp->word << " --> ";
				temp = temp->next;
			}
			cout << endl;
		}
	}
	void insert(string w, string m) {
		Node *newNode = new Node(w, m);
		int k = HashFunction(w);
		if (headNodes[k] == NULL) {
			headNodes[k] = newNode;
		} else {
			Node *temp = headNodes[k];
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
		cout << "INserted";
	}
	void search(string w) {
		int k = HashFunction(w);
		Node *temp = headNodes[k];
		if (temp == NULL) {
			cout << "\n Word Not found";
		} else {
			while (temp != NULL && temp->word != w) {
				temp = temp->next;
			}
			if (temp == NULL) {
				cout << "\n Word Not found";
			} else {
				cout << "Word \t Meaning";
				cout << temp->word << " \t" << temp->meaning;
			}
		}
	}
	void remove(string w) {
		int k = HashFunction(w);
		Node *temp = headNodes[k];
		if (temp == NULL) {
			cout << "\n Word Not found";
		} else {
			if(temp->word == w)
			{
				headNodes[k] = temp->next;
				delete(temp);
				return;
			}
			
			Node *p = temp;
			while (temp != NULL && temp->word != w) {
				p = temp;
				temp = temp->next;
			}
			if (temp == NULL) {
				cout << "\n Word Not found";
			} else {
				p->next = temp->next;
				delete (temp);
			}
		}
	}

};

int main() {
	cout << "!!!Dictionary!!!" << endl; // prints !!!Hello World!!!
	Dictionary d(5);
	int ch;
	string w, m;

	while (1) {
		cout << "\n1.Insert 2.Search 3.Remove 4.Display";
		cin >> ch;

		switch (ch) {
		case 1:
			cout << "\nEnter word : ";
			cin >> w;
			cout << "Enter meaning : ";
			cin >> m;

			d.insert(w, m);
			break;
		case 2:
			cout << "\nEnter word to Search: ";
			cin >> w;
			d.search(w);
			break;
		case 3:
			cout << "\nEnter word to Remove: ";
			cin >> w;
			d.remove(w);
			break;
		case 4:
			cout << "\n***Dictionary***\n";
			d.display();
			break;
		default:
			exit(0);
		}
	}
	return 0;
}
