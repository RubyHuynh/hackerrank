//415. Add Strings
class Solution {
public:
    char addChar(char a , char b , int &carry){
        char ans = carry+a+b-48;
        if(ans>57){
            carry=1;
            ans -= 10;
            return ans;
        }
        else{
            carry=0;
            return ans;
        }
    }
    string addStrings(string num1, string num2) {
        int inum1=num1.length()-1;
        int inum2=num2.length()-1;
        int carry = 0;
        string ans;
        while(true){
            if(inum1>=0 && inum2>=0){
                char ch = addChar(num1[inum1],num2[inum2],carry);
                ans.push_back(ch);
                inum1--;
                inum2--;
            }
            else if(inum1>=0){
                char ch = addChar(num1[inum1],'0',carry);
                ans.push_back(ch);
                inum1--;
            }
            else if(inum2>=0){
                char ch = addChar('0',num2[inum2],carry);
                ans.push_back(ch);
                inum2--;
            }
            else if(carry>0){
                ans.push_back(carry+48);
                carry = 0;
            }
            else{
                break;
            }
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};

//414. Third Maximum Number
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        int *fmax = nullptr, *smax = nullptr, *tmax = nullptr;
        for(int i = 0;i < nums.size();i++) {
            int x = nums[i];
            if(!fmax || x > *fmax) {
                tmax = smax;
                smax = fmax;
                fmax = &nums[i];
            } else if((!smax || x > *smax) && (fmax && x != *fmax)) {
                tmax = smax;
                smax = &nums[i];
            } else if((!tmax || x > *tmax) && (smax && x != *smax) && (fmax && x != *fmax)) {
                tmax = &nums[i];
            }
        }
        return(tmax == nullptr ? *fmax : *tmax);
    }
};

//412. Fizz Buzz
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> ret(n);
        for (int i = 1; i <=n; i++) {
            if (i%3 == 0 && i%5 ==0) ret[i-1] = "FizzBuzz";
            else if (i%3==0) ret[i-1] = "Fizz";
            else if (i%5==0) ret[i-1] = "Buzz";
            else ret[i-1] = to_string(i);
        }
        return ret;
    }
};

//409. Longest Palindrome
class Solution {
public:
    int longestPalindrome(string s) {
        int n = s.size();
        unordered_map<char, int> m;
        int even = 0;
        int odd = 0;
        for (int i = 0; i < n; i++) {
            m[s[i]]++;
            if (m[s[i]] % 2 == 0) even+=2;
        }
        for (int i = 0; i < n; i++) {
            if (m[s[i]] % 2 == 1) {
                odd++;
                break;// can only 1 odd at the middle
            }
        }
        return odd + even;
        
    }
};

//405. Convert a Number to Hexadecimal
class Solution {
    unordered_map<int, char> mp;

public:
    string toHex(int num) {
        if (num == 0) return "0";

        for (int i = 0; i < 10; i++){
            mp[i] = '0' + i;
        }
        for (int i = 10; i < 16; i++){
            mp[i] = 'a' + (i-10);
        }

        long long n = num;
        if (num < 0) {
            n = ((long) INT_MAX*2) + 2 + num; //?
        }
        string ret;
        while (n) {
            int dig = n %16;
            ret += mp[dig];
            n/= 16;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

//404. Sum of Left Leaves
class Solution {
    int help(TreeNode* root, bool isLeft) {
        if (!root) return 0;
        if (!root->left && !root->right && isLeft) return root->val;
        return help(root->left, true) + help(root->right, false);
    }
public:
    int sumOfLeftLeaves(TreeNode* root) {
        return help(root, false);
    }
};

//232. Implement Queue using Stacks
class MyQueue {
    stack<int> st;
    stack<int> tmp;
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        if (!st.size()) {
            st.push(x);
            return;
        }
        else {
            while (st.size()) {
                tmp.push(st.top());
                st.pop();
            }
            st.push(x);
            while (tmp.size()) {
                st.push(tmp.top());
                tmp.pop();
            }
        }
    }
    
    int pop() {
        int x = st.top();
        st.pop();
        return x;
    }
    
    int peek() {
        return st.top();
    }
    
    bool empty() {
        return st.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

///203. Remove Linked List Elements
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode tmp(51);
        tmp.next = head;
        ListNode* cur = &tmp;
        ListNode* prev = cur;
        while (cur) {
            if (cur->val == val) {
                prev->next = cur->next;
            }
            else {
                prev = cur;
            }
            cur = cur->next;
        }
        return tmp.next;
    }
};

//110. Balanced Binary Tree (max diff = 1 only)
class Solution {
    int height(TreeNode* root) {
        if (!root) return 0;
        int l = height(root->left);
        int r = height(root->right);
        if (l == -1 || r == -1 || abs(l-r) > 1) return -1;
        return max(l, r) + 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        if (height(root) == -1) return false;
        return true;
    }
};

//88. Merge Sorted Array
class Solution {
public:
    void merge1(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for (int i = m, j = 0; j < n; j++) {
            nums1[i] = nums2[j];
            i++;
        }
        sort(nums1.begin(), nums1.end());
    }
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m -1;
        int j = n -1;
        int k = m + n -1;

        while (j >= 0) {
            if (i >=0 && nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            }
            else {
                nums1[k--] = nums2[j--];
            }
        }
    }
};

//100 is same tree
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == nullptr && q == nullptr) return true;
        if(p == nullptr || q == nullptr) return false;
        return p->val == q-> val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

