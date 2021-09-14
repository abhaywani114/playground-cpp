#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<list>
#include<queue>
#include<fstream>
#include<sstream>

#define INF 2e10

using namespace std;

struct Edge;
struct Vertex {
	string name;
	vector<Edge*> edges;
	
	double distance = INF;
	Vertex * prev = NULL;

	int misc;

	Vertex(const string & nm) : name(nm) {}
	void updateDistance(double d, Vertex *p) { distance = d , prev = p ;}
};

struct Edge {
	double cost;
	Vertex * destination;

	Edge(Vertex * d, double c) : cost(c), destination(d) {}
};

class myGraph {
	private:
		typedef map<string, Vertex *, less<string> > vmap;
		vmap vertexList;

		Vertex * getVertex(const string & vertexName);

	public:
		void printDistanceTable();
		void addEdge(const string & sourceName, const string & destinationName, double cost);
		void dijk(const string & sourceName); 
};

void myGraph::dijk(const string & sourceName) {
	cout << "dijk()" << endl;
	struct Path {
		double cost = 0.0;
		Vertex * destination = NULL;

		Path() {}
		Path(Vertex *v, double c) : destination(v), cost(c) {}
		
		bool operator> (const Path & rhs) const { return cost > rhs.cost;}
		bool operator< (const Path & rhs) const { return cost < rhs.cost;}
	};

	priority_queue<Path, vector<Path>, greater<Path> > pq;
	Path vrec;

	auto itr = vertexList.find(sourceName);
	itr->second->distance = 0;
	pq.push(Path(itr->second, 0));

	for (int countNode = 0; countNode < vertexList.size(); countNode++) {
		do {
			vrec = pq.top();
			pq.pop();
		} while (vrec.destination->misc != 0);
		vrec.destination->misc = 1;
	
		for(auto E:vrec.destination->edges) {
			int new_distance = vrec.destination->distance + E->cost;
			if (E->destination->distance > new_distance) {
				E->destination->updateDistance(new_distance, vrec.destination);
				pq.push(Path(E->destination, new_distance));
			}
		}
	}
}

Vertex * myGraph::getVertex(const string & vertexName) {
	auto itr = vertexList.find(vertexName);

	if (itr == vertexList.end()) {
		Vertex * new_vertex = new Vertex(vertexName);
		vertexList[vertexName] = new_vertex;
		return new_vertex;
	}

	return itr->second;
}

void myGraph::addEdge(const string & sourceName, const string & destinationName, double cost) {
	Vertex * v = getVertex(sourceName);
	Vertex * w = getVertex(destinationName);
	v->edges.push_back(new Edge(w, cost));
}

void myGraph::printDistanceTable() {
	cout << "printDistanceTable()" << endl;
	for (auto itr = vertexList.begin(); itr != vertexList.end(); ++itr) {
		cout << "Vertex: " << itr->second->name;
		cout << " Distance: " << itr->second->distance;
		if (itr->second->prev != NULL)
			cout << " Prev: " << itr->second->prev->name;
		cout << endl;
	}
}

int main() {
	myGraph g1;
	string file;

	cout << "Enter graph data file: " ;
	cin >> file;

	ifstream in(file.c_str());
	if (!in) {
		cerr << "Ops! file not found" << endl;
		return 1;
	}


	while(!getline(in, file).eof()) {
		string source, dest;
		double cost;
		std::istringstream s(file);
		s >> source;
		s >> dest;
		s >> cost;
		cout << file << endl;
		g1.addEdge(source, dest, cost);
	}

	string sourceVertex;
	cout << "Enter source vertex: ";
	cin >> sourceVertex;

	g1.printDistanceTable();
	g1.dijk(sourceVertex);

	g1.printDistanceTable();
	return 0;
}
