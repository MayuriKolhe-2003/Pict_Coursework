#include <iostream>
#include <string.h>
#define size 10

using namespace std;

class data {
	string name;
	int telno;
public:
	data() {
		name = " ";
		telno = -1;
	}
	friend class hashTable;
};

class hashTable {
	data *ht;
public:
	hashTable() {
		ht = new data[size];
	}
	int hashFunction(int key) {
		/*int i = 1, unit = 0;
		 int sum = 0;
		 while (key > 0) {
		 unit = key % 10;
		 sum = sum + (unit * i * i);
		 key = key / 10;
		 i++;
		 }*/
		return (key % size);
	}
	void display() {
		cout << "----Hash Table---\n";
		for (int i = 0; i < size; i++) {
			cout << "[" << i << "]\t" << ht[i].name << "\t" << ht[i].telno
					<< "\n";
		}
	}
	void insert_without_replacement(int telno, string name) {
		int hashIndex;
		hashIndex = hashFunction(telno);

		while (ht[hashIndex].telno != -1) {
			if (ht[hashIndex].telno == telno) {
//cout << "Duplicate\n";
				return;
			}
			hashIndex = (hashIndex + 1) % size;

		}
		ht[hashIndex].telno = telno;
		ht[hashIndex].name = name;
	}
	void insert_with_replacement(int telno, string name) {
		int hashIndex, curr, temp;
		hashIndex = hashFunction(telno);

//index empty
		if (ht[hashIndex].telno == -1) {
			ht[hashIndex].telno = telno;
			ht[hashIndex].name = name;
		} else if (ht[hashIndex].telno != -1) {
			temp = ht[hashIndex].telno;
			curr = hashFunction(temp);
			if (curr == hashIndex) {
				hashIndex = (hashIndex + 1) % size;
			} else {
				ht[hashIndex].telno = telno;
				ht[hashIndex].name = name;
				telno = temp;
			}
		}

		while (ht[hashIndex].telno != -1) {
			if (ht[hashIndex].telno == telno) {
				cout << "Duplicate\n";
				return;
			}
			hashIndex = (hashIndex + 1) % size;
		}

		ht[hashIndex].telno = telno;
		ht[hashIndex].name = name;

	}

	void search(int telno) {
		int hashIndex;
		int cmp = 1; //number of cmparisons
		hashIndex = hashFunction(telno);

//if stored at hashIndex itself
		if (ht[hashIndex].telno == telno) {
			cout << "Element found at :" << hashIndex << " found in :" << cmp
					<< " comparisons." << endl;
			return;
		}

		while (cmp != size) {
			cmp++;
			hashIndex = (hashIndex + 1) % size;
			if (ht[hashIndex].telno == telno) {
				cout << "Element found at :" << hashIndex << " found in :"
						<< cmp << " comparisons." << endl;
				return;
			}
		}
		cout << "Not found \n";
	}

};

using namespace std;

int main() {
	hashTable h1;
	h1.insert_with_replacement(11, "abc");
	h1.insert_with_replacement(1, "vbh");
	h1.insert_with_replacement(21, "iou");
	h1.insert_with_replacement(3, "iou");

	h1.display();

//h1.search();

	return 0;
}
