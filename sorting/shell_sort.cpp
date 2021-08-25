#include<iostream>
#include<vector>
using namespace std;

//#define debug 1

void printArray(vector<int> &a);

void shellSort(vector<int> &a) {
	// when gap is 1 then it becomes normal insertion sort.
	for(int gap = a.size()/2; gap > 0; gap/=2) {
		for (int i = gap; i < a.size(); i+=gap) {
			int key = a[i], j = i;
			
			#ifdef debug
				printf("gap: %d, i:%d, a[j-gap]: %d, a[j]: %d,\n", gap, i, a[j-gap], a[j]);
			#endif

			for (;j >= gap && a[j-gap] > key; j -= gap) {
				a[j] = a[j-gap];
			}
			a[j] = key;
		}

	}
}

void printArray (vector<int> &arr) {
	for(auto i:arr)
		cout << "\t" << i;
	cout << endl;
}
int main() {
	vector<int> a = {1,2,9,10,5,3,6};

	cout << "Before sorted:"<<endl;
	printArray(a);

	shellSort(a);
	cout << "After sorted:"<<endl;
	printArray(a);

	return 0;
}
