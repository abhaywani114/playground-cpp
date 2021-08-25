#include<iostream>
#include<string>
#include<vector>
#include<utility>
#define V vector<int>

using namespace std;

class quickSelect {
	private:
		V arr;
	public:
		quickSelect(V &a, int k): arr(a) {
			printArray("Unsorted Array:");
			select(0, arr.size() - 1 , k);
			printArray("Partially sorted array");

			printf("%dth (k) element is %d\n", k, arr[k]);
			cout << endl << endl;
		}

		int patition(int start, int end) {
			int mid = (start + end) / 2;
			int pivot = arr[mid];

			swap(arr[end], arr[mid]);

			int last_swap = start;
			for(int i = start; i <= end-1;i++)
				if (arr[i] < pivot)
					swap(arr[i], arr[last_swap++]);
		
			swap(arr[end], arr[last_swap]);

			return last_swap;
		}

		void select(int start, int end, int k) {
			if (start >= end) return;
			int last_swap = patition(start, end);

			if (k < last_swap)
				select(start, last_swap-1, k);
			else if (k > last_swap)
				select(last_swap+1, end, k);
			
		}

		void printArray(string label) {
			cout << label << endl;
			for (auto i:arr)
				cout << "\t" << i;
			cout << endl;
		}

};

int main() {
	vector<pair<V,int > > test_case  {
		{{0,9,2,3,8,7,8,4,1,5},6},
		{{1,4,3},2}
	};

	for (auto i:test_case)
		quickSelect test_quick_select(i.first, i.second);

	return 0;
}
