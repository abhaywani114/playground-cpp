#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<map>
#define INF 2147483647
using namespace std;

struct Path {
	int vectex_no;
	int prev_vertex;
	double distance;
	Path(int v, int p, double d) : vectex_no(v), prev_vertex(p), distance(d) {}
	void updatePath(double d, int p) { distance = d, prev_vertex = p;}
};

class myGraph {
	private:
		vector<vector<int> > adj_matrix;
		typedef map<int, Path*> dmap;
		dmap dTable;
	public:
		void readMatrix();
		void printAdjMatrix();
		void printDistanceTable();
		void dijkstra();
		int minUnvisitedVertex(const vector<bool> & isProcessed);
};

int myGraph::minUnvisitedVertex(const vector<bool> & isProcessed) {
	int min = INF,  minIndex = 0;

	for(auto itr = dTable.begin(); itr != dTable.end(); ++itr) {
		if (itr->second->distance < min && !isProcessed[itr->second->vectex_no])
			minIndex = itr->second->vectex_no;
	}

	return minIndex;
}

void myGraph::dijkstra() {
	cout << "dijkstra():" << endl;

	int sourceVertex;
	cout << "Enter the source vertex: ";
	cin >> sourceVertex;
	dTable[sourceVertex] = new Path(sourceVertex, -1, 0);

	vector<bool> isProcessed(adj_matrix.size(), false);

	for(int count = 0; count < adj_matrix.size(); count++) {

		int v = minUnvisitedVertex(isProcessed);
		isProcessed[v] = true;
		for(int i = 0; i < adj_matrix[v].size(); i++) {

			if (adj_matrix[v][i] == 0) continue;

			int new_distance = dTable[v]->distance + adj_matrix[v][i];
			auto is_exist = dTable.find(i);

			if (is_exist == dTable.end()) {
				dTable[i] = new Path(i, v, new_distance);
			} else if (new_distance < dTable[i]->distance) {
				is_exist->second->updatePath(new_distance, v);
			}
		}
	}
}

void myGraph::printDistanceTable() {
	cout << "printDistanceTable():" << endl;

	for (auto itr = dTable.begin();itr != dTable.end(); ++itr) {
		cout << "Vetex No: " << itr->second->vectex_no;
		cout << " Prev Vetex No: " << itr->second->prev_vertex;
		cout << " Distance: " << itr->second->distance << endl;
	}
}

int countWords(const string & line) {
	int words = 0;
	bool state = false;

	for(int i = 0; i < line.length(); i++) {
		if ((line[i] == ' ' || line[i] == '\t' || line[i] == '\n') && state) {
			state = false;
		} else {
			words++;
			state = true;
		}
	}

	return words;
}

void myGraph::readMatrix() {
	string file_name, line_buffer;
	ifstream inFile;

	do {
		cout << "Enter matrix file: ";
		cin >> file_name;
		inFile.open(file_name);
	} while(!inFile);

	int row = 0, element;
	while (!getline(inFile, line_buffer).eof()) {
		cout << line_buffer << "\tCount:" << countWords(line_buffer) << endl;

		// adjusting
		adj_matrix.resize(adj_matrix.size()+1);
		//adj_matrix[x].resize(countWords(line_buffer));
		
		std::istringstream is(line_buffer);

		while(!is.eof()) {
			is >> element;
			adj_matrix[row].push_back(element);
		}

		row++;
	}
}

void myGraph::printAdjMatrix() {
	cout << "printAdjMatrix():"<<endl;
	for(auto row:adj_matrix) {
		for(auto i:row)
			cout << i << "\t";
		cout << endl;
	}
}

int main() {
	myGraph g1;
	g1.readMatrix();	
	//g1.printAdjMatrix();
	g1.dijkstra();
	g1.printDistanceTable();
	return 0;
}
