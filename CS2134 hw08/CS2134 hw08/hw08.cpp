//Matthew Avallone
//hw08

#include <map>
#include<vector>
#include <string>
#include <iostream>
#include<fstream>
#include <queue>
using namespace std;

//1
int wordValue(string& word, const vector<int>& values) {
	int value = 0;
	for (size_t i = 0; i < word.size(); i++) {
		word[i] = tolower(word[i]); //converts the letter to lower case
		int pos = word.at(i)-97; //finds the correct index for the letter
		value += values[pos]; //adds the letter point value to the total word value
	}
	return value;
}


//////////////////////////////////////////////


//2
template<class Comparable>
struct BinaryNode
{
	Comparable element;
	BinaryNode *left;
	BinaryNode *right;

	BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
		: element{ theElement }, left{ lt }, right{ rt } { }

	BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
		: element{ std::move(theElement) }, left{ lt }, right{ rt } { }
};


// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// bool contains( x )     --> Return true if x is present
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************


template <typename Comparable>
class BinarySearchTree
{
public:
	typedef BinaryNode<Comparable> Node;

	BinarySearchTree() : root{ nullptr }
	{
	}

	/**
	* Copy constructor
	*/
	BinarySearchTree(const BinarySearchTree & rhs) : root{ nullptr }
	{
		root = clone(rhs.root);
	}

	/**
	* Move constructor
	*/
	BinarySearchTree(BinarySearchTree && rhs) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	/**
	* Destructor for the tree
	*/
	~BinarySearchTree()
	{
		makeEmpty();
	}

