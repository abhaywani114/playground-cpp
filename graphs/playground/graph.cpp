#include<iostream>
#include<vector>
#include<map>

using namespace std;

class myGraph {
	private:
		vector<vector<int> > adj_matrix;
		struct distanceTable {
			int vertex_no;
			int prev_vertex;
			double cost;
		};

	public:
		void getMatrix();
		void printMatrix();
		void calculateDistance();
};

void myGraph::calculateDistance() {
	cout << "calculateDistance():" << endl;
	int startingVertex;

	cout << "Enter the source vertex: ";
	cin >> startingVertex;
	
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

	return 0;

}
