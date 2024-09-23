#include<iostream>
#include<ostream>
#include<string.h>
#include<limits.h>
using namespace std;

//89. Gray Code
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> grey;
        for (int i = 0; i <pow(2, n); i++) {
            grey.push_back(i^(i>>1));
        }
        return grey;
    }
};


//91. Decode Ways
class Solution {
public:
    int help(string s, int i, vector<int>& dp) {
        if (s[i] == '0') return 0;
        if (i == s.size()) return 1;
        if (dp[i] != -1) return dp[i];

        int twoDigit = -1;
        if (i+1 != s.size() || s[i] == '0') {
            twoDigit = ((s[i] - '0')*10) + (s[i+1] - '0');
        }
        if (twoDigit != -1 && twoDigit <= 26) {
            return dp[i] = help(s, i+2, dp) + help(s, i+1, dp);
        }
        return dp[i] = help(s, i+1, dp);
    }
    int numDecodings(string s) {
        if (s[0] == '0') return 0;
        vector<int> dp(s.size() + 1, -1);
        return help(s, 0, dp);
    }
};

//92. Reverse Linked List II
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || left == right) return head;

        ListNode* tmp = new ListNode(0);
        tmp->next = head;
        ListNode* prev = tmp;

        for (int i = 1; i < left; i++) {
            prev = prev->next;
        }

        ListNode* start = prev->next;
        ListNode* end = start->next;

        for (int i = 0; i < right - left; i++) {
            start->next = end->next;
            end->next = prev->next;
            prev->next = end;
            end = start->next;
        }
        return tmp->next;
    }
};

//99. Recover Binary Search Tree (cleaner)
class Solution {
public:
        TreeNode* prev = nullptr;
        TreeNode* num1 = nullptr;
        TreeNode* num2 = nullptr;

    void inorder(TreeNode* root) {
        if (!root) return;
        inorder(root->left);

        // init
        if (prev) {
            if (prev->val > root->val) {
                if (!num1) {
                    num1 = prev;
                }
                num2 = root;
            }
        }
        prev = root;
        inorder(root->right);
    }
    void recoverTree(TreeNode* root) {
        inorder(root);

        int tmp = num1->val;
        num1->val = num2->val;
        num2->val = tmp;
    }
};

//99. Recover Binary Search Tree
class Solution {
public:
        TreeNode* prev = new TreeNode(INT_MIN);
        TreeNode* num1 = nullptr;
        TreeNode* num2 = nullptr;

    void inorder(TreeNode* root) {
        if (!root) return;
        inorder(root->left);

        // init
        if (!num1 && prev->val > root->val) {
            num1 = prev;
        }

        if (num1 && prev->val > root->val) {
            num2 = root;
        }
        prev = root;
        inorder(root->right);
    }
    void recoverTree(TreeNode* root) {
        inorder(root);

        int tmp = num1->val;
        num1->val = num2->val;
        num2->val = tmp;
    }
};
//98. Validate Binary Search Tree
class Solution {
    bool help(TreeNode* node, long min, long max) {
        if (!node) return true;
        if (!(node->val > min && node->val < max)) return false;
        return help(node->left, min, node->val) 
                && help(node->right, node->val, max);
    }
public:
    bool isValidBST(TreeNode* root) {
        return help(root, LONG_MIN, LONG_MAX);
    }
};

//97. Interleaving String
class Solution1 {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.length();
        int n = s2.length();
        int l = s3.length();
        if (m + n != l) return false;
        if (m < n) return isInterleave(s2, s1, s3);
        vector<bool> dp(n+1, false);
        dp[0] = true;

        for (int j = 1; j <=n ; j++) {
            dp[j] = dp[j-1] && s2[j-1] == s3[j-1];
        }
        for (int i =1; i <= m; i++) {
            dp[0] = dp[0] && s1[i-1] == s3[i-1];
            for (int j = 1; j <=n; j++) {
                dp[j] = (dp[j] && s1[i-1] == s3[i+j-1]) ||
                        (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        return dp[n];
    }

};

class Solution {
public:
    int dp[101][101];
    bool help(string s1, string s2, string s3, int p1, int p2, int p3) {
        if (p1 == s1.size() && p2 == s2.size() && p3 == s3.size()) 
            return true;
        if (p3 == s3.size())
            return false;
        if (dp[p1][p2] != -1)
            return dp[p1][p2];
        
        bool path1 = false;
        bool path2 = false;
        if (s1[p1] == s3[p3]) {
            path1 = dp[p1][p2] = help(s1, s2, s3, p1+1, p2, p3+1);
        }
        if (s2[p2] == s3[p3]) {
            path2 = dp[p1][p2] = help(s1, s2, s3, p1, p2+1, p3+1);
        }
        return path1 || path2;
        
    }

    bool isInterleave(string s1, string s2, string s3) {
        memset(dp, -1, sizeof(dp));
        return help(s1, s2, s3, 0, 0, 0);
    }

};

//130. Surrounded Regions
class Solution {
    void dfs(vector<vector<char>>& board, int i, int j) {
        if (i <0 || i >= board.size() 
            || j <0 || j >= board[0].size()
            || board[i][j] != 'O') return;
        board[i][j] = 'B';
        // expand 4 directions if possible
        dfs(board, i - 1, j);
        dfs(board, i + 1, j);
        dfs(board, i, j - 1);
        dfs(board, i, j + 1);
    }
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty()) return;
        int r = board.size();
        int c = board[0].size();
        // find boundary first and last row/column
        for (int j = 0; j < c; j++) {
            if (board[0][j] == 'O') dfs(board, 0, j);
            if (board[r-1][j] == 'O') dfs(board, r-1, j);
        }
        for (int i = 0; i < r; i++) {
            if (board[i][0] == 'O') dfs(board, i, 0);
            if (board[i][c-1] == 'O') dfs(board, i, c -1);
        }

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (board[i][j] == 'B') {
                    board[i][j] = 'O';
                }
            }
        }
    }
};
//134. Gas Station
class Solution {
public:
    int canCompleteCircuit1(vector<int>& gas, vector<int>& cost) {
        for (int i = 0 ; i < gas.size(); i++) {
            cost[i] = gas[i] - cost[i];
        }
        int state = 0;
        for (int i = 0; i < cost.size(); i++) {
            state += cost[i];
        }
        if (state < 0) return -1;
        state = 0;
        int idx = 0;
        for (int i = 0; i < cost.size(); i++) {
            state += cost[i];
            if (state < 0) {
                idx = i + 1;
                state = 0;
            }
        }
        return idx;
    }

    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int ret = 0;
        int curGas = 0;
        int totalGas = 0;
        int totalCost = 0;

        for (int i = 0; i < n; i++) {
            totalGas += gas[i];
            totalCost += cost[i];
            curGas += gas[i] - cost[i];
            if (curGas < 0) {
                ret = i+1;
                curGas = 0;
            }
        }
        if (totalGas < totalCost) return -1;
        return ret;
    }
};

//116. Populating Next Right Pointers in Each Node
class Solution {
public:
    Node* connectDFS(Node* root) {
        if (!root) return nullptr;
        auto L = root->left, R = root->right, N = root->next;
        if (L) {
            L->next = R;
            if (N) R->next = N->left;
            connect(L);
            connect(R);
        }
        return root;
    }
    Node* connect(Node* root) {
        if (!root) return nullptr;
        Node* cur = root, *L = cur->left;
        while (L) {
            cur->left->next = cur->right;
            if (cur->next) {
                cur->right->next = cur->next->left;
                cur = cur->next;
            }
            else {
                cur = L;
                L = cur->left; //descend!
            }
            
        }
        return root;
    }
};

//96. Unique Binary Search Trees
class Solution {
public:
    int numTrees1(int n) {
        if (n <= 1) return 1;

        int ret = 0;
        for (int i = 1; i <= n; i++) {
            ret += numTrees(i-1) * numTrees(n-i);
        }
        return ret;
    }

    int solveMem(int n, vector<int> &dp) {
        if (n <=1) return 1;

        if (dp[n] != -1) return dp[n];

        int ret = 0;
        for (int i = 1; i <=n; i++) {
            ret += solveMem(i-1, dp) * solveMem(n-i, dp);
        }
        return dp[n] = ret;
    }


    int numTrees(int n) {
        vector<int> dp(n+1, -1);
        return solveMem(n, dp);
    }
};

//29. Divide Two Integers
class Solution {
public:
    int divide(int dividend, int divisor) {
        if(dividend == divisor)
            return 1;
        bool sign = true;
        //taking care of sign
        if(divisor < 0 && dividend >= 0) sign = false;
        else if(divisor > 0 && dividend <= 0) sign = false;
        long p = abs(dividend);
        long q = abs(divisor);
        long quotient = 0;
        while(p >= q) {
            int count = 0;
            //divisor << count+1 means divisor * 2^(count+1)
            while(p >= (q << (count+1)))
                count++;
            quotient += (1 << count); //2^count
            p -= (q << count);
        }
        //handling overflows
        if(quotient == (1 << 31) && sign)
            return INT_MAX;
        if(quotient == (1 << 31) && !sign)
            return INT_MIN;

        return sign? quotient : -quotient;
    }
};

//18. 4Sum
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;

        for (int i = 0; i< n -3; i++) {
            for (int j = i+1; j < n-2; j++) {
                long long remain = (long long)target 
                    - (long long) nums[i] 
                    - (long long) nums[j];
                int low = j + 1, high = n - 1;
                while (low < high) {
                    if (nums[low] + nums[high] < remain) {
                        low++;
                    }
                    else if (nums[low] + nums[high] > remain) {
                        high--;
                    }
                    else {
                        ret.push_back({nums[i], nums[j], nums[low], nums[high]});
                        int tmp1 = low, tmp2 = high;
                        // skip duplicate
                        while (low < high && nums[low] == nums[tmp1]) low++;
                        while (low < high && nums[high] == nums[tmp2]) high--;
                    }
                }
                while (j+1 < n && nums[j] == nums[j+1]) j++;
            }
            while (i+1 < n && nums[i] == nums[i+1]) i++;
        }
        return ret;
    }
};


//57. Insert Interval
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        int i = 0;
        vector<vector<int>> ret;

        while (i < n && newInterval[0] > intervals[i][1]) {
            ret.push_back(intervals[i]);
            i++;
        }

        while (i < n && newInterval[1] >= intervals[i][0]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ret.push_back(newInterval);

        while (i < n) {
            ret.push_back(intervals[i]);
            i++;
        }
        return ret;
    }
};


//56. Merge Intervals
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end()
            , [](const vector <int> &a, const vector<int>&b) {
            return a[0] < b[0];
        });

        vector<vector<int>> merged;
        vector<int> prev = intervals[0];

        for (int i = 1; i < intervals.size(); i++) {
            vector<int> cur = intervals[i];
            if (cur[0] <= prev[1]) {
                prev[1] = max(prev[1], cur[1]);
            }
            else {
                merged.push_back(prev);
                prev = cur;
            }
        }
        merged.push_back(prev);
        return merged;
    }
};

//16. 3Sum Closest
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int ret = INT_MAX/2; // /2 to avoid overflow

        for (int i = 0; i < nums.size() - 2; i++) {
            int l = i+1;
            int r = nums.size() - 1;
            while (l < r) {
                int cur = nums[i] + nums[l] + nums[r];
                if (abs(cur-target) < abs(ret-target)) {
                    ret = cur;
                }
                if (cur < target) {
                    l++;
                }
                else if (cur > target) {
                    r--;
                }
                else {
                    return ret;
                }
            }
        }
        return ret;
    }
};

//151. Reverse Words in a String
class Solution {
public:
    string reverseWords(string s) {
        stack<string> st;
        string tmp = "";
        string ret ="";

        for (int i =0; i < s.size(); i++) {
            if (s[i] == ' ' && tmp != "") {
                st.push(tmp);
                tmp = "";
            }
            else if (s[i] != ' ') {
                tmp += s[i];
            }
        }

        if (tmp != "") st.push(tmp);

        while (!st.empty()) {
            ret += st.top();
            st.pop();
            if (!st.empty()) {
                ret += " ";
            }
        }
        return ret;
    }
};


//114. Flatten Binary Tree to Linked List
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
    TreeNode* helper(TreeNode* root) {
        if (!root) return NULL;

        auto r = root->right;
        root->right = root->left;
        root->left = NULL;

        auto leftR = helper(root->right);
        if (leftR) {
            leftR->right = r;
        }
        else {
            root->right = r;
        }
        
        auto ret = helper(r);
        if (ret) return ret;
        else if (leftR) return leftR;
        return root;
    }

    void flatten1(TreeNode* root) {
        helper(root);
    }
    
    void flatten(TreeNode* root) {
        if (!root) return;

        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode* cur = st.top();
            st.pop();
            if (cur->right) {
                st.push(cur->right);
            }
            if (cur->left) {
                st.push(cur->left);
            }

            cur->left = NULL;
            if (!st.empty()) {
                cur->right = st.top(); //just link, no pop
            }
        }
    }


};


