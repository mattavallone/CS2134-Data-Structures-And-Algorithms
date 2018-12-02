//Matthew Avallone
//Vector Class HW

#include <iostream>
#include <string>
#include <iterator>
using namespace std;

class Student {
	friend ostream& operator<<(ostream& os, const Student& rhs);
public:
	Student(const string& name, double gpa) : name(name), gpa(gpa){}

	double getGPA() const { return gpa; }
	string getName() const { return name;  }
private:
	string name;
	double gpa;
};

ostream& operator<<(ostream& os, const Student& rhs) {
	os << rhs.name << " " << rhs.gpa << endl;
	return os;
}

template <typename Object>
class Vector
{
public:
	explicit Vector(int initSize = 0): theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
	{
		objects = new Object[theCapacity];
	}

	Vector(const Vector & rhs): theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
	{
		objects = new Object[theCapacity];
		for (int k = 0; k < theSize; ++k)
			objects[k] = rhs.objects[k];
	}

	Vector & operator= (const Vector & rhs)
	{
		Vector copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	~Vector()
	{
		delete[] objects;
	}

	Vector(Vector && rhs): theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
	{
		rhs.objects = nullptr;
		rhs.theSize = 0;
		rhs.theCapacity = 0;
	}

	Vector & operator= (Vector && rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(objects, rhs.objects);

		return *this;
	}

	bool empty() const
	{
		return size() == 0;
	}
	int size() const
	{
		return theSize;
	}
	int capacity() const
	{
		return theCapacity;
	}

	Object & operator[](int index)
	{
		return objects[index];
	}

	const Object & operator[](int index) const
	{
		return objects[index];
	}

	void resize(int newSize)
	{
		if (newSize > theCapacity)
			reserve(newSize * 2);
		theSize = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
			return;

		Object *newArray = new Object[newCapacity];
		for (int k = 0; k < theSize; ++k)
			newArray[k] = std::move(objects[k]);

		theCapacity = newCapacity;
		std::swap(objects, newArray);
		delete[] newArray;
	}

	// Stacky stuff
	void push_back(const Object & x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = x;
	}
	// Stacky stuff
	void push_back(Object && x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = std::move(x);
	}


	// Iterator stuff: not bounds checked
	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator begin()
	{
		return &objects[0];
	}
	const_iterator begin() const
	{
		return &objects[0];
	}
	iterator end()
	{
		return &objects[size()];
	}
	const_iterator end() const
	{
		return &objects[size()];
	}

	//erases the element that vItr points to and returns next element
	//vItr must exist
	iterator erase(iterator vItr) { 
		iterator start = begin(); 
		while (start != end()) {
			if (start == vItr) {
				iterator copy = start + 1;
				delete start;
				--theSize;
				return copy;
			}
			else if (start == nullptr) //cehcks if the value at start does not exist before the end is reached
				return vItr;

			start++;
		}
		return ++start;
	}

	static const int SPARE_CAPACITY = 2;
	
private:
	int theSize;
	int theCapacity;
	Object * objects;
};

template<class Itr>
class check {
public:
	bool operator()(const Itr val) {
		return val;
	}
};

template< class Itr, class UnaryPred >
void print_if(Itr start, Itr end, UnaryPred pred) {
	for (start; start != end; start++) {
		if (pred(start))
			cout << *(*start) << endl;
	}
}

class GPA_in_range {
public:
	GPA_in_range(double l, double h) : low(l), high(h){}
	bool gpaCheck(const Student& s) const {
		return low <= s.getGPA() && high >= s.getGPA();
	}
private:
	double low;
	double high;
};


int main() {
	Vector<Student*> vec;
	vec.push_back(new Student("Jon", 3.1));
	vec.push_back(new Student("Matt", 4.0));
	vec.push_back(new Student("Jordan", 2.2));
	GPA_in_range range(3.0, 4.0);
	for (int i = 0; i < vec.size(); i++) { //testing to see if student's GPA is in range [3.0,4.0]
		cout << boolalpha << vec[i]->getName() << " " << range.gpaCheck(*vec[i]) << endl;
	}
	cout<< endl << "print_if(vec.begin(), vec.end(), pred(vec.begin()));" << endl;
	print_if(vec.begin(), vec.end(), check); //tests the print_If statement and pred functor

	Vector<Student*>::iterator v = vec.begin(); //tests the erase() method
	vec.erase(v); //causes RUNTIME error, infinite loop? not sure why though

}