//Matthew Avallone
//HW03B

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
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

	for (size_t i = 0; i < data.size(); i++) { //prints out data
		cout << data[i] << endl;
	}
}