//143. Reorder List
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
    void reorderList(ListNode* head) {
        if (!head) return ;

        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* prev = NULL;
        ListNode* cur = slow;
        ListNode* next = NULL;
        while (cur) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        ListNode* first = head;
        ListNode* second = prev;
        ListNode* tmp = head;
        while (second->next) {
            tmp = tmp->next;
            first->next = second;
            second = second->next;
            first->next->next = tmp;
            first = first->next->next;
        }
        return ;
    }
};

//24. Swap Nodes in Pairs
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
    ListNode* swapPairs(ListNode* head) {
        int cnt = 0;
        if (!head) return NULL;
        if (!head->next) return head;

        ListNode* prev, *cur, *tmp;
        cur = head;
        head = head->next;
        while (cur && cur->next) {
            tmp = cur->next;
            cur->next = tmp->next;
            tmp->next = cur;
            if (cnt == 1) {
                prev->next = tmp;
            }
            prev = cur;
            cur = cur->next;
            cnt = 1;
        }
        return head;
    }
};

//36. Valid Sudoku
class Solution1{
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_map<int,unordered_map<char,int>> board_map;
        for(auto i = 0; i<9; i++){
            for(auto j = 0; j<9; j++){
                char cell = board[i][j];
                if(cell != '.'){
                    if(board_map[i][cell]++ > 0) return false;
                    if(board_map[j+9][cell]++ > 0) return false;
                    if(board_map[27 + (i/3)*3 +j/3][cell]++ > 0) return false;
                    }
            }
        }
        return true;
    }
};
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_map<char,int> eachBox;
        unordered_map<char,int> row;
        unordered_map<char,int> column ;
        int j= 0 ;
        int i=0 ;
        for( i =0 ; i < 9 ;i++){
            for( j=0 ; j< 9 ;j++){
                if(board[i][j] != '.'){
                    row[board[i][j]]++;
                }
                if(board[j][i]!='.'){
                    column[board[j][i]]++;
                }
                if(row[board[i][j]]>1) return false;
                if(column[board[j][i]]>1) return false ;
            }
            row.clear();
            column.clear();
        }
        for(i=0 ; i < 9 ;i+=3){
            for(j=0 ; j <9 ;j+=3){
                eachBox.clear();
                for(int x = i ; x < i+3 ; x++){
                    for(int y = j ; y < j+3; y++){
                        if(board[x][y]!='.'){
                            eachBox[board[x][y]]++;
                        }
                        if(eachBox[board[x][y]]>1) return false ;
                    }
                }
            }
        }
        return true;
    }

};

//11. Container With Most Water
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0;
        int r = height.size() - 1;
        int ret = 0;

        while (l < r) {
            int w = r - l;
            int h = min(height[l], height[r]);
            int capa = w * h;
            ret = max(ret, capa);
            if (height[l] < height[r]) {
                l++;
            }
            else {
                r--;
            }
        }
        return ret;
    }
};

//43. Multiply Strings
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        string s1 = "";
        string s2 = "";

        if (s1[0] == '-') {
            s1 = "-"; num1 = num1.substr(1);
        }
        if (s2[0] == '-') {
            s2 = "-"; num2 = num2.substr(1);
        }

        if (s1 == "-" && s2 == "-") {
            s1 = s2 = "";
        }

        int n = num1.size();
        int m = num2.size();
        string ret(n+m, '0');

        for (int i = n-1; i >= 0; i--) {
            for (int j = m-1; j >= 0; j--) {
                int num = (num1[i] - '0') * (num2[j] - '0') + (ret[i+j+1] - '0'); // ret w carry
                ret[i+j+1] = num %10 + '0';
                ret[i+j] += num/10;
            }
        }

        int i = 0;
        while (i < ret.size() && ret[i] == '0') i++;
        return s1 + s2 + ret.substr(i);
    }
};

//47. Permutations II
class Solution {
public:
    void help(vector<int> &nums, set<vector<int>> &s, vector<int> cur, int idx) {
        if (idx == nums.size()) {
            s.insert(cur);
            return;
        }
        for (int i = idx; i < cur.size(); i++) {
            swap(cur[idx], cur[i]);
            help(nums, s, cur, idx+1);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ret;
        vector<int> cur = nums;
        sort(cur.begin(), cur.end());

        set<vector<int>> s;
        help(nums, s, cur, 0);
        for (auto it : s) {
            ret.push_back(it);
        }
        return ret;
    }
};

//1140. Stone game II
class Solution {
public:
    int xstoneGameII(vector<int>& piles) {
        int n = piles.size();
        function<int(int, int, int)> f = [&] (int p, int i, int m) -> int {
            if (i == n) return 0;
            int res = p == 1 ? 1000000 : -1, s = 0;
            for (int x = 1; x <= min(2*m, n-i); x++) {
                s += piles[i+x-1];
                if (p == 0) res = max(res, s + f (1, i+x, max(m,x)));
                else        res = min(res, f(0, i+x, max(m,x)));
            }
            return res;
        };
        return f(0, 0, 1);
    }

    int stoneGameII(vector<int>& piles) {
        int n = piles.size();    
        vector dp(2, vector(n+1, vector<int>(n+1, -1)));

        function<int(int, int, int)> f = [&] (int p, int i, int m) -> int {
            if (i == n) return 0;

            if (dp[p][i][m] != -1) return dp[p][i][m];
            int res = p == 1 ? INT_MAX : INT_MIN, s = 0;
            for (int x = 1; x <= min(2*m, n - i); x++) {
                s += piles[i+x-1];
                if (p) {
                    res = min(res, f(0, i+x, max(m, x)));
                }
                else {
                    res = max(res, s + f(1, i+x, max(m, x)));
                }
            }
            return dp[p][i][m] = res;
        };
        return f(0, 0, 1);
    }

};

//877. Stone Game
class Solution {
public:
    bool stoneGame1(vector<int>& piles) {
        return true;
    }
    int dfs(vector<int>& piles,int i,int j,vector<vector<int>> &dp){
        bool aliceTurn = (j -i) % 2;
        if(i>j)
            return 0;
        if(dp[i][j]!=-1)
            return dp[i][j];
        if(aliceTurn)
            return dp[i][j]= max(piles[i]+dfs(piles,i+1,j,dp), piles[j]+dfs(piles,i,j-1,dp));
        
        return dp[i][j]=min(dfs(piles,i+1,j,dp)-piles[i],dfs(piles,i,j-1,dp)-piles[j]);
    }
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n,vector<int>(n,-1));
        return dfs(piles, 0, n-1, dp) >0;
    }
};

//2542. Maximum Subsequence Score
class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<pair<int, int>> v;
        for (int i = 0 ; i < n; i++) {
            v.push_back({nums2[i], nums1[i]});
        }

        sort(v.begin(), v.end(), greater<>());
        priority_queue<int, vector<int>, greater<int>> pq;
        long long sum =0, ret = 0;
        for (int i = 0; i < n; i++) {
            pq.push(v[i].second);
            sum+= v[i].second;
            if (pq.size() > k) {
                sum -= pq.top();
                pq.pop();
            }
            if (pq.size() == k) {
                ret = max(ret, sum * v[i].first);
            }
        }
        return ret;
    }
};

//934. Shortest Bridge
class Solution {
public:
    int n, m;
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = { 0, 0, 1, -1};

    bool isValid( int i, int j) {
        return i < n && i >= 0 && j < m && j >=0;
    }
    void dfs(queue<pair<int, int>> &q, vector<vector<int>> &grid, int i, int j) {
        if (!isValid(i, j) || grid[i][j] != 1) return;
        q.push({i,j});
        grid[i][j] = -1;

        dfs(q, grid, i+1, j);
        dfs(q, grid, i-1, j);
        dfs(q, grid, i, j+1);
        dfs(q, grid, i, j-1);
    }

    int shortestBridge(vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        n = grid.size();
        m = grid[0].size();
        int foundFirstIsland = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    dfs(q, grid, i, j);
                    foundFirstIsland = 1;
                    goto _flip;
                }
            }
        }

_flip:
        int level = 0;
        while (q.size()) {
            int sz = q.size();
            level++;
            for (int i = 0; i < sz; i++) {
                pair<int, int> p = q.front();
                q.pop();

                for (int x = 0; x < 4; x++) {
                    int nr = p.first + dx[x];
                    int nc = p.second + dy[x];
                    if (isValid(nr, nc)) {
                        switch (grid[nr][nc]) {
                            case 0:
                                grid[nr][nc] = -1;
                                q.push({nr,nc});
                                break;
                            case 1:
                                return level - 1;
                            default:
                                break;
                        }
                    }
                }
            }
        }
        return 0;
    }
};


//399. Evaluate Division
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, unordered_map<string, double>> graph = {};
        for (int i = 0; i < equations.size(); i++) {
            graph[equations[i][0]][equations[i][1]] = values[i];
            graph[equations[i][1]][equations[i][0]] = 1/values[i];
        }

        vector<double> ret = {};
        for (auto query : queries) {
            string a = query[0];
            string b = query[1];
            if (graph.count(a) == 0 || graph.count(b) == 0) {
                ret.push_back(-1.0);
            }
            else {
                unordered_map<string, bool> visited = {};
                ret.push_back(dfs(a, b, graph, visited));
            }
        }
        return ret;
    }

    double dfs(string a, string b, unordered_map<string, unordered_map<string, double>> &graph, unordered_map<string, bool> &visited) {
        if (a == b) return 1.0;
        double val = 1.0;
        for (auto item : graph[a]) {
            if (visited.count(item.first) == 0) {
                visited[item.first] = true;
                val = item.second * dfs(item.first, b, graph, visited);
                if (val > 0) return val;
            }
        }
        return -1;
    }
};


//785. Is Graph Bipartite?
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> colors(graph.size(), -1);
        queue<pair<int,int>> q;
        for (int i = 0; i < graph.size(); i++) {
            if (colors[i] == -1) {
                q.push({i, 0});
                colors[i] = 0;

                while (q.size()) {
                    pair<int, int> p = q.front();
                    q.pop();

                    int v = p.first;
                    int c = p.second;

                    for (int j : graph[v]) {
                        if (colors[j] == c) return false;
                        if (colors[j] == -1) {
                            if (c == 0) colors[j] = 1;
                            else colors[j] = 0;
                            q.push({j, colors[j]});
                        }
                    }
                }
            }
        }
        return true;
    }
};

//1557. Minimum Number of Vertices to Reach All Nodes
class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<bool> maps(n, 0);
        vector<int> ret;

        for (int i = 0; i < edges.size(); i++) {
            maps[edges[i][1]] = true;
        }
        
        for (int i = 0; i < maps.size(); i++) {
            if (!maps[i]) {
                ret.push_back(i);
            }
        }
        return ret;
    }
};

//2130. Maximum Twin Sum of a Linked List
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
    int pairSum(ListNode* head) {
        ListNode* slow = head, *fast = head;
        stack<int> ret;
        while (fast && fast->next) {
            ret.push(slow->val);
            slow = slow->next;
            fast = fast->next->next;
        }
        int m = 0;
        //slow = head;
        while (ret.size()) {
            m = max(m, ret.top() + slow->val);
            ret.pop();
            slow = slow->next;
        }
        return m;
    }
};

//1035. Uncrossed Lines
class Solution {
public:
    int solve(int i, int j, vector<int>& nums1, vector<int>& nums2, vector<vector<int>> &memo) {
        if (i <= 0 || j <= 0) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        if (nums1[i - 1] == nums2[j - 1]) {
            memo[i][j] = 1 + solve(i-1, j-1, nums1, nums2, memo);
        }
        else {
            memo[i][j] = max(solve(i, j-1, nums1, nums2, memo), solve(i-1, j, nums1, nums2, memo));
        }
        return memo[i][j];
    }
    int maxUncrossedLines1(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        vector<vector<int>> memo(n1+1, vector<int>(n2+1, -1));
        return solve(n1, n2, nums1, nums2, memo);
    }
    int maxUncrossedLines2(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        vector<vector<int>> memo(n1+1, vector<int>(n2+1, 0));
        
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (nums1[i-1] == nums2[j-1]) {
                    memo[i][j] = 1 + memo[i-1][j-1];
                }
                else {
                    memo[i][j] = max(memo[i][j-1], memo[i-1][j]);
                }
            }
        }
        return memo[n1][n2];
    }
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();

        vector<int> dp(n2 + 1), dpPrev(n2 + 1);

        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[j] = 1 + dpPrev[j - 1];
                } else {
                    dp[j] = max(dp[j - 1], dpPrev[j]);
                }
            }
            dpPrev = dp;
        }

        return dp[n2];
    }
};

