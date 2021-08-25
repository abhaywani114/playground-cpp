#include<iostream>
#include<vector>
#include<string>
#define vec vector<int>

using namespace std;

class mergeSort {
	private:
		vec arr;

	public:
		mergeSort(vec &a) : arr(a) {
			printArray("Unsorted:", arr);

			arr = sort(arr);

			printArray("Sorted:", arr);
		}

		vec sort(vec &a) {
			//base case
			if (a.size() <= 1) return a;
		
			int mid = a.size() / 2;

			//divide
			vec left = divide_array(0, mid, a);
			vec right = divide_array(mid, a.size(), a);
	
			// opration
			left = sort(left);
			right = sort(right);

			//conqure
			return merge(left, right);
		}
		
		vec divide_array(int start, int end, vec &arr) {
			vec new_array;

			for (int i  = start; i < end; i++)
				new_array.push_back(arr[i]);

			return new_array;
		}

		vec merge(vec a, vec b) {
			vec sorted_array;
			int i = 0, j = 0;

			while( i < a.size() && j < b.size()) {
				if (a[i] < b[j]) {
					sorted_array.push_back(a[i]);
					i++;
				} else {
					sorted_array.push_back(b[j]);
					j++;
				}
			}

			while( i < a.size()) {
				sorted_array.push_back(a[i]);
				i++;
			}

			while(j < a.size()) {
				sorted_array.push_back(b[j]);
				j++;
			}

			return sorted_array;

		}
	
		void printArray(string ch, vec &a) {
			cout << ch << endl;
	
			for (auto i:a)
				cout << "\t" << i;
	
			cout << endl;
		}

};

int main() {
	vec list = {32,4,1,28,3,23};
	mergeSort s1(list);
	return 0;
}
