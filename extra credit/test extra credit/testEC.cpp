//Matthew Avallone

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

class Maze {
private:
	vector<vector<char>> maze; //creates matrix

	class Coordinates { //way of storing location in matrix
	public:
		Coordinates(int x, int y) : x(x), y(y) {}
		Coordinates(const Coordinates& rhs) : x(rhs.x), y(rhs.y) {}
		void setX(int row) {
			x = row;
		}
		void setY(int col) {
			y = col;
		}
		int getX() const {
			return x;
		}
		int getY() const {
			return y;
		}

		bool operator==(const Coordinates& rhs) {
			return x == rhs.x && y == rhs.y;
		}

	private:
		int x;
		int y;
	};

public:

	Maze(ifstream& ifs) {
		createMaze(ifs);
	}

	void createMaze(ifstream& ifs) {
		string line;
		while (getline(ifs, line)) { //takes each line from the file
			vector<char> charVec;
			for (size_t i = 0; i < line.length(); i++) {
				charVec.push_back(*line.substr(i, 1).c_str()); //places X or . in correct spot in matrix
			}
			maze.push_back(charVec); //adds each line to the maze
		}
	}
	bool inRange(const vector<vector<char>>& maze, Coordinates point) {
		if (point.getX() < maze.size() && -1 < point.getX() && point.getY() < maze[0].size() && -1 < point.getY()) {
			return true;
		}
		return false;
	}

	//e must be located someplace inside maze in reachable location
	void recLocation(Coordinates curr, Coordinates prev) {
		try {
			if (maze[curr.getX()][curr.getY()] == 'e') {
				cout << "Location, Row: " << curr.getX() << " Column: " << curr.getY() << endl;
				throw "a";
				return;
			}
		}
		catch (string s) { //was not able to get my program to end without this try/catch block oops LOL
			return;
		}
		cout << "Row  Col" << endl;
		cout << curr.getX() << "     " << curr.getY() << endl;
		cout << prev.getX() << "     " << prev.getY() << endl << endl;


		Coordinates below(curr.getX() + 1, curr.getY());
		if (inRange(maze, below) && !(below == prev) && (maze[curr.getX() + 1][curr.getY()] == '.' || maze[curr.getX() + 1][curr.getY()] == 'e')) { 																																			//else {
			cerr << "Moved down" << endl;
			recLocation(below, curr);
		}

		Coordinates right(curr.getX(), curr.getY() + 1);
		if (inRange(maze, right) && !(right == prev) && (maze[curr.getX()][curr.getY() + 1] == '.' || maze[curr.getX()][curr.getY() + 1] == 'e')) {
			cerr << "Moved right" << endl;
			recLocation(right, curr);
		}

		Coordinates above(curr.getX() - 1, curr.getY());
		if (inRange(maze, above) && !(above == prev) && (maze[curr.getX() - 1][curr.getY()] == '.' || maze[curr.getX() - 1][curr.getY()] == 'e')) {
			cerr << "Moved up" << endl;
			recLocation(above, curr);

		}
		Coordinates left(curr.getX(), curr.getY() - 1);
		if (inRange(maze, left) && !(left == prev) && (maze[curr.getX()][curr.getY() - 1] == '.' || maze[curr.getX()][curr.getY() - 1] == 'e')) {
			cerr << "Moved left" << endl;
			recLocation(left, curr);
		}

	}

	Coordinates findLocation() {
		Coordinates start(0, 0);
		for (size_t row = 0; row < maze.size(); row++) {
			for (size_t col = 0; col < maze[row].size(); col++) { //finding location of s using brute force
				if (maze[row][col] == 's') {
					start = Coordinates(row, col);
					return start;
				}
			}
		}
		return start;
	}

	void print_maze() {
		for (size_t row = 0; row < maze.size(); row++) {
			for (size_t col = 0; col < maze[row].size(); col++) { //finding location of s using brute force
				cout << maze[row][col];
			}
			cout << endl;
		}
	}

};


int main() {
	Maze myMaze(ifstream("maze.txt"));
	myMaze.findLocation();
	myMaze.recLocation(myMaze.findLocation(), myMaze.findLocation());
	myMaze.print_maze();
}