//54. Spiral Matrix
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int r_min = 0, c_min = 0;
        int r_max = matrix.size() - 1, c_max = matrix[0].size() - 1;
        double all_items = matrix.size()*matrix[0].size();
        vector<int> ret;

        for (double i = 0, r = 0, c = 0; i < all_items; i++) {
            ret.push_back(matrix[r][c]);
            if      (r == r_min && c != c_max) c++;
            else if (r != r_max && c == c_max) r++;
            else if (r == r_max && c != c_min) c--;
            else if (r != r_min && c == c_min) r--;

            if (r == r_min && c == c_min) {
                r++, c++;
                r_min++, c_min++;
                r_max--, c_max--;
            }
        }
        return ret;
    }
};

//1498. Number of Subsequences That Satisfy the Given Sum Condition
class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        int ret = 0;
        int n = nums.size();
        int mod = 1e9 +7;
        sort(nums.begin(), nums.end());
        int l = 0, r = n - 1;
        vector<int> pows(n, 1);

        for (int i = 1 ; i < n; i++) {
            pows[i] = (pows[i-1] << 1) % mod;
        }
        while (l <= r) {
            if (nums[l] + nums[r] <= target) {
                ret = (ret + pows[r-l]) % mod;
                l++;
            }
            else {
                r--;
            }
        }
        return ret;
    }
};



//17. Letter Combinations of a Phone Number

class Solution {
public:
    vector<string> _ret;
    void solve(string digits, string *arr, int i, string com) {
        if (i == digits.size()) {
            _ret.push_back(com);
            return;
        }
        char c = digits[i];
        string a = arr[c - '0'];
        for (int k = 0; k <a.size(); k++) {
            solve(digits, arr, i+1, com+a[k]);
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> a;
        if (digits.size() == 0) return a;
        string arr[] = {"0","0", "abc", "def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        solve(digits, arr, 0, "");
        return _ret;
    }
};
//77. Combinations

class Solution {
public:
    vector<vector<int>> arr;
    vector<int> nums;
    void bt(vector<int> nums, vector<vector<int>>& arr, int n, int k, int pos, int cur) {
        if (pos == k) {
            arr.push_back(nums);
            return;
        }
        for (int i = cur; i <= n - k + pos + 1; i++) {
            nums[pos] = i;
            bt(nums, arr, n, k, pos+1, i+1);
        }
    }


    vector<vector<int>> combine(int n, int k) {
        nums = vector<int>(k);
        bt(nums, arr, n, k, 0, 1);
        return arr;
    }
};

//712. Minimum ASCII Delete Sum for Two Strings

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1, 0));

        for (int i = 1; i <= s1.size(); i++)
            dp[i][0] = dp[i - 1][0] + s1[i - 1];

        for (int j = 1; j <= s2.size(); j++)
            dp[0][j] = dp[0][j - 1] + s2[j - 1];

        for (int i = 1; i <= s1.size(); i++) {
            for (int j = 1; j <= s2.size(); j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]);
                }
            }
        }
        
        return dp[s1.size()][s2.size()];
    }
};
class Solution1 {
public:
    long long solve(string s1, string s2, vector<vector<int>>&dp, int i, int j) {
        if (i == s1.size() && j == s2.size()) return 0;
        if (i == s1.size()) {
            int d = 0;
            for (int k = j; k < s2.size(); k++) {
                d += (int)s2[k];
            }
            return d;
        }
        if (j == s2.size()) {
            int d = 0;
            for (int k = i; k < s1.size(); k++) {
                d += (int)s1[k];
            }
            return d;
        }
        if (dp[i][j] != -1) return dp[i][j];
        long long ret = 1e9;
        if (s1[i] == s2[j]) {
            ret = solve(s1,s2, dp, i+1, j+1);
        }
        else {
            ret = min(ret, s1[i] + solve(s1, s2, dp, i+1, j));
            ret = min(ret, s2[j] + solve(s1, s2, dp, i, j+1));
        }
        return dp[i][j] = ret;
    }
    int minimumDeleteSum(string s1, string s2) {
        vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), -1));
        return solve(s1, s2, dp, 0, 0);
    }
};

//486. Predict the Winner

class Solution {
public:
    int solve (vector<vector<int>>&dp, vector<int> &nums, int i, int j, int k) {
        if (i > j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        int first = 0, last = 0, ret = 0;
        if (k %2 == 0) {
            first = nums[i] + solve(dp, nums, i+1, j, k+1);
            last = nums[j] + solve(dp, nums, i, j-1, k+1);
            ret = max(first, last);
        }
        else {
            first = -nums[i] + solve(dp, nums, i+1, j, k+1);
            last = -nums[j] + solve(dp, nums, i, j-1, k+1);
            ret = min(first, last);
        }
        return dp[i][j] = ret;
    }

    bool PredictTheWinner(vector<int>& nums) {
        int i = 0;
        int n = nums.size();

        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solve(dp, nums, 0, n-1, 0) >= 0;
    }
};
//1870. Minimum Speed to Arrive on Time

class Solution {
public:
    bool possible(vector<int> & dict, int speed, double hour) {
        double ret = 0;
        for (int i = 0; i < dict.size(); i++) {
            double cost = dict[i]*1.0 /speed;
            if (i != dict.size() -1) {
                ret += ceil(cost);
            }
            else {
                ret += cost;
            }
            if (ret > hour) return false;
        }
        return (ret <= hour);
    }

    int minSpeedOnTime(vector<int>& dist, double hour) {
        int i = 1;
        int j = 1e7;
        int minSpeed = -1;

        while (i <= j){
            int midSpeed = i + (j-i)/2;
            if (possible(dist, midSpeed, hour)) {
                minSpeed = midSpeed;
                j= midSpeed -1;
            }
            else {
                i = midSpeed + 1;
            }
        }
        return minSpeed;
    }
};

//50. Pow(x, n)

class Solution {
public:
 double solve(double x,int n){
          if(n==0){
            return 1; //power of 0 is 1;
        }
       double temp=myPow(x,n/2);
        temp=temp*temp;
        if(n%2==0){ // if even  return  just without doing nothing
            return temp;
        }
        else{
            return temp*x;//if odd multiple  return by multipling once more with given number
        }
    }
    double myPow(double x, int n) {
        double ans=solve(x,abs(n));
        if(n<0)
            return 1/ans;
            return ans;
       
    }
}; 
//894. All Possible Full Binary Trees

class Solution {
public:
    unordered_map<int, vector<TreeNode*>> memo;
    vector<TreeNode*> allPossibleFBT(int n) {
        if ((n % 2) == 0) {
            return {};
        }
        if (n == 1) {
            return {new TreeNode()};
        }
        if (memo.find(n) != memo.end()) {
            return memo[n];
        }
        vector<TreeNode*> ret;
        for (int i = 1; i < n; i+=2) {
            vector<TreeNode*> left = allPossibleFBT(i);
            vector<TreeNode*> right = allPossibleFBT(n - i - 1);

            for (auto l : left) {
                for(auto r : right) {
                    TreeNode *root = new TreeNode(0, l, r);
                    ret.push_back(root);
                }
            }
        }
        memo[n] = ret;
        return memo[n];
    }
};
//688. Knight Probability in Chessboard

class Solution {
public:

double dp[30][30][105];
int X[8]={ 2, 1, -1, -2, -2, -1, 1, 2 };
int Y[8]={ 1, 2, 2, 1, -1, -2, -2, -1 };

double dfs(int i,int j,int k, int n)
{
    if(i < 0 || j < 0 ||i >= n || j >= n) return 0;
    if(k == 0) return 1;
    if(dp[i][j][k] != 0) return dp[i][j][k];

    double res = 0;

    for(int l = 0;l < 8; ++l)
    {
      int x = i + X[l];
      int y = j + Y[l];
      res += dfs(x,y,k-1,n);
    }
    return dp[i][j][k] += (res/8.0);
}

    double knightProbability(int n, int k, int row, int column) {

        memset(dp,0,sizeof(dp));
        return dfs(row,column,k,n); 
    }
};
//735. Asteroid Collision

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;
        
        for (int asteroid : asteroids) {
            int flag = 1;
            while (!st.empty() && (st.top() > 0 && asteroid < 0)) {
                // If the top asteroid in the stack is smaller, then it will explode.
                // Hence pop it from the stack, also continue with the next asteroid in the stack.
                if (abs(st.top()) < abs(asteroid)) {
                    st.pop();
                    continue;
                }
                // If both asteroids are the same size, then both asteroids will explode.
                // Pop the asteroid from the stack; also, we won't push the current asteroid to the stack.
                else if (abs(st.top()) == abs(asteroid)) {
                    st.pop();
                }

                // If we reach here, the current asteroid will be destroyed
                // Hence, we should not add it to the stack
                flag = 0;
                break;
            }
            
            if (flag) {
                st.push(asteroid);
            }
        }
        
        // Add the asteroids from the stack to the vector in the reverse order.
        vector<int> remainingAsteroids (st.size());
        for (int i = remainingAsteroids.size() - 1; i >= 0; i--){
            remainingAsteroids[i] = st.top();
            st.pop();
        }
        
        return remainingAsteroids;
    }
};
//435. Non-overlapping Intervals

bool cmp(vector<int> &a, vector<int> &b) {
    return a[1] < b[1];
}

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        int ret = 0;
        int k = INT_MIN;

        for (int i = 0; i < intervals.size(); i++) {
            int x = intervals[i][0];
            int y = intervals[i][1];

            if (x >= k) {
                k = y;
            }
            else {
                ret++;
            }
        }
        return ret;
    }
};
//445. Add Two Numbers II

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* temp;
        while (head) {
            // Keep the next node.
             temp = head->next;
            // reverse the link
            head->next = prev;
            // Update the previous node and the current node.
            prev = head;
            head = temp;
        }
        return prev;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* r1 = reverseList(l1);
        ListNode* r2 = reverseList(l2);

        int totalSum = 0;
        int carry = 0;
        ListNode* ans = new ListNode();
        while (r1 || r2) {
            if (r1) {
                totalSum += r1->val;
                r1 = r1->next;
            }
            if (r2) {
                totalSum += r2->val;
                r2 = r2->next;
            }

            ans->val = totalSum % 10;
            carry = totalSum / 10;
            ListNode* head = new ListNode(carry);
            head->next = ans;
            ans = head;
            totalSum = carry;
        }

        return carry == 0 ? ans->next : ans;
    }
};
class Solution1 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1, s2;
        while (l1) {
            s1.push(l1->val);
            l1 = l1->next;
        }
        while (l2) {
            s2.push(l2->val);
            l2 = l2->next;
        }

        int totalSum = 0, carry = 0;
        ListNode* ret = new ListNode();
        while (!s1.empty() || !s2.empty()) {
            if (!s1.empty()) {
                totalSum += s1.top();
                s1.pop();
            }
            if (!s2.empty()) {
                totalSum += s2.top();
                s2.pop();
            }

            ret->val = totalSum % 10;
            carry = totalSum / 10;
            ListNode* next = new ListNode(carry);
            next->next = ret;
            ret = next;
            totalSum = carry;
        }
        return carry == 0 ? ret->next : ret;
    }
};
//1218. Longest Arithmetic Subsequence of Given Difference

class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        unordered_map<int, int> dp;
        int ret = 1;

        for (int a : arr) {
            int beforeA = dp.count(a-difference) ? dp[a-difference] : 0;
            dp[a] = beforeA + 1;
            ret = max(ret, dp[a]);
        }
        return ret;
    }
};
//802. Find Eventual Safe States
//Kahn'
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<int> vis(n,0);
        vector<int> dis(n,0);
        vector<int> adj[n];
        for(int i=0;i<n;i++){
            for(auto &x:graph[i]){
                adj[x].push_back(i);
                dis[i]++;
            }
        }
        queue<int> q;
        for(int i=0;i<n;i++){
            if(dis[i]==0){
                q.push(i);
            }
        }
        vector<int> ans;
        while(!q.empty()){
            int node=q.front();
            ans.push_back(node);
            q.pop();
            for(auto x:adj[node]){
                dis[x]--;
                if(dis[x]==0){
                    q.push(x);
                }
            }
        }
        sort(ans.begin(),ans.end());
        return ans;
    }
};

