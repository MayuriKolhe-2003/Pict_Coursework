//============================================================================
// Name        : pr12(directfile).cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#define size 10

class student {
	int id;
	char name[20];

public:
	student() {
		id = -1;
		strcpy(name, "");
	}
	void accept() {
		string n;
		cout << "enter data";
		cin >> id;
		cin >> n;
		strcpy(name, n.c_str());
	}
	void display() {
		cout << id << "\t" << name << endl;
	}
	friend class direct;
};

class direct {
public:
	direct() {
		int c = 0;
		student s;
		ifstream file;
		file.open("rec.dat", ios::binary);
		if (!file.good()) {
			ofstream of;
			of.open("rec.dat", ios::binary);
			while (c <= size) {
				of.write((char*) &s, sizeof(s));
				c++;
			}
			cout << "new created\n";
			of.close();
		}
		cout << "exist\n";
		file.close();
	}
	int hf(int i) {
		return i % size;
	}
	void insert() {
		student n;
		student s;
		n.accept();

		fstream file;
		file.open("rec.dat", ios::binary | ios::out | ios::in);
		if (!file) {
			cout << "Err\n";
		} else {
			int hash = hf(n.id);
			file.seekg(hash * sizeof(n));
			file.read((char*) &s, sizeof(s));
			int tmp = s.id;

			if (s.id == -1) {
				file.seekp(hash * sizeof(n));
				file.write((char*) &n, sizeof(n));
				file.close();
			} else if (s.id == n.id) {
				cout << "dup\n";
			} else {
				file.read((char*) &s, sizeof(s));
				while (s.id != -1 && s.id != tmp) {
					if (!file.eof()) {
						file.read((char*) &s, sizeof(s));
					} else {
						file.clear();
						file.seekg(0);
					}
				}
				if (s.id != tmp) {
					file.seekp(
							file.tellp()
									- static_cast<std::streamoff>(sizeof(student)));
					file.write((char*) &n, sizeof(n));
					file.close();
				} else {
					cout << "fulll\n";
				}
			}
		}
	}

	void read() {
		ifstream fin;
		fin.open("rec.dat", ios::binary);
		student s;
		fin.read((char*) &s, sizeof(s));
		while (!fin.eof()) {
			s.display();
			fin.read((char*) &s, sizeof(s));
		}
		fin.close();
	}

	void search(int id) {
		int hash = hf(id);
		student s;
		ifstream f;
		f.open("rec.dat", ios::binary);
		if (!f) {
			cout << "err\n";
			return;
		} else {
			f.seekg(hash * sizeof(s));
			f.read((char*) &s, sizeof(s));
			int tmp = s.id;
			if (s.id == id) {
				cout << "rec found\n";
				s.display();
				return;
			} else {
				f.read((char*) &s, sizeof(s));
				while (s.id != id && s.id != tmp) {
					//f.read((char*)&s,sizeof(s));
					if (!f.eof()) {
						f.read((char*) &s, sizeof(s));
					} else {
						f.clear();
						f.seekg(0);
					}
				}
				if (s.id != tmp) {
					cout << "rec found\n";
					s.display();
					return;
				} else {
					cout << "not found";
				}
			}
		}
	}

	void remove(int id) {
		student s;
		student n;
		int hash = hf(id);
		fstream f;
		f.open("rec.dat", ios::binary | ios::in | ios::out);
		if (!f) {
			cout << "err\n";
			return;
		} else {
			f.seekg(hash * sizeof(s));
			f.read((char*) &s, sizeof(s));
			int tmp = s.id;
			if (s.id == id) {
				f.seekp(
						f.tellp()
								- static_cast<std::streamoff>(sizeof(student)));
				f.write((char*) &n, sizeof(n));
				f.close();
			} else {
				f.read((char*) &s, sizeof(s));
				while (s.id != id && s.id != tmp) {
					if (!f.eof()) {
						f.read((char*) &s, sizeof(s));
					} else {
						f.clear();
						f.seekg(0);
					}
				}
				if (s.id != tmp) {
					f.seekp(
							f.tellp()
									- static_cast<std::streamoff>(sizeof(student)));
					f.write((char*) &n, sizeof(n));
					f.close();
				} else {
					cout << "not found\n";
					return;
				}
			}
		}
	}
};

int main() {
	direct f;
	//f.insert();
	f.read();
	cout<<endl;
	f.remove(88);
	f.read();

	return 0;
}
