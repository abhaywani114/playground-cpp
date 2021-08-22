#include<iostream>
#include<vector>
using namespace std;

void insertionSort(vector<int> &arr) {
	for (int i = 0; i < arr.size(); i++) {
		int key = arr[i], j = 0;

		//assuming arr upto i-th element is sorted
		//cheking if j-1 element is greater than the key, if so them copy it to j element
		//after reaching the end of ">" set the j-1 element to key
		//
		//EX: 10,2,4,12
		//10,2,4,12 KEY:10
		//10,10,4,12 Key:2
		//Yeild: 2,10,4,12
		//

		for(j = i; j > 0 && arr[j-1] > key; j--) {
			arr[j] = arr[j-1]; //copy the j-1th element to jth element
		}

		arr[j] = key; //set j-1 th element.
	}
}
void printArray(vector<int> &arr) {
	for(auto i:arr)
		cout << "\t" << i;
	cout << endl;
}

int main() {
	vector<int> arr = {10,2,4,12,34,6,8};

	cout << "Unsorted array:" << endl;
	printArray(arr);
	
	insertionSort(arr);
	cout << "Sorted array: " << endl;
	printArray(arr);	
	return 0;
}
