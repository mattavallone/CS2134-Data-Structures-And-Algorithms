//Matthew Avallone
//hw10 question 2

#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class trainStopData;
const int DEFAULT_VAL = -1;


class MTA {
public:
	MTA() {}
	MTA(const string& fileName); //see definitions below trainStopData class for all the methods
	typedef list<trainStopData>::iterator itr;
	itr findTrainStop(const string& id);
	void shortestpaths(const trainStopData& s);
	void addNewLine(const string& newLineFile, const string& newTransfersFile);
protected:
	unordered_map<char, list<trainStopData>> data; //needs to be protected in order for trainStopData class to be able to use the unordered_map
};
//this code is from the previous hw09 solution with some personal changes
class trainStopData {
	friend bool operator<(const trainStopData& lhs, const trainStopData& rhs); //see function definition below class
	friend ostream& operator<<(ostream& os, const trainStopData& rhs);
public:
	trainStopData(const string& id, const string& name, double lat, double lon, const string& transfers = "transfers.txt") : stop_id(id), stop_name(name), stop_lat(lat), stop_lon(lon), transferFile(transfers) { addTransfers(); }
	trainStopData(const trainStopData& rhs) {
		stop_id = std::move(rhs.stop_id);
		stop_name = std::move(rhs.stop_name);
		stop_lat = std::move(rhs.stop_lat);
		stop_lon = std::move(rhs.stop_lon);
	}
	string get_id()         const { return stop_id; }
	string get_stop_name()  const { return stop_name; }
	double get_latitude()   const { return stop_lat; }
	double get_longitude()  const { return stop_lon; }
	int numOfAdjacentStations() const { return adjList.size(); }

private:
	string stop_id;
	string stop_name;
	double stop_lat;
	double stop_lon;
	string transferFile;
	list<trainStopData> adjList; //this is an adjacency list for every trainStop
};

void addTransfers(MTA data) {
	ifstream transfersFile(transferFile);
	if (!transfersFile) {
		cerr << "The file for train stop data cannot be found.\n";
		exit(1);
	}
	// Read the file line-by-line
	string line;
	getline(transfersFile, line);
	while (getline(transfersFile, line)) {
		// Get the first two elements in each line
		stringstream eachLine(line);
		string fromStop;
		string toStop;
		// Get the from_stop_id
		getline(eachLine, fromStop, ',');
		// Get the to_stop_id
		getline(eachLine, toStop, ',');
		// Add the toStop to the adjacency list of the fromStop
		// Make sure that the two are different data
		if (fromStop != toStop && fromStop == stop_id) { /* && MTA::findTrainStop(toStop) != data[stop_id[0]].end()*/
			trainStopData to = *data.findTrainStop(toStop);
			adjList.push_back(to);
		}
		transfersFile.close();
	}
	cout << stop_name << endl;
	for (list<trainStopData>::iterator start = adjList.begin(); start != adjList.end(); start++) {
		cout << *start << endl;
	}
	cout << endl;
}
ostream& operator<<(ostream& os, const trainStopData& rhs) {
	os << rhs.stop_name;
	return os;
}

//////////////////////////////
//MTA CLASS METHOD DEFINITIONS
//////////////////////////////
MTA::MTA(const string& fileName) {
	ifstream ifs;
	ifs.open(fileName);
	if (!ifs) { //checks if file exists
		cerr << "Could not open MTA file" << endl;
		exit(1);
	}
	string id = "", name = "";
	double lat = 0, lon = 0;
	string dumb = ""; //place holder
	int count = 0; //counts what piece of info being read (going in order of member variable list 1-4)
	getline(ifs, dumb); //goes through first line which doesn't contain any relevant data
	while (getline(ifs, dumb, ',')) {
		if (dumb != "") { //checks to make sure the variable isn't empty string
			++count;
			if (count == 1) {
				id = dumb;
			}
			else if (count == 2) {
				name = dumb;
			}
			else if (count == 3) {
				lat = stod(dumb); //converts string to double
			}
			else if (count == 4) {
				count = 0;
				lon = stod(dumb); //converts string to double
				if (id[3] < 65) {
					trainStopData tsd(id, name, lat, lon);
					data[id[0]].push_back(tsd); //adds the station name to the id key
				}

				getline(ifs, dumb); //brings to next line
			}
		}
		
	}
	ifs.close();
}

