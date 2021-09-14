#include "graph.h"
#include<fstream>
#include<sstream>

using namespace std;

bool processRequest(istream & in, myGraph & g) {
	cout << endl << endl;
	string startName, destName;
	
	cout << "Enter start node: ";
	if (!(in >> startName))
		return false;

	cout << "Enter destination node: ";
	if (!(in >> destName))
		return false;

	try {
		g.negative(startName);
		//g.unweighted(startName);
		//g.dijkstra(startName);
		g.printDistanceTable();
		g.printPath(destName);
	} catch (const GraphException & e) {
		cerr << "Error: " << e.getError() << endl;
	}

	return true;
	
}

int main(int argc, char *argv[]) {

	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " graphfile" << endl;
		return 1;
	}	

	ifstream inFile(argv[1]);
	if (!inFile) {
		 cerr << "Cannot open " << argv[1] << endl;
		return 1;
	}

	cout << "Reading graph file..." << endl;

	//Reading file producure 
	string oneLine;
	
	myGraph g;
	while(!getline(inFile, oneLine).eof()) {
		cout << oneLine << endl;
		string source, dest;
		double cost;

		istringstream st(oneLine);

		st >> source;
		st >> dest;
		st >> cost;

		if (st.fail())
			cerr << "Bad line: " << oneLine << endl;
		else
			g.addEdge(source, dest, cost);
	}
	
	cout << "Reading graph file... Done" << endl << endl;

	while(processRequest(cin, g));
	
	return 0;
}