//104. Maximum Depth of Binary Tree
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        int l = maxDepth(root->left);
        int r = maxDepth(root->right);
        return max(l,r) + 1;
    }
};

//66. Plus One
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size() -1 ; i>=0; i--) {
            if (digits[i] + 1 != 10) {
                digits[i] += 1;
                return digits;
            }
            digits[i] = 0;
            if (i == 0) {
                digits.insert(digits.begin(), 1);
                return digits;
            }
        }
        return digits;
    }
};

//21. Merge Two Sorted Lists
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1) return list2;
        if (!list2) return list1;
        if (list1->val <= list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
};
//13. Roman to Integer
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> vals;
        vals['I'] = 1;
        vals['V'] = 5;
        vals['X'] = 10;
        vals['L'] = 50;
        vals['C'] = 100;
        vals['D'] = 500;
        vals['M'] = 1000;

        int ret = 0;
        for (int i = 0 ; i < s.size(); i++) {
            if (vals[s[i]] < vals[s[i+1]]) {
                ret -= vals[s[i]];
            }
            else {
                ret += vals[s[i]];
            }
        }
        return ret;
    }
};

//58. Length of Last Word
class Solution {
public:
    int lengthOfLastWord(string s) {
        int ret = 0;
        bool found = false;
        for (int i = s.size() -1 ; i >=0; i--) {
            if (s[i] != ' ') {
                found = true;
                ret++;
            }
            else if (found) {
                break;
            }
        }
        return ret;
    }
};

//26. Remove Duplicates from Sorted Array
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int j = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i-1]) {
                nums[j] = nums[i];
                j++;
            }
        }
        return j;
    }
};

//14. Longest Common Prefix
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ret;
        sort(strs.begin(), strs.end());
        int n = strs.size();
        string first = strs[0], last = strs[n-1];
        for (int i = 0; i < min(first.size(), last.size()); i++)  {
            if (first[i] != last[i]) {
                return ret;
            }
            ret += first[i];
        }
        return ret;
    }
};


//83. Remove Duplicates from Sorted List
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* cur = head;
        ListNode* tmp;
        while (cur && cur->next) {
            tmp = cur->next;
            if (cur->val == tmp->val) {
                cur->next = tmp->next;
                delete tmp;
            }
            else {
                cur = cur->next;
            }
        }
        return head;
    }
};


//27. Remove Element 
class Solution {
public:
    int removeElement2(vector<int>& nums, int val) {
        int ret = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[ret] = nums[i];
                ret++;
            }
        }

        return ret;
    }

    int removeElement(vector<int>& nums, int val) {
        for (auto it = nums.begin(); it != nums.end(); ) {
            if (*it == val) {
                it = nums.erase(it);
            } else {
                it++;
            }
        }
        return nums.size();
    }
};

//35. Search Insert Position
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0; 
        int r = nums.size();
        int mid; 

        if (target > nums[r-1]) return r;

        while (l <= r) {
            mid = (r+l)/2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[mid] > target) r = mid - 1;
            else l = mid + 1;
        }
        return l;
    }
};

//121. Best Time to Buy and Sell Stock
class Solution {
public:
    int maxProfit1(vector<int>& prices) {
        int n = prices.size();
        int ret = 0;
        for (int i = 0; i < n; i++) {
            for (int j = n -1; j > i; j--) {
                ret = max(ret, prices[j]-prices[i]);
            }
        }
        return ret;
    }

