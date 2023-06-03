#include <iostream>
using namespace std;

class data{
	string name;
	int no;
	public:
	data(){
		name = "";
		no = -1;
	}
	data(int n,string name){
		no = n;
		name = name;
	}
	friend class hashTable;
};

class hashTable{
	data *ht;
	int size;
	public:
	hashTable(){
		ht = nullptr;
		size = 0;
	}
	hashTable(int s){
		size = s;
		ht = new data[size];
	}
	int hashFunction(int key){
		return key%size;
	}

	void display()
	{
		cout<<"Hashtable content "<<endl;
		for(int i=0;i<size;i++)
		{
			cout << "[ "<<i<<" ] -> " <<ht[i].no << "\t" <<ht[i].name <<endl;
		}
	}

	void insert_without_rep(int telno , string name)
	{
		int hashIndex = hashFunction(telno);
		while(ht[hashIndex].no != -1){
			if(ht[hashIndex].no == telno){
				return;
			}
			hashIndex = (hashIndex+1)%size;
		}
		ht[hashIndex].no = telno;
		ht[hashIndex].name = name;
		cout<<"inserted at : "<<hashIndex<<endl;
	}

	void insert_with_rep(int telno, string name)
	{
		int temp,curr;
		string tempN;
		int hashIndex = hashFunction(telno);

		if(ht[hashIndex].no == -1){
			ht[hashIndex].no = telno;
			ht[hashIndex].name = name;
		}else{
			temp = ht[hashIndex].no;
			tempN = ht[hashIndex].name;
			curr = hashFunction(temp);
;
			if(curr == hashIndex){
				hashIndex = (hashIndex+1)%size;
				insert_without_rep(telno , name);
			}else{
				cout<<temp <<":"<<tempN<<endl;
				ht[hashIndex].no = telno;
				ht[hashIndex].name = name;
				telno = temp;
				insert_without_rep(telno,tempN);
			}
			
		}
	}
};


int main()
{
	hashTable h(10);
	h.insert_with_rep(12,"abc");
	h.insert_with_rep(22,"exy");
	h.insert_with_rep(33,"x");
	h.insert_with_rep(44,"44");
	h.display();
	
	return 0;
}