class Solution1 {
public:
    bool dfs(int node, vector<vector<int>>& adj, vector<bool>& visit, vector<bool>& inStack) {
        // If the node is already in the stack, we have a cycle.
        if (inStack[node]) {
            return true;
        }
        if (visit[node]) {
            return false;
        }
        // Mark the current node as visited and part of current recursion stack.
        visit[node] = true;
        inStack[node] = true;
        for (auto neighbor : adj[node]) {
            if (dfs(neighbor, adj, visit, inStack)) {
                return true;
            }
        }
        // Remove the node from the stack.
        inStack[node] = false;
        return false;
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> adj(n);

        for (int i = 0; i < n; i++) {
            for (auto node : graph[i]) {
                adj[i].push_back(node);
            }
        }

        vector<bool> visit(n), inStack(n);

        for (int i = 0; i < n; i++) {
            dfs(i, adj, visit, inStack);
        }

        vector<int> safeNodes;
        for (int i = 0; i < n; i++) {
            if (!inStack[i]) {
                safeNodes.push_back(i);
            }
        }
        return safeNodes;
    }
};

//863. All Nodes Distance K in Binary Tree

class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> ret;
        unordered_map<int, TreeNode*> parent;
        queue<TreeNode*> q;

        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto top = q.front();
                q.pop();

                if (top->left) {
                    parent[top->left->val] = top;
                    q.push(top->left);
                }
                if (top->right) {
                    parent[top->right->val] = top;
                    q.push(top->right);
                }
            }
        }

        unordered_map<int, int> visited;
        q.push(target);
        while (k-- && !q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto top = q.front();
                q.pop();

                visited[top->val] = 1;
                if (top->left && !visited[top->left->val]) {
                    q.push(top->left);
                }
                if (top->right && !visited[top->right->val]) {
                    q.push(top->right);
                }
                
                if (parent[top->val] && !visited[parent[top->val]->val]) {
                    q.push(parent[top->val]);
                }
            }
        }

        while (!q.empty()) {
            ret.push_back(q.front()->val);
            q.pop();
        }
        return ret;
    }
};
//1493. Longest Subarray of 1's After Deleting One Element

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int zeroCount = 0;
        int ret = 0;
        int start = 0;

        for (int i = 0; i < nums.size(); i++) {
            zeroCount += (nums[i] == 0);
            while (zeroCount > 1) {
                zeroCount -= (nums[start] == 0);
                start++;
            }
            ret = max(ret, i - start);
        }
        return ret;
    }
};
//137. Single Number II

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ones = 0;
        int twos = 0;

        for (int num : nums) {
            ones ^= (num & ~twos);
            twos ^= (num & ~ones);
        }
        return ones;
    }
};

//2305. Fair Distribution of Cookies

class Solution {
public:
    int distributeCookies(vector<int>& cookies, int k) {
        vector<int> distributes(k, 0);

        return dfs(0, distributes, cookies, k, k);
    }

    int dfs(int i, vector<int>& distributes, vector<int>& cookies, int k, int zeroCount) {
        if (cookies.size() - i < zeroCount) {
            return INT_MAX;
        }

        if (i == cookies.size()) {
            return *max_element(distributes.begin(), distributes.end());
        }

        int ret = INT_MAX;
        for (int j = 0; j < k; ++j) {
            zeroCount -= distributes[j] == 0 ? 1 : 0;
            distributes[j] += cookies[i];
            ret = min(ret, dfs(i+1, distributes, cookies, k, zeroCount));
            distributes[j] -= cookies[i];
            zeroCount += distributes[j] == 0 ? 1 : 0;
        }
        return ret;
    }
};


//1027. Longest Arithmetic Subsequence

class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n  = nums.size();
        if (n <=2) {
            return n;
        }
        int longest = 2;
        vector<unordered_map<int, int>> dp(n);

        for (int i = 0; i < n; i++) {
            for (int j =0; j < i; j++) {
                int diff = nums[i] - nums[j];
                dp[i][diff] = dp[j].count(diff) ? dp[j][diff] + 1 : 2;
                longest = max(longest, dp[i][diff]);
            }
        }
        return longest;
    }
}; 

class Solution:
    def longestArithSeqLength(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 2:
            return n

        longest = 2
        dp = [{} for _ in range(n)]

        for i in range(n):
            for j in range(i):
                diff = nums[i] - nums[j]
                dp[i][diff] = dp[j].get(diff, 1) + 1
                longest = max(longest, dp[i][diff])

        return longest
//1161. Maximum Level Sum of a Binary Tree

class Solution {
public:
    void dfs(TreeNode* node, int level, vector<int>& sumLvl) {
        if (!node) return;

        if (sumLvl.size() == level) {
            sumLvl.push_back(node->val);
        }
        else {
            sumLvl[level] += node->val;
        }
        dfs(node->left, level+1, sumLvl);
        dfs(node->right, level+1, sumLvl);
    }

    int maxLevelSum(TreeNode* root) {
        vector<int> sumLvl;
        dfs(root, 0, sumLvl);

        int maxSum = INT_MIN;
        int ret = 0;

        for (int i = 0; i < sumLvl.size(); i++) {
            if (maxSum < sumLvl[i]) {
                maxSum = sumLvl[i];
                ret = i+1;
            }
        }

        return ret;
    }
};
class Solution1 {
public:
    int maxLevelSum(TreeNode* root) {
        int maxSum = INT_MIN;
        int ret = 0;
        int level = 0;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            level++;
            int sumAtCurLvl = 0;

            for (int sz = q.size(); sz > 0; sz--) {
                TreeNode* node = q.front();
                q.pop();
                sumAtCurLvl += node->val;
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            if (maxSum < sumAtCurLvl) {
                maxSum = sumAtCurLvl;
                ret = level;
            }
        }
        return ret;
    }
};
//2352. Equal Row and Column Pairs
class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        map <vector<int>, int> hashmap;
        int ret = 0;
        int rowNb = grid.size();
        int colNb = grid[0].size();
        for (int i = 0; i < rowNb; i++) {
            hashmap[grid[i]]++;
        }
        for (int j = 0; j < colNb; j++) {
            vector<int> cur;
            for (int i = 0; i < rowNb; i++) {
                cur.emplace_back(grid[i][j]);
            }
            ret += hashmap[cur];
        }
        return ret;
    }
};

class TrieNode:
    def __init__(self):
        self.count = 0
        self.children = {}

class Trie:
    def __init__(self):
        self.trie = TrieNode()
    
    def insert (self, array) :
        myTrie = self.trie
        for a in array :
            if a not in myTrie.children :
                myTrie.children[a] = TrieNode()
            myTrie = myTrie.children[a]
            myTrie.count += 1

    def search (self, array):
        myTrie = self.trie
        for a in array:
            if a in myTrie.children:
                myTrie = myTrie.children[a]
            else :
                return 0
        return myTrie.count

class Solution:
    def equalPairs(self, grid: List[List[int]]) -> int:
        myTrie = Trie()
        count = 0
        n  = len(grid)

        for r in grid:
            myTrie.insert(r)

        for c in range(n):
            colArr = [grid[i][c] for i in range(n)]
            count += myTrie.search(colArr)
        return count

class Solution2:
    def equalPairs(self, grid: List[List[int]]) -> int:
        count = 0
        n = len(grid)

        rowCounter = collections.Counter(tuple(row) for row in grid)

        for c in range(n) :
            col = [grid[i][c] for i in range(n)]
            count += rowCounter[tuple(col)]
        return count


class Solution1:
    def equalPairs(self, grid: List[List[int]]) -> int:
        count = 0
        n = len(grid)

        for r in range (n) : 
            for c in range (n):
                match = True

                for i in range (n) :
                    if grid[r][i] != grid [i][c] :
                        match = False
                        break
                count += int(match)
        return count

//1146. Snapshot Array
class SnapshotArray {
    int snapId;
    vector<vector<pair<int, int>>> history;
public:
    SnapshotArray(int length) {
        this->snapId = 0;
        this->history.resize(length);
        for (int i = 0; i < length; i++) {
            history[i].push_back(make_pair(0,0));
        }
    }
    
    void set(int index, int val) {
        history[index].push_back(make_pair(snapId, val));
    }
    
    int snap() {
        return snapId++;
    }
    
    int get(int index, int snap_id) {
        auto it = upper_bound(history[index].begin(), history[index].end(), make_pair(snap_id, INT_MAX));
        return prev(it)->second;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */

//1802. Maximum Value at a Given Index in a Bounded Array
class Solution {
public:
    long calc(long n) {
        return (n*(n+1)) / 2;
    }

    long getSum (int totalLen, int val) {
        long totalSum = 0;
        int descLen = val;

        if (totalLen >= descLen) {
            long curSum = calc(val);
            int remainSum = totalLen - descLen;
            totalSum = curSum + remainSum;
        }
        else {
            long lastVal = descLen - totalLen;
            totalSum = calc(val) - calc(lastVal);
        }
        return totalSum;
    }

    int maxValue(int n, int index, int maxSum) {
        int low = 1, high = maxSum;
        int leftCount = index, rightCount = n - index - 1;
        int ret = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            long leftSum = getSum(leftCount, mid - 1);
            long rightSum = getSum(rightCount, mid - 1);
            long totalSum = leftSum + mid + rightSum;
            if (totalSum > maxSum) {
                high = mid -1;
            }
            else {
                ret = mid;
                low = mid + 1;
            }
        }
        return ret;
    }
};


//1318. Minimum Flips to Make a OR b Equal to c
class Solution {
public:
    int minFlips(int a, int b, int c) {
        int ret = 0;

        while (a !=0 | b != 0 | c != 0) {
            if ((c & 1) == 1) {
                if ((a & 1) == 0 && (b & 1) == 0 ) {
                    ret++;
                }
            }
            else {
                ret += (a & 1) + (b & 1);
            }
            a >>= 1;
            b >>= 1;
            c >>= 1;
        }
        return ret;
    }
};
class Solution:
    def minFlips(self, a: int, b: int, c: int) -> int:
        ret = 0

        while a != 0 or b != 0 or c != 0 :
            if c & 1 == 1 :
                if a & 1 == 0 and b & 1 == 0 :
                    ret += 1
            else :
                ret += (a & 1) + (b & 1)
            a >>= 1
            b >>= 1
            c >>= 1

        return ret



//547. Number of Provinces
class Solution {
public:
    void dfs(int node, vector<vector<int>>& isConnected, vector<bool>& visited) {
        visited[node] = true;
        for (int i = 0; i < isConnected.size(); i++) {
            if (isConnected[node][i] && !visited[i]) {
                dfs(i, isConnected, visited);
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        int numberOfComponents = 0;
        vector<bool> visited(n);

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                numberOfComponents++;
                dfs (i, isConnected, visited);
            }
        }
        return numberOfComponents;
    }
};
class Solution:
    def findCircleNum(self, isConnected: List[List[int]]) -> int:
        n = len(isConnected)
        provinces = 0
        visited = [False] * n

        def dfs(node) :
            visited[node] = True
            for neighbor in range(n) :
                if isConnected[neighbor][node] == 1 and not visited[neighbor] :
                    dfs(neighbor)
        
        for i in range(n) :
            if not visited[i] :
                provinces += 1
                dfs(i)

        return provinces
        



//1376. Time Needed to Inform All Employees
class Solution {
public:
    int maxTime = INT_MIN;

    void dfs (vector<int> subordinates[], vector<int>& informTime, int curID, int time) {
        this->maxTime = max(this->maxTime, time);

        for (auto sub : subordinates[curID]) {
            dfs (subordinates, informTime, sub, time + informTime[curID]);
        }
    }
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        vector<int> subordinates[n];

        for (int i = 0; i <n; i++) {
            if (manager[i] != -1) {
                subordinates[manager[i]].push_back(i);
            }
        }

        dfs(subordinates, informTime, headID, 0);
        return this->maxTime;
    }
};
class Solution:
    def dfs (self, managerID, informTime, adjList) :
        maxTime = 0
        for subordinate in adjList[managerID]:
            maxTime = max (maxTime, self.dfs(subordinate, informTime, adjList))
        return maxTime + informTime[managerID]


    def numOfMinutes(self, n: int, headID: int, manager: List[int], informTime: List[int]) -> int:
        adjList = defaultdict(list)
        for i in range(n):
            if manager[i] != -1:
                adjList[manager[i]].append(i)
        return self.dfs(headID, informTime, adjList)

			
			
			
			
			
			
//2101. Detonate the Maximum Bombs

#define ll long long int

class Solution {
public:
    void dfs(vector<vector<int>> &gr, vector<bool> &visited, int &c, int &i) {
        visited[i] = true;
        c++;
        for (int j = 0; j < gr[i].size(); j++) {
            if (!visited[gr[i][j]]) {
                dfs (gr, visited, c, gr[i][j]);
            }
        }
    }

    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<vector<int>> gr(n);

        // d^2 = x^2 + y^2
        for (int i = 0; i < n; i++) {
            ll x1 = bombs[i][0];
            ll y1 = bombs[i][1];
            ll r1 = bombs[i][2];

            for (int j = 0; j < n; j++) {
                ll x,y;
                x = abs(x1 - bombs[j][0]);
                y = abs(y1 - bombs[j][1]);
                if (x * x + y * y <= r1 * r1)
                    gr[i].push_back(j);
            }
        }
            
