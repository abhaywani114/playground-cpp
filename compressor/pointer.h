#include<iostream>
#include<string>
#include<vector>
using namespace std;

template<typename C>
class Pointer {
	private:
		C *ptr;
	public:
		Pointer(C *rhs = NULL) : ptr(rhs) {}
		bool operator<(const C &rhs) const { return *ptr < *rhs.ptr;}
		bool operator>(const C &rhs) const { return *ptr > *rhs.ptr;}
		bool operator==(const C &rhs) const { return *ptr == *rhs.ptr;}
		operator C *() const {return ptr;}
		C *get() const {return ptr;}	
};

