//============================================================================
// Name        : pr6(adjlist).cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

class node {
	int id;
	int wt;
	node *next;
public:
	node() {
		id = wt = 0;
		next = nullptr;
	}
	node(int i, int w) {
		id = i;
		wt = w;
		next = nullptr;
	}
	friend class Graph;
};
class Graph {
	int v, e;
	node **adjList;
	string *cityNames;

public:
	Graph() {
		v = e = 0;
		adjList = nullptr;
		cityNames = nullptr;
	}
	Graph(int v, int e) {
		this->v = v;
		this->e = e;
		adjList = new node*[v];
		for (int i = 0; i < v; i++) {
			adjList[i] = nullptr;
		}
		cityNames = new string[v];
	}
	void setdata(int v, int e) {
		this->v = v;
		this->e = e;
		adjList = new node*[v];
		for (int i = 0; i < v; i++) {
			adjList[i] = nullptr;
		}
		cityNames = new string[v];
	}
	void accept_nodes() {
		cout << "Enter " << e << " edges" << endl;
		int srcId, destId, wt;
		string src, dest;

		for (int i = 0; i < e; i++) {
			cout << "Souce Id and City ";
			cin >> srcId >> src;
			cout << "Destination Id and City ";
			cin >> destId >> dest;
			cout << "Edge weight (Time of flight in hrs) ";
			cin >> wt;

			insert_edge(srcId, destId, src, dest, wt);
			cout << "Edge " << src << " -> " << dest << " inserted ." << endl;
		}
	}
	void insert_edge(int srcid, int destid, string src, string dest, int wt) {
		cityNames[srcid] = src;
		cityNames[destid] = dest;

		node *newNode = new node(destid, wt);

		//empty list
		if (adjList[srcid] == nullptr) {
			adjList[srcid] = newNode;
			return;
		}
		//non-empty list
		node *temp = adjList[srcid];
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
		return;
	}
	void display() {
		cout << "Adjacency List of Graph:" << endl;
		for (int i = 0; i < v; i++) {
			node *temp = adjList[i];
			cout << "[ " << i << " - " << cityNames[i] << " ] " << " -> \t";
			while (temp != nullptr) {
				cout << "|" << temp->id << ":" << cityNames[temp->id] << ":"
						<< temp->wt << "|";
				temp = temp->next;
			}
			cout << endl;
		}
	}

	int indegree(int id) {
		int indeg = 0;
		node *temp;
		for (int i = 0; i < v; i++) {
			temp = adjList[i];
			while (temp != nullptr) {
				if (temp->id == id) {
					indeg++;
				}
				temp = temp->next;
			}
		}
		return indeg;
	}
	int outdegree(int id) {
		node *temp = adjList[id];
		int outdeg = 0;
		while (temp != nullptr) {
			outdeg++;
			temp = temp->next;
		}
		return outdeg;
	}
	bool isConnected() {
		int *indeg = new int[v];
		int *outdeg = new int[v];

		for (int i = 0; i < v; i++) {
			indeg[i] = indegree(i);
			outdeg[i] = outdegree(i);
		}
		for (int i = 0; i < v; i++) {
			if (indeg[i] == 0 && outdeg[i] == 0) {
				return false;
			}
		}
		return true;
	}

	void DFS(int src) {

	}
	void DFS_iterative(int src) {
		stack<int> st;
		bool *visited = new bool[v];
		st.push(src);
		visited[src] = true;

		while (!st.empty()) {
			src = st.top();
			st.pop();
			cout << cityNames[src] << " ";

			//check adjList of curr node
			node *temp = adjList[src];
			while (temp != nullptr) {
				if (!visited[temp->id]) {
					visited[temp->id] = true;
					st.push(temp->id);
				}
				temp = temp->next;
			}
		}
	}
	void BFS(int src) {
		queue<int> q;
		bool *visited = new bool[v];
		q.push(src);
		visited[src] = true;

		while (!q.empty()) {
			src = q.front();
			q.pop();
			cout << cityNames[src] << " ";

			//check adjList of curr node
			node *temp = adjList[src];
			while (temp != nullptr) {
				if (!visited[temp->id]) {
					visited[temp->id] = true;
					q.push(temp->id);
				}
				temp = temp->next;
			}
		}
	}
};

int main() {
	cout << "!!!Hello World!!!" << endl;
	Graph g;
	int ch;
	int temp = 0,v=0,e=0;
	string status;

	cout << "# Flight Paths using Graph\n";
	while (true) {
		cout
				<< "1.Create 2.Accept NOdes 3.Display 4.Check Indeg 5.Check Outdeg 6.check connected 7.DFS 8.BFS 9.Exit"
				<< endl;
		cin >> ch;

		switch (ch) {
		case 1:
			cout << "Enter no. of vertices and edges = ";
			cin >> v >> e;
			g.setdata(v, e);
			break;
		case 2:
			g.accept_nodes();
			break;
		case 3:
			g.display();
			break;
		case 4:
			cout << "Enter vertex ID to find in-degree = ";
			cin >> temp;
			cout << "In-degree of " << temp << " = " << g.indegree(temp)<<endl;
			break;
		case 5:
			cout << "Enter vertex ID to find out-degree = ";
			cin >> temp;
			cout << "Out-degree of " << temp << " = " << g.outdegree(temp)<<endl;
			break;
		case 6: // Check if graph is connected

			status =
					(g.isConnected()) ?
							("graph is connected") : ("graph is disconnected");
			cout << status << endl;
			break;
		case 7:
			temp = 0;
			cout << "Enter src to start dfs :";
			cin >> temp;
			cout << "Nodes visited by DFS = ";
			g.DFS_iterative(temp);
			break;
		case 8:
			temp = 0;
			cout << "Enter src to start bfs :";
			cin >> temp;
			cout << "Nodes visited by BFS = ";
			g.BFS(temp);
			break;
		case 9:
			exit(0);
		default:
			exit(0);

		}
	}
	return 0;
}

