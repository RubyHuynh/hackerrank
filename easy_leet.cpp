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
