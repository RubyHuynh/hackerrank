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
