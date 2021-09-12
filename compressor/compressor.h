#ifndef COMPRESSOR_CLASS
#define COMPRESSOR_CLASS

#include<string>
#include<iostream>
#include<fstream>
#include "huffman.h"
#include "charcounter.h"

using namespace std;
class Compressor {
	private:
		static const int READ_MODE;
		static const int WRITE_MODE;

	public:
		static void compress(const string &inFile);
		static void uncompress(const string &compressedFile);
};

#define READ_MODE ios::in | ios::binary
#define WRITE_MODE ios::out | ios::binary

void Compressor::compress(const string &inFile) {
	// compressed file name
	string compressedFile = inFile + ".huf";
	
	//open file in READ_MODE
	ifstream in(inFile.c_str(), READ_MODE);
	
	if (!in) {
		cerr << "unable to open the file" << endl;
		return;
	}
	
	// count char
	charCounter countObj(in);

	// build huffmanTree
	HuffmanTree codeTree(countObj);
	
	ofstream out(compressedFile.c_str(), WRITE_MODE);
	codeTree.writeEncodingTable(out);

	in.clear();
	in.seekg(0, ios::beg);
	obstream bout(out);

	char ch;
	while( in.get(ch))
		bout.writeBits(codeTree.getCode(ch & 0xff));

	bout.writeBits(codeTree.getCode(EOF));


}

void Compressor::uncompress(const string &compressedFile) {
	int i;
	string inFile, extension;
	// PARSE THE FILE NAME WITH OUT EXTENTION
	for(i = 0; i < compressedFile.length() - 4; i++)
		inFile += compressedFile[i];

	for(;i< compressedFile.length(); i++)
		extension += compressedFile[i];	

	if (extension != ".huf") {
			cerr << "Invalid compressed file" << endl;
			return;
	}

	inFile = "mz_" + inFile; //ilysm

	ifstream in(compressedFile.c_str(), READ_MODE);

	if (!in) {
		cerr << "unable to open the file" << endl;
		return;
	}

	ofstream out(inFile.c_str(), WRITE_MODE);

	HuffmanTree codeTree;
	codeTree.readEncodingTable(in);

	ibstream bin(in);
	vector<int> bits;
	int bit, decode;

	while (true) {
		// read bit
		bit = bin.readBit();
		bits.push_back(bit);
		decode = codeTree.getChar(bits);

		if (decode == HuffmanTree::INCOMPLETE_CODE)
			continue;
		else if (decode == HuffmanTree::ERROR) {
			cerr << "error occured while decoding" << endl;
			return;
		}
		else if (decode == HuffmanTree::END)
			break;
		else {
			out.put(static_cast<char>(decode));
			bits.resize(0);
		}
	}
}
#endif