	/**
	* Copy assignment
	*/
	BinarySearchTree & operator=(const BinarySearchTree & rhs)
	{
		BinarySearchTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	/**
	* Move assignment
	*/
	BinarySearchTree & operator=(BinarySearchTree && rhs)
	{
		std::swap(root, rhs.root);
		return *this;
	}


	/**
	* Returns true if x is found in the tree.
	*/


	bool contains(const Comparable & x) const
	{
		return contains(x, root); //see private methods
	}

	/**
	* Test if the tree is logically empty.
	* Return true if empty, false otherwise.
	*/
	bool isEmpty() const
	{
		return root == nullptr;
	}

	/**
	* Make the tree logically empty.
	*/
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(const Comparable & x)
	{
		insert(x, root);
	}

	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(Comparable && x)
	{
		insert(std::move(x), root);
	}

	//////////////
	//2
	void printRange(const Comparable& low, const Comparable& high) const {
		printRange(low, high, root); //see private methods
	}
	void printStringy() const { //prints a stingy BST
		Node* curr = root;
		while (curr) {
			cout << curr->element;
			curr = curr->right;
		}
		cout << endl;
	}

	void stringy() {
		stringy(root); //see private methods
		sortStringy();
	}

	double average_node_depth(int size) const { //returns a rounded double because it is a more accurate average than integer division
		return std::round((double)average_node_depth(root, 0) / (double)size); //see private methods
	}
	

	/////////////////////////////////

	//3
	void listNodes() { 
		Node* curr = root;
		queue<Node*> nodes;
		nodes.push(curr);

		Node* l = curr->left;
		Node* r = curr->right;

		while (l && !r) {
			nodes.push(l);
			Node* temp = l->right;
			l = l->left;
			r = temp;
		}
		while (r && !l) {
			nodes.push(r);
			Node* temp = r->left;
			r = r->right;
			l = temp;
		}

		while (l && r) { 
				nodes.push(l);
				nodes.push(r);
				if (l->left)
					nodes.push(l->left);

				if (l->right)
					l = l->right;
				else {
					l = l->left;
				}
				if (r->right)
					nodes.push(r->right);
				if (r->left)
					r = r->left;
				else {
					r = r->right;
				}
		} //double counting of some nodes will be handled in the following code

		cout << nodes.front()->element;
		Comparable prev = nodes.front()->element; //this is to make sure prev element wasn't a duplicate
		nodes.pop();
		while (!nodes.empty()) {
			if (nodes.front()->element != prev) { //checks element with previous outputed element
				cout << nodes.front()->element;
			prev = nodes.front()->element;
			}
			nodes.pop();
		}
		cout << endl;
	}

private:

	BinaryNode<Comparable> *root;

	/**
	* Internal method to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(const Comparable & x, Node * & t)
	{
		if (t == nullptr)
			t = new Node{ x, nullptr, nullptr };
		else if (x < t->element)
			insert(x, t->left);
		else if (t->element < x)
			insert(x, t->right);
		else
			;  // Duplicate; do nothing
	}

	/**
	* Internal method to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(Comparable && x, Node * & t)
	{
		if (t == nullptr)
			t = new Node{ std::move(x), nullptr, nullptr };
		else if (x < t->element)
			insert(std::move(x), t->left);
		else if (t->element < x)
			insert(std::move(x), t->right);
		else
			;  // Duplicate; do nothing

	}

	/**
	* Internal method to make subtree empty.
	*/
	void makeEmpty(Node * & t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}


	/**
	* Internal method to clone subtree.
	*/
	Node * clone(Node *t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new Node{ t->element, clone(t->left), clone(t->right) };
	}

	bool contains(const Comparable& x, Node* root) const {
		if (!root) return false;
		if (root->element == x) return true;
		else if (root->element < x)
			return contains(x, root->right);
		else
			return contains(x, root->left);
	}

	void printRange(const Comparable& low, const Comparable& high, const Node* curr) const {
		if (!curr) return;
		else if (curr->element < low) { //if current element is too low
			printRange(low, high, curr->right);
		}
		else if (high < curr->element) { //if current element is too high
			printRange(low, high, curr->left);
		}
		else {
			cout << curr->element;
			printRange(low, high, curr->left);
			printRange(low, high, curr->right);
		}
	}

	Node* findMin(Node* t) const { //finds the minimum node in a binary search tree
		if (!t) return nullptr;
		while (t->left)
			t = t->left;
		return t;
	//	//////////////////////////////////////
	//	//Node* min = curr;
	//	//while (curr) {
	//	//	if (curr->element < min->element) //checks if current node element is the smallest element
	//	//		min = curr;
	//	//	if (curr->right && curr->right->element < curr->element)
	//	//		curr = curr->right;
	//	//	else
	//	//		curr = curr->left;
	//	//}
	//	//return min;
	//	//This was slightly modified version of findMinStringy() which found the lowest node based on actual element value
	}
	Node* findMinStringy(Node* curr) const { //finds the minimum node in an unbalanced stringy search tree
		Node* min = curr;
		while (curr) {
			if (curr->element < min->element) //checks if current node element is the smallest element
				min = curr;
			curr = curr->right;
		}
		return min;
	}
	void sortStringy() { //sorts an unordered stringy BST
		Node* copy = root;
		while (copy) {
			std::swap(copy->element, findMinStringy(copy)->element); //swaps the elements
			copy = copy->right;
		}
	}

	void stringy(Node*& curr) { //creates a stringy BST
		if (!curr) return;

		if (findMin(curr->right)) { //finds minimum value of right side of tree
			findMin(curr->right)->left = curr->left; //sets the left side of tree to the left side of right's minimum node
			curr->left = nullptr;
			stringy(curr->right); //goes to next element on right side
		}
		else {
			curr->right = curr->left; //if there is no elements to right, then just shift all the left side of current node to the right side
			curr->left = nullptr;
			stringy(curr->right);
		}
	}

	//void stringy1(Node* curr) {
	//	if (!curr) return;
	//	else {
	//		if (findMin(curr->left)) {
	//			std::swap(curr->element, findMin(curr->left)->element);
	//			if (findMin(curr->right)) { //finds minimum value of right side of tree
	//				findMin(curr->right)->left = curr->left; //sets the left side of tree to the left side of right's minimum node
	//				curr->left = nullptr;

	//			}
	//			else {
	//				curr->right = curr->left; //if there is no elements to right, then just shift all the left side of current node to the right side
	//				curr->left = nullptr;

	//			}
	//		}
	//		else {
	//			if (findMin(curr->right) && findMin(curr->right)->element < curr->element) { //if the root had no left tree, then find the minimum element in right tree
	//				std::swap(curr->element , findMin(curr->right)->element);
	//			}
	//		}
	//		stringy1(curr->right);
	//		
	//	}
//	}
	//stringy1() was a second attempt at part c but I could not get it to work properly. It only printed out half the stringy tree correctly. 
	//I leave it here as a look into how I tried rethinking my original solution
	///////////////////////////////


	int average_node_depth(Node* curr, int counter ) const {
		if (!curr) return -1;
		else
			return (average_node_depth(curr->left, counter++) + average_node_depth(curr->right, counter++) + counter) ; //returns the sum of the depths at each node

	}

};

int main() {
	//1
	ifstream lpv("Letter_point_value.txt");
	if (!lpv)
		cerr << "Could not open file" << endl;
	vector<int> letterValues(26);
	char letter;
	int val;
	while (lpv >> val >> letter) {
		letterValues[(int)letter - 65] = val;
	}
	
	ifstream words("ENABLE.txt");
	if (!words)
		cerr << "Could not open file" << endl;
	map<string, int> wordsWithFriends;
	string word;
	while (words >> word) {
		wordsWithFriends[word] = wordValue(word, letterValues); //adds point value to word key in the map
		//cout << word << " " << wordsWithFriends[word] << endl;
	}

	///////////////

	//2
	BinarySearchTree<int> bst;
	bst.insert(5);
	bst.insert(1);
	bst.insert(4);
	bst.insert(8);
	bst.insert(9);
	bst.insert(7);
	bst.insert(3);
	bst.insert(2);
	bst.insert(0);
	bst.insert(6);
	cout << endl;

	//a
	cout << "Contains 4? " << boolalpha << bst.contains(4) << endl;
	cout << "Contains 11? " << bst.contains(11) << noboolalpha << endl;

	//b
	cout << "print from 3 to 8 " << endl;
	bst.printRange(3, 8);
	cout << endl;
	cout << "print from 0 to 9 " << endl;
	bst.printRange(0, 9);
	cout << endl;

	//c
	BinarySearchTree<int> b = bst;
	b.stringy();
	cout << "Stringy b ";
	b.printStringy();
	
	//d
	cout << "Avg depth of tree bst " << bst.average_node_depth(10) << endl;
	cout << "Avg depth of stringy tree b " << b.average_node_depth(10) << endl;

	/////////////////

	//3
	cout << "Nodes in bst: ";
	bst.listNodes();
	
	cout << "Nodes in b: ";
	b.listNodes();
	cout << endl;
	//it runs in worst case O(n) because it will take roughly O(n) to go through every element in the queue 
	//after it was filled. The while loop will take O(n) as well since it will need to be traversed through every element

}