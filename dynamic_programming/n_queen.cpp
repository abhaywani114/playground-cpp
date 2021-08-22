#include<iostream>
#include<vector>
#include<climits>
using namespace std;

class NQueen {
	private:
		vector<vector<int>> sol;
	public:
		NQueen(int row, int queen) {
			sol.resize(row);

			for(auto &i : sol)
				i.resize(row, 0);

			placeQueens(0,0,queen);
		}

		~NQueen() {
			cout << endl;
			cout << "Solution: " << endl;

			for(auto i:sol) {
				for(auto j:i)
					cout << "\t" << j;
				cout << endl;
			}
		}

		int placeQueens(int x, int y, int queen) {

			if (queen == 0)
				return 1;

			for (int i=0; i < sol.size(); i++) {

				if (isSafe(x+i,y)) {
					sol[x+i][y] = 1;

					if (placeQueens(0,y+1,queen-1) == 1)
						return 1;
					else
						sol[x+i][y] = 0;
				}
			}

			return 0;
		}

		bool isSafe(int x, int y) {
			if (x > sol.size() || y > sol.size() || checkDiagonalSafe(x,y) || !isColSafe(x)) {
				return false;
			}

			return true;
		}

		bool isColSafe(int x) {
			for(auto i:sol[x])
				if (i == 1)
					return false;
			return true;
		}

		bool checkDiagonalSafe(int x, int y) {
			if (x-1 > 0 && y-1>0)
				if (sol[x-1][y-1] == 1)
					return true;

			if (x+1 < sol.size() && y+1 < sol.size())
				if (sol[x+1][y+1] == 1)
					return true;
	
			if (x+1 <sol.size() && y-1 > -1)
				if (sol[x+1][y-1] == 1)
					return true;

			if (x-1 > -1 && y+1 <sol.size())
				if (sol[x-1][y+1] == 1)
					return true;

			return false;	
		}
};

int main() {
	NQueen p1(4,4);
	return 0;
}
