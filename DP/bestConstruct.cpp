#include<iostream>
#include<ostream>
#include<map>
#include<vector>
#include<stdlib.h>
#include<string.h>

using namespace std;



bool canConstruct2(const string target, vector<char*>& arr) {
	vector<bool> tabu(target.size() + 1, false);

	tabu[0] = true;
	for (int i = 0; i < tabu.size(); i++) {
		if (tabu[i]) {
			string remainder = target.substr(i);
			for (int j = 0; j < arr.size(); j++) {
				if (!remainder.find(arr[j])) {
					tabu[i+ strlen(arr[j])] = true;
				}
			}
		}
	}
	return tabu[target.size()];
}


int _counter1 = 0;
bool canConstruct1(const string target, vector<char*>& arr, map<string, bool> &memo) {
	if (memo[target]) return memo[target];
	if (!target.size()) return true;
	for (int i = 0; i < arr.size(); i++) {
		if (!target.find(arr[i])) {
			string remainder = target.substr(strlen(arr[i]));
			if (canConstruct1(remainder, arr, memo)) {
				cout << "\n\t\tsaving " << remainder.c_str();
				memo.insert({remainder, true});
				return true;
			}
		}
	}
	memo.insert({target, false});
	return false;
}

int _counter = 0;
bool canConstruct(string& target, vector<char*>& arr) {
	if (!target.size()) return true;
	for (int i = 0; i < arr.size(); i++) {
		if (!target.find(arr[i])) {
			string remainder = target.substr(strlen(arr[i]));
			if (canConstruct(remainder, arr)) {
				return true;
			}
		}
	}
	return false;
}




int main() {
	string target{"abcdef"};
	vector<char*> arr;
	arr.push_back("abcd");
	arr.push_back("abcd");
	arr.push_back("abcd");
	arr.push_back("abcd");
	arr.push_back("abcd");
	arr.push_back("abcd");
	arr.push_back("cdef");
	arr.push_back("ef");
	arr.push_back("f");
	
	cout << "\nRS = " << canConstruct(target, arr);
	cout << "\nRS2 = " << canConstruct2(target, arr);
	map<string, bool> memo;
	cout << "\nRS1 = " << canConstruct1(target, arr, memo);
	return 0;
}
