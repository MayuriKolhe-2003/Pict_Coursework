#include <iostream>
using namespace std;

class heap_array {
	int *heap;
	int size;
	int cnt = 0;
public:
	heap_array() {
		size = 0;
		heap = NULL;
	}
	heap_array(int n) {
		size = n;
		heap = new int[size];
	}
	void insert_heap() {
		cout << "----- Enter Heap elements ----" << endl;
		for (int i = 0; i < size; i++) {
			cout << i << " : ";
			cin >> heap[i];
		}
		cout << endl;
	}
	void print_heap() {
		cout << "----- HEAP CONTENTS ----" << endl;
		for (int i = 0; i < size; i++) {
			cout << heap[i] << "\t";
		}
		cout << endl;
	}

// To heapify the subtree rooted with node i and tree of size n
	void heapify(int n, int i) {
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

// If left child is larger than root
		if (left < n && heap[left] > heap[largest]) {
			largest = left;
		}
// If right child is larger than root
		if (right < n && heap[right] > heap[largest]) {
			largest = right;
		}

// If largest is not root
		if (largest != i) {
			int temp = heap[largest];
			heap[largest] = heap[i];
			heap[i] = temp;
// Recursively heapify the affected sub-tree
			heapify(n, largest);
		}

	}
	void heap_sort() {
// Build heap (rearrange array)
		for (int i = size / 2 - 1; i >= 0; i--)
					heapify(size, i);

// One by one extract an element from heap
		for (int i = size - 1; i >= 0; i--) {
// Move current root to end
			int temp = heap[0];
			heap[0] = heap[i];
			heap[i] = temp;

// call max heapify on the reduced heap
			heapify(i, 0);
		}
	}

	void sort() {
//heapify algorithm
// the loop must go reverse you will get after analyzing manually
// (i=n/2 -1) because other nodes/ ele's are leaf nodes
// (i=n/2 -1) for 0 based indexing
// (i=n/2)  for 1 based indexing
		for (int i = size / 2 - 1; i >= 0; i--) {
			heapify(size, i);
		}

	}
};

int main() {
	heap_array obj(6);
	obj.insert_heap();
	cout << "Before : " << endl;
	obj.print_heap();

	obj.sort();
	cout << "After : " << endl;
	obj.print_heap();

	obj.heap_sort();
	cout << "After heap sort : " << endl;
	obj.print_heap();
	return 0;
}
