#include<iostream>
#include<string>
#include<map>
#include<list>
#include<vector>
#define INF 2.3e100
using namespace std;


struct Edge;

struct Vertex {
	string name;
	vector<Edge*> adj_list;
	
	double dist = INF; // distance from starting source vertex
	Vertex * prev = NULL;

	Vertex(const string & nm) : name(nm) {}
};

struct Edge {
	double cost = 0.0;
	Vertex * dest = NULL;
	Edge(Vertex * d = NULL, double c = 0) : dest(d), cost(c) {}
};

class myGraph {
	private:
		typedef map<string,Vertex*,less<string> > vmap;
		vmap vertexList;
		Vertex * getVertex(string & name);

	public:
		myGraph();
		~myGraph();
		void addEdge(string & source, string & dest, double cost); 
		void distanceTable();
		void calculateDist();
		void tracePath(Vertex *v);
};

void myGraph::tracePath(Vertex *v) {

	if (v->prev != NULL) {
		tracePath(v->prev);
		cout << " to ";
	}

	cout << v->name;
}

void myGraph::calculateDist() {
	string sourceName;
	cout << "Enter source vertex: ";
	cin >> sourceName;

	vmap::iterator itr = vertexList.find(sourceName);
	if (itr == vertexList.end()) {
		cout << sourceName << " vertex not found" << endl;
		return;
	}

	list<Vertex*> q;
	itr->second->dist = 0;

	q.push_back(itr->second);

	while(!q.empty()) {
		Vertex *v = q.front();
		q.pop_front();

		for(auto e:v->adj_list) {
			if (e->dest->dist == INF) {
				e->dest->dist = v->dist + 1;
				e->dest->prev = v;
				q.push_back(e->dest);
			}
		}
	}	
}

void myGraph::distanceTable() {
	cout << endl << "distanceTable()" << endl;
	for(vmap::iterator itr = vertexList.begin(); itr != vertexList.end(); ++ itr) {
		cout << "Vertex name: " << itr->second->name;
		cout << " dist: " << itr->second->dist;
		if (itr->second->prev != NULL)
			cout << " prev: " << itr->second->prev->name << endl;
		else
			cout << endl;
	}
	cout << endl << endl;
}

Vertex * myGraph::getVertex(string & name) {
	vmap::iterator itr = vertexList.find(name);

	if (itr == vertexList.end()) {
		Vertex *new_vertex = new Vertex(name);
		vertexList[name] = new_vertex;
		return new_vertex;
	}

	return itr->second;
}

void myGraph::addEdge(string & source, string & dest, double cost) {
	Vertex * w = getVertex(source);
	Vertex * v = getVertex(dest);
	Edge * new_edge  = new Edge(v, cost);

	w->adj_list.push_back(new_edge);
}

myGraph::~myGraph() {
	distanceTable();

	for(vmap::iterator itr = vertexList.begin(); itr != vertexList.end(); ++ itr)
		delete itr->second;
}

myGraph::myGraph() {
	string source, destination; double cost;
	int noLines;
	cout << "How many lines of graph data? ";
	cin >> noLines;

	cout << "Enter graph data: " << endl;

	for(;noLines > 0; noLines--) {
		cin >> source >> destination >> cost;
		addEdge(source, destination, cost);
	}

	calculateDist();
	cout << "Trace path to: ";
	cin >> source;
	vmap::iterator itr = vertexList.find(source);
	tracePath(itr->second);
}

int main() {
	myGraph	g1;
	return 0;
}