    int maxProfit(vector<int>& prices) {
        int l = 0;
        int r = 0;
        int n = prices.size();
        int ret = 0;
        
        while (++r < n) {
            if (prices[r] > prices[l]) {
                ret = max(ret, prices[r]-prices[l]);
            }
            else if (prices[r] < prices[l]) {
                l = r; // l will always try to jump to the smallest 
                // and the result is counted already with each "min" assumption.
            }
        }
        return ret;
    }
};

//292. Nim Game
class Solution {
public:
    bool canWinNim(int n) {
        return n%4 != 0;
    }
};

//1572. Matrix Diagonal Sum
class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int ret = 0;
        int n = mat.size();
        for (int i = 0; i < n; i++) {
            ret += mat[i][i];
            ret += mat[i][n-i-1];
        }
        if (n % 2) ret -= mat[n/2][n/2];
        return ret;
    }
};


//557. Reverse Words in a String III
class Solution {
public:
    string reverseWords1(string s) {
        string ret;
        stack<char> temp;

        for (auto it : s) {
            if (it != ' ') {
                temp.push(it);
            }
            else {
                while (!temp.empty()) {
                    ret += temp.top();
                    temp.pop();
                }
                ret += ' ';
            }
        }
        while (!temp.empty()) {
            ret += temp.top();
            temp.pop();
        }
        return ret;
        
    }
    string reverseWords(string s) {
        string ret;
        int l = 0, r = -1;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] != ' ') {
                r++;
            }
            else {
                while (r >= l) {
                    ret += s[r];
                    r--;
                }
                l = r = i + 1;
            }
        }
        while (r >= l) {
            if (r == s.size()) ret += " ";
            else ret += s[r];
            r--;
        }
        return ret;
        
    }
};


//111. Minimum Depth of Binary Tree

class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root)      return 0;

        int depth = 1;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                TreeNode* node = q.front();
                q.pop();
                if (!node) continue;
                if (!node->left && !node->right)        return depth; 
                q.push(node->left);
                q.push(node->right);
            }
            depth++;
        }
        return depth;
    }
};

class Solution1 {
public:
    int dfs(TreeNode* root) {
        if (!root)              return 0;

        if (!root->left)        return 1 + dfs(root->right);
        else if (!root->right)  return 1 + dfs(root->left);

        return 1 + min(dfs(root->left), dfs(root->right));
    }

    int minDepth(TreeNode* root) {
        return dfs(root);
    }
};

//859. Buddy Strings

class Solution {
public:
    bool buddyStrings(string s, string goal) {
        if (s.size() != goal.size()) {
            return false;
        }

        if (s == goal) {
            vector<int> frequency(26,0);
            for (auto & c : s) {
                frequency[c - 'a'] +=1;
                if (frequency[c - 'a'] == 2) {
                    return true;
                }
            }
            return false;
        }
        int firstIdx = -1;
        int secondIdx = -1;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != goal[i]) {
                if (firstIdx == -1) {
                    firstIdx = i;
                }
                else if (secondIdx == -1) {
                    secondIdx = i;
                }
                else {
                    return false; // too many
                }
            }
        }

        if (secondIdx == -1) return false;

        return s[firstIdx] == goal[secondIdx] &&  s[secondIdx] == goal[firstIdx];
    }
};
//530. Minimum Absolute Difference in BST
class Solution {
public:
    int minDifference = INT_MAX;
    // Initially, it will be null.
    TreeNode* prevNode;
        
    void inorderTraversal(TreeNode* node) {
        if (node == NULL) {
            return;
        }
        
        inorderTraversal(node->left);
        // Find the difference with the previous value if it is there.
        if (prevNode != NULL) {
            minDifference = min(minDifference, node->val - prevNode->val);
        }
        prevNode = node;
        inorderTraversal(node->right);
    }
    
    int getMinimumDifference(TreeNode* root) {
        inorderTraversal(root);
        return minDifference;
    }
};
class Solution2 {
public:
    // List to store the tree nodes in the inorder traversal.
    vector<int> inorderNodes;

    void inorderTraversal(TreeNode* node) {
        if (node == NULL) {
            return;
        }

        inorderTraversal(node->left);
        // Store the nodes in the list.
        inorderNodes.push_back(node->val);
        inorderTraversal(node->right);
    }