typedef list<trainStopData>::iterator itr;
itr MTA::findTrainStop(const string& id) {
	char trainLine = id[0];
	itr start = data[trainLine].begin();
	while (start != data[trainLine].end()) {
		if (start->get_id() == id) return start;
		++start;
	}
	return start;
}


void MTA::shortestpaths(const trainStopData& tStop) { //train stop must exist
	//struct vertexInf {  // Stores information for a vertex
	//	int dist;  // distance to vertex from the source
	//	int prev;  // previous node in BFS tree
	//};

	//queue<int> q;             // q is the queue of vertex numbers

	//vector<vertexInf> vertices(data.size());               // stores BFS info for the vertices
	//							   // info for vertex j is in position j
	//for (int j = 0; j < vertices.size(); ++j) {
	//	vertices[j].dist = DEFAULT_VAL; vertices[j].prev = DEFAULT_VAL;
	//}

	//vertices[s].dist = 0;
	//q.push(s);
	//while (!q.empty())
	//{
	//	int v = q.front();
	//	q.pop();
	//	for (list<string>::const_iterator w = g[v].begin(); w != g[v].end(); w++)
	//	{

	//		if (vertices[*w].dist == DEFAULT_VAL)          // distance of *w from source not determined yet
	//		{
	//			vertices[*w].dist = vertices[v].dist + 1;
	//			vertices[*w].prev = v;
	//			q.push(*w);
	//		}
	//	}
	//}
	//for (int j = 0; j < vertices.size(); j++) {      // print distances from source and paths
	//	cout << "vertex " << j << endl;
	//	cout << "distance: " << vertices[j].dist << endl;
	//	cout << "shortest path: ";
	//	stack<trainStopData> t;
	//	trainStopData current = j;
	//	while (current != DEFAULT_VAL){
	//		t.push(current);
	//		current = vinfo[current].prev;
	//	}
	//	while (!t.empty()){
	//		cout << t.top() << " ";
	//		t.pop();
	//	}
	//	cout << endl;
	//}
}

void MTA::addNewLine(const string& newLineFile, const string& newTransfersFile) { //passing in file containing trainStopData for a new line (such as the future T line on 2nd Ave) as well as file for all the transfers for new line
	ifstream ifs(newLineFile);
	if (!ifs) { //checks if file exists
		cerr << "Could not open file TSD" << endl;
		exit(0);
	}
	string id = "", name = "";
	double lat = 0, lon = 0;
	string dumb = ""; //place holder
	int count = 0; //counts what piece of info being read (going in order of member variable list 1-4)
	getline(ifs, dumb); //goes through first line which doesn't contain any relevant data
	while (getline(ifs, dumb, ',')) {
		if (dumb != "") { //checks to make sure the variable isn't empty string
			++count;
			if (count == 1) {
				id = dumb;
			}
			else if (count == 2) {
				name = dumb;
			}
			else if (count == 3) {
				lat = stod(dumb); //converts string to double
			}
			else if (count == 4) {
				count = 0;
				lon = stod(dumb); //converts string to double
				if (id[3] < 65) {
					trainStopData tsd(id, name, lat, lon, newTransfersFile); //passes in an updated transfers file needed for finding the adjacent stations
					data[id[0]].push_back(tsd); //adds the station name to the id key
				}

				getline(ifs, dumb); //brings to next line
			}
		}

	}
	ifs.close();
}

int main() {
	//this code is from the previous hw
	string MTAfilename = "MTA_train_stop_data.txt";
	MTA mta(MTAfilename);
	list<trainStopData>::iterator stop = mta.findTrainStop("306"); //id must exist
	//mta.shortestpaths(*stop);

}