        int res = INT_MIN;
        for (int i = 0; i < n; i++) {
            int c = 0;
            vector<bool> visited (n, false);
            dfs (gr, visited, c, i);
            res = max(res, c);
        }
        return res;
    }
};
/*
class Solution:
    def maximumDetonation(self, bombs: List[List[int]]) -> int:
        adj = collections.defaultdict(list)

        for i in range(len(bombs)) :
            for j in range (i+1, len(bombs)) :
                x1, y1, r1 = bombs[i]
                x2, y2, r2 = bombs[j]

                d = sqrt ((x1 - x2)**2 + (y1 -y2)**2)

                if d <= r1 :
                    adj[i].append(j)
                if d <= r2 :
                    adj[j].append(i)

        def dfs(i, visit) :
            if i in visit :
                return 0
            visit.add(i)

            for neighbor in adj[i]:
                dfs(neighbor, visit)
            return len(visit)


        res = 0

        for i in range(len(bombs)) :
            res = max(res, dfs(i, set()))
        return res

*/

//1091. Shortest Path in Binary Matrix
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        queue<pair<pair<int, int>, int>> q;
        q.push({{0, 0}, 1});

        if (grid[0][0] == 1) return -1;

        if (grid[0][0] == 0 && grid.size() ==1 && grid[0].size() == 1) return 1;

        vector<vector<bool>> visited(grid.size(), vector<bool>(grid.size(), false));
        visited[0][0] = true;

        while (!q.empty()) {
            auto p = q.front().first;
            int x = p.first;
            int y = p.second;
            int lengthOfPath = q.front().second;
            q.pop();

            vector<pair<int, int>> neighbors = {
                    {0, 1}, {0, -1}
                    ,{1, 0}, {-1, 0}
                    ,{1, 1}, {-1, -1}
                    ,{-1, 1}, {1, -1}
                };
            for (auto neighbor : neighbors) {
                int newX = neighbor.first + x;
                int newY = neighbor.second + y;
                
                if (newX >=0 && newY >=0 && newX < grid.size() && newY <grid[0].size()
                    && grid[newX][newY] == 0 && !visited[newX][newY]) {
                        q.push({{newX, newY}, lengthOfPath+1});
                        visited[newX][newY] = true;

                        if (newX == grid.size() - 1  && newY == grid[0].size() -1) {
                            return lengthOfPath + 1;
                        }
                    }
            }
        }
        return -1;
    }
};

/*
class Solution:
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        n = len(grid)
        if grid[0][0] or grid[n-1][n-1] :
            return -1

        q = [(0, 0, 1)]
        grid[0][0] = 1

        for i, j, d in q:
            if i == n-1 and j == n-1:
                return d
            directions = [
                (i - 1, j - 1), (i - 1, j), (i - 1, j + 1),
                (i, j - 1), (i, j + 1),
                (i + 1, j - 1), (i + 1, j), (i + 1, j + 1)
            ]
            for x, y in directions :
                if 0 <= x < n and 0 <= y <n and not grid[x][y]:
                    grid[x][y] = 1
                    q.append((x, y, d +1))
        return -1


*/

// 1396. Design Underground System
class UndergroundSystem {
    unordered_map<int, pair<string, int>> checkInStation;
    unordered_map<string, pair<int, int>> checkOutStation;
public:
    UndergroundSystem() {
        
    }
    
    void checkIn(int id, string stationName, int t) {
        checkInStation[id] = {stationName, t};
    }
    
    void checkOut(int id, string stationName, int t) {
        auto ci = checkInStation[id];
        checkInStation.erase(id);
        auto route = ci.first + "-" + stationName;
        checkOutStation[route].first += t - ci.second;
        checkOutStation[route].second += 1;
    }
    
    double getAverageTime(string startStation, string endStation) {
        auto route = startStation + "-" + endStation;
        auto time = checkOutStation[route];
        return (double)time.first/time.second;
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
/* PYTHON 3  VERSION
class UndergroundSystem:

    def __init__(self):
        self.travel_times = {}
        self.check_ins = {}
        
    def checkIn(self, id: int, stationName: str, t: int) -> None:
        self.check_ins[id] = (stationName, t)
        
    def checkOut(self, id: int, stationName: str, t: int) -> None:
        start_station, t1 = self.check_ins.pop(id)
        route = (start_station, stationName)
        t2 = t - t1
        if route in self.travel_times:
            total_time, count = self.travel_times[route]
            self.travel_times[route] = (total_time + t2, count + 1)
        else:
            self.travel_times[route] = (t2, 1)

    def getAverageTime(self, startStation: str, endStation: str) -> float:
        route = (startStation, endStation)
        total_time, count = self.travel_times[route]
        return total_time/count

*/







//28. Find the Index of the First Occurrence in a String
class Solution {
public:
    int strStr(string haystack, string needle) {
        int szH = haystack.size();
        int szN = needle.size();
        int j = 0;

        if (szH == 0) 
            return 0;
        for (int i = 0; i < szH; i++) {
            if (haystack[i] == needle[j]) {
                j++;
            }
            else {
		// reset the index of haystack by the current window's size
                i -= j; 
                j = 0;
            }
            if (j == szN) {
                return i - j + 1;
            }
        }
        return -1;
    }
};

//994. Rotting Oranges
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) 
    {
        
        vector<int> dir={-1,0,1,0,-1}; //used for finding all 4 adjacent coordinates
        
        int m=grid.size();
        int n=grid[0].size();
        
        queue<pair<int,int>> q;
        int fresh=0; //To keep track of all fresh oranges left
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
            {
                if(grid[i][j]==2)
                    q.push({i,j});
                if(grid[i][j]==1)
                    fresh++;
            }
        int ans=-1; //initialised to -1 since after each step we increment the time by 1 and initially all rotten oranges started at 0.
        while(!q.empty())
        {
            int sz=q.size();
            while(sz--)
            {
                pair<int,int> p=q.front();
                q.pop();
                for(int i=0;i<4;i++)
                {
                    int r=p.first+dir[i];
                    int c=p.second+dir[i+1];
                    if(r>=0 && r<m && c>=0 && c<n &&grid[r][c]==1)
                    {
                        grid[r][c]=2;
                        q.push({r,c});
                        fresh--; // decrement by 1 foreach fresh orange that now is rotten
                    }
                    
                }
            }
            ans++; //incremented after each minute passes
        }
        if(fresh>0) return -1; //if fresh>0 that means there are fresh oranges left
        if(ans==-1) return 0; //we initialised with -1, so if there were no oranges it'd take 0 mins.
        return ans;
        
    }
};

//131. Palindrome Partitioning
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string> > ret;
        if(s.empty()) return ret;
        
        vector<string> path;
        dfs(0, s, path, ret);
        
        return ret;
    }
    
    void dfs(int index, string& s, vector<string>& path, vector<vector<string> >& ret) {
        if(index == s.size()) {
            ret.push_back(path);
            return;
        }
        for(int i = index; i < s.size(); ++i) {
            if(isPalindrome(s, index, i)) {
                path.push_back(s.substr(index, i - index + 1));
                dfs(i+1, s, path, ret);
                path.pop_back();
            }
        }
    }
    
    bool isPalindrome(const string& s, int start, int end) {
        while(start <= end) {
            if(s[start++] != s[end--])
                return false;
        }
        return true;
    }
};

//128. Longest Consecutive Sequence
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(!size(nums)) return 0;
        sort(begin(nums), end(nums));
        int longest = 0, cur_longest = 1;
        for(int i = 1; i < size(nums); i++) 
            if(nums[i] == nums[i - 1]) continue;
            else if(nums[i] == nums[i - 1] + 1) cur_longest++; // consecutive element - update current streak length
            else longest = max(longest, cur_longest), cur_longest = 1;  // reset current streak length
        return max(longest, cur_longest);
    }
};

//33. Search in Rotated Sorted Array
class Solution {
public:
    int search1(int A[], int n, int target) {
        int lo=0,hi=n-1;
        // find the index of the smallest value using binary search.
        // Loop will terminate since mid < hi, and lo or hi will shrink by at least 1.
        // Proof by contradiction that mid < hi: if mid==hi, then lo==hi and loop would have been terminated.
        while(lo<hi){
            int mid=(lo+hi)/2;
            if(A[mid]>A[hi]) lo=mid+1;
            else hi=mid;
        }
        // lo==hi is the index of the smallest value and also the number of places rotated.
        int rot=lo;
        lo=0;hi=n-1;
        // The usual binary search and accounting for rotation.
        while(lo<=hi){
            int mid=(lo+hi)/2;
            int realmid=(mid+rot)%n;
            if(A[realmid]==target)return realmid;
            if(A[realmid]<target)lo=mid+1;
            else hi=mid-1;
        }
        return -1;
    }
    
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[low] <= nums[mid]) {
                if (nums[low] <= target && target <= nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else {
                if (nums[mid] <= target && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        
        return -1;
    }
};

//875. Koko Eating Bananas
/*
    Given array of banana piles, guards are gone for h hours
    Return min int k such that can eat all banans within h
    Ex. piles = [3,6,7,11] h = 8 -> 4 (1@3, 2@6, 2@7, 3@11)

    Binary search, for each k count hours needed, store min

    Time: O(n x log m) -> n = # of piles, m = max # in a pile
    Space: O(1)
*/

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();
        
        int low = 1;
        int high = 0;
        for (int i = 0; i < n; i++) {
            high = max(high, piles[i]);
        }
        
        int result = high;
        
        while (low <= high) {
            int k = low + (high - low) / 2;
            long int hours = 0;
            for (int i = 0; i < n; i++) {
                hours += ceil((double) piles[i] / k);
            }
            if (hours <= h) {
                result = min(result, k);
                high = k - 1;
            } else {
                low = k + 1;
            }
        }
        
        return result;
    }
};
//53. Maximum Subarray
class Solution {
public:
    int maxSubArray1(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n);
        dp[0] = nums[0];
        int max = dp[0];
        
        for (int i = 1; i< n; i++) {
            dp[i] = nums[i] + (dp[i-1] > 0 ? dp[i-1] : 0);
            max = std::max(max, dp[i]);
        }
        return max;
    }
    
    int maxSubArray(vector<int>& nums) {
        int curr = nums[0];
        int result = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            curr = max(curr + nums[i], nums[i]);
            result = max(result, curr);
        }
        
        return result;
    }
};

//5. Longest Palindromic Substring
class Solution {
public:
     string longestPalindrome1(string s) 
    {   
        int len = s.size();
        int dp[len][len];
        memset(dp,0,sizeof(dp));
        int end=1;
        int start=0;

        for(int i=0;i<len;i++)
        {
            dp[i][i] = 1;
        }
        for(int i=0;i<len-1;i++)
        {
            if(s[i]==s[i+1])
            { dp[i][i+1]=1;start=i;end=2;}
        }

        for(int j=2;j<len;j++)
        {
            for(int i=0;i< len-j;i++)
            {  
                int left=i; //start point
                int right = i+j;  //ending point

                if(dp[left+1][right-1]==1 && s[left]==s[right]) 
                {
                    dp[left][right]=1; start=i; end=j+1; 
                }        
            }
        }
       return s.substr(start, end);
    }
    
    string longestPalindrome(string s) {
        if(s.size()==0) return "";
        int i = 0, j = 0;
        int n = s.size();
        //initialize P[n][n], we only need half of P, and initialize it like: (e.g. : s="abbc")
        bool P[n][n];
        for(int x = 0;x<n;x++){
            P[x][x]=true;
            if(x==n-1) break;
            P[x][x+1] = (s[x]==s[x+1]);
        }
        //dp 
        for(int i = n-3; i>=0; --i){
            for(int j = i+2;j<n; ++j){
                P[i][j] = (P[i+1][j-1] && s[i]==s[j]);     
            }
        }
        //get maxstr result
        int max = 0;
        string maxstr = "";
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if(P[i][j]==true and j-i+1>max){
                    max = j-i+1;
                    maxstr = s.substr(i,j-i+1);
                }
            }
        }
        return maxstr;
    }
};

//39. Combination Sum
class Solution {
public:
    
    void Sum(vector<int>& candidates, int target, vector<vector<int> >& res, vector<int>& r, int i)
    {
        
        if(target == 0)
        {
            // if we get exact answer
            res.push_back(r);
            return;
        }
        
        while(i <  candidates.size() && target - candidates[i] >= 0)
        {
            // Till every element in the array starting
            // from i which can contribute to the target
            r.push_back(candidates[i]);// add them to vector
            
            // recur for next numbers
            Sum(candidates,target - candidates[i],res,r,i);
            ++i;
            
            // Remove number from vector (backtracking)
            r.pop_back();
        }
    }
    
     
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end()); // sort candidates array
        
        // remove duplicates
        candidates.erase(unique(candidates.begin(),candidates.end()),candidates.end());
        
        vector<int> r;
        vector<vector<int> > res;
        
        Sum(candidates,target,res,r,0);
        
        return res;
    }
};

