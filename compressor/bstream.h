#ifndef BSTREAM_CLASSES
#define BSTREAM_CLASSES

#include<fstream>
#include<iostream>
#include<vector>

using namespace std;

static const int BITS_PER_CHAR = 8;
static const int DIFF_CHARS = 256;

/*
 * ###########################
 * Helper functions
 * getBit(..)
 * setBit(..)
*/

int getBit(char pack, int pos) {
	return (pack & (1 << pos)) ?  1:0;
}

void setBit(char & pack, int pos, int val) {
	if (val == 1)
		pack |= (val << pos);
}


/* #############################
 * bit-at-a-time input stream
 *
*/

class ibstream {
	private:
		istream & in;
		char buffer;
		int bufferPos;
	public:
		ibstream(istream & is);
		int readBit();
		istream & getInputStream() const;
};

ibstream::ibstream(istream & is): bufferPos(BITS_PER_CHAR), in(is) {}

int ibstream::readBit() {

	if (bufferPos == BITS_PER_CHAR) { // buffer is full
		in.get(buffer); // get next set of buffer

		if (in.eof())
			return EOF;

		bufferPos = 0;
	}

	return getBit(buffer, bufferPos++);
}

istream & ibstream::getInputStream() const {
	return in;
}

/*
 * bit-at-a-time output stream
 *
*/
class obstream {
	private:
		ostream & out;
		char buffer;
		int bufferPos;
	public:
		obstream(ostream & os);
		~obstream();
		
		void writeBit(int val);
		void writeBits(const vector<int> & val);
		void flush();
		ostream & getOutputStream() const;
};

obstream::obstream(ostream & os) : bufferPos(0), buffer(0), out(os) {}
obstream::~obstream() {
	flush();
}

void obstream::flush() {
	if (bufferPos == 0)
		return;

	//flush old
	out.put(buffer);
	bufferPos = 0;
	buffer = 0;
}

void obstream::writeBit(int val) {
	setBit(buffer, bufferPos++, val);
	if (bufferPos == BITS_PER_CHAR)
		flush();
}

void obstream::writeBits(const vector<int> & val) {
	for (auto v:val)
		writeBit(v);
}

ostream & obstream::getOutputStream() const {
	return out;
}

#endif
