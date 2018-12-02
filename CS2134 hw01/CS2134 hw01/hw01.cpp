//Matthew Avallone
#include <vector>
#include <iostream>
#include "time.h"
#include "Math.h"
using namespace std;

class timer {
public:
	timer() : start(clock()) {}
	double elapsed() { return (clock() - start) / CLOCKS_PER_SEC; }
	void reset() { start = clock(); }
private:
	double start;
};

/**
* Cubic maximum contiguous subsequence sum algorithm.
*/
int maxSubSum1(const vector<int> & a)
{
	int maxSum = 0;

	for (size_t i = 0; i < a.size(); ++i)
		for (size_t j = i; j < a.size(); ++j)
		{
			int thisSum = 0;

			for (size_t k = i; k <= j; ++k)
				thisSum += a[k];

			if (thisSum > maxSum)
				maxSum = thisSum;
		}

	return maxSum;
}


/**
* Quadratic maximum contiguous subsequence sum algorithm.
*/
int maxSubSum2(const vector<int> & a)
{
	int maxSum = 0;

	for (size_t i = 0; i < a.size(); ++i)
	{
		int thisSum = 0;
		for (size_t j = i; j < a.size(); ++j)
		{
			thisSum += a[j];

			if (thisSum > maxSum)
				maxSum = thisSum;
		}
	}

	return maxSum;
}

/**
* Linear-time maximum contiguous subsequence sum algorithm.
*/
int maxSubSum4(const vector<int> & a)
{
	int maxSum = 0, thisSum = 0;

	for (size_t j = 0; j < a.size(); ++j)
	{
		thisSum += a[j];

		if (thisSum > maxSum)
			maxSum = thisSum;
		else if (thisSum < 0)
			thisSum = 0;
	}

	return maxSum;
}


void funcA(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		++sum;
}
void funcB(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; ++j)
		++sum;
}
void funcC(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) for (int j = 0; j < i; ++j)
		++sum;
}

void funcD(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				++sum;

}


int main() {

	timer t; 
	double nuClicks;
	vector<int> items;
	cout.setf(ios::fixed, ios::floatfield); 
	cout.precision(12);
	cout << CLOCKS_PER_SEC << endl << endl;

//Question 1
	for (size_t i = 0; i < pow(2, 7); i++) { //n = 2^7 (I implemented the Math library to save writing)
		int x = (rand() % 2001) - 1000;
		items.push_back(x);
	}

	cout << "n = 2^7" << endl;
	t.reset(); 
	maxSubSum1( items );
	nuClicks = t.elapsed();
	cout << "Cubic: " << nuClicks << endl;

	t.reset();
	maxSubSum2(items);
	nuClicks = t.elapsed();
	cout << "Quadratic: " << nuClicks << endl;

	t.reset();
	maxSubSum4(items);
	nuClicks = t.elapsed();
	cout << "Linear: " << nuClicks << endl;
	
	items.clear();
	cout << "=======================" << endl;

	for (size_t i = 0; i < pow(2, 8); i++) { //n = 2^8 (I implemented the Math library to save writing)
		int x = (rand() % 2001) - 1000;
		items.push_back(x);
	}

	cout << "n = 2^8" << endl;
	t.reset();
	maxSubSum1(items);
	nuClicks = t.elapsed();
	cout << "Cubic: " << nuClicks << endl;

	t.reset();
	maxSubSum2(items);
	nuClicks = t.elapsed();
	cout << "Quadratic: " << nuClicks << endl;

	t.reset();
	maxSubSum4(items);
	nuClicks = t.elapsed();
	cout << "Linear: " << nuClicks << endl;

	items.clear();
	cout << "=======================" << endl;

	for (size_t i = 0; i < pow(2, 9); i++) { //n = 2^9 (I implemented the Math library to save writing)
		int x = (rand() % 2001) - 1000;
		items.push_back(x);
	}

	cout << "n = 2^9" << endl;
	t.reset();
	maxSubSum1(items);
	nuClicks = t.elapsed();
	cout << "Cubic: " << nuClicks << endl;

	t.reset();
	maxSubSum2(items);
	nuClicks = t.elapsed();
	cout << "Quadratic: " << nuClicks << endl;

	t.reset();
	maxSubSum4(items);
	nuClicks = t.elapsed();
	cout << "Linear: " << nuClicks << endl;

	items.clear();
	cout << "=====================" << endl;

	for (size_t i = 0; i < pow(2, 10); i++) { //n = 2^10 (I implemented the Math library to save writing)
		int x = (rand() % 2001) - 1000;
		items.push_back(x);
	}

	cout << "n = 2^10" << endl;
	t.reset();
	maxSubSum1(items);
	nuClicks = t.elapsed();
	cout << "Cubic: " << nuClicks << endl;

	t.reset();
	maxSubSum2(items);
	nuClicks = t.elapsed();
	cout << "Quadratic: " << nuClicks << endl;

	t.reset();
	maxSubSum4(items);
	nuClicks = t.elapsed();
	cout << "Linear: " << nuClicks << endl;

	items.clear();
	cout << "=====================" << endl;

	for (size_t i = 0; i < pow(2, 11); i++) { //n = 2^11 (I implemented the Math library to save writing)
		int x = (rand() % 2001) - 1000;
		items.push_back(x);
	}

	cout << "n = 2^11" << endl;
	t.reset();
	maxSubSum1(items);
	nuClicks = t.elapsed();
	cout << "Cubic: " << nuClicks << endl;

	t.reset();
	maxSubSum2(items);
	nuClicks = t.elapsed();
	cout << "Quadratic: " << nuClicks << endl;

	t.reset();
	maxSubSum4(items);
	nuClicks = t.elapsed();
	cout << "Linear: " << nuClicks << endl;

	items.clear();
	cout << "=====================" << endl;

	for (size_t i = 0; i < pow(2, 12); i++) { //n = 2^12 (I implemented the Math library to save writing)
		int x = (rand() % 2001) - 1000;
		items.push_back(x);
	}

	cout << "n = 2^12" << endl;
	t.reset();
	maxSubSum1(items);
	nuClicks = t.elapsed();
	cout << "Cubic: " << nuClicks << endl;

	t.reset();
	maxSubSum2(items);
	nuClicks = t.elapsed();
	cout << "Quadratic: " << nuClicks << endl;

	t.reset();
	maxSubSum4(items);
	nuClicks = t.elapsed();
	cout << "Linear: " << nuClicks << endl;

	items.clear();

//============================
//Question 2
	cout << "===================" << endl;

	for (int i = 256; i <= 4096; i *= 2) {
		cout << "n = " << i << endl;

		t.reset();
		funcA(i); //2A
		nuClicks = t.elapsed();
		cout << "2A: " << nuClicks << endl;

		t.reset(); 
		funcB(i); //2B
		nuClicks = t.elapsed();
		cout << "2B: " << nuClicks << endl;

		t.reset(); 
		funcC(i); //2C
		nuClicks = t.elapsed();
		cout << "2C: " << nuClicks << endl;

		t.reset(); 
		funcD(i); //2D
		nuClicks = t.elapsed();
		cout << "2D: " << nuClicks << endl;
	}

}