//208. Implement Trie (Prefix Tree)
class Trie {
    Trie* next[26] = {};
    bool isWord = false;
    
public:
    Trie() {};
    
    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            c -= 'a';
            if (!node->next[c]) {
                node->next[c] = new Trie();
            }
            node = node->next[c];
        }
        node->isWord = true;
    }
    
    bool search(string word) {
        Trie *node = this;
        
        for (char c : word) {
            c -= 'a';
            if (!node->next[c]) {
                return false;
            }
            node = node->next[c];
        }
        return node->isWord;
    }

    bool startsWith(string preFix) {
        Trie* node = this;
        for (char c : preFix) {
            c -= 'a';
            if (!node->next[c]) {
                return false;
            }
            node = node->next[c];
        }
        return true;
    }

};

class Trie2 {
public:
    Trie2() {}

    void insert(string word) {
        Trie2* node = this;
        for (char ch : word) {
            if (!node->next.count(ch)) { node->next[ch] = new Trie2(); }
            node = node->next[ch];
        }
        node->isword = true;
    }

    bool search(string word) {
        Trie2* node = this;
        for (char ch : word) {
            if (!node->next.count(ch)) { return false; }
            node = node->next[ch];
        }
        return node->isword;
    }

    bool startsWith(string prefix) {
        Trie2* node = this;
        for (char ch : prefix) {
            if (!node->next.count(ch)) { return false; }
            node = node->next[ch];
        }
        return true;
    }

private:
    map<char, Trie2*> next = {};
    bool isword = false;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

//74. Search a 2D Matrix
class Solution {
public:
    bool searchMatrix3(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();
        
		// if matrix have 0 rows or 0 colums
        if(n == 0 || m == 0)
            return false;
        
		// treating matrix as array just taking care of endices
		// [0..n*m]
        int start = 0, end = m*n - 1;
        
        while(start <= end)
        {
            int mid = start + (end - start) / 2;
			// a[x] : matrix[x / m][x % m] formulae
            int ind = matrix[mid/m][mid%m];
            if (target == ind)
                return true;
			// left half
            else if(target < ind)
                end = mid - 1;
            else
			// right half
                start = mid + 1;       
        }
        return false;
    }
    bool searchMatrix2(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size(),
			cols = matrix[0].size(),
            row = 0, col = cols - 1;
			
        while (row < rows && col > -1) {
            int cur = matrix[row][col];
            if (cur == target) return true;
            if (target > cur) row++;
            else col--;
        }
        
        return false;
    }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int lowRow = 0;
        int highRow = matrix.size() - 1;
        
        while (lowRow < highRow) {
            int mid = lowRow + (highRow - lowRow) / 2;
            if (matrix[mid][0] == target) {
                return true;
            }
            if (matrix[mid][0] < target && target < matrix[mid + 1][0]) {
                lowRow = mid;
                break;
            }
            if (matrix[mid][0] < target) {
                lowRow = mid + 1;
            } else {
                highRow = mid - 1;
            }
        }
        
        int lowCol = 0;
        int highCol = matrix[0].size() - 1;
        
        while (lowCol <= highCol) {
            int mid = lowCol + (highCol - lowCol) / 2;
            if (matrix[lowRow][mid] == target) {
                return true;
            }
            if (matrix[lowRow][mid] < target) {
                lowCol = mid + 1;
            } else {
                highCol = mid - 1;
            }
        }
        
        return false;
    }
};
//155. Min Stack
class MinStack {
public:
    vector<int> a;
    vector<int> min;
    MinStack() {
        min.push_back(2147483647);
    }
    void push(int x) {
        a.push_back(x);
        if (x < min.back()) {
            min.push_back(x);
        } else {
            min.push_back(min.back());
        }
    }

    void pop() {
        a.pop_back();
        min.pop_back();
    }

    int top() {
        return a.back();
    }

    int getMin() {
        return min.back();
    }
};
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */


//567. Permutation in String
class Solution {
    bool areVectorsEqual(vector<int> a, vector<int> b){
        for(int i=0; i<26; i++){
            if(a[i]!=b[i]) return false;
        }
        return true;
    }
public:
    bool checkInclusion(string s1, string s2) {
        if(s2.size()<s1.size()) return false;
        vector<int> freqS1(26, 0);
        for(char c: s1) freqS1[c-'a']++;
        
        vector<int> freqS2(26, 0);
        int i=0, j=0;
        
        while(j<s2.size()){
            freqS2[s2[j]-'a']++;
            
            if(j-i+1==s1.size()){
                if(areVectorsEqual(freqS1, freqS2)) return true;
            }
            
            if(j-i+1<s1.size()) j++;
            else{
                freqS2[s2[i]-'a']--;
                i++;
                j++;
            }
        }
        return false;
    }
};


//40. Combination Sum II
class Solution {
    void dfs(vector<int>& nums, int target, int idx, vector<int>& cur, vector<vector<int>> &ret) {
        if (target == 0) {
            ret.push_back(cur);
            return;
        }
        
        for (int i = idx; i < nums.size(); i++) {
            if (i > idx && nums[i] == nums[i - 1]) { //hmm
                continue;
            }
            if (nums[i] <= target) {
                cur.push_back(nums[i]);
                dfs(nums, target - nums[i], i + 1, cur, ret);
                cur.pop_back();
            }
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
        vector<vector<int>> ret;
        vector<int> cur;
        sort(nums.begin(), nums.end());
        dfs(nums, target, 0, cur, ret);
        return ret;
    }
};

//133. Clone Graph
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == NULL) {
            return NULL;
        }
        
        Node* copy = new Node(node->val);
        std::vector<Node*> check(101, NULL);
        
        queue<Node*> q;
        q.push(node);
        check[node->val] = copy;
        
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            
            for (int i = 0; i < curr->neighbors.size(); i++) {
                Node* neighbor = curr->neighbors[i];
                
                if (!check[neighbor->val]) {
                    check[neighbor->val] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                
                check[curr->val]->neighbors.push_back(check[neighbor->val]);
            }
        }
        
        return copy;
    }
    
    Node* cloneGraph1(Node* node) {
        if (node == NULL) {
            return NULL;
        }
        
        Node* copy = new Node(node->val);
        m[node] = copy;
        
        queue<Node*> q;
        q.push(node);
        
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            
            for (int i = 0; i < curr->neighbors.size(); i++) {
                Node* neighbor = curr->neighbors[i];
                
                if (m.find(neighbor) == m.end()) {
                    m[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                
                m[curr]->neighbors.push_back(m[neighbor]);
            }
        }
        
        return copy;
    }
private:
    unordered_map<Node*, Node*> m;
};


//309. Best Time to Buy and Sell Stock with Cooldown
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sold = 0;
        int hold = INT_MIN;
        int rest = 0;
        
        for (int i = 0; i < prices.size(); i++) {
            int prevSold = sold;
            sold = hold + prices[i];
            hold = max(hold, rest - prices[i]);
            rest = max(rest, prevSold);
        }
        
        return max(sold, rest);
    }
};

//78. Subsets
class Solution {
public:

    void dfs(vector<int> &nums, vector<vector<int>> &ret, vector<int> &cur, int i) {
        ret.push_back(cur);
        for (int j = i; j < nums.size(); j++) {
            cur.push_back(nums[j]);
            dfs(nums, ret, cur, j+1);
            cur.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> cur;
        vector<vector<int>> ret;
        dfs(nums, ret, cur, 0);
        return ret;
    }
};

//1143. Longest Common Subsequence
class Solution {
public:
    int longestCommonSubsequencrrre(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (text1[i] == text2[j]) {
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
                }
            }
        }
        
        return dp[0][0];
    }
};

int longestCommonSubsequence(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();
    vector<int> prev(m+1,0), curr(m+1,0);

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            curr[j] = text1[i-1]==text2[j-1] ? prev[j-1] + 1 : max(prev[j],curr[j-1]);
        
        prev = curr;
    }
    return prev[m];
}
//62. Unique Paths
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> grid(m, vector<int>(n, 0));
        
        for (int i = 0; i < m; i++) {
            grid[i][0] = 1;
        }
        for (int j = 0; j < n; j++) {
            grid[0][j] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
            }
        }
        
        return grid[m - 1][n - 1];
    }
};

//90. Subsets II
class Solution {
private:
    void dfs(vector<int> &nums, int start, vector<int> & cur, vector<vector<int>> &ret) {
        ret.push_back(cur);
        
        for (int i = start; i < nums.size(); i++) {
            if (i > start && nums[i] == nums[i-1]) {
                continue;        
            }
            cur.push_back(nums[i]);
            dfs(nums, i+1, cur, ret);
            cur.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> cur;
        vector<vector<int>> ret;
        
        sort(nums.begin(), nums.end());
        dfs(nums, 0, cur, ret);
        return ret;
    }
};
/*Runtime: 5 ms, faster than 57.72% of C++ online submissions for Subsets II.
Memory Usage: 7.5 MB, less than 89.01% of C++ online submissions for Subsets II.*/

//238. Product of Array Except Self
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, 1);
        
        int pre = 1;
        for (int i = 0; i < n; i++) {
            ret[i] = pre;
            pre *= nums[i];
        }
        
        int pos = 1;
        for (int i = n - 1; i >= 0; i--) {
            ret[i] = ret[i] * pos;
            pos *= nums[i];
        }
        return ret;
    }
};
/*Runtime: 16 ms, faster than 99.46% of C++ online submissions for Product of Array Except Self.
Memory Usage: 24.1 MB, less than 63.84% of C++ online submissions for Product of Array Except Self.
*/

//347. Top K Frequent Elements
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> map;
        
        for (int i = 0; i <n; i++) {
            map[nums[i]]++;
        }
        
        vector<vector<int>> buckets(n+1);
        for (auto it = map.begin(); it != map.end(); it++) {
            buckets[it->second].push_back(it->first);
        }
        
        vector<int> result;
        
        for (int i = n; i >= 0; i--) {
            if (result.size() >= k) {
                break;
            }
            if (!buckets[i].empty()) {
                result.insert(result.end(), buckets[i].begin(), buckets[i].end());
            }
        }
        return result;
    }
};
/*Runtime: 23 ms, faster than 63.92% of C++ online submissions for Top K Frequent Elements.
Memory Usage: 15.4 MB, less than 6.80% of C++ online submissions for Top K Frequent Elements.*/
//17. Letter Combinations of a Phone Number
class Solution {
private:
    void solve(string digits,vector <string> &ans,string output,int index,string mapping[10]){
        if(index>=digits.length()){
            ans.push_back(output);
            return;
        }
        int num = digits[index]-'0';
        string value = mapping[num];
        for(int i = 0; i < value.length(); i++){
            output.push_back(value[i]);
            solve(digits,ans , output, index +1,mapping);
            output.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        vector <string> ans;
        if(digits.size()==0){
            return ans;
        }
        string output = "";
        int index = 0;
        string mapping[10]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        solve(digits,ans,output,index,mapping);
        return ans;
    }
};



//695. Max Area of Island
int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        int result = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    result = max(result, dfs(grid, i, j, m, n));
                }
            }
        }
        
        return result;
    }
private:
    int dfs(vector<vector<int>>& grid, int i, int j, int m, int n) {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0) {
            return 0;
        }
        grid[i][j] = 0;
        
        return 1 + dfs(grid, i - 1, j, m, n) + dfs(grid, i + 1, j, m, n)
            + dfs(grid, i, j - 1, m, n) + dfs(grid, i, j + 1, m, n);
    }
/*Runtime: 20 ms, faster than 85.47% of C++ online submissions for Max Area of Island.
Memory Usage: 23.2 MB, less than 86.95% of C++ online submissions for Max Area of Island.*/





