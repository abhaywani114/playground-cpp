#ifndef GRAPH_CLASS
	#define GRAPH_CLASS
	#include<iostream>
	#include<string>
	#include<vector>
	#include<map>
	#include<climits>
	#include<exception>
	#include<list>
	#include<queue>
	
	#define INFINITY 2.3e100
	using namespace std;
		
	struct vertex;
	struct Edge {
		vertex *dest;
		double cost;
		Edge(vertex *d = NULL, double c = 0.0) : dest(d), cost(c) {}
	};

	struct vertex {
		string 	name;
		vector<Edge> adj;

		double dist;
		vertex *prev;
		
		int scratch;

		vertex (const string & nm) : name(nm) { reset(); }
		void reset() {
			dist = INFINITY;
			prev = NULL;
			scratch = 0;
		}
	};

	// A custom exceptional class	
	class GraphException : exception {
		private:
			string error_msg;
		public:
			GraphException(const string & error) : error_msg(error) {
			}

			const string & getError() const {
				return error_msg;
			}
	};

	class myGraph {
		private:
			// vmap will store vertex list
			typedef map<string, vertex *, less<string> > vmap;
			vmap vertexMap;

			vertex *getVertex(const string & vertexName);
			void printPath(const vertex & dest) const;
			void clearAll();
			
		public:
			myGraph (); 
			~myGraph();
			
			void addEdge(const string & sourceName, const string & destName, double cost);
			void printPath(const string & destName) const;
			
			void unweighted(const string & startName);
			void dijkstra(const string & startName);
			void negative(const string & startName);
			void acyclic(const string & startName);
			vmap & getVertexList() { return vertexMap;}

			void printDistanceTable() {
				cout << endl << "printDistanceTable():" << endl ;
				for(vmap::iterator itr = vertexMap.begin(); itr != vertexMap.end(); ++itr) {
						cout << "Vertex: " << (*itr).second->name;
						cout << " dist: " << (*itr).second->dist;
						if (itr->second->prev != NULL)
							cout << " prev_node: " << ((*itr).second->prev)->name << "\n";
						else
							cout << endl;
				}

				cout << endl << endl;
			}

			// disable sym copy
			 myGraph( const myGraph & rhs ) {}
			const myGraph & operator= ( const myGraph & rhs )
				{return *this;}

	};
	myGraph::myGraph() {}

	//destructor
	myGraph::~myGraph() {
		
		for(vmap::iterator itr = vertexMap.begin(); itr != vertexMap.end(); ++itr)
			delete (*itr).second;
	}


	// Query for a vertex name, if not found add it.
	vertex * myGraph::getVertex(const string & vertexName) {
		//Query map
		vmap::iterator itr = vertexMap.find(vertexName);

		//not found
		if (itr == vertexMap.end()) {
			vertex *new_vertex = new vertex(vertexName);
			vertexMap[vertexName]  = new_vertex;
			return new_vertex;
		}

		return (*itr).second;
	}

	// addEdge to the source v vertex.
	void myGraph::addEdge(const string & sourceName, const string & destName, double cost) {
		vertex * v = getVertex(sourceName);
		vertex * w = getVertex(destName);
		v->adj.push_back(Edge(w,cost));
	}

	// reset all the calculation piror to running any shortest path algorithm
	void myGraph::clearAll() {
		for(vmap::iterator itr = vertexMap.begin(); itr != vertexMap.end(); ++itr)
			(*itr).second->reset();
	}

	// print path recursively
	void myGraph::printPath(const vertex & dest) const {
		if (dest.prev != NULL) {
			printPath(*dest.prev);
			cout << " to " ;
		}
		cout << dest.name;
	}

	// drive to print path and handle infinite and unknown dest
	void myGraph::printPath(const string & destName) const {
		vmap::const_iterator itr = vertexMap.find(destName);

		if (itr == vertexMap.end())
			throw GraphException("Destination vertex not found");
		else if ((*itr).second->dist == INFINITY)
			throw GraphException("Destination not reachable");
		else {
			cout << "The cost to reach " << (*itr).second->name << " : " << (*itr).second->dist << endl;
			printPath(*(*itr).second);
		}

	}

	// Unweighted graph		
	void myGraph::unweighted(const string & startName) {
		vmap::iterator itr = vertexMap.find(startName);

		if (itr == vertexMap.end())
			throw GraphException("Starting node not found");

		clearAll();
		list<vertex *> q;

		vertex *start = (*itr).second;
		start->dist = 0;
		q.push_back(start);
		
		while(!q.empty()) {
			vertex *v = q.front();
			q.pop_front();

			for(auto e:v->adj) {
				vertex *w = e.dest;
				if (w->dist == INFINITY) {
					w->dist = v->dist + 1;
					w->prev = v;
					q.push_back(w);
				}
			}
		}		
	}

	// weighted non-negetive graph:
	void myGraph::dijkstra(const string & startName) {
		// struct for PQ
		struct Path {
			vertex *dest; // w
			double cost; // d(w)
	
			Path (vertex * d = NULL, double c = 0.0) : dest(d), cost(c) {}
		
			//comparision operators
			bool operator> (const Path & rhs) const { return cost > rhs.cost;}
			bool operator< (const Path & rhs) const { return cost < rhs.cost;}
		};

		//init PQ
		priority_queue<Path, vector<Path>, greater<Path> > pq;
		Path vrec;

		// get the source vertex
		vmap::iterator itr = vertexMap.find(startName);
		if (itr == vertexMap.end())
			throw GraphException("Source vertex not found");

		// reset
		clearAll();
		
		vertex *start = itr->second;
		itr->second->dist = 0;
		pq.push(Path(start, 0));
		
		int seenNode = 0;	
		for(; seenNode < vertexMap.size(); seenNode++) {

			//find an unvisited node
			do {
				if (pq.empty())
					return;

				vrec  = pq.top();
				pq.pop();

			} while (vrec.dest->scratch != 0);

			// Set flag as visited
			vertex *v = vrec.dest;
			v->scratch = 1;

			for(auto E:v->adj) {
				
				if (E.cost < 0)
					throw GraphException("Negetive cost found.");

				if (E.dest->dist > v->dist + E.cost) {
					E.dest->dist = v->dist + E.cost;
					E.dest->prev = v;
					pq.push(Path(E.dest, E.dest->dist));
				}
			}
		}
	}

