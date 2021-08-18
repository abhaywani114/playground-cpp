#include<iostream>
#include<vector>
using namespace std;

class ratInMaze {
	private:
		vector<vector<int> > maze;
		vector<vector<int> > path;

	public:
		ratInMaze(vector<vector<int> > &m) : maze(m) {
			path.resize(maze.size());

			for (int i = 0; i < maze.size(); i++)
				path[i].resize(maze[i].size(), 0);

			moveRat(0,0);
		}

		~ratInMaze() {
			cout << endl;

			cout << "Maze: " << endl;
			for(auto i:maze) {
				for (auto j:i)
					cout << "\t" << j;
				cout << endl;
			}

			cout << "Path: " << endl;
			for(auto i:path) {
				for (auto j:i)
					cout << "\t" << j;
				cout << endl;
			}
		}
		int moveRat(int x, int y) {
			if (maze.size() -1 ==x && maze.size()-1==y)
				return path[x][y] = 1;


			return path[x][y] = max( isSafe(x+1,y) ? moveRat(x+1,y):0 , isSafe(x,y+1) ? moveRat(x,y+1):0);
		}

		bool isSafe(int x, int y) {
			if (x >= maze.size() || y >= maze.size() || maze[x][y] == 0)
				return false;

			return true;
		}
};

int main() {
	vector<vector<int> > grid {
		{1,1,0,0},
		{0,1,1,1},
		{0,1,0,0},
		{0,1,1,1}
	};	
	ratInMaze p1(grid);
	return 0;
}
