//Matthew Avallone

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

class Maze {
private:
	vector<vector<char>> maze; //creates matrix

	class Coordinates { //way of storing location in matrix
	public:
		Coordinates(int x, int y) : x(x), y(y) {}
		Coordinates(const Coordinates& rhs) : x(rhs.x), y(rhs.y) {}

		bool above, below, left, right = false; //stores if any location around the point is a possible path to take (for stack/ queue implementation)


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

	Maze(ifstream& ifs)  {
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

	bool isIntersection(Coordinates curr) {
		bool isInt = false;
		Coordinates b(curr.getX() + 1, curr.getY());
		Coordinates r(curr.getX(), curr.getY() + 1);
		Coordinates a(curr.getX() - 1, curr.getY());
		Coordinates l(curr.getX(), curr.getY() - 1);
		if ((inRange(maze, b) && maze[b.getX()][b.getY()] != 'x' && curr.below == false)) {
			curr.below = true;
			isInt == true;
		}
		if ((inRange(maze, a) && maze[a.getX()][a.getY()] != 'x' && curr.above == false)) {
			curr.above = true;
			isInt == true;
		}
		if ((inRange(maze, l) && maze[l.getX()][l.getY()] != 'x' && curr.left == false)) {
			curr.left = true;
			isInt = true;
		}
		if ((inRange(maze, r) && maze[r.getX()][r.getY()] != 'x' && curr.right == false)) {
			curr.right = true;
			isInt = true;
		}
		return isInt;
	}

	void stackLocation(Coordinates curr) {
		stack<Coordinates> path;
		stack<Coordinates> intersections;
		path.push(curr);

		if (isIntersection(curr)) path.push(curr);

		while (!path.empty() && maze[path.top().getX()][path.top().getY()] != 'e') {
			Coordinates below(curr.getX() + 1, curr.getY());
			curr = below; //current location is now one below previous location
			while (inRange(maze, curr) && (maze[curr.getX()][curr.getY()] == '.' || maze[curr.getX()][curr.getY()] == 'e')) {
				curr.below = true;
				cerr << "Moved down" << endl;
				path.push(curr);
				if (isIntersection(curr)) intersections.push(curr);
				curr.setX(curr.getX() + 1); //keeps moving down while it is able to move there
			}
			curr.below = false;

			Coordinates right(curr.getX(), curr.getY() + 1);
			curr = right;
			while (inRange(maze, curr) && (maze[curr.getX()][curr.getY()] == '.' || maze[curr.getX()][curr.getY()] == 'e')) {
				curr.right = true;
				cerr << "Moved right" << endl;
				path.push(curr);
				if (isIntersection(curr)) intersections.push(curr);
				curr.setY(curr.getY() + 1);
			}
			curr.right = false;

			Coordinates above(curr.getX() - 1, curr.getY());
			curr = above;
			while (inRange(maze, curr) && (maze[curr.getX()][curr.getY()] == '.' || maze[curr.getX()][curr.getY()] == 'e')) {
				curr.above = true;
				cerr << "Moved up" << endl;
				path.push(curr);
				if (isIntersection(curr)) intersections.push(curr);
				curr.setX(curr.getX() - 1);

			}
			curr.above = false;

			Coordinates left(curr.getX(), curr.getY() - 1);
			curr = left;
			while (inRange(maze, curr) && (maze[curr.getX()][curr.getY()] == '.' || maze[curr.getX()][curr.getY()] == 'e')) {
				curr.left = true;
				cerr << "Moved left" << endl;
				path.push(curr);
				if (isIntersection(curr)) intersections.push(curr);
				curr.setY(curr.getY() - 1);
			}
			curr.left = false;
			if (maze[curr.getX()][curr.getY()] != 'e'){
				while (!(path.top() == intersections.top())) {
					path.pop();
				}
			}
			curr = path.top();
		}
		cout << curr.getX() << " " << curr.getY() << endl;
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
	myMaze.recLocation(myMaze.findLocation(), myMaze.findLocation());
	myMaze.print_maze();
	//myMaze.stackLocation(myMaze.findLocation());
}
