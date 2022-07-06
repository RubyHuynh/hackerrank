#include<iostream>
#include<ostream>
#include<vector>
#include<list>
#include<unordered_map>
#include<queue>
#include<limits.h>
#include<algorithm>
#include<string.h>
#include<math.h>

using namespace std;

// 11. Find all subsets of a given set of integers
void  subset(std::vector<int> &arr) {
	unsigned int n = pow(2, arr.size());

	for (int i = 0; i < n ; i++) {
		std::cout <<"\n";
		for (int j = 0; j < arr.size(); j++) {
			if (i & (1<<j)) {
				std::cout << "," << arr[j];
			}
		}
	}
}


// 10. Find Kth permutation
// O(n^2), O(n)
std::string getKPermutation(int n, int k) {
	int fact = 1;
	vector<int> numbers;
	std::cout << "\n " << __func__ << " n = " << n  << " k =  " << k;	
	for (int i = 1; i < n; i++) {
		std::cout<< " " << i;
		fact *= i;
		numbers.emplace_back(i);
	}
	std::cout << "\n\t factorial of " << n-1 << " is " << fact;	
	numbers.emplace_back(n);
	std::string rs("");
	k -= 1;
	
	while (1) {
		std::cout << "\n\t fact is " << fact;
		std::cout << "\n\t k is " << k;
		std::cout << "\n\t sz is " << numbers.size();
		std::cout << "\n\t saving at index " << k/fact;
		rs += std::to_string(numbers[k/fact]);
		numbers.erase(numbers.begin() + k/fact);
		if (!numbers.size()) {
			break;
		}
		k %= fact;
		fact /= numbers.size();
	}
	std::cout << "\n\t result is " << rs;
	return rs;

}

/*
// Function to find the index of number
// at first position of
// kth sequence of set of size n
int findFirstNumIndex(int& k, int n)
{
 
    if (n == 1)
        return 0;
    n--;
 
    int first_num_index;
    // n_actual_fact = n!
    int n_partial_fact = n;
 
    while (k >= n_partial_fact
           && n > 1) {
        n_partial_fact
            = n_partial_fact
              * (n - 1);
        n--;
    }
 
    // First position of the
    // kth sequence will be
    // occupied by the number present
    // at index = k / (n-1)!
    first_num_index = k / n_partial_fact;
 
    k = k % n_partial_fact;
 
    return first_num_index;
}
 
// Function to find the
// kth permutation of n numbers
string findKthPermutation(int n, int k)
{
    // Store final answer
    string ans = "";
 
    set<int> s;
 
    // Insert all natural number
    // upto n in set
    for (int i = 1; i <= n; i++)
        s.insert(i);
 
    set<int>::iterator itr;
 
    // Mark the first position
    itr = s.begin();
 
    // subtract 1 to get 0 based indexing
    k = k - 1;
 
    for (int i = 0; i < n; i++) {
 
        int index
            = findFirstNumIndex(k, n - i);
 
        advance(itr, index);
 
        // itr now points to the
        // number at index in set s
        ans += (to_string(*itr));
 
        // remove current number from the set
        s.erase(itr);
 
        itr = s.begin();
    }
    return ans;
}
*/

// 9. How many ways can you make change with coins and a total amount
// O(mn), O(n);
int coint3( int S[], int m, int n )         
{         
	 int table[n+1];         
	
	 memset(table, 0, sizeof(table));         
 	 table[0] = 1;         

	 // Pick all coins one by one and update the table[] values         
	 // after the index greater than or equal to the value of the         
	 // picked coin         
	 for(int i=0; i<m; i++)         
		 for(int j=S[i]; j<=n; j++)         
			 table[j] += table[j-S[i]];         
	 return table[n];         
}    

// O(mn), O(mn)
int coin2(vector<int>& a, int v, int n,
               vector<vector<int> >& dp)
{
    if (v == 0)
        return dp[n][v] = 1;
    if (n == 0)
        return 0;
    if (dp[n][v] != -1)
        return dp[n][v];
    if (a[n - 1] <= v) {
        // Either Pick this coin or not
        return dp[n][v] = coin2(a, v - a[n - 1], n, dp)
                          + coin2(a, v, n - 1, dp);
    }
    else // We have no option but to leave this coin
        return dp[n][v] = coin2(a, v, n - 1, dp);
}

