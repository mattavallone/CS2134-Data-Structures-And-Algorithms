//Matthew Avallone
//hw05

#include <iostream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>
using namespace std;

template<class RandItr>
void mergeSort(RandItr temp, RandItr start, RandItr stop) {
	if (start != stop-1) {
		int center = (stop - start) / 2;
		mergeSort(temp, start, stop - center);
		mergeSort(temp, stop - center+1, stop);
		merge(start, stop-center, stop-center+1, stop, temp);
	}
}

template <class RandItr, class Object> 
void mergeSort(RandItr start, RandItr end) {
	int sz = end - start; 
	vector<Object> tmp(sz);
	mergeSort<vector<Object>::iterator>(tmp.begin(), start, end);
}

// #2
class Student {
public:
	Student(const string& who, double grade) : name(who), gpa(grade) {}
	string getName() const { return name; }
	double getGPA() const { return gpa; }
private:
	string name;
	double gpa;
};

class meFirst {
public:
	meFirst(const string& me) : me(me){}
	bool operator()(const Student& lhs, const Student& rhs) {
		if (rhs.getName() == me)
			return false;
		else if (lhs.getName() < rhs.getName())
			return true;
		else
			return false;
	}
private:
	string me;
};

//3
class boolObj { //boolean object class
public:
	boolObj(bool value) : val(value) {}
	bool getValue() const {
		return val;
	}
private:
	bool val;
};

class check { //functor checking the boolean value of each boolObj
public:
	bool operator()(const boolObj& rhs) {
		if (rhs.getValue())
			return true;
		else
			return false;
	}
};

template<class Comparable>
vector<boolObj>::iterator sortBool(vector<boolObj>::iterator start, vector<boolObj>::iterator stop, Comparable boolCheck, vector<boolObj> boolVec) {
	if (start == stop - 1) return start; //checks if only one item is in vector
	int center = (stop - start) / 2; //finds the midpoint neeeded for divide and conquer approach
	
	if (!boolCheck(*start)) { //checks first if the value is false
		boolVec.push_back(boolObj(false));
	}
	sortBool(start, stop - center, boolCheck, boolVec);
	sortBool(stop - center, stop, boolCheck, boolVec);
	if (boolCheck(*start)) { //after going through both halves for false boolObj, then checks for true values
		boolVec.push_back(boolObj(true));
	}

	return boolVec.begin(); //returns the first iterator to the sorted bool vector
}

void printVec(vector<boolObj>::iterator start, int size) { //prints out the items in the boolVector
	for (int i = 0; i <= size; i++) {
		cout << boolalpha << start->getValue() << " ";
	}
	cout << noboolalpha << endl;
}

int main() {
	vector<int> vec = { 1,4,7,5,3,2 };
	for (int num : vec)
		cout << num;
	cout << endl;
	//mergeSort<vector<int>::iterator, int>(vec.begin(), vec.end());
	for (int num : vec)
		cout << num;
	cout << endl;

	//2
	vector<Student> v;
	v.push_back(Student("yo", 3));
	v.push_back(Student("whats", 4));
	v.push_back(Student("good", 2));
	sort(v.begin(), v.end(), meFirst("pop"));

	//3
	vector<boolObj> vecB;
	vecB.push_back(boolObj(false));
	vecB.push_back(boolObj(true));
	vecB.push_back(boolObj(false));
	vecB.push_back(boolObj(true));
	check newCheck;
	vector<boolObj> temp;
	vector<boolObj>::iterator sortedVec = sortBool(vecB.begin(), vecB.end(), newCheck, temp);
	printVec(sortedVec, vecB.size());

}