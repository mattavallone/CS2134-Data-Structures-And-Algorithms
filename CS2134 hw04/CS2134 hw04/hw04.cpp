//Matthew Avallone
//hw04

//Matthew Avallone
//HW03B

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <functional>
using namespace std;



class trainStopData {
	friend ostream& operator<<(ostream& os, const trainStopData& rhs);
public:
	trainStopData(const string& stop_id, const string& stop_name, double stop_lat, double stop_lon) : stop_id(stop_id), stop_name(stop_name), stop_lat(stop_lat), stop_lon(stop_lon) {}

	string get_id() const {
		return stop_id;
	}
	string get_stop_name() const {
		return stop_name;
	}
	double get_latitude() const {
		return stop_lat;
	}
	double get_longitude() const {
		return stop_lon;
	}
	char get_route() const {
		return stop_id[0];
	}

private:
	string stop_id; //id of train stop (1st token)
	string stop_name; //name of station (4th token)
	double stop_lat; //latitude of train stop location
	double stop_lon; //logitude of train stop location
};

ostream& operator<<(ostream& os, const trainStopData& rhs) {
	os << "ID: " << rhs.stop_id << ", Name: " << rhs.stop_name << ", Latitude: " << rhs.stop_lat << ", Longitude: " << rhs.stop_lon << endl;
	return os;
}


//HAVERSINE DISTANCE
double degrad(double d) {
	return d * 3.1415926535897 / 180;
}

double haverdist(double lat1, double longit1, double lat2, double longit2)
{
	double r = 6371;
	double dlat = degrad(lat2 - lat1);
	double dlongit = degrad(longit2 - longit1);
	double a = sin(dlat / 2)*sin(dlat / 2) +
		cos(degrad(lat1))*cos(degrad(lat2))*sin(dlongit / 2)*sin(dlongit / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return r*c;
}

//TEMPLATED FUNCTORS
template<class Object>
class isStopOnRoute {
public:
	isStopOnRoute(char rt) : route(rt){}
	bool operator()(const Object& data) {
		return route == data.get_route();
	}
private:
	char route;
};

template<class Object>
class isSubwayStop {
public:
	isSubwayStop(const string& id) : stopID(id) {}
	bool operator()(const Object& data) {
		return stopID == data.get_id();
	}
private:
	string stopID;
};

template<class Object>
class isSubwayStopNearX {
public:
	isSubwayStopNearX(double lon, double lat, double d) :  lon(lon), lat(lat), d(d) {}
	bool operator()(const Object& data) {
		return haverdist(abs(lat), abs(lon), abs(data.get_latitude()), abs(data.get_longitude())) <= d;
	}
private:
	double lon;
	double lat;
	double d;
};

template<class Object>
class printTrainStopInfo {
public:
	void operator()(const Object& data) {
		cout << data << endl;
	}
};


//HW04 #1
template < class Iterator, class Comparable, class doIt>
int  perform_if(Iterator start, Iterator stop, Comparable pred, doIt op) {
	int how_many = 0;
	while (start != stop) {
		if (pred(*start)) {
			op(*start);
			how_many++;
		}
		++start;
	}
	return how_many;
}

void menu(const vector<trainStopData> vec) {
	cout << "Which function would you like to call: A, B, C, or Quit?" << endl;
	char choice = ' ';
	cin >> choice;
	if (choice == 'A') {
		cout << "Which route?";
		cin >> choice; //receives data from user
		cout << "Called " << perform_if(vec.begin(), vec.end(), isStopOnRoute<trainStopData>(choice), printTrainStopInfo<trainStopData>()) << " times" << endl;
		
	}

	else if (choice == 'B') {
		cout << "Which subway stop?" << endl;
		string stopID;
		cin >> stopID; //receives data from user
		cout << "Called " << perform_if(vec.begin(), vec.end(), isSubwayStop<trainStopData>(stopID), printTrainStopInfo<trainStopData>()) << " times" << endl;
	}

	else if (choice == 'C') {
		cout << "What location would you like?" << endl;
		int latitude, logitude;
		double dist;
		cin >> latitude >> logitude >> dist; //receives data from user
		cout << "Called" << perform_if(vec.begin(), vec.end(), isSubwayStopNearX<trainStopData>(latitude, logitude, dist), printTrainStopInfo<trainStopData>()) << " times" << endl;
	}
	else
		cout << "Quit" << endl;
		return; //Quit
}

//HW04 #2
int GCD(int a, int b) {
	if (b == 0) return a;
	else if (b > a) return GCD(b, a);
	else
		return GCD(b, a % b);
}

//HW04 #3

template<class Object, class Iter>
Object recSumVec(Iter start, Iter stop) {
	if (start == stop-1) return *start; //checks if only one value in vector
	Object mid = (stop-start) / 2; //gets the value at the midpoint
	return recSumVec<int, vector<int>::iterator>(start, stop - mid) + recSumVec<int, vector<int>::iterator>(stop - mid, stop);
}

template<class Object> 
Object sumVector(const vector<Object> & a) { // driver program
	vector<Object> copy = std::move(a);
	Object sum = recSumVec<int, vector<int>::iterator>(copy.begin(), copy.end());
	return sum;
}




int main() {

	vector<trainStopData> data;
	ifstream ifs;
	ifs.open("MTA_train_stop_data.txt");
	if (!ifs) { //checks if file exists
		cerr << "Could not open file" << endl;
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
				trainStopData tsd(id, name, lat, lon);
				data.push_back(tsd);
				getline(ifs, dumb); //brings to next line
			}
		}

	}
	ifs.close();
	
	// #1
	menu(data);
	cout << endl;

	// #2
	cout << "GCD:" << endl;
	cout << GCD(12, 4) << endl;
	cout << GCD(2, 3) << endl;
	cout << GCD(8, 0) << endl << endl;

	// #3
	vector<int> v = { 1,2,3,4,5 };
	cout << "sumVector: " << endl << sumVector<int>(v) << endl;
}