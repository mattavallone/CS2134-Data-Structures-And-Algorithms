//Matthew Avallone
//hw06

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

//1
template <typename Object>
class List
{
private:

	struct Node
	{
		Object  data;
		Node   *next;

		Node(const Object & d = Object{}, Node * n = nullptr)
			: data{ d }, next{ n } { }

		Node(Object && d, Node * n = nullptr)
			: data{ std::move(d) }, next{ n } { }

	};

public:
	class iterator
	{
	public:

		iterator() : current(nullptr) { }

		Object & operator* (){
			return current->data;
		}

		const Object & operator* () const {
			return  current->data;
		}

		iterator & operator++ (){
			this->current = this->current->next;
			return *this;
		}

		iterator operator++ (int){
			iterator old = *this;
			++(*this);
			return old;
		}

		bool operator== (const iterator & rhs) const {
			return current == rhs.current;
		}

		bool operator!= (const iterator & rhs) const {
			return !(*this == rhs);
		}

	private:
		Node * current;

		iterator(Node *p) : current(p){ }

		friend class List<Object>;
	};

public:
	List(){
		header = new Node;
	}

	~List(){
		clear();
		delete header;
	}

	List(const List & rhs) : header(new Node) {
		Node* copyHead = rhs.header->next;
		iterator head = header;
		while (copyHead) {
			insert_after(head, copyHead->data);
			copyHead = copyHead->next;
			++head;
		}
	}

	List & operator= (const List & rhs){
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	List(List && rhs) : header(new Node){
		header->next = rhs.header->next;
		rhs.header->next = nullptr;
	}

	List & operator= (List && rhs){
		std::swap(header, rhs.header);
		return *this;
	}

	iterator begin() const{
		return iterator(header->next);
	}

iterator end() const {
	return iterator(nullptr);
}

iterator before_begin() const {
	return iterator(header);
}

bool empty() const {
	return header->next == nullptr;
}

void clear() {
	while (!empty())
		pop_front();
}

void pop_front() {
	erase_after(before_begin());
}

iterator insert_after(iterator itr, const Object & x) {
	Node *p = itr.current;
	p->next = new Node{ x, p->next };

	return iterator(p->next);
}

void remove(const Object & x) {
	Node * prev = header;

	while (prev->next != nullptr) {
		if (prev->next->data == x)
			erase_after(iterator(prev));
		else
			prev = prev->next;
	}
}

iterator erase_after(iterator itr) {
	Node *p = itr.current;
	Node *oldNode = p->next;

	p->next = oldNode->next;
	delete oldNode;

	return iterator(p->next);
}

Object& back() {
	Node* copy = header;
	while (copy->next) {
		copy = copy->next;
	}
	return copy->data;
}

const Object & back() const {
	Node* copy = header;
	while (copy->next) {
		copy = copy->next;
	}
	return copy->data;
}

Object & front() {
	return header->next->data;
}

const Object & front() const {
	return header->next->data;
}

void sort() {
	if (empty()) return;
		Node* copy = header->next;
		while (copy->next) {
			if (copy->data > copy->next->data) {
				swap(copy->data, copy->next->data);
			}
			copy = copy->next;
		}
}

void merge(List & alist) {
	sort();
	alist.sort();
	
	iterator start1 = begin();
	iterator start2 = alist.begin();
	iterator stop1 = end();
	iterator stop2 = alist.end();


	while (true) {
		if (*start1 == back()) {
			while (start2 != stop2) {
				insert_after(start1, *start2);
				++start2;
			}
			return;
		}
		
		if (*start2 <= *start1) {
			insert_after(start1, *start2);
			++start2;
		}
		else {
			++start1;
		}
	}
}

void remove_adjacent_duplicates() {
	if (!empty() && header->next->next) {
		Node* copy = header->next;
		iterator curr = begin();
		while (copy->next) {
			if (copy->next->data == copy->data) {
				erase_after(curr);
			}
			copy = copy->next;
			++curr;
		}
	}
}

template<class Predicate>
void remove_if(Predicate pred) {
	Node* copy = header;
	iterator curr = before_begin();
	while (copy->next) {
		if (pred(copy->next->data)) {
			erase_after(curr);
		}
		copy = copy->next;
		++curr;
	}
}

iterator insert_after(iterator itr, Object && x) {
	Node *p = itr.current;
	p->next = new Node{ std::move(x), p->next };
	return iterator(p->next);
}

private:
	Node *header;
};

template<class iter>
void printList(iter start, iter stop) {
	while(start != stop){
		cout << *start << endl;
		++start;
	}
}

//2
template<class Object>
class Queue {
public:

	Queue(const Object& x) : begin(new Node(x)) {}
	Queue(const Object&& x) : begin(new Node(x)) {}

	Object& front() {
		return begin->data;
	}

	Object& back(){
		return end->data;
	}

	bool empty() {
		return begin == nullptr;
	}

	void enqueue(const Object& obj) {
		end->next = new Node(obj, end->next);
	}

	void enqueue(const Object&& obj) {
		//begin = new Node(move(obj), begin);
		//end = end->next;
		end->next = new Node(move(obj), end->next);
	}

	void dequeue() {
		Node *p = begin->next;
		delete begin;
		begin = p;
	}
	
private:

	struct Node
	{
		Object  data;
		Node   *next;

		Node(const Object & d = Object(), Node * n = nullptr)
			: data{ d }, next{ n } { }

		Node(Object && d, Node * n = nullptr)
			: data{ std::move(d) }, next{ n } { }

	};

	Node* begin;
	Node* end = begin;
	
};

class isEven {
public:
	bool operator()(int num){
		return num % 2 == 0;
	}
};

int main() {
	List<int> numbers;
	List<int>::iterator current = numbers.before_begin();
	for (int i = 1; i <= 10; i++) {
		numbers.insert_after(current, i);
		current++;
	}
	
	cout << "numbers.front() " << numbers.front() << endl;
	
	cout << "List(const List & rhs) " << endl;
	List<int> numbers2 = numbers;
	printList<List<int>::iterator>(numbers2.begin(), numbers2.end());

	cout << "merge(List & alist) " << endl;
	numbers.merge(numbers2);
	printList(numbers.begin(), numbers.end());

	cout << "insert_after(numbers.begin(), 3) " << endl;
	numbers.insert_after(numbers.begin(), 3);
	printList(numbers.begin(), numbers.end());

	cout << "void remove_if(Predicate pred) " << endl;
	//isEven check;
	//numbers.remove_if(check);
	printList(numbers.begin(), numbers.end());

	cout << "void remove_adjacent_duplicates() " << endl;
	numbers.remove_adjacent_duplicates();
	printList(numbers.begin(), numbers.end());

	/////////////////////////////////
	cout << endl << "==========================" << endl;

	Queue<char> letters('a');
	letters.enqueue('b');
	letters.enqueue('c');
	letters.enqueue('d');
	cout << "Testing enqueue() and front() " << letters.front() << endl;

	letters.dequeue();
	cout << "dequeue() " << letters.front() << endl;

	cout << "back() " << letters.back() << endl;

	cout << boolalpha << "empty() " << letters.empty() << noboolalpha << endl;

}