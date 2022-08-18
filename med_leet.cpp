#include<iostream>
#include<ostream>
#include<string.h>
#include<limits.h>
using namespace std;

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
