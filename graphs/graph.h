#ifndef GRAPH_CLASS
	#define GRAPH_CLASS
	#include<iostream>
	#include<string>
	#include<vector>
	#include<map>
	#include<climits>
	#include<exception>
	#include<list>
	
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

#endif
