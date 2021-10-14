#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<stack>
#include "../graph.h"

using namespace std;

class topologicalSort : public myGraph {
	private:
		stack<string> order;
		list<vertex *> orderedVertexList;
		map<string, bool, less<string> > isVisited;
		void dfs(vertex * v);
	public:
		void readGraph();
		void getTopologicalOrder();
		void findTopologicalDistance();
};

/*
 *
 * It works with acyslic graph and can detected a negetive cycle
 *
*/
void topologicalSort::findTopologicalDistance() {
	cout << "findTopologicalDistance():" << endl;
	string sourceVertex;	
	cout << "Enter starting vertex: " << endl;
	cin >> sourceVertex;	
	auto itr = getVertexList().find(sourceVertex);
	if (itr == getVertexList().end())
		throw GraphException("Vertex not found");

	itr->second->dist = 0;
	auto iterationCount = 0;
	for	(;!orderedVertexList.empty();iterationCount++) {

		vertex * v = orderedVertexList.back();
		orderedVertexList.pop_back();

		if (v->dist == INFINITY)
			continue;	

		for (auto E:v->adj) {
			int new_distance = v->dist + E.cost;
			if (new_distance < E.dest->dist) {
				if (E.dest->name == sourceVertex)
					throw GraphException("Negetive cycle detectd");
				E.dest->dist = new_distance;
				E.dest->prev = v;
			}
		}
	}

	cout << "iterationCount: " << iterationCount << endl;
}

void topologicalSort::dfs(vertex * v) {
	isVisited[v->name] = true;

	for (auto E:v->adj) {
		if (!isVisited[E.dest->name]) {
			dfs(E.dest);
		}
	}

	order.push(v->name);
	orderedVertexList.push_back(v);
}

void topologicalSort::getTopologicalOrder() {
	cout << "getTopologicalOrder():" << endl;
	for (auto itr = getVertexList().begin(); itr != getVertexList().end(); ++itr) {
		if (isVisited[itr->second->name] == false)
			dfs(itr->second);		
	}	

	while (!order.empty()) {
		cout << order.top() << "\t";
		order.pop();
	}
	cout << endl;
}

void topologicalSort::readGraph() {
	cout << "readGraph()" << endl;

	string v1, v2;
	double cost;

	cout << "Enter graph data:" << endl;	

	while (true) {
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

int main() {
	topologicalSort s1;
	s1.readGraph();
	s1.getTopologicalOrder();
	s1.findTopologicalDistance();
	s1.printDistanceTable();
	return 0;
}