    int getMinimumDifference(TreeNode* root) {
        inorderTraversal(root);

        int minDifference = INT_MAX;
        // Find the diff between every two consecutive values in the list.
        for (int i = 1; i < inorderNodes.size(); i++) {
            minDifference = min(minDifference, inorderNodes[i] - inorderNodes[i - 1]);
        }

        return minDifference;
    }
};
class Solution1 {
public:
    vector<int> arr;

    void dfs(TreeNode* node) {
        if (!node) return;
        arr.push_back(node->val);
        dfs(node->left);
        dfs(node->right);
    }

    int getMinimumDifference(TreeNode* root) {
        dfs(root);

        sort(arr.begin(), arr.end());
        int ret = INT_MAX;

        for (int i = 1; i < arr.size(); i++) {
            ret = min(arr[i] - arr[i-1], ret);
        }
        return ret;
    }
};

//228. Summary Ranges
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ret;

        for (int i = 0; i <nums.size(); i++) {
            int start = nums[i];
            while (i + 1 < nums.size() 
                && nums[i] + 1 == nums[i+1]) {
                    i++;
            }
            if (start != nums[i]) {
                ret.push_back(to_string(start) + "->" + to_string(nums[i]));
            }
            else {
                ret.push_back(to_string(start));
            }
        }
        return ret;
    }
};

 class Solution:
    def summaryRanges(self, nums: List[int]) -> List[str]:
        ranges = []
        i = 0

        while i < len(nums) :
            start = nums[i]
            while i + 1 < len(nums) and nums[i] + 1 == nums[i+1] :
                i += 1

            if start != nums[i] :
                ranges.append(str(start) + "->" + str(nums[i]))
            else :
                ranges.append(str(start))
            i += 1
        return ranges

//744. Find Smallest Letter Greater Than Target
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
       int left = 0;
        int right = letters.size()-1;
        int mid = 0;
        if (letters[right] <= target) {
            return letters[0];
        }
        while (left <= right) {
            mid = left + (right - left) / 2;
            if (letters[mid] > target) {
                right = mid-1;
            } else {
                left = mid+1;
            }
        }
        return letters[left];
    }
};
class Solution:
    def nextGreatestLetter(self, letters: List[str], target: str) -> str:
        left = 0
        right = len(letters) - 1

        while left <= right :
            mid = left + (right - left) // 2
            if letters[mid] <= target :
                left = mid + 1
            else :
                right = mid - 1
        if left == len(letters) :
            return letters[0]
        return letters[left]


//1351. Count Negative Numbers in a Sorted Matrix
class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int ret = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = m-1 ; i >=0; i--) {
            for (int j = n-1; j >=0; j--) {
                if (grid[i][j] >= 0) break;
                ret++;
            }
        }
        return ret;
    }
};

class Solution1:
    def countNegatives(self, grid: List[List[int]]) -> int:
        i = 0
        j = len(grid[0]) - 1
        ret = 0

        while i < len(grid) and j >= 0 :
            if grid[i][j] < 0 :
                ret += len(grid) - i
                j -= 1
            else:
                i += 1
        return ret

class Solution:
    def countNegatives(self, grid: List[List[int]]) -> int:
        ret = 0
        n = len(grid[0])

        for row in grid :
            left, right = 0, n - 1
            while left <= right :
                mid = (left + right) // 2
                if row[mid] < 0 :
                    right = mid - 1
                else :
                    left = mid + 1
            ret += n - left
        
        return ret







//1502. Can Make Arithmetic Progression From Sequence
class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        sort (arr.begin(), arr.end());
        int diff = arr[1] - arr[0];
        for (int i = 2; i < arr.size(); i++) {
            if (arr[i] - arr[i-1] != diff) {
                return false;
            }
        }
        return true;
    }
};

class Solution:
    def canMakeArithmeticProgression(self, arr: List[int]) -> bool:
        arr.sort()
        diff = arr[1] - arr[0]
        for i in range(2, len(arr)) :
            if arr[i] - arr[i-1] != diff :
                return False
        return True
        




