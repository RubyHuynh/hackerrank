#include<iostream>
#include<ostream>
#include<map>
#include<vector>
#include<stdlib.h>
#include<string.h>

using namespace std;


vector<char*>* howConstruct2(const string target, vector<char*>& arr) {
	vector<char*>* tabu[target.size() + 1];
	memset(tabu, 0, sizeof(tabu));
	tabu[0] = new vector<char*>{};

	for (int i = 0; i < target.size()  + 1; i++) {
		if (tabu[i]) {
			for (int j = 0; j < arr.size(); j++) {
				if (!((target.substr(i)).find(arr[j]))
					&& (i + strlen(arr[j])) <= target.size()) {
					tabu[i+strlen(arr[j])] = new vector<char*>(*tabu[i]);
					tabu[i+strlen(arr[j])]->push_back(arr[j]);
				}
			}
		}
	}
	return tabu[target.size()];
}

vector<char*>* howConstruct1(const string target, vector<char*>& arr, map<string,vector<char*>*>& memo) {
	vector<char*>* rs = NULL;
	if (memo[target]) return memo[target];
	if (!target.size()) return new vector<char*>;
	for (int i = 0; i < arr.size(); i++) {
		if (!target.find(arr[i])) {
			string remainder = target.substr(strlen(arr[i]));
			if ((rs = howConstruct1(remainder, arr, memo))) {
				rs->insert(rs->begin(), arr[i]);
			}
		}
	}
	memo.insert({target, rs});
	return rs;
}


vector<char*>* howConstruct(const string target, vector<char*>& arr) {	
	vector<char*>* rs = NULL;
	if (!target.size()) return new vector<char*>;
	for (int i = 0; i < arr.size(); i++) {
		if (!target.find(arr[i])) {
			string remainder = target.substr(strlen(arr[i]));
			if ((rs = howConstruct(remainder, arr))) {
				rs->insert(rs->begin(), arr[i]);
			}
		}
	}
	return rs;
}

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
	
	{
		cout << "\n\nHOW = ";
		auto howdy = howConstruct(target, arr);
		for (auto it = howdy->begin(); it != howdy->end(); it++) {
			cout << *it << " ";
		}

		cout << "\n\nHOW = ";
		map<string, vector<char*>*> memo;
		auto howdy1 = howConstruct1(target, arr, memo);
		for (auto it = howdy1->begin(); it != howdy1->end(); it++) {
			cout << *it << " ";
		}
		
		cout << "\n\nHOW = ";
		auto howdy2 = howConstruct2(target, arr);
		for (auto it = howdy2->begin(); it != howdy2->end(); it++) {
			cout << *it << " ";
		}
	}	
	return 0;
}
