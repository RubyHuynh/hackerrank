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
