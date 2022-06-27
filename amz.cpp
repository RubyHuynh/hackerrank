#include<iostream>
#include<ostream>
#include<vector>
#include<list>
#include<unordered_map>

using namespace std;


struct Node {
	int val;
	Node *tail;
	Node *next;
	Node *arbitrary;
	Node(int v) : val(v), next(NULL), arbitrary(NULL), tail (NULL) {};
	Node* add(int v) {
		Node *item = new Node(v);
		item->arbitrary = this->next;
		item->next = this;
		return item;
	}

	Node* add(Node* n) {
		Node* item = new Node(n->val);
		item->arbitrary = n->arbitrary;
		item->next = this;
		return item;
	}
};

// TODO reverse
// O(n)
Node* deepCopy(Node *list) {
	Node *rs = NULL;
	Node *tmp = list;
	Node *newItem;
	int i = 0;
	unordered_map<Node*, Node*> pos;

	while (tmp) {
		cout << tmp->val << " (" << tmp->arbitrary  << ") ";
		if (!rs) {
			newItem = rs = new Node(tmp->val);
		}
		else {
			newItem = rs->add(tmp);
			rs = newItem;
		}
		newItem->arbitrary = tmp->arbitrary;
		pos[tmp] = newItem;
		tmp = tmp->next;
	}

	// remapping arbitrary
	tmp = rs;
	while (tmp) {
		if (tmp->arbitrary) {
			tmp->arbitrary = pos[tmp->arbitrary];
		}
		tmp = tmp->next;
	}
	return rs;
}



// runtime O(m+n), space O(m+n)
list<int>* merge2Lists(std::list<int>* l1, list<int>* l2) {
	if (!l1->size()) return l2;
	if (!l2->size()) return l1;
	auto i1 = l1->begin();
	auto i2 = l2->begin();
	list<int>* rs = new list<int>();

	while (i1 != l1->end() || i2 != l2->end()) {
		if (i1 != l1->end() && i2 != l2->end()) {
			if (*i1 < *i2) {
				rs->push_back(*i1);
				i1++;
			} 
			else {
				rs->push_back(*i2);
				i2++;
			}
		}
		else if (i1 != l1->end()) {
			rs->push_back(*i1);
			i1++;
		}
		else {
			rs->push_back(*i2);
			i2++;
		}
	}
	return rs;
}


bool sumTwo(vector<int> &arr, int n) {
	unordered_map<int, int> map;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] == map[n - arr[i]]) {
			cout << "\t "<< arr[i] << "+" << n -arr[i] << "\n";
			return true;
		}
		map[arr[i]] =  n - arr[i];
	}
	return false;
}

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
	cout << "sumTwo(9) " << sumTwo(arr, 9) << "\n";

	list<int> l1{4,8,15,19};
	list<int> l2{7, 9, 10, 16};
	cout << "merge2Lists\n";
	auto merged = merge2Lists(&l1, &l2);
	auto it = merged->begin();
	while (it != merged->end()) {
		cout << *it << ", ";
		it++;
	}
	
	//
	cout << "deepCopy arbitrary list\n";
	Node* node1 = new Node(1);
	node1 = node1->add(2);
	node1 = node1->add(3);
	Node* cloned = deepCopy(node1);
	cout << "\n";
	while (cloned) {
		cout << cloned->val << " (" << cloned->arbitrary  << ") ";
		cloned = cloned->next;
	}
	return 0;
}
