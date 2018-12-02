//Matthew Avallone
//HW02

#include <vector>
#include <iostream>
using namespace std;

class IntArray {
public:
	//constructor
	explicit IntArray(int n = 0) : size(n), array(new int[n]) { cout << "Constructor" << endl; } 

	//copy constructor
	IntArray(const IntArray& rhs) : size(rhs.size), array(new int[rhs.size]) {
		for (int i = 0; i < size; i++) {
			array[i] = rhs.array[i];
		}
		cout << "Copy Constructor" << endl;
	}

	//move copy constructor
	IntArray(IntArray&& rhs) : array(rhs.array), size(rhs.size) {
		rhs.array = nullptr;
		cout << "Move Copy Constructor" << endl;
	}
	
	//destructor
	~IntArray() {
		delete[] array;
		cout << "Destructor" << endl;
	}

	//move assignment operator
	IntArray& operator=(IntArray&& rhs) {
		//int* temp = array;
		//array = rhs.array;
		//rhs.array = temp;
		std::swap(array, rhs.array);
		size = rhs.size;
		cout << "Move Assignment Operator" << endl;
		return *this;
	}

private: 
	int * array; 
	int size;
};

int main() {
	IntArray a(4);
	IntArray b(a);
	IntArray c = IntArray(2); //does not call correct constructor (not sure why)
	a = IntArray(3);
}

