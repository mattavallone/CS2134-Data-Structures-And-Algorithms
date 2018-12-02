//Matthew Avallone
//hw09

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <unordered_map>
using namespace std;

template< class HashedObj >
class HashTable
{
public:
	explicit HashTable(int size = 101) :currentSize(0) { arr.resize(size); }
	std::hash<HashedObj> hf; // create a hash function object
	void makeEmpty() {
		arr.clear();
		currentSize = 0;
	}
	bool find(const HashedObj& x){
		size_t i = hf(x) % arr.size();
		size_t pos = i; //holds starting position
		while (arr[i].element != x) {
			if (i == arr.size() - 1) i = -1; //if the current position is the size of the arr
			++i;
			if (i == pos) { //if all the positions are active in the arr (current pos = starting pos)
				return false;
			}
		}
		return true;
	}
	bool insert(const HashedObj & x) {
		if (find(x))
			return false;
		size_t i = hf(x) % arr.size();
		HashEntry h(x, ACTIVE);
		if (arr[i].info != 0)
			arr[i] = h;
		else {
			size_t pos = i; //holds starting position
			while (arr[i].info == 0) {
				if (i == arr.size()) i = -1; //if the current position is the size of the arr
				++i;
				if (i == pos) { //if all the positions are active in the arr (current pos = starting pos)
					rehash();
				}
			}
			arr[i] = h;
		}

		if (++currentSize >= arr.size() * MAXLOADFACTOR)
			rehash();
		return true;
	}
	bool remove(const HashedObj & x){
		size_t i = hf(x) % arr.size();

		vector<HashEntry>::iterator itr = std::find(arr.begin(), arr.end(), x);
		if (itr == arr.end())
			return false;

		arr.erase(itr);
		--currentSize;
		return true;
	}
	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;
		HashEntry(const HashedObj & e = HashedObj(), EntryType i = EMPTY)
			: element(e), info(i) {}
		bool operator==(const HashedObj& x) {
			return element == x;
		}
	};
	vector<HashEntry> arr;
	int currentSize;
	double MAXLOADFACTOR = 0.5;

	void rehash() {
		vector< HashEntry > oldarr = std::move(arr);
		makeEmpty();
		arr.resize(2 * oldarr.size() + 1);
		// better to resize to a prime size
		for (size_t i = 0; i < oldarr.size(); i++){
			arr.push_back(std::move(oldarr[i]));
		}
	}
};

void fillData(unordered_map<char, list<pair<string, string>>>& data) {
	ifstream ifstr;
	ifstr.open("MTA_train_stop_data.txt");
	if (!ifstr) { //checks if file exists
		cerr << "Could not open file" << endl;
	}

	string id, name;
	string dumb = ""; //place holder
	int count = 0; //counts what piece of info being read (going in order of member variable list 1-4)
	getline(ifstr, dumb); //goes through first line which doesn't contain any relevant data
	while (getline(ifstr, dumb, ',')) {
		if (dumb != "") { //checks to make sure the variable isn't empty string
			++count;
			if (count == 1) {
				id = dumb;
			}
			else if (count == 2) {
				name = dumb;
			}
			else if (count == 4) {
				count = 0;
				if (id[3] < 65) {
					data[id[0]].push_back(pair<string, string>(id, name)); //adds the station name to the id key
				}
				getline(ifstr, dumb); //brings to next line
			}
		}

	}
	ifstr.close();
}

pair<string, string> findAdjacent(list<pair<string, string>>&  trainLines, const string& id) { //will either return an iterator to the following station or return end()
	typedef list<pair<string, string>>::iterator itr;
	itr start = trainLines.begin();
	
	if (start->first == id) {
		itr next = ++start;
		return pair<string, string>(".", next->second);
	}
	while (start->first != id) {
		if (start == trainLines.end()) {
			itr prev = --start;
			return pair<string, string>(prev->second, ".");
		}
		++start;
	}
	itr copy = start;
	
	if (start != trainLines.end()) {
		return pair<string, string>((--start)->second, (copy++)->second);
	}
	else {
		return pair<string, string>((--start)->second, ".");
	}
}

string findStationName(list<pair<string, string>>&  trainLines, const string& id) {
	list<pair<string, string>>::iterator start = trainLines.begin();
	while (start->first != id) {
		start++;
	}
	return start->second;
}

int main() {
	//1
	
	HashTable<int> ht(10);
	cout << "insert() " << boolalpha << ht.insert(3) << endl;
	ht.insert(5);
	ht.insert(23);
	ht.insert(41);
	ht.insert(15);
	cout << "remove() " << ht.remove(23) << endl;;
	cout << "find() " << ht.find(3) <<  endl;
	cout << "find() " << ht.find(23) << noboolalpha << endl;
	
	//////////////////////////////////////
	//2
	//////////////////////////////////////

	unordered_map<char, list<pair<string, string>>> data; //creates this map with the train line as a char and then the list of stops on the line and their ids as a list of pairs (station name and id)
														  //makes for O(1) find and insert
	fillData(data);

	for (auto& x : data) { //checking data stored in train stop data unordered_map
		cout << x.first << ": ";
		for (auto& s : x.second) {
			cout << s.first << ", "; // << s.second << " ";
		}
		cout << endl;
	}
	cout << "start" << endl;
	unordered_map<string, list<string>> transfers;
	ifstream ifs("transfers.txt");
	if (!ifs) //checks if file exists
		cerr << "Cannot open ifs";
	string s;
	getline(ifs, s); //removes the first like that just holds string idetifiers for the different columns of data
	string from, to; //these are ids for the stations
	while (getline(ifs, s)) {
		from = s.substr(0, 3);
		to = s.substr(4, 3);
		pair<string, string> adjStations = findAdjacent(data[from[0]], to);

		if (adjStations.first != ".")
			transfers[findStationName(data[from[0]], from)].push_back(adjStations.first); //places the previous station's name into the current station's list of adjacent stations
		if (adjStations.second != ".")
			transfers[findStationName(data[from[0]], from)].push_back(adjStations.second); //places the next station's name into the current station's list of adjacent stations
	}
	ifs.close();

	for (auto& x : transfers) {
		if (x.second.begin() != x.second.end()) { //only prints out stations where there are transfers
			cout << x.first << ": ";
			for (auto& s : x.second) {
				cout << s << "; ";
			}
			cout << endl;
		}
	}
}