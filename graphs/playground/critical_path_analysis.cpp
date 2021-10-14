#include "../graph.h"
#define INF 2147483647

using namespace std;

struct Packet {
	vertex * member;
	Packet * prev;
	int E_START;
	int E_END;
	int duration;
	int L_START;
	int L_END;

	Packet(vertex *v, Packet *p, int d) : member(v), prev(p), duration(d) {
		E_START = 0;
		E_END = 0;
	}
};

class CP_Analysis : public myGraph {
	private:
		map<string, Packet*> dict;
		string start_point;	
		string end_point;
		void init_dict();
		void dfs_helperf_id(vertex * v);
	public:
		void readGraphData();
		void calculateCP();
};

void CP_Analysis::dfs_helperf_id(vertex * v) {
	for (auto E:v->adj) {
		//cout << "Adding edge: " << E.dest->name << endl;
		dict[E.dest->name] = new Packet(E.dest, dict.find(E.dest->name)->second, E.cost);
		dfs_helperf_id(E.dest);
	}

	if (v->adj.size() == 0)
		end_point = v->name;	
}

void CP_Analysis::calculateCP() {
	cout << "CP_Analysis::calculateCP():" << endl;

	cout << "Enter starting point: ";
	cin >> start_point;
	init_dict();
}

void CP_Analysis::init_dict() {

	auto itr = getVertexList().find(start_point);
	dict[itr->second->name] = new Packet(itr->second, NULL, 0);

	dfs_helperf_id(itr->second);
	
	for(auto itr = dict.begin(); itr != dict.end(); ++itr) {
		if (itr->second->prev != NULL) {
			if(itr->second->E_START > itr->second->prev->E_END)
				itr->second->E_START = itr->second->prev->E_END;	
			itr->second->E_END = itr->second->E_START + itr->second->duration;
		}	
	}

	for(auto itr = dict.begin(); itr != dict.end(); ++itr) {
		cout << "Vertex: " << itr->second->member->name;
		cout << " E_START: " << itr->second->E_START;
		cout << " E_END: " << itr->second->E_END;
		cout << endl;
	}
}

void CP_Analysis::readGraphData() {
	cout << "CP_Analysis::readGraphData():" << endl;

	string v1, v2;
	double cost;

	cout << "Enter graph data: " << endl;

	while (true) {

		cin >> v1;	
		if (v1 == "END")
			break;

		cin >> v2;
		if (v1 == "END")
			break;
		cin >> cost;

		addEdge(v1,v2,cost);
	}
}
int main() {
	CP_Analysis a1;
	a1.readGraphData();
	a1.calculateCP();
	return 0;
}