//1232. Check If It Is a Straight Line
class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int dx = coordinates[1][0] - coordinates[0][0];
        int dy = coordinates[1][1] - coordinates[0][1];

        /*
                dy1/dx1 = dy2/dx2
            <-> dy1*dx2 = dy2*dx1
            
        */
        for (int i = 2; i < coordinates.size(); i++) {
            if (dx * (coordinates[i][1] - coordinates[0][1]) 
                != dy * (coordinates[i][0] - coordinates[0][0])) {
                    return false;
            }
        }
        return true;
    }
};


class Solution:
    def checkStraightLine(self, coordinates: List[List[int]]) -> bool:
        dx = coordinates[1][0] - coordinates[0][0]
        dy = coordinates[1][1] - coordinates[0][1]

        for i in coordinates : 
            if (dx * (i[1] - coordinates[0][1])) != (dy * (i[0] - coordinates[0][0])) :
                return False
        return True
	


//704. Binary Search
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] < target) {
                low = mid + 1;
            } else if (nums[mid] > target) {
                high = mid - 1;
            } else {
                return mid;
            }
        }
        
        return -1;
    }
};

//20. Valid Parentheses
class Solution {
public:
    bool isValid(string s) {
        stack<char> pipe;
        
        
        for (auto it : s) {
            if (it == '(' || it == '{' || it == '[') {
                pipe.push(it);
            }
            else {
                if (pipe.empty() 
                    || (pipe.top() == '(' && it != ')')
                    || (pipe.top() == '{' && it != '}')
                    || (pipe.top() == '[' && it != ']')){
                    return false;
                }
                else {
                    pipe.pop();
                }
            }
        }
        
        return pipe.empty();
    }
};
/*Runtime: 3 ms, faster than 47.07% of C++ online submissions for Valid Parentheses.
Memory Usage: 6.3 MB, less than 50.99% of C++ online submissions for Valid Parentheses.
*/


//112. Path Sum
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        if (!root->left && !root->right && root->val == targetSum) return true;
        
        return hasPathSum(root->left, targetSum - root->val) 
            || hasPathSum(root->right, targetSum - root->val);
    }
    /*Runtime: 14 ms, faster than 72.86% of C++ online submissions for Path Sum.
Memory Usage: 21.2 MB, less than 92.08% of C++ online submissions for Path Sum.*/
    
    
    bool hasPathSum1(TreeNode* root, int targetSum) {
        stack<TreeNode*> nodes;
        stack<int> sums;
        
        if (!root) return false;
        
        nodes.push(root);
        sums.push(targetSum - root->val);
        while (sums.size()) {
            TreeNode* cur = nodes.top();
            int curSum = sums.top();
            nodes.pop();
            sums.pop();
            
            if (!cur->left && !cur->right && curSum == 0) {
                return true;
            }
            if (cur->left) {
                nodes.push(cur->left);
                sums.push(curSum - cur->left->val);
            }
            if (cur->right) {
                nodes.push(cur->right);
                sums.push(curSum - cur->right->val);
            }
        }
        return false;
    }
};

/*Runtime: 10 ms, faster than 89.13% of C++ online submissions for Path Sum.
Memory Usage: 21.6 MB, less than 39.41% of C++ online submissions for Path Sum.*/


//101. Symmetric Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return isSym(root, root);
    }
    
    bool isSym(TreeNode* l, TreeNode* r) {
        if (!l && !r) return true;
        if (!l || !r) return false;
        
        return l->val == r->val && isSym(l->left, r->right) && isSym(l->right, r->left);
    }
};
/*Runtime: 9 ms, faster than 47.74% of C++ online submissions for Symmetric Tree.
Memory Usage: 16.5 MB, less than 18.26% of C++ online submissions for Symmetric Tree.*/


//55. Jump Game
class Solution {
public:
    bool canJump1(vector<int>& nums) {
        int n = nums.size();
        int goal = n-1, i;
        for (int i = n; i--;)
            if (i + nums[i] >= goal)
                goal = i;
        return !goal;
    }
     bool canJump2(vector<int>& nums) {
        int n = nums.size();
        int reachable = 0;
        
        for (int i = 0; i < n; i++) {
            if (i > reachable) {
                return false;
            }
            reachable = max(reachable, i + nums[i]);
            if (reachable >= n - 1) {
                break;
            }
        }
        
        return true;
    }
    
