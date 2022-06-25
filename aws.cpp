#include<iostream>
#include<ostream>
#include<vector>

using namespace std;

// runtime O(n), space O(1)
int findMissingNo1(vector<int> &arr, int n) {
	int expected = 1;
	
	for (int i = 2; i <= n; i++) {
		expected += i;
		expected -= arr[i-2];
	}
	return expected;
}

// runtime O(n), space O(1)
int findMissingNo(vector<int> &arr, int n) {
	int expected = (n * (n +1)) / 2;
	
	for (auto it = arr.begin(); it != arr.end(); it++) {
		expected -= *it;
	}
	return expected;
}

int main() {
	vector<int> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(5);
	arr.push_back(6);
	arr.push_back(7);
	arr.push_back(8);
	
	cout << "findMissingNo(8) " << findMissingNo(arr, 8) << "\n";
	cout << "findMissingNo1(8) " << findMissingNo1(arr, 8) << "\n";
	return 0;
}