// O(mn), O(mn)
int coin1( int S[], int m, int n )
{
    int i, j, x, y;
 
    int table[n + 1][m];
     
    for (i = 0; i < m; i++)
        table[0][i] = 1;
 
    for (i = 1; i < n + 1; i++)
    {
        for (j = 0; j < m; j++)
        {
            // Count of solutions including S[j]
            x = (i-S[j] >= 0) ? table[i - S[j]][j] : 0;
 
            // Count of solutions excluding S[j]
            y = (j >= 1) ? table[i][j - 1] : 0;
 
            // total count
            table[i][j] = x + y;
        }
    }
    return table[n][m - 1];
}

// O(2^n), O(target)
int coin(int S[], int m, int n)
{
     
    // If n is 0 then there is 1 solution
    // (do not include any coin)
    if (n == 0)
        return 1;
     
    // If n is less than 0 then no
    // solution exists
    if (n < 0)
        return 0;
 
    // If there are no coins and n
    // is greater than 0, then no
    // solution exist
    if (m <= 0 && n >= 1)
        return 0;
 
    // count is sum of solutions (i)
    // including S[m-1] (ii) excluding S[m-1]
    return coin(S, m - 1, n) +
           coin(S, m, n - S[m - 1]);
}

// 8. Reverse Words in a Sentence
// O(n), O(n)
void reverse(std::string &s) {
	std::vector<string> tmp;
	std::string str("");

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ') {
			tmp.emplace_back(str);
			str = "";
		}
		else {
			str += s[i];
		}
	}

	tmp.emplace_back(str);

	for (int i = tmp.size() - 1; i >= 0; i--) {
		std::cout << tmp[i] << " ";
	}
}

// 7. O(n^2*m), O(n)
bool wordBreak(string s, vector<string>& arr) {
        vector<bool> tabu(s.size() + 1, false);
        
        tabu[0] = true;
        
        for (int i = 0; i <= s.size(); i++) {
	    std::cout << "\t\t working on " << s[i] << "\n";
            for (int j = 0; j < i; j++) {
	    	std::cout << "\t\t\t comparing with " << s.substr(j, i-j) << "\n";
                if (tabu[j] 
                    && find(arr.begin(), arr.end(), s.substr(j, i-j)) != arr.end()) {
                    tabu[i] = true;
		    std::cout << "\t\t\t break " << i << "\n";
                    break;
                }
                    
            }
        }
        return tabu.back(); 
}

// 7. memo
/*
    unordered_map<string, bool> memo;
    
    bool wordBreakHelp(string word, unordered_map<string, bool>& dict)
    {
        //if present in dict
        if(dict.find(word) != dict.end())
            return true;
        
        //if present in memo, no need to call 
        if(memo.find(word) != memo.end())
            return memo[word];
        
        
        for(int i=0; i<word.length(); i++)
        {
            string left = word.substr(0, i+1); //always starts from beginning
            string right = word.substr(i+1); //remaining string till the last letter;
            
            if(dict.find(left) != dict.end())
            {
                bool ros = wordBreakHelp(right, dict); //rest of the string is recursed
                
                if(ros == true)
                {
                    memo[word] = true; //entire word exists
                    return true;
                }
            }
        }
        
        //if no prefix is found to be matching, word does not exist
        memo[word] = false;
        return false;
          
    }
    
    bool wordBreak(string s, vector<string>& wordDict) 
    {
        unordered_map<string, bool> dict;
        
        for(string s : wordDict)
            dict[s] = true;
        
        return wordBreakHelp(s, dict);
    }
*/
struct Node {
	int val;
	Node *prev;
	Node* child;
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

// chasing rabbit :v
bool isCyclic(Node* head) {
	Node *fast, *slow;

	if (!head) return false;

	slow = head;
	fast = head->next;
	while (1) {
		if (!fast || !fast->next) return false;
		if (fast == slow || fast->next == slow) return true;
		slow = slow->next;
		fast = fast->next->next;
	}
}

void newTail(Node** tail, Node *child) {
	Node *cur;

	(*tail)->next = child;
	child->prev = *tail;
	
	for (cur = child; cur->next; cur = cur->next);
	*tail = cur;
}

void flattenList(Node *head, Node **tail) {
	Node * cur = head;

	while (cur) {
		if (cur->child) {
			newTail(tail, cur->child);
		}
		cur = cur->next;
	}
}


	auto findFromLast(Node* head, int m) -> Node* {
		Node *cur, *behind;
		int i;

		cur = head;
		for (int i = 0; i < m; i++) {
			if (cur->next) cur = cur->next;
			else return NULL;
		}

		behind = head;
		while (cur->next) {
			cur = cur->next;
			behind = behind->next;
		}
		return behind;
	}

struct Tree {
	int 	val;
	struct Tree *left;
	struct Tree *right;