     bool canJump(vector<int>& nums) {
        int size=nums.size();
        int step=nums[0];
        for(int i=1;i<size;++i){
            step--;
            if(step<0)
               return false;
            if(nums[i]>step)
               step=nums[i];
        }
        return true;
    
};

//9. Palindrome Number
// class Solution {
// public:
// //     bool isPalindrome(int x) {
// //         char* l = (char*) &x;
// //         char* r = (char*) &x;
// //         int tmp = x;
        
// //         while (tmp) {
// //             tmp = tmp >> 1;
// //             r++;
// //         }
        
// //         while (r && l && r > l) {
// //             if (r[0] != l[0]) return false;
// //             r--;
// //             l++;
// //         }
// //         return true;
// //     }
//     // bool isPalindrome(int x) {
//     //     if(x<0|| (x!=0 &&x%10==0)) return false;
//     //     int sum=0;
//     //     while(x>sum)
//     //     {
//     //         sum = sum*10+x%10;
//     //         x = x/10;
//     //     }
//     //     return (x==sum)||(x==sum/10);
//     // }
// };

// Solution I:
// Convert the number to a string, revert it and compare.

class Solution1 {
public:
    bool isPalindrome(int x) {
        string rev = to_string(x);
        reverse(rev.begin(), rev.end());
        return to_string(x) == rev;
    }
};
// Solution II:
// Convert the number to a string, then use two pointers at beginning and end to check if it's a palindrome.

class Solution2 {
public:
    bool isPalindrome(int x) {
        string s = to_string(x);
        int i = 0, j = s.size()-1;
        while (i <= j) if (s[i++] != s[j--]) return false;
        return true;
    }
};
// Solution III:
// Reverse the second half of the number and then compare.

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;
        int rev = 0;
        while (rev < x) {
            rev = rev * 10 + x % 10;
            x /= 10;
        }
        
        return x == rev || x == rev / 10;
    }
};

//226. Invert Binary Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return NULL;
        
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        
        root->left = right;
        root->right = left;
        return root;
    }
};
/*Runtime: 7 ms, faster than 24.94% of C++ online submissions for Invert Binary Tree.
Memory Usage: 9.6 MB, less than 97.32% of C++ online submissions for Invert Binary Tree.*/

//617. Merge Two Binary Trees
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if(t2==NULL) return t1;
        if(t1==NULL) return t2;
        TreeNode* res=t1;
        stack<TreeNode*> s1, s2;
        s1.push(t1), s2.push(t2);
        while(!s1.empty()) {
            TreeNode* c1=s1.top();
            TreeNode* c2=s2.top();
            s1.pop(), s2.pop();
            c1->val+=c2->val;
            if(c1->right==NULL&&c2->right!=NULL) c1->right=c2->right;
            else if(c1->right!=NULL&&c2->right!=NULL) s1.push(c1->right), s2.push(c2->right);
            if(c1->left==NULL&&c2->left!=NULL) c1->left=c2->left;
            else if(c1->left!=NULL&&c2->left!=NULL) s1.push(c1->left), s2.push(c2->left);
        }
        return res;
    }
    /*Runtime: 66 ms, faster than 44.35% of C++ online submissions for Merge Two Binary Trees.
Memory Usage: 32.7 MB, less than 43.28% of C++ online submissions for Merge Two Binary Trees.*/
    
//     TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
//         if (!root1) return root2;
//         if (!root2) return root1;
        
//         root1->val += root2->val;
//         root1->left = mergeTrees(root1->left, root2->left);
//         root1->right = mergeTrees(root1->right, root2->right);
//         return root1;
//     }
};
/*Runtime: 49 ms, faster than 76.52% of C++ online submissions for Merge Two Binary Trees.
Memory Usage: 32.3 MB, less than 87.32% of C++ online submissions for Merge Two Binary Trees.*/


// 589. N-ary Tree Preorder Traversal
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> preorder(Node* root) {
        std::vector<int> rs;
        std::stack<Node*> stack;
        Node* cur = root;
        
        if (!root) return rs;
        
        stack.push(cur);
        while (stack.size()) {
            cur = stack.top();
            stack.pop();
            rs.push_back(cur->val);
            std::reverse(cur->children.begin(), cur->children.end());
            for (auto it : cur->children) {
                stack.push(it);
            }
        }
        return rs;
    }
};
/*Runtime: 36 ms, faster than 51.52% of C++ online submissions for N-ary Tree Preorder Traversal.
Memory Usage: 10.9 MB, less than 98.76% of C++ online submissions for N-ary Tree Preorder Traversal.*/

