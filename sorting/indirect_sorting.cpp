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

template<typename C>
class inDirectSorting {
	private:
		vector<int> arr;
		vector<Pointer<int> > arr_ptr;
	public:
		inDirectSorting(vector<int> &a) : arr(a) {
			arr_ptr.resize(arr.size());
			for(int i = 0; i < arr.size(); i++)
				arr_ptr[i] = &arr[i];

			sort(0, arr_ptr.size()-1);

			cout << "Unsorted: " << endl;
			for(auto i:arr)
				cout << "\t" << i;
			cout << endl;

			cout << "Sorted: " << endl;
			for(auto i:arr_ptr)
				cout << "\t" << *i;
			cout << endl;
			
			reposition_array();

			cout << "Main array: " << endl;
			for(auto i:arr)
				cout << "\t" << i;
			cout << endl;


		}

	void reposition_array() {
		cout << "reposition_array()" << endl;
		int next_j,j;
		for(int i = 0; i < arr.size(); i++) {
			if (arr[i] != *arr_ptr[i]) {
				C temp = arr[i];
				for(j = i; arr_ptr[j] != &arr[i]; j = next_j) {
						next_j = arr_ptr[j] - &arr[0]; 
						arr[j] = *arr_ptr[j];
						arr_ptr[j] = &arr[j];
				}					
				arr[j] = temp;
				arr_ptr[j] = &arr[j];
			}
		}
	}

	int patition(int start, int end) {
		int middle = (start  + end) / 2;
		int pivot = *arr_ptr[middle];

		swap(arr_ptr[middle], arr_ptr[end]);

		int last_swap = start;
		for (int i = start; i < end; i++) {
			if (*arr_ptr[i] < pivot)
				swap(arr_ptr[i], arr_ptr[last_swap++]);
		}

		swap(arr_ptr[last_swap], arr_ptr[end]);

		return last_swap;	
	}
	void sort(int start, int end) {
		if (start >= end) return;
		int last_swap = patition(start, end);
		sort(start, last_swap - 1);
		sort(last_swap + 1, end);
	}

};
int main() {
	vector<int> a = {1,5,4,3,2};
	inDirectSorting<int> p(a);
	return 0;
}
