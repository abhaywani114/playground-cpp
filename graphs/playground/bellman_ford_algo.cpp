#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include<sstream>
#define INF 100000
using namespace std;
struct dVertex {
	int vertex_no;
	int prev = -1;
	double distance;
	dVertex(int v, double d) : vertex_no(v) , distance(d) {}
	void	updateDistance(double d, int p) {prev = p, distance = d;}
};

class bellmanFord {
	private:
		vector<vector<int> > adjMatrix;
		typedef map<int, dVertex*, less<int> > dmap;
		dmap dTable;
	public:
		void printMatrix();
		void readMatrix();
		void printDistanceTable();
		void initdTable();
		void calculateDistance();
};

void bellmanFord::calculateDistance() {
	cout << "calculateDistance():" << endl;
	int sourceVertex; 
	cout << "Enter source vertex: ";
	cin >> sourceVertex;
	dTable[sourceVertex]->distance = 0;
	int v = -1;
	for(int count = 0 ; count < adjMatrix.size() + 1; count++) {
		if (v == -1)
			v = sourceVertex;
		else
			v = (v+1) % adjMatrix.size();

		for(int j = 0; j < adjMatrix[v].size(); j++) {

			if (adjMatrix[v][j] == 0) continue;

			int new_distance = dTable[v]->distance + adjMatrix[v][j];
			if (dTable[j]->distance > new_distance) {
				if (count == adjMatrix.size())
					cerr << "ERROR NEGETIVE CYCLE DETECTED" << endl;
				dTable[j]->updateDistance(new_distance, v);
			}
		}

	}
}

void bellmanFord::initdTable()  {
	for(int i = 0; i < adjMatrix.size(); i++) {
		dTable[i] = new dVertex(i, INF);
	}
}

void bellmanFord::printDistanceTable() {
	cout << "printDistanceTable():" << endl;
	for(dmap::iterator itr = dTable.begin(); itr != dTable.end(); ++itr) {
		cout << "Vertex: " << itr->second->vertex_no;
		cout << " Prev: " << itr->second->prev;
		cout << " Distance: " << itr->second->distance;
		cout << endl;
	}
}

void bellmanFord::readMatrix() {
	string fileName, bufferLine;
	int bufferElement, row = 0;

	cout << "Enter matrix file name: ";
	cin >> fileName;

	ifstream in(fileName);
	if (!in)
		cerr << "File not found" << endl;
	
	while(!getline(in, bufferLine).eof()) {
		cout << bufferLine << endl;
		adjMatrix.resize(row+1);

		istringstream is(bufferLine);
		while(!is.eof()) {
			is >> bufferElement;
			adjMatrix[row].push_back(bufferElement);
		}
		row++;
	}
	initdTable();
}

void bellmanFord::printMatrix() {
	cout << "printMatrix():" << endl;
	
	for (auto row:adjMatrix) {
		for (auto element:row)
			cout << element << "\t";
		cout << endl;
	}
}

int main() {
	bellmanFord p1;
	p1.readMatrix();
	p1.printMatrix();	
	p1.calculateDistance();	
	p1.printDistanceTable();
	return 0;
}