//94. Binary Tree Inorder Traversal
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> rs;
        stack<TreeNode*> stack;
        
        TreeNode* cur = root;
        while (cur || stack.size()) {
            while (cur) {
                stack.push(cur);
                cur = cur->left;
            }
            
            cur = stack.top();
            stack.pop();
            rs.push_back(cur->val);
            cur = cur->right;
        }
        return rs;
    }
};


//590. N-ary Tree Postorder Traversal
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> postorder(Node* root) {
        stack<Node*> stack;
        vector<int> rs;
        
        if (!root) return rs;
        
        stack.push(root);
        while (stack.size()) {
            Node* cur = stack.top();
            stack.pop();
            rs.push_back(cur->val);
            for (auto child : cur->children) {
                stack.push(child);
            }
        }
        std::reverse(rs.begin(), rs.end());
        return rs;
    }
    /*Runtime: 24 ms, faster than 87.32% of C++ online submissions for N-ary Tree Postorder Traversal.
Memory Usage: 11.2 MB, less than 55.79% of C++ online submissions for N-ary Tree Postorder Traversal.*/
    
    
//     vector<int> postorder(Node* root) {
//         stack<Node*> stack;
//         vector<int> rs;
        
//         if (!root) return rs;
        
//         stack.push(root);
//         while (stack.size()) {
//             Node* cur = stack.top();
//             stack.pop();
//             rs.insert(rs.begin(), 1, cur->val); // bad here, reallocation and coppying data
//             for (auto child : cur->children) {
//                 stack.push(child);
//             }
//         }
//         return rs;
//     }
    
/*Runtime: 82 ms, faster than 5.19% of C++ online submissions for N-ary Tree Postorder Traversal.
Memory Usage: 11 MB, less than 93.11% of C++ online submissions for N-ary Tree Postorder Traversal.*/
};


// 234. Palindrome Linked List
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        
        slow = reverse(slow);
        fast = head;
        
        while (slow) {
            if (slow->val != fast->val) {
                return false;
            }
            slow = slow->next;
            fast = fast->next;
        }
        return true;
    }
private:
    ListNode* reverse(ListNode* head) {
        ListNode* prev = NULL;
        
        while (head) {
            ListNode* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
};
/*Runtime: 357 ms, faster than 55.14% of C++ online submissions for Palindrome Linked List.
Memory Usage: 114 MB, less than 85.80% of C++ online submissions for Palindrome Linked List.*/



//167. Two Sum II - Input Array Is Sorted
class Solution {
public:
   vector<int> twoSum(vector<int>& nums, int target) {
        int N = nums.size();
        for(int i=0;i<N-1;i++){
            int lo = i+1;
            int hi = N;
            while(lo<hi){
                int mid = lo + (hi-lo)/2;
                if(nums[mid]==target-nums[i]) return {i+1,mid+1};
                else if(nums[mid]>=target-nums[i]) hi=mid;
                else lo = mid+1;
            }
            if(lo!=nums.size() && nums[lo]==target-nums[i]) return {i+1,lo+1};
        }
        return {}; // not found
    }
    
//     vector<int> twoSum(vector<int>& numbers, int target) {
//         int a = 0;
//         int b = numbers.size() - 1;
//         vector<int> rs;
        
//         if (b < 0)  return rs;
        
//         while (a <= b) {
//             if (numbers[a] + numbers[b] > target) {
//                 b--;
//             }
//             else if (numbers[a] + numbers[b] < target) {
//                 a++;
//             }
//             else {
//                 rs.push_back(a+1);
//                 rs.push_back(b+1);
//                 break;
//             }
//         }
//         return rs;
//     }
    /*Runtime: 22 ms, faster than 46.56% of C++ online submissions for Two Sum II - Input Array Is Sorted.
    Memory Usage: 15.6 MB, less than 43.13% of C++ online submissions for Two Sum II - Input Array Is Sorted.
    */
};


//206. Reverse Linked List
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = NULL;
        
        while (head) {
            ListNode* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
};

/*Success
Details 
Runtime: 3 ms, faster than 98.41% of C++ online submissions for Reverse Linked List.
Memory Usage: 8.3 MB, less than 79.70% of C++ online submissions for Reverse Linked List.*/

//217. Contains Duplicate
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        return containsDuplicate2(nums);
    }
    bool containsDuplicate1(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i=0; i<int(nums.size())-1; i++) {
            if (nums[i]==nums[i+1])
                return true;
        }
        return false;    
    }

    bool containsDuplicate2(vector<int>& nums) {
        map<int, bool> myMap;
        // unordered_map<int, bool> myMap;
        for (auto& num: nums) {
            if (myMap.find(num) != myMap.end())
                return true;
            else
                myMap[num] = true;
        }
        return false;
    }

    bool containsDuplicate3(vector<int>& nums) {
        multimap<int, bool> myMap;
        // unordered_multimap<int, bool> myMap;
        for (auto& num: nums) {
            if (myMap.find(num) != myMap.end())
                return true;
            myMap.insert(make_pair(num, true));
        }
        return false;
    }

    bool containsDuplicate4(vector<int>& nums) {
        set<int> mySet;
        // unordered_set<int> mySet;
        // multiset<int> mySet;
        // unordered_multiset<int> mySet;
        for (auto& num: nums) {
            if (mySet.find(num) != mySet.end())
                return true;
            mySet.insert(num);
        }
        return false;
    }
};

