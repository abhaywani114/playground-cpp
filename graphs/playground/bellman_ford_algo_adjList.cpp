#include<iostream>
#include<string>
#include<map>
#include<list>
#include<vector>
#include<sstream>
#define INF 2.5e100

using namespace std;

struct Edge;
struct Vertex {
	string name;
	vector<Edge*> edgeList;	

	double distance;
	Vertex * prev;

	int misc;
	Vertex(const string & n) : name(n) {
		distance = INF;
		prev = NULL;
	}
};

struct Edge {
	double cost;
	Vertex * destination;

	Edge(double c, Vertex * d) : cost(c), destination(d) {}
};

class myGraph {
	private:
		typedef map<string, Vertex*, less<string> > vmap;
		vmap myVertex;		
		Vertex * getVertex(const string & vertexName);
	public:
		void addEdge(const string & v1, const string & v2, double cost);
		void printDistanceTable();
		void readGraph();
		void bellmanFord();
};

void myGraph::bellmanFord() {
	cout << "bellmanFord():" << endl;

	string sourceVetex;
	cout << "Enter source vertex: ";
	cin >> sourceVetex;

	auto start = myVertex.find(sourceVetex);
	if (start == myVertex.end())
		cerr << "Invalid vertex";

	start->second->distance = 0;
	
	list<Vertex*> q;
	q.push_back(start->second);

	while(!q.empty()) {
		Vertex *v = q.front();
		q.pop_front();

		if (v->misc > 2 * myVertex.size()) {
			cerr << "Negetive cycle found" << endl;
			return;
		}

		for (auto E:v->edgeList) {
			int new_distance = v->distance + E->cost;
			if (new_distance < E->destination->distance) {
				E->destination->distance = new_distance;
				E->destination->prev = v;
				E->destination->misc++;
				q.push_back(E->destination);
			}
		}
	}
}

void myGraph::readGraph() {
	cout << "readGraph():" << endl;
	cout << "Enter your graph data: " << endl;
	string line, v1, v2;
	double cost;
	while ( true ) {
		cin >> v1;
		if (v1 == "END")
			break;

		cin >> v2; 
		if (v2 == "END")
			break;

		cin >> cost;
		addEdge(v1, v2, cost);	
	}		
}

void myGraph::printDistanceTable() {
	cout << "printDistanceTable():" << endl;
	for(vmap::iterator itr = myVertex.begin(); itr != myVertex.end(); ++itr) {
		cout << "Vertex: " << itr->second->name;
		cout << " Distance: " << itr->second->distance;
		if (itr->second->prev != NULL)
			cout << " Prev: " << itr->second->prev->name;
		cout << endl;
	}
}

void myGraph::addEdge(const string & v1, const string & v2, double cost) {
	Vertex * v = getVertex(v1);
	Vertex * w = getVertex(v2);
	v->edgeList.push_back(new Edge(cost, w));
}

Vertex * myGraph::getVertex(const string & vertexName) {
	auto itr = myVertex.find(vertexName);
	return itr == myVertex.end() ? 
		myVertex[vertexName] = new Vertex(vertexName):itr->second;
}


int main() {
	cout << "Bellman ford Algorithm..." << endl;
	myGraph g1;
	g1.readGraph();
	g1.bellmanFord();
	g1.printDistanceTable();
	return 0;
}
