//Matthew Avallone
//hw10

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


//1
template<class Comparable> //object must have overloaded < operator
void print_kth_largest(vector<Comparable>& a, int k) {
	priority_queue<Comparable> pq(a.begin(), a.end());
	int repeatCounter = 0;
	if (pq.empty()) { //checks in case container was empty
		cout << "There is no " << k << " largest element" << endl;
		return;
	}
	
	for(int i = 1; i != k; i++) {
		if (i > a.size() - repeatCounter) {
			cout << k << " is out of range" << endl;
			return;
		}

		Comparable prev = pq.top();
		pq.pop();
		while (!pq.empty() && prev == pq.top()) {//if multiple elements have the same value
			pq.pop();
			++repeatCounter;
		}	
	}
		Comparable kVal = pq.top();
		cout << k << " largest = ";
		while (!pq.empty() && pq.top() == kVal) { //if multiple elements have the same value
			cout << pq.top() << " ";
			pq.pop();
		}
		cout << endl;
}

namespace k {
	int main() {
		//1
		vector<int> vec(10);
		for (size_t i = 0; i < vec.size(); i++) {
			vec[i] = (rand() % 100); //filled with random numbers between 0 and 99
		}
		vec.push_back(67);
		vec.push_back(67);
		for (int x : vec)
			cout << x << " ";
		cout << endl;

		print_kth_largest(vec, 3); //case when multiple equal values
		print_kth_largest(vec, 5); //normal case
		print_kth_largest(vec, 8); //normal case
		print_kth_largest(vec, 9);
		print_kth_largest(vec, 10); //smallest value
		print_kth_largest(vec, 12); //when k value = size of container
		print_kth_largest(vec, 13); //when k value goes past the size of container
		//print_kth_largest(vec, 11);
		return 0;
	}
	
}