// 118. Pascal's Triangle
class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int>> r(numRows);

        for (int i = 0; i < numRows; i++) {
            r[i].resize(i + 1);
            r[i][0] = r[i][i] = 1;
  
            for (int j = 1; j < i; j++)
                r[i][j] = r[i - 1][j - 1] + r[i - 1][j];
        }
        
        return r;
    }
    /*
    Runtime: 0 ms, faster than 100.00% of C++ online submissions for Pascal's Triangle.
    Memory Usage: 6.3 MB, less than 99.37% of C++ online submissions for Pascal's Triangle.
    */
//     vector<vector<int>> generate(int numRows) {
//         vector<vector<int>> rs;
//         vector<int> first;
        
//         if (numRows == 0) return rs;
        
//         first.push_back(1);
//         rs.push_back(first);
        
//         for (int i = 1; i < numRows; i++) {
//             auto prevRow = rs[i-1];
//             vector<int> newRow;
//             newRow.push_back(1);
//             for (int j = 1; j < i; j++) {
//                 newRow.push_back(prevRow[j-1] + prevRow[j]);
//             }
//             newRow.push_back(1);
//             rs.push_back(newRow);
//         }
//         return rs;
//     }
    /*
    Runtime: 3 ms, faster than 39.24% of C++ online submissions for Pascal's Triangle.
    Memory Usage: 6.6 MB, less than 32.60% of C++ online submissions for Pascal's Triangle.
    */
};

//746. Min Cost Climbing Stairs
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int cost1 = cost[0];
        int cost2 = cost[1];
        int rs = min(cost1, cost2);
        
        for (int i = 2; i < cost.size(); i++) {
            rs = cost[i] + min(cost1, cost2);
            cost1 = cost2;
            cost2 = rs;
        }
        return min(cost1, cost2);
    }
    
};


// 70. Climbing Stairs
class Solution {
public:
    int climbStairs(int n) {
        int rs = 1;
        int step1 = 1;
        int step2 = 1;
        
        for (int i = 2; i <= n; i++) {
            rs = step1 + step2;
            step2 = step1;
            step1 = rs;
        }
        return rs;
    }
};


//121. Best Time to Buy and Sell Stock
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //pointers only move right
        int l=0;//left pointer------- logic: get the least value possible
        int r=0;//right pointer------- logic: traverse the array and update profit, if you get something less than left pointer, then update left pointer, 
        
        int profit=0;
        
        //we move r while price[l] is lower than price[r]
        while(++r<prices.size()){
            
            if(prices[r]>prices[l]){
            
                profit=max(profit,prices[r]-prices[l]);//this is update to the max of current value of p and the profit if the share bought at l(the lowest so far) is sold at r
            
            }else if(prices[r]<prices[l]){
                //right pointer points to a value lower than left pointer
                
                l=r;// since l can be at most r, it can never cross r
                //keeping new lower value of l will be more profitable 
                //for the future higher values
            }
        }
        
        return profit;
    }
};


//125. Valid Palindrome
class Solution {
public:
    bool isPalindrome(string s) {
        for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
            while (!isalnum(s[i]) && i < j) i++; // Increment left pointer if not alphanumeric
            while (!isalnum(s[j]) && i < j) j--; // Decrement right pointer if no alphanumeric
            if (toupper(s[i]) != toupper(s[j])) return false;
        }

        return true;
    }
};