//15. 3Sum
class Solution {
public:
    
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin() , nums.end());     //Sorted Array
        if(nums.size() < 3){                // Base Case 1
            return {};
        }
        if(nums[0] > 0){                    // Base Case 2
            return {};
        }
        unordered_map<int , int> hashMap;
        for(int i = 0 ; i < nums.size() ; ++i){     //Hashing of Indices
            hashMap[nums[i]] = i;
        }
        vector<vector<int>> answer;
        for(int i = 0 ; i < nums.size() - 2 ; ++i){     //Traversing the array to fix the number.
            if(nums[i] > 0){     //If number fixed is +ve, stop there because we can't make it zero by searching after it.
                break;
            }
            for(int j = i + 1 ; j < nums.size() - 1 ; ++j){     //Fixing another number after first number
                int required = -1*(nums[i] + nums[j]);    //To make sum 0, we would require the -ve sum of both fixed numbers.
                if(hashMap.count(required) && hashMap.find(required)->second > j){ //If it exists in hashmap and its last occurrence index > 2nd fixed index, we found our triplet.
                    answer.push_back({nums[i] , nums[j] , required});
                }
                j = hashMap.find(nums[j])->second; //Update j to last occurence of 2nd fixed number to avoid duplicate triplets.
            }
            i = hashMap.find(nums[i])->second;     //Update i to last occurence of 1st fixed number to avoid duplicate triplets.
        }
        return answer;  //Return answer vector.
    }
    /*Runtime: 340 ms, faster than 20.07% of C++ online submissions for 3Sum.
Memory Usage: 20.4 MB, less than 52.46% of C++ online submissions for 3Sum.*/
    
//     vector<vector<int>> threeSum(vector<int>& nums) {
//         vector<vector<int>> result;
        
//         int n = nums.size();
//         if (n < 3) {
//             return result;
//         }
        
//         sort(nums.begin(), nums.end());
        
//         for (int i = 0; i < n - 2; i++) {
//             if (nums[i] > 0) {
//                 break;
//             }
//             if (i > 0 && nums[i - 1] == nums[i]) {
//                 continue;
//             }
            
//             int j = i + 1;
//             int k = n - 1;
            
//             while (j < k) {
//                 int sum = nums[i] + nums[j] + nums[k];
                
//                 if (sum < 0) {
//                     j++;
//                 } else if (sum > 0) {
//                     k--;
//                 } else {
//                     result.push_back({nums[i], nums[j], nums[k]});
                    
//                     while (j < k && nums[j] == nums[j + 1]) {
//                         j++;
//                     }
//                     j++;
                    
//                     while (j < k && nums[k - 1] == nums[k]) {
//                         k--;
//                     }
//                     k--;
//                 }
//             }
//         }
        
//         return result;
//     }
};
/*Runtime: 136 ms, faster than 59.32% of C++ online submissions for 3Sum.
Memory Usage: 19.8 MB, less than 98.25% of C++ online submissions for 3Sum.*/


//200. Number of Islands
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int rs = 0;
        
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '1') {
                    rs++;
                    maskConnected(grid, i, j);
                }
            }
        }
        return rs;
    }
    
private:
    void maskConnected(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[i].size()
            || grid[i][j] == '0') return;
        grid[i][j] = '0';
        maskConnected(grid, i-1, j);
        maskConnected(grid, i+1, j);
        maskConnected(grid, i, j-1);
        maskConnected(grid, i, j+1);
    }
};

/*
Runtime: 48 ms, faster than 66.36% of C++ online submissions for Number of Islands.
Memory Usage: 12.3 MB, less than 83.09% of C++ online submissions for Number of Islands.
*/
int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0, islands = 0, offsets[] = {0, 1, 0, -1, 0};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    islands++;
                    grid[i][j] = '0';
                    queue<pair<int, int>> todo;
                    todo.push({i, j});
                    while (!todo.empty()) {
                        pair<int, int> p = todo.front();
                        todo.pop();
                        for (int k = 0; k < 4; k++) {
                            int r = p.first + offsets[k], c = p.second + offsets[k + 1];
                            if (r >= 0 && r < m && c >= 0 && c < n && grid[r][c] == '1') {
                                grid[r][c] = '0';
                                todo.push({r, c});
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }

// 213. House Robber II
// class Solution {
// public:
//     int rob(vector<int>& nums) {
//         vector<int> loots(nums.size()+1);
//         bool useFirst = false;
//         if (nums.size() == 0) return 0;
//         loots[0] = 0;
//         loots[1] = nums[0];
//         for (int i = 1; i < nums.size(); i++) {
//             if (loots[i-1]+nums[i] > loots[i]) {
//                 if (i - 1 == 0) useFirst = true;
                
//             }
//             if (i == nums.size() && useFirst) {
//                     loots[i+1] = loots[i];
//                     break;
//                 }
//             loots[i+1] = max(loots[i-1]+nums[i], loots[i]);
//         }
//         return loots[nums.size()];
//     }
// };
class Solution {
public:

//     int robOriginal(vector<int>& nums) {
//         int a = 0, b = 0, res = 0;
        
//         for(int i = 0; i < nums.size(); ++i){
//             res = max(b + nums[i], a);
//             b = a;
//             a = res;
//         }
        
//         return res;
//     }

//     int rob(vector<int>& nums) {
//         if(nums.empty()) return 0;
//         if(nums.size() == 1) return nums[0];
        
//         vector<int> numsA(nums.begin() + 1, nums.end());
//         vector<int> numsB(nums.begin(), nums.end()-1);
        
//         return max(robOriginal(numsA), robOriginal(numsB));
//     }
    int rob(vector<int>& nums)
	{
	    if(nums.size() == 0)
		return 0;
	    if(nums.size() == 1)
		return nums[0];

	    int pre1 = 0, cur1 = 0;
	    for(int i = 0; i < nums.size() - 1; ++ i)
	    {
		int temp = pre1;
		pre1 = cur1;
		cur1 = max(temp + nums[i], pre1);
	    }

	    int pre2 = 0, cur2 = 0;
	    for(int i = 1; i < nums.size(); ++ i)
	    {
		int temp = pre2;
		pre2 = cur2;
		cur2 = max(temp + nums[i], pre2);
	    }

	    return max(cur1, cur2);
	}
};

// 198. House Robber
 int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        vector<int> dp(nums.size()+1);
        dp[0] = 0;
        dp[1] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            dp[i+1] = max(dp[i], dp[i-1]+nums[i]);
        }
        return dp[nums.size()];
        
    }
class Solution {
public:
//     int rob(vector<int>& nums) {
//         int a = 0;
//         int b = 0;

//         for (int i=0; i<nums.size(); i++)
//         {
//             if (i&1)
//             {
                
//                 b = max(a, b+nums[i]);
//             }
//             else
//             {
//                 a = max(a+nums[i], b);
//             }
//         }

//         return max(a, b);
//     }
    /*
    There is some frustration when people publish their perfect fine-grained algorithms without sharing any information abut how they were derived. This is an attempt to change the situation. There is not much more explanation but it's rather an example of higher level improvements. Converting a solution to the next step shouldn't be as hard as attempting to come up with perfect algorithm at first attempt.

This particular problem and most of others can be approached using the following sequence:

Find recursive relation
Recursive (top-down)
Recursive + memo (top-down)
Iterative + memo (bottom-up)
Iterative + N variables (bottom-up)
Step 1. Figure out recursive relation.
A robber has 2 options: a) rob current house i; b) don't rob current house.
If an option "a" is selected it means she can't rob previous i-1 house but can safely proceed to the one before previous i-2 and gets all cumulative loot that follows.
If an option "b" is selected the robber gets all the possible loot from robbery of i-1 and all the following buildings.
So it boils down to calculating what is more profitable:

robbery of current house + loot from houses before the previous
loot from the previous house robbery and any loot captured before that
rob(i) = Math.max( rob(i - 2) + currentHouseValue, rob(i - 1) )

Step 2. Recursive (top-down)
Converting the recurrent relation from Step 1 shound't be very hard.

public int rob(int[] nums) {
    return rob(nums, nums.length - 1);
}
private int rob(int[] nums, int i) {
    if (i < 0) {
        return 0;
    }
    return Math.max(rob(nums, i - 2) + nums[i], rob(nums, i - 1));
}
This algorithm will process the same i multiple times and it needs improvement. Time complexity: [to fill]

Step 3. Recursive + memo (top-down).

int[] memo;
public int rob(int[] nums) {
    memo = new int[nums.length + 1];
    Arrays.fill(memo, -1);
    return rob(nums, nums.length - 1);
}

private int rob(int[] nums, int i) {
    if (i < 0) {
        return 0;
    }
    if (memo[i] >= 0) {
        return memo[i];
    }
    int result = Math.max(rob(nums, i - 2) + nums[i], rob(nums, i - 1));
    memo[i] = result;
    return result;
}
Much better, this should run in O(n) time. Space complexity is O(n) as well, because of the recursion stack, let's try to get rid of it.

Step 4. Iterative + memo (bottom-up)

public int rob(int[] nums) {
    if (nums.length == 0) return 0;
    int[] memo = new int[nums.length + 1];
    memo[0] = 0;
    memo[1] = nums[0];
    for (int i = 1; i < nums.length; i++) {
        int val = nums[i];
        memo[i+1] = Math.max(memo[i], memo[i-1] + val);
    }
    return memo[nums.length];
}
Step 5. Iterative + 2 variables (bottom-up)
We can notice that in the previous step we use only memo[i] and memo[i-1], so going just 2 steps back. We can hold them in 2 variables instead. This optimization is met in Fibonacci sequence creation and some other problems [to paste links].*/
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int prev1 = 0;
        int prev2 = 0;
        for (int num : nums) {
            int tmp = prev1;
            prev1 = max(prev2 + num, prev1);
            prev2 = tmp;
        }
        return prev1;
    }
};

// 209. Minimum Size Subarray Sum
class Solution {
public:
    
    int minSubArrayLen(int s, vector<int>& nums) {
        int l = 0, r = 0, n = nums.size(), sum = 0, len = INT_MAX;
        while (r < n) {
            sum += nums[r++];
            while (sum >= s) {
                len = min(len, r - l);
                sum -= nums[l++];
            }
        }
        return len == INT_MAX ? 0 : len;
    }
        
//     int minSubArrayLen(int target, vector<int>& nums) {
//         int l = 0, r = 0, tmp = nums[l];
//         int rs = INT_MAX;
//         for (int i = 0; i < nums.size(); i++) {
//             if (r!=0) {
//                 tmp += nums[r];
//             }
//             if (tmp >= target) {
//                 rs = min(rs, r - l -1);
//                 tmp -= nums[l];
//                 l++;
//             }
//             r++;
//         }
//         return rs;
//     }
};

// 424. Longest Repeating Character Replacement
/*
If we want to replace the characters in a substring and make it into the longest repeating, then we definitely want to find the character with maximum frequency and then replace all the other characters by this one, hence in this way, we can minimize the number of replacement.

Hence, with such idea within mind, when we build a sliding window [start, end], we want this window to have this property: (the length of the window) - (the maximum frequency of the character in this window) > k. Then we can see that [start, end-1] can be fit into k replacement.

If we can find such a sliding window, then how to we move this window? We can simply shift the start to start+1, since in this way this window will no longer hold the property (the length of the window) - (the maximum frequency of the character in this window) > k, and then we can keep moving end to end+1 to see if we have a longer window.

Below, we use localMaxFreq to record the maximum frequency seen so far in the current window.

class Solution {
public:

 int characterReplacement(string s, int k) {
        vector<int> count(26);
        int maxCount = 0;
        
        int i = 0;
        int j = 0;
        
        int result = 0;
        
        while (j < s.size()) {
            count[s[j] - 'A']++;
            maxCount = max(maxCount, count[s[j] - 'A']);
            if (j - i + 1 - maxCount > k) {
                count[s[i] - 'A']--;
                i++;
            }
            result = max(result, j - i + 1);
            j++;
        }
        
        return result;
    }
    /*Runtime: 13 ms, faster than 69.75% of C++ online submissions for Longest Repeating Character Replacement.
Memory Usage: 6.9 MB, less than 85.18% of C++ online submissions for Longest Repeating Character Replacement.*/


    int characterReplacement(string s, int k) {
        int size = s.size(); int ret = 0;
        vector<int> count(26, 0);
        int start = 0; int end = 0; int localMaxFreq = 0; 
        for(; end<size; end++){
            count[s[end]-'A'] += 1;
            localMaxFreq = max(localMaxFreq, count[s[end]-'A']);
            if((end-start+1)-localMaxFreq > k) {
                ret = max(ret, (end-start));
                count[s[start]-'A'] -= 1;
                start += 1;
                localMaxFreq = *(max_element(count.begin(), count.end()));
            }
        }
        return max(ret, end-start);
    }
};
The above code uses localMaxFreq to keep track the maximum frequency of each current window. However, if we think carefully, we can find that if localMaxFreq of window A >= localMaxFreq of window B, then the A window must have longer length than the B window, this is because since both window A and window B hold this property (the length of the window) - (the maximum frequency of the character in this window) > k, and if localMaxFreq of window A >= localMaxFreq of window B, then (the length of the window A) >= (the length of the window B) by simple algebra .