void myGraph::negative(const string & startName) {
	auto itr = vertexMap.find(startName);
	if (itr == vertexMap.end())
		throw GraphException("Vertex not found");

	clearAll();
	list<vertex *> q;

	vertex *start = itr->second;
	start->dist = 0;
	start->scratch++;
	q.push_back(start);

	while(!q.empty()) {
		vertex *v = q.front();
		q.pop_front();

		if (v->scratch++ > vertexMap.size() + 1 )
			throw GraphException("Negetive cycle detected");

		for(auto E:v->adj) {
			vertex *w = E.dest;
			double cvw = E.cost;	
			if (w->dist > v->dist + cvw) {
				w->dist = v->dist + cvw;
				w->prev = v;
				if (w->scratch++ % 2 == 0)
					q.push_back(w);
				else
					w->scratch++;
			}
		}
	}
}

void myGraph::acyclic(const string & startName) {
	auto itr = vertexMap.find(startName);
	if (itr == vertexMap.end())
		throw GraphException("Vertex not found");

	clearAll();
	vertex * start = itr->second;
	start->dist = 0;
	list<vertex *> q;

	// calculate in degree
	for(itr = vertexMap.begin(); itr != vertexMap.end(); ++itr) {
		vertex * v = itr->second;
		for(auto i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->scratch++;
		}
	}

	// enqueue vertex with 0 degree	
	for(itr = vertexMap.begin(); itr != vertexMap.end(); ++itr) {
		vertex * v = itr->second;
		cout << "Vertex: " << v->name  << " scratch " << v->scratch << endl;
		if (v->scratch == 0) {
			q.push_back(v);
			cout << "Enqueue: " << v->name << endl;
		}
	}
	cout << endl << endl;
	// run main algorithm
	int iteration;
	for(iteration = 0; !q.empty(); iteration++) {
		vertex *v = q.front(); q.pop_front();
		for(int i = 0; i < v->adj.size(); i++) {
			Edge e = v->adj[i];
			vertex * w = e.dest;
				w->scratch--;
			if (w->scratch == 0) {
				cout << "Enqueue: " << w->name  << " scratch " << w->scratch << endl;
				q.push_back(w);
			}

			if (v->dist == INFINITY)
				continue;

			double cvw =  e.cost;
			if (w->dist > v->dist + cvw) {
				w->dist = v->dist + cvw;
				w->prev = v;
			}
		}
	}

	if (iteration != vertexMap.size())
		throw GraphException("Negetive cycle detectted");
}

#endif
