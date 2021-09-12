#ifndef HUFF_MAN_TREE_CLASS
#define HUFF_MAN_TREE_CLASS

#include<map>
#include<vector>
#include<iostream>
#include<algorithm>
#include<queue>
#include "charcounter.h"
#include "bstream.h"
#include "pointer.h"

using namespace std;

struct HuffNode {
	int value;
	int weight;

	HuffNode * left;
	HuffNode * right;
	HuffNode * parent;

	HuffNode(int v, int w, HuffNode *l, HuffNode *r, HuffNode * p) :
		value(v), weight(w), left(l), right(r), parent(p) {}
};

class HuffmanTree {
	private:
		charCounter theCounts;
		map<int, HuffNode *, less<int> > theNodes;
		HuffNode *root;

		void createTree();

	public:
		HuffmanTree();
		HuffmanTree(const charCounter & cc);
		enum {ERROR = -3, INCOMPLETE_CODE = -2, END = -1};
		vector<int> getCode(int ch) const;
		int getChar(vector<int> & code) const;
		
		void writeEncodingTable(ostream & out);
		void readEncodingTable(istream & in);
};

HuffmanTree::HuffmanTree(const charCounter & cc) : theCounts(cc) {
	root = NULL;
	
	createTree();
}

HuffmanTree::HuffmanTree() {
	root = NULL;
}

vector<int> HuffmanTree::getCode(int ch) const {

	//vector to be returned as code for ch
	vector<int> v;

	//  Search ch in the map theNodes
	map<int, HuffNode *, less<int> >::const_iterator itr;
	itr = theNodes.find(ch);
	
	// if not found
	if (itr == theNodes.end())
		return v;

	// get current node corespondig to ch
	HuffNode *current = (*itr).second;
	
	// get parent code coresponding to ch's node
	HuffNode *par = current->parent;

	// generate the ch code in reverse order	
	while(par != NULL) {
		if (par->left == current)
			v.push_back(0);
		else
			v.push_back(1);

		current = par;
		par = par->parent;
	}
	
	//fix order and return;
	reverse(v.begin(), v.end());
	return v;
}

int HuffmanTree::getChar(vector<int> & code) const {
	HuffNode *p = root;

	for (auto c:code) {
		if (p != NULL) {
			if (c == 0)
				p = p->left;
			else if (c == 1)
				p = p->right;
		}
	}

	return p == NULL ? ERROR:p->value;
}


void HuffmanTree::writeEncodingTable(ostream & out) {
	for (int i = 0; i < DIFF_CHARS; i++) {
		if (theCounts.getCount(i) > 0)
			out << static_cast<char>(i) << theCounts.getCount(i) << '\n';
	}	

	out << '\0' << 0 << '\n';
}

void HuffmanTree::readEncodingTable(istream & in) {
	for (int i = 0; i < DIFF_CHARS; i++)
		theCounts.setCount(i,0);
	
	char ch, nl;
	int num;

	while(true) {
		in.get(ch);
		in >> num;
		in.get(nl);

		if (num == 0)
			break;

		theCounts.setCount(ch, num);
	}

	createTree();
}

bool operator< (const HuffNode &lhs, const HuffNode &rhs) {
		return lhs.weight < rhs.weight;
}

void HuffmanTree::createTree() { 
	priority_queue<Pointer<HuffNode>, vector<Pointer<HuffNode> >, less<Pointer<HuffNode>  > > pq;
	
	//generate Huffman forest	
	for (int i = 0; i < DIFF_CHARS; i++) {
		if (theCounts.getCount(i) > 0 )  {
			HuffNode * newNode = new HuffNode(i, theCounts.getCount(i), NULL, NULL, NULL);
			theNodes[i] = newNode;
			pq.push(Pointer<HuffNode> (newNode) );
		}
	}
	
	// end node
	theNodes[END] = new HuffNode(END, 1, NULL, NULL, NULL);
	pq.push(Pointer<HuffNode>(theNodes[END]));

	// build unfied tree
	while(pq.size() > 1) {
		HuffNode * n1 = pq.top(); pq.pop();
		HuffNode * n2 = pq.top(); pq.pop();

		HuffNode * result = new HuffNode(INCOMPLETE_CODE, n1->weight + n2->weight, n1, n2, NULL);
		n1->parent = n2->parent = result;
		pq.push(result);
	}

	root = pq.top();
}
#endif