Hence, we only need to keep track of a globalMaxFreq to record the globally maximum frequency of each window what has been seen so far.
*/
class Solution {
public:
    int characterReplacement(string s, int k) {
        int size = s.size(); int ret = 0;
        vector<int> count(26, 0);
        int start = 0; int end = 0; int globalMaxFreq = 0; 
        for(; end<size; end++){
            count[s[end]-'A'] += 1;
            globalMaxFreq = max(globalMaxFreq, count[s[end]-'A']);
            if((end-start+1)-globalMaxFreq > k) {
                ret = max(ret, (end-start));
                count[s[start]-'A'] -= 1;
                start += 1;
            }
        }
        return max(ret, end-start);
    }
};
// 46. Permutations
class Solution {
public:
    
    void bt(vector<int> &nums, vector<int> &candidate, vector<vector<int> > &rs, vector<bool> &used) {
        if (candidate.size() == nums.size()) {
            rs.push_back(candidate);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (!used[i]) {
                used[i] = true;
                candidate.push_back(nums[i]);
                bt(nums, candidate, rs, used);
                used[i] = false;
                candidate.pop_back();
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> candidate;
        vector<vector<int>> rs;
        vector<bool> used(nums.size(), false);
        
        bt(nums, candidate, rs, used);
        return rs;
    }
};
//86. Partition List
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        
        ListNode* last = nullptr;
        ListNode* prev = nullptr;
        auto node = head;
        while(node) {
            if(node->val < x) {
                
                if(!prev) {
                    last = node;
                    node = node->next;    
                    continue;
                }
                
                prev->next = node->next;
                
                auto nextNode = node->next;
                if(last) {
                    node->next = last->next;    
                    last->next = node;
                } else {
                    node->next = head;
                    head = node;
                }
                
                last = node;
                node = nextNode;
                
            } else {
                prev = node;
                node = node->next;    
            }
        }
        
        return head;
    }
};

class Solution {
public:
    
    ListNode* partition(ListNode* head, int x) {
        
        ListNode* small = new ListNode(-1);
        ListNode* large = new ListNode(-1);
        ListNode* small_head = small;
        ListNode* large_head = large;
        
        while (head){
            if (head->val < x){
                small->next = head;
                small = small -> next;
                head = head -> next;
                small->next = NULL;
            }
            else{
                large->next = head;
                large = large -> next;
                head = head -> next;
                large -> next = NULL;
            }
        }
        small -> next = large_head -> next;

        return small_head -> next;
    }
};


//93. Restore IP Addresses
//https://leetcode.com/problems/restore-ip-addresses/submissions/
vector<string> restoreIpAddresses(string s) {
        if(s.length()<4 ||s.length()>12) return {};
        vector<string> ans;
        backtrackDFS(s, "", 0, 0, ans);
        return ans;
    }
    void backtrackDFS(string s, string curr, int idx, int count, vector<string>& ans){
        if(idx == s.length()){
            if(count == 4){
                curr.pop_back(); //remove last "."
                ans.push_back(curr);
            }
            return;
        }
        int len = s.length();
        int bound = min(len, idx+3);
        string str = "";
        for(int i=idx; i<bound; i++){
            if(i>idx && s[idx]=='0') continue; //start with 0 but not 0
            str += s[i];
            if(stoi(str) >=0 && stoi(str)<=255)
                backtrackDFS(s, curr+str+".", i+1, count+1, ans);
        }
    }

class Solution {
public:
    bool isValid(string temp)
    {
        if(temp[0] == '0')
            return false;
        int m = stoi(temp);
        return m<=255;
    }
    void solve(string s, int n, int curr, int par, string str, vector<string>&res)
    {
        if(curr >= n || par == 4)
        {
            if(n == curr && par == 4)
                res.push_back(str.substr(0, str.length()-1));
            return;
        }
        solve(s, n, curr+1, par+1, str+s[curr]+".", res);
        if(n>=curr+2 && isValid(s.substr(curr, 2)))
            solve(s, n, curr+2, par+1, str+s.substr(curr, 2)+".", res);
        if(n>=curr+3 && isValid(s.substr(curr, 3)))
            solve(s, n, curr+3, par+1, str+s.substr(curr, 3)+".", res);
    }
    vector<string> restoreIpAddresses(string s) {
        vector<string>res;
        int n = s.length();
        solve(s, n, 0, 0, "", res);
        return res;
    }
};


class Solution {
public:

    vector<string>All_Combinations ;
    
    bool isValid(string &s)
    {
        
    string temp = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '.' or i == s.size() - 1 )
        {
            if (i == s.size() - 1)
                temp.push_back(s[i]);

if (i + 1 < s.size() and s[i + 1] == '0' and i+2<s.size() and s[i+2] != '.')  //(Check I)
                return 0;

       if(temp[0]=='0' and temp.size()!=1) return 0 ; //(Check III)
            
            int val = stoi(temp);
            if (val > 255) // (Check IV) 
                return 0;
            temp.clear();
        }
        else if (isdigit(s[i]))
            temp.push_back(s[i]);

        else
            return 0;
    }
    return 1;
}

void solve(string &s, int j, int p)
{ 
// p = No. of points we need to insert
// j = Index at which we need to insert point  .

    if (p == 0)
    {
        All_Combinations.push_back(s);
        return;
    }

    for (int i = j; i < s.size()-1; i++)
    {
        string p1 = s.substr(0, i + 1);
        string p2 = s.substr(i + 1);
        p1.push_back('.');

        s = p1 + p2;

        solve(s, i + 2, p - 1);

        p1.pop_back();
        s = p1 + p2;
    }
    return;
}


    
    vector<string> restoreIpAddresses(string s) {
if(s.size()>12) return {} ; 
    solve(s, 0, 3);
        
        vector<string>ValidIPs={} ;
    for (auto x : All_Combinations)
    {
        if (isValid(x))
            ValidIPs.push_back(x) ; 
    }
   return ValidIPs ;
    }
};

//79. Word Search
//https://leetcode.com/problems/word-search/
bool wordSearch(int i,int j,int idx ,vector<vector<char>>& board, string word, vector<vector<int>>&used)
    {
        //This condition can only occur when the given word exists in the matrix
        if(idx==word.length())
            return true;
        
        //Checking boundary conditions
        if(i<0 || i>=board.size() || j<0 || j>=board[0].size())
            return false;
        
        //If the letter at the current cell doesnt match the letter at idx index of the word OR if we have already used the cell before then return false
        if(word[idx]!=board[i][j] || used[i][j]==1)
            return false;
        
        //Mark the cell as visited
        used[i][j]=1;
        
        //Search horizontally and vertically neighbouring cells for the next letter
        bool left = wordSearch(i,j-1,idx+1,board,word,used);
        bool right = wordSearch(i,j+1,idx+1,board,word,used);
        bool up = wordSearch(i-1,j,idx+1,board,word,used);
        bool down = wordSearch(i+1,j,idx+1,board,word,used);
        
        //Backtrack
        used[i][j]=0;
        
        //Returning true if any one of them is true
        return (left || right || up || down);
        
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        
        //Since we cannot use the same cell more than once, if the length of the word is more than the number of elements in the matrix then we return false
        if(word.length()>n*m)
            return false;
        
        //Declaring another matrix of the same dimension to track the cells used
        vector<vector<int>>used(n,vector<int>(m,0));
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                //if the letter in ith row and jth column of the matrix is equal to the first letter of the word
                if(board[i][j]==word[0])
                {
                    if( wordSearch(i,j,0,board,word,used))
                        return true;
                }
            }
        }     
        return false; 
    }


//30. Substring with Concatenation of All Words
//https://leetcode.com/problems/substring-with-concatenation-of-all-words/
class Solution {
public:
	
	
    struct Node {
        Node *w[26];
        int i;
        Node() {memset(w, 0, sizeof(w)); i = -1;}
    };
	//insert word in to Trie
    void insert(Node *h, string word, int id)
    {
        Node *p = h;
        for (int i = 0; i < word.length(); i ++)
        {
            if (p->w[word[i]-'a'] == NULL) p->w[word[i]-'a'] = new Node();
            p = p->w[word[i]-'a'];
        }
        p->i = id;
    }
	//find word in Trie
    int find(Node *h, string &s, int a, int L)
    {
        Node *p = h;
        for (int i = a; i < a + L && i < s.length(); i ++)
            if (p->w[s[i]-'a']) p = p->w[s[i]-'a'];
            else break;
        return p->i;
    }
    vector<int> findSubstring(string s, vector<string>& words) {
		//sort array to avoid duplicate word
        sort(words.begin(), words.end());
        Node *head = new Node();
        int num[5001] = {0};
        int k = 0;
		//insert words into Trie and count number of each word
        for (int i = 0; i < words.size(); i ++)
            if (i == 0 || words[i-1] != words[i])
            {
                insert(head, words[i], i);
                k = i;
                num[k] = 1;
            }
            else num[k] ++;
        vector<int> res;
        if (words.size() == 0) return res;
        int L = words[0].length();
		//i = start point of search
        for (int i = 0; i < L; i ++)
        {
            int x = i; //start position of result string
            int has[5001] = {0};
            queue<int> qu;
            int n = 0; //number of confirmed words
			//search every L-lenths word
            for (int j = i; j < s.length(); j += L)
            {
                int id = find(head, s, j, L);
                //if not found, move x to next position, clear flags
                if (id == -1)
                {
                    x = j + L;
                    memset(has, 0, sizeof(has));
                    while (!qu.empty()) qu.pop();
                    n = 0;
                }
                //if found
                else
                {
                    //no words[id] left, slide x position, until removed one words[id] flag 
                    while (x <= j && has[id] >= num[id])
                    {
                        int t = qu.front();
                        qu.pop();
                        has[t] --; n --;
                        x += L;
                    }
					//count words[id]
                    n ++; has[id] ++;
                    qu.push(id);
                    //found one result
                    if (n == words.size()) res.push_back(x);
                }
            }
        }
        return res;
    }
};

//https://leetcode.com/problems/string-to-integer-atoi/
//8. String to Integer (atoi)
    bool isDigit(char ch){
        return ch >= '0' && ch <= '9';
    }

    int myAtoi(string s) {
	std::cout << "\n" << __func__;
        
        const int len = s.size();
        
        if(len == 0){
            return 0;
        }
        
        int index = 0;
        while(index < len && s[index] == ' '){
            ++index;
        }

        if(index == len){
            return 0;
        }
        
        char ch;
        bool isNegative = (ch = s[index]) == '-';
        
        if(isNegative || ch == '+'){
            ++index;
        }
		
        const int maxLimit = INT_MAX / 10;
        int result = 0;
        while(index < len && isDigit(ch = s[index])){ 

            int digit = ch - '0';

            if(result > maxLimit || (result == maxLimit && digit > 7)){
                return isNegative ? INT_MIN : INT_MAX;
            }

            result = (result * 10) + digit;
            
            ++index;
        }
        
        return isNegative ? -result : result;
    }
    

//https://leetcode.com/problems/zigzag-conversion/submissions/
// 6. Zigzag Conversion
string convert(string s, int nRows) {
//          if (!str.size() || r <= 0) return "";

//         if (str.size() == 1 || r == 1) return str;
//         string rs;
//         int c = (str.size()/2)+2;
//         char arr[r][c];
//         memset(arr, 0, sizeof (arr));

//         int i = 0, j = 0, idx = 0;
//         for (i = 0; i <= r; i++) {
//             if (idx == str.size()) break;
//             if (i == r) {
//                 while (--i > 0) {
//                     //std::cout << "\n\t\t (zigzag)" << str[idx] << " i=" << i-1 << " j=" << j+1;
//                     arr[--i][++j] = str[idx++];
//                 }
//             }
//             //std::cout << "\n\t\t" << str[idx] << " i=" << i << " j=" << j;
//             arr[i][j] = str[idx++];
//         }
//         for (i = 0; i < r; i++) {
//             for (j = 0; j < c; j++) {
//                 if (arr[i][j] != 0) {
//                     rs += arr[i][j];
//                 }
//             }
//         }
//         return rs;
         if(nRows==1)
        return s;
    
        int y=0;
        bool flag= true;
        string sArray[nRows];
        for(int i=0;i<nRows;i++)
            sArray[i]="";

        for(int i=0;i<s.length();i++){

            sArray[y]+=s[i];

            if(y==0){
                flag=true;
            }
            if(y==nRows-1){
                flag=false;
            }

            if(flag==true){
                y++;
            }else{
                y--;
            }


        }

        string ret="";

        for(int i=0;i<nRows;i++){
            ret+=sArray[i];
        }

        return ret;
    }




int main(){
	auto rs1 = convert("PAYPALISHIRING", 3);
	std::cout << "\n\t rs = " << rs1;


	// 6. atoi
	std::cout << "\n\t" << myAtoi("-43224");
	std::cout << "\n\t" << myAtoi("143224");
	std::cout << "\n";
}
