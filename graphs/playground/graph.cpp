#include<iostream>
#include<vector>
#include<map>
#define INF 2147483647

using namespace std;

class myGraph {
	private:
		vector<vector<int> > adj_matrix;
		struct distanceTable {
			int vertex_no;
			int prev_vertex;
			double cost;
			distanceTable(int v, int p, double c) : vertex_no(v), prev_vertex(p), cost(c) {}
		};

		map<int, distanceTable*, less<int> > dTable;

	public:
		void getMatrix();
		void printMatrix();
		void calculateDistance();
		void printDistanceTable();
		int minDistVertex(vector<bool> & processed);
};

int myGraph::minDistVertex(vector<bool> & processed) {
	int min = INF, index = -1;

	for( auto itr = dTable.begin(); itr != dTable.end(); ++itr) {
		if (itr->second->cost < min && processed[itr->second->vertex_no] == false) 
			min = itr->second->cost, index = itr->second->vertex_no;
	}
	
	return index;
}

void myGraph::calculateDistance() {
	cout << "calculateDistance():" << endl;
	int startingVertex;

	cout << "Enter the source vertex: ";
	cin >> startingVertex;

	//####### Main Algorithm
	vector<bool> isProcessed(adj_matrix.size(), false);
	dTable[startingVertex] = new distanceTable(startingVertex, -1, 0);

	//looping over all verticies
	for (int count = 0; count < adj_matrix.size(); count++) {
			int  i = minDistVertex(isProcessed);
			//updating processing flag
			isProcessed[i] = true;
		
			for (int j = 0; j < adj_matrix.size(); j++) {
				if (adj_matrix[i][j] == 0)
					continue;

				int cost_i_j = dTable[i]->cost + adj_matrix[i][j];
				map<int, distanceTable*, less<int> >::iterator itr = dTable.find(j);

				if (itr == dTable.end()) {
					dTable[j] = new distanceTable(j,i,cost_i_j);
				} else {
					if (itr->second->cost > cost_i_j) {
						itr->second->cost = cost_i_j;
						itr->second->prev_vertex = i;
					}
				}
		}			
	}
	
}

void myGraph::printDistanceTable() {
	cout << "printDistanceTable():" << endl;
	for(map<int, distanceTable*, less<int> >::iterator itr = dTable.begin(); itr != dTable.end(); ++itr) {
		cout << "Vertex: " << itr->second->vertex_no;
		cout << " prev_vertex: " << itr->second->prev_vertex;
		cout << " cost: " << itr->second->cost << endl;
	}
}


void myGraph::getMatrix() {
	int no_vertices;

	cout << "Enter no of verticies: ";
	cin >> no_vertices;

	cout << "Enter your adj matrix of graph: " << endl;	
	adj_matrix.resize(no_vertices);

	for(auto & row:adj_matrix) {
		row.resize(no_vertices);
		for (auto & ele:row)
			cin >> ele;
	}
}

void myGraph::printMatrix() {
	cout << "Adj matrix is: " << endl;
	for(auto row:adj_matrix) {
		for(auto ele:row)
			cout << ele << "\t";
		cout << endl;
	}
}

int main() {
	myGraph g1;
	g1.getMatrix();
	g1.printMatrix();
	g1.calculateDistance();
	g1.printDistanceTable();

	return 0;

}
