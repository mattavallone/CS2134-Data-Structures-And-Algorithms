//Matthew Avallone

#include <iostream>
#include <cmath>
using namespace std;

int sumDigits(int x) {
	return (abs(x) < 10) ? abs(x) : sumDigits(abs(x) / 10) + (abs(x) % 10);
}

//divide and conquer find the largest value in a vector

int main() {
	//terinary operator
	int a = 5;
	int b = (a % 2 == 0) ? 10 : 20;
	//cout << b << endl;

	//recursion
	cout << sumDigits(2) << endl;
	cout << sumDigits(123) << endl;
	cout << sumDigits(90) << endl;
	cout << sumDigits(-123) << endl;
}