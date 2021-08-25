#include<iostream>
#include<string>
#include<vector>
#define VEC vector<int>

using namespace std;

class quick_sort {
	private:
		VEC arr;
	public:
		quick_sort(VEC &a) : arr(a) {
			printArray("Unsorted array: ");
			sort(0, arr.size() - 1);
			printArray("Sorted array: ");
		}

		int partition(int start, int end) {
			int middle = (start+end)/2;
			int pivot = arr[middle];

			swap(arr[middle], arr[end]);		
		
			int last_swap = start;

			for(int i = start; i < end; i++)
				if (arr[i] < pivot)
					swap(arr[i], arr[last_swap++]); 

			swap(arr[end], arr[last_swap]);
	
			return last_swap;
		}

		void sort(int start, int end) {
			if (start >= end) return;
			int last_swap = partition(start, end);

			sort(start, last_swap -1);
			sort(last_swap+1, end);
		}

		void printArray(string label) {
			cout << label << endl;
			for(auto i:arr)
				cout << "\t" << i;
			cout << endl;
		}

};

int main() {
	vector<vector<int> > test_sorting {
		{9,3,5,1,2,0},
		{2,4,6,1,99,24},
		{10,7,2,12,6,2,3,2,8},
		{1},
		{}
	};

	for (auto i:test_sorting) {
		quick_sort test_quick_sort(i);
		cout << endl << endl;
	}

	return 0;
}