	Tree(int v) : val(v), left(NULL), right(NULL) {};

};

void dumpPre(Tree *root) {
	if (!root) return;
	std::cout << " " << root->val;
	dumpPre(root->left);
	dumpPre(root->right);
}


void dumpIn(Tree *root) {
	if (!root) return;
	dumpIn(root->left);
	std::cout << " " << root->val;
	dumpIn(root->right);
}
void dumpPost(Tree *root) {
	if (!root) return;
	dumpPost(root->left);
	dumpPost(root->right);
	std::cout << " " << root->val;
}

int height(Tree *root) {
	if (!root) return 0;
	int lHeight = height(root->left);
	int rHeight = height(root->right);
	return lHeight > rHeight ? lHeight + 1 : rHeight + 1;
}

bool isBst1(Tree *root) {
	static Tree* prev = NULL;
	if (root) {
		if (!isBst1(root->left)) return false;
		if (prev && root->val <= prev->val) return false;
		prev = root;
		return isBst1(root->right);
	}
	return true;
}

Tree* findTree(Tree *root, int val) {
	if (!root) return NULL;
	if (isBst1(root)) {
		while (root) {
			if (root->val == val) break;
			else if (root->val > val) root = root->left;
			else root = root->right;
		}
	}
	else {
			// TODO
	}
	return root; 
}


// O(n) O(n)
bool isBst(Tree *root, int min, int max) {
	if (!root) return true;

	if (root->val < min || root->val > max) return false;
	
	return isBst(root->left, min, root->val) && isBst(root->right, root->val, max);
}

// O(n), space O(n)
void _dumpByLvl(Tree *root, int lvl) {
	if (!root) return;
	if (lvl == 1) std::cout << root->val << " ";
	else if (lvl > 1) {
		_dumpByLvl(root->left, lvl - 1);
		_dumpByLvl(root->right, lvl - 1);
	}
}

// 5. O(n^2)
void dumpBfs(Tree* root) {
	int h = height(root);
	for (int i = 0; i <= h; i++) {
		_dumpByLvl(root, i);
	}
}

// 5. O(n), O(n)
void dumpBfs1(Tree* root) {
	queue<Tree*> todo;
	while (root) {
		cout << root->val << " ";
		if (root->left) todo.push(root->left);
		if (root->right) todo.push(root->right);
		root = todo.front();
		todo.pop();
	}
}

// 4.
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
	node1 = node1->add(4);
	Node* cloned = deepCopy(node1);
	cout << "\n";
	while (cloned) {
		cout << cloned->val << " (" << cloned->arbitrary  << ") ";
		cloned = cloned->next;
	}

	// 5. BFS tree
	{
		cout << "5.Level Order Binary Tree Traversal\n";
		Tree* root = new Tree(100);
		root->left = new Tree(4);
		root->right = new Tree(203);
		root->left->left = new Tree(2);
		root->left->right = new Tree(5);
		dumpBfs(root);
		cout << "\nanother try\n";
		dumpBfs1(root);

	// 6. isbinary serach tree
		cout << "6. Determine if a binary tree is a binary search tree\n";
		cout << "\t" << isBst(root, -INT_MAX, INT_MAX) << "\n";
		cout << "\t" << isBst1(root) << "\n";

	// Book: traversals
		std::cout << "\nPre-order:"; dumpPre(root);
		std::cout << "\nIn-order:"; dumpIn(root);
		std::cout << "\nPost-order:"; dumpPost(root);
		std::cout <<"\n";
	}

	// 7.
	{
		std::vector<std::string> bank{"leet", "code"};
		std::vector<std::string> bank2{"cats","dog","sand","and","cat"};
		std::string s{"leetcode"};
		std::string s2{"catsandogs"};
		cout << "7. String segmentation\n";
		cout << "\t" << wordBreak(s, bank) << "\n";
		cout << "\t" << wordBreak(s2, bank2) << "\n";
	}	
	
	// book, find m from last
	Node* mmm = findFromLast(node1, 1);
	cout << "\t last from m: " << (mmm ? mmm->val : -1) << "\n";

	//8.
	std::string s("Stuying with the cat above my head, literally");
	reverse(s);

	// 9. 
	{
		int i, j;
                int arr[] = { 1, 2, 3 };
                int m = sizeof(arr) / sizeof(arr[0]);
     
	        cout << "\n9. How many ways can you make change with coins and a total amount\n";
	        cout << "\n\t" << coin(arr, m, 4);

	}

	// 10. Kth permutaion
	getKPermutation(4, 17);

	// 11. find all subsets
	std::vector<int> sasa{2,3,4};
	subset(sasa);


	// book. is cyclic or acylic
	cout << "\nIs the list cyclic? "<< isCyclic(node1);

     	cout<< "\n";
	return 0;
}
