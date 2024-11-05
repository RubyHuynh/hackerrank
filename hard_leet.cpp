//410. Split Array Largest Sum
class Solution {
     int help(vector<int>& nums, int maxSum) {
        int ret = 1;
        long long sum = 0;
        for (int i =0; i< nums.size(); i++) {
            if (sum + nums[i] <= maxSum) {
                sum += nums[i];
            }
            else {
                ret++;
                sum =nums[i];
            }
        }
        return ret;
     }
public:
    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        int h = 0;
        int l = 0;
        for (int i = 0; i < n; i++) {
            h += nums[i];
            l = max(l, nums[i]);
        }

        while (l <= h) {
            int m = (l + h) /2;
            int count = help(nums, m);
            if (count > k) {
                l = m + 1;
            }
            else {
                h = m - 1;
            }
        }
        return l;
    }
};

//403. Frog Jump
class Solution {
    map<pair<int, int>, bool> t;
    unordered_set<int> s;
    
    bool help(int lastStone, int curStone, int k) {
        if (curStone == lastStone) return true;
        if (t.find(make_pair(curStone, k)) != t.end()) {
            return t[make_pair(curStone, k)];
        }
        bool ret = false;
        if (k-1 > 0 && s.find(curStone+k-1) != s.end()) {
            ret = ret| help(lastStone, curStone + k-1, k-1);
        }
        if (s.find(curStone+k) != s.end()) {
            ret = ret| help(lastStone, curStone + k, k);
        }
        if (s.find(curStone+k+1) != s.end()) {
            ret = ret| help(lastStone, curStone + k+1, k+1);
        }
        t[make_pair(curStone, k)] = ret;
        return ret;
    }
public:
    bool canCross(vector<int>& stones) {
        if (stones[1] - stones[0] != 1) return false;
        int lastStone = stones[stones.size()-1];
        for (int i : stones) {
            s.insert(i);
        }
        return help(lastStone, stones[1], 1);
    }
};

//68. Text Justification
class Solution {
public:
    string buildline(vector<string>& curr, int maxWidth, int &currlen){
        int spaces = maxWidth - currlen;

        for(int i=0;i<spaces;i++){
            if(curr.size()==1)
                curr[0]+=" ";
            else
                curr[i%(curr.size()-1)]+=" ";
        }

        string finl = accumulate(curr.begin(),curr.end(),string(""));
        curr.clear();
        currlen = 0;
        return finl;
    }
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> curr;
        vector<string> res;
        int currlen = 0;
        for(int i=0;i<words.size();i++){
            if(words[i].length() + currlen + curr.size() > maxWidth){
                res.push_back(buildline(curr,maxWidth,currlen));
            }
            curr.push_back(words[i]);
            currlen+=words[i].length();
        }

        // to take care the last line of series
        string finl;
        for(auto it : curr)
            finl+=it+" ";
        finl.pop_back();
        for(int i = finl.length();i<maxWidth;i++)
            finl+=" ";
        res.push_back(finl);
        return res;
    }
};

class Solution1 {
public:
    vector<string> fullJustify1(vector<string>& words, int maxWidth) {
        vector<string> ret;
        int cur = 0, alen = 0;
        vector<string> aux;
        for (string s : words) {
            int l = s.size();
            if (maxWidth - cur > l) {
                cur += s.size() + 1;
                alen += s.size();
                aux.push_back(s);
            }
            else if (maxWidth - cur == l) {
                cur += s.size();
                alen += s.size();
                aux.push_back(s);
            }
            else {
                cur = 0;
                string help;
                int totalSpaces = maxWidth - alen;
                alen = 0;
                int pos = aux.size() - 1;
                for (string x : aux) {
                    int spaces = 0;
                    if (pos) {
                        spaces = (ceil)(totalSpaces*1.00/pos);
                    }
                    string sp;
                    for (int i = 0; i < spaces; i++) {
                        sp += " ";
                    }
                    help += x + sp;
                    totalSpaces -= spaces;
                    pos--;
                }
                aux.clear();
                help = help.substr(0, maxWidth);
                int extra = maxWidth - help.size();
                for (int i = 0; i < extra; i++) {
                    help += " ";
                }
                ret.push_back(help);
                aux.push_back(s);
                cur += s.size() + 1;
                alen += s.size();
            }
        }
        string help;
        for (string x : aux) {
            help += x + " ";
        }
        int spaces = maxWidth - help.size();
        for (int i = 0; i < spaces; i++) {
            help += " ";
        }
        help = help.substr(0, maxWidth);
        ret.push_back(help);
        return ret;
    }
};


//154. Find Minimum in Rotated Sorted Array II
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, h = nums.size() - 1;
        while (l < h) {
            int m = (h+l)/2;
            if (nums[m] > nums[h]) {
                l = m + 1;
            }
            else if (nums[m] < nums[h]) {
                h = m;
            }
            else {
                h--;
            }
        }
        return nums[l];
    }
};
//871. Minimum Number of Refueling Stops
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int nStation = stations.size();
        vector<long> dp(nStation+1, INT_MIN);

        dp[0] = startFuel;
        for (int i = 0; i < nStation; i++) {
            for (int t = i; t >= 0; t--) {
                if (dp[t] >= stations[i][0]) {
                    dp[t+1] = max(dp[t+1], dp[t] + (long) stations[i][1]);
                }
            }
        }

        for (int i = 0; i <= nStation; i++) {
            if (dp[i] >= target) return i;
        }
        return -1;
    }
};

//174. Dungeon Game
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<vector<int>> hp(m + 1, vector(n + 1, INT_MAX));
        hp[m][n-1] = 1;
        hp[m-1][n] = 1;

        for (int i = m-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                int need = min(hp[i+1][j], hp[i][j+1]) - dungeon[i][j];
                hp[i][j] = need <= 0 ? 1 : need;
            }
        }
        return hp[0][0];
    }
};

//1547. Minimum Cost to Cut a Stick
class Solution {
public:
   int minCost1(int len, vector<int>& cuts) {
       cuts.push_back(0);
       cuts.push_back(len);
       sort(cuts.begin(), cuts.end());
       int n = cuts.size();
       vector<vector<int>> dp(n+1, vector<int>(n+1));

       for (int i = n - 2; i >= 1; i--) {
           for (int j = i; j <= n - 2; j++) {
               int cost = INT_MAX;
               for (int k = i; k <= j; k++) {
                   cost = min (cost, cuts[j+1] - cuts[i -1] + dp[i][k-1] + dp[k+1][j]);
               }
               dp[i][j]= cost;
           }
       }
        return dp[1][n-2];
   }

int solve(int i, int j, vector<int> &cuts, vector<vector<int>> &dp)
{

    if (i > j)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int minm = INT_MAX;

    for (int ind = i; ind <= j; ind++)
    {

        int cost = cuts[j + 1] - cuts[i - 1] + solve(i, ind - 1, cuts, dp) + solve(ind + 1, j, cuts, dp);
        minm = min(minm, cost);
    }

    return dp[i][j] = minm;
}

int minCost(int n, vector<int> &cuts)
{

    int c = cuts.size();
    cuts.push_back(0);
    cuts.push_back(n);

    sort(cuts.begin(), cuts.end());
    vector<vector<int>> dp(c + 1, vector<int>(c + 1, -1));

    return solve(1, c, cuts, dp);
}
};


//1799. Maximize Score After N Operations
class Solution {
public:
    int gcd(int num1, int num2) {
        if (num2 == 0) return num1;
        return gcd(num2, num1%num2);
    }
    int solve(vector<int>& nums, int mask, int op, unordered_map<int, int>& mp) {
        if (mp.find(mask) != mp.end()) return mp[mask];

        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (((1<<i) & mask) || ((1<<j) & mask)) continue;
                int newMask = mask | (1<<i) | (1<<j);
                int score = op * gcd(nums[i], nums[j]);
                mp[mask] = max(mp[mask], score + solve(nums, newMask, op+1, mp));
            }
        }
        return mp[mask];
    }

    int maxScore(vector<int>& nums) {
        unordered_map<int, int> mp;
        return solve(nums, 0, 1, mp);
    }
};


//664. Strange Printer
class Solution {
public:
    int strangePrinter(string s) {
        int n = s.size();
        vector dp(n, vector<int>(n, n));
        for (int length = 1; length <= n; length++) {
            for (int left = 0; left <= n - length; left++) {
                int right = left + length - 1;
                int j = -1;
                for (int i = left; i < right; i++) {
                    if (s[i] != s[right] && j == -1) {
                        j = i;
                    }
                    if (j != -1) {
                        dp[left][right] = min(dp[left][right], 1 + dp[j][i] + dp[i + 1][right]);
                    }
                }
                
                if (j == -1) {
                    dp[left][right] = 0;
                }
            }
        }
        
        return dp[0][n - 1] + 1;
    }
};
class Solution11{
public:
    int solve(string s, vector<vector<int>> &dp, int i, int j) {
        if (i == j) return 1;

        if (dp[i][j] != -1) return dp[i][j];
        int minCut = 1e9;
        for (int k = i; k < j; k++) {
            minCut = min(minCut, (solve(s, dp, i, k) + solve(s, dp, k+1, j)));
        }
        return dp[i][j] = s[i] == s[j] ? minCut - 1 : minCut;
    }
    int strangePrinter(string s) {
        int n = s.length();
        vector<vector<int>> dp (n+1, vector<int>(n+1, -1));
        return solve(s, dp, 0, n-1);
    }
};

//2141. Maximum Running Time of N Computers
class Solution {
public:
    bool possible(int n, vector<int> & batteries, long long hours) {
        long long int time = 0;
        for (int i = 0;  i<batteries.size(); i++) {
            time += batteries[i];
            if (time >= hours) {
                time -= hours;
                n--;
            }
            if (n == 0) return true;
        }
        return false;
    }
    long long maxRunTime(int n, vector<int>& batteries) {
        long long int l = 1; 
        long long int r = 0;

        for (int i = 0; i < batteries.size(); i++)  {
            r += batteries[i];
        }
        r/=n;
        sort(batteries.begin(), batteries.end());

        while (l < r) {
            long long int m = l + (r-l+1)/2;
            if (possible(n, batteries, m)) {
                l = m;
            }
            else {
                r = m -1;
            }
        }
        return l;
    }
}; 


//1601. Maximum Number of Achievable Transfer Requests
class Solution {
public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
        int ret = 0;
        for (int mask = 0; mask < (1<< requests.size()); mask++) {
            vector<int> indegree(n, 0);
            int pos = requests.size() - 1;

            int bitCount = __builtin_popcount(mask);

            if (bitCount <= ret) {
                continue;
            }

            for (int cur = mask; cur > 0; cur >>=1, pos--) {
                if (cur & 1) {
                    indegree[requests[pos][0]]--;
                    indegree[requests[pos][1]]++;
                }
            }
            int flag = 1;
            for (int i = 0; i < n; i++) {
                if (indegree[i]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                ret = bitCount;
            }
        }
        
        return ret;
    }
};

class Solution1 {
public:
    int ret = 0;

    int maximumRequests(int n, vector<vector<int>>& requests) {
        vector<int> indregree(n, 0);
        util(requests, indregree, n, 0, 0);
        return ret;
    }

    void util(vector<vector<int>>& requests, vector<int> & indegree, int n, int index, int count) {
        if (index == requests.size()) {
            for (int i = 0; i <n; i++) {
                if (indegree[i]) {
                    return;
                }
            }
            ret = max(ret, count);
            return;
        }
        indegree[requests[index][0]]--;
        indegree[requests[index][1]]++;
        util(requests, indegree, n, index+1, count+1);
        indegree[requests[index][0]]++;
        indegree[requests[index][1]]--;
        util(requests, indegree, n, index+1, count);
    }
};


//1575. Count All Possible Routes
class Solution {
public:
    int dp[101][201];
    int mod = 1e9 + 7;
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        memset(dp, -1, sizeof(dp));
        return rec(locations, start, finish, fuel);
    }

    int rec(vector<int>& locations, int idx, int finish, int fuel) {
        if (fuel < 0) return 0;
        long long ret = 0;

        if (dp[idx][fuel] != -1) return dp[idx][fuel] % mod;

        for (int i = 0; i < locations.size(); i++) {
            if (i == idx) continue;
            ret = (ret % mod + rec(locations, i, finish, fuel - abs(locations[i] - locations[idx]))%mod) % mod;
        }
        if (idx == finish) return dp[idx][fuel] = (1 + ret) % mod;
        return dp[idx][fuel] = ret % mod;
    }
};

//956. Tallest Billboard
class Solution {
public:
     int tallestBillboard(vector<int>& rods) {
        const auto sum = reduce(rods.begin(), rods.end());
        // Difference cannot be larger than half of the sum.
        vector memo(rods.size(), vector(sum / 2 + 1, -1));
        return helper(rods, 0, sum / 2, 0, memo);
    }

    int helper(
        const vector<int>& rods,
        const size_t idx,
        const int limit,
        const int diff,
        vector<vector<int>>& memo) {

        if (idx == rods.size())
            return diff == 0 ? 0 : INT_MIN; // Using INT_MIN as a sentinel value works because the sum cannot be larger than 5000.

        if (diff > limit)
            return INT_MIN;

        auto& m = memo[idx][diff];
        if (m != -1)
            return m;

        return m = max({
            // Length does not change when we don't pick the rod.
            helper(rods, idx + 1, limit, diff, memo),
            // Length increases when we add the rod to the longer side.
            helper(rods, idx + 1, limit, diff + rods[idx], memo) + rods[idx],
            // Length increases depending on whether the rod is longer than the difference between the sides.
            helper(rods, idx + 1, limit, abs(diff - rods[idx]), memo) + (diff > rods[idx] ? 0 : rods[idx] - diff)});
    }
};


class Solution1 {
public:
    int tallestBillboard(vector<int>& rods) {
        int sum = 0;
        for (int rod : rods) {
            sum += rod;
        }

        int dp[sum + 1];
        dp[0] = 0;

        // Initialize all other elements in dp[] to -1
        for (int i = 1; i <= sum; i++) {
            dp[i] = -1;
        }

        for (int rod : rods) {
            int dpCopy[sum + 1];
            // Copy the current state of dp[] to dpCopy[]
            copy(dp, dp + (sum + 1), dpCopy);

            for (int i = 0; i <= sum - rod; i++) {
                if (dpCopy[i] < 0) continue;

                // Case 1: Place the current rod on the same height billboard
                dp[i + rod] = max(dp[i + rod], dpCopy[i]);

                // Case 2: Place the current rod on the taller billboard
                // Calculate the absolute difference between current height and rod length
                dp[abs(i - rod)] = max(dp[abs(i - rod)], dpCopy[i] + min(i, rod));
            }
        }

        // Return the maximum height of the billboard stored at dp[0]
        return dp[0];
    }
};

//2448. Minimum Cost to Make Array Equal
class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& cost) {
        
        int n = nums.size();
        
        vector<vector<int>> nums_cost(n,vector<int>(2));
        
        for(int i=0;i<n;i++){
            
            nums_cost[i][0] = nums[i];
            nums_cost[i][1] = cost[i];
            
        }
        sort(nums_cost.begin(),nums_cost.end());
        int left_index = 0, right_index = n-1;
        
        long long left_total_cost = 0, right_total_cost = 0;
        
        long left_cost_unit = nums_cost[left_index][1], right_cost_unit = nums_cost[right_index][1];
        
        long difference;
        
        while(right_index - left_index > 0){
           
            if(left_cost_unit<right_cost_unit){
        
                difference = (nums_cost[left_index+1][0] - nums_cost[left_index][0]);
                
                left_total_cost += (difference * left_cost_unit);
                
                left_cost_unit += nums_cost[left_index+1][1];
                
                left_index += 1;
                
            }
            else{
                
                 difference = (nums_cost[right_index][0] - nums_cost[right_index-1][0]);

                right_total_cost += (difference * right_cost_unit);

                right_cost_unit += nums_cost[right_index-1][1];
                
                right_index -= 1;
                
            }
        }
        
        return left_total_cost + right_total_cost;
        
    }
};

class Solution:
    def minCost(self, nums: List[int], cost: List[int]) -> int:
        size = len(nums)
        nums_costs = sorted([(nums[i], cost[i]) for i in range(size)], key=itemgetter(0))
        #nums_costs.item = (num, cost) sorted by num low to high
        
        left_index = 0
        left_cost_accrued = 0
        left_per_unit_cost = nums_costs[left_index][1]
        right_index = size - 1
        right_cost_accrued = 0
        right_per_unit_cost = nums_costs[right_index][1]

        while right_index - left_index > 0:
            if left_per_unit_cost < right_per_unit_cost:
                low_value = nums_costs[left_index][0]
                next_lowest_value = nums_costs[left_index + 1][0]
                left_cost_accrued += (next_lowest_value - low_value) * left_per_unit_cost
                left_per_unit_cost += nums_costs[left_index + 1][1]
                left_index += 1
            else:
                high_value = nums_costs[right_index][0]
                next_highest_value = nums_costs[right_index - 1][0]
                right_cost_accrued += (high_value - next_highest_value) * right_per_unit_cost
                right_per_unit_cost += nums_costs[right_index - 1][1]
                right_index -= 1
        
        total_cost = left_cost_accrued + right_cost_accrued
        return total_cost


//2328. Number of Increasing Paths in a Grid

class Solution {
public:
    int BIG = 1e9 + 7;
    int dfs(int i, int j, int prev, vector<vector<int>> & dp, vector<vector<int>> & grid) {
        int n = grid.size();
        int m = grid[0].size();

        if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] <= prev) {
            return 0;
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        return dp[i][j] = (1 
                            + dfs(i+1, j, grid[i][j], dp, grid)
                            + dfs(i-1, j, grid[i][j], dp, grid)
                            + dfs(i, j+1, grid[i][j], dp, grid)
                            + dfs(i, j-1, grid[i][j], dp, grid)) % BIG;
    }

    int countPaths(vector<vector<int>>& grid) {
        int i, j, n = grid.size(), m = grid[0].size(), ret = 0;
        vector<vector<int>> dp(n, vector<int>(m, -1));

        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                ret = (ret + dfs(i, j, -1, dp, grid)) % BIG;
            }
        }
        return ret;
    }
};

//1187. Make Array Strictly Increasing

class Solution {
    int check(int cur, int left, vector<int>& arr1, vector<int>& arr2, vector<unordered_map<int, int>> &dp) {
        if (cur == arr1.size()) {
            return 0;
        }

        if (dp[cur].find(left) != dp[cur].end()) {
            return dp[cur][left];
        }

        int exclude, include;
        if (arr1[cur] > left) {
            exclude = check(cur+1, arr1[cur], arr1, arr2, dp);
        }
        else {
            exclude = INT_MAX;
        }
        int rep = upper_bound(arr2.begin(), arr2.end(), left) - arr2.begin();
        if (rep == arr2.size()) {
            include = INT_MAX;
        }
        else {
            include = check(cur+1, arr2[rep], arr1, arr2, dp);
        }
        
        if (include == INT_MAX) {
            dp[cur][left] = exclude;
        }
        else {
            dp[cur][left] = min(exclude,include+1);
        }
        return dp[cur][left];
    }

public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        vector<unordered_map<int, int>> dp (2001);

        int val = check(0, INT_MIN, arr1, arr2, dp);
        return (val == INT_MAX) ? -1 : val;
    }
};

//1569. Number of Ways to Reorder Array to Get Same BST

class Solution {
public:
        int numOfWays(vector<int>& nums) 
        {
        int n = nums.size();
        vector<vector<int>> comb(n + 1, vector<int>(n + 1));
        comb[0][0] = 1;
        for (int i = 1; i <= n; ++i) 
        {
            comb[i][0] = 1;
            for (int j = 1; j <= i; ++j)
             {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % 1000000007;
            }
        }
        function<int(vector<int>&)> dfs = [&](vector<int>& nums)
         {
            int n = nums.size();
            if (n <= 2) return 1;
            vector<int> left, right;
            for (int i = 1; i < n; ++i) 
            {
                if (nums[i] < nums[0]) left.push_back(nums[i]);
                else right.push_back(nums[i]);
            }
            long long res = comb[n - 1][left.size()];
            res = res * dfs(left) % 1000000007;
            res = res * dfs(right) % 1000000007;
            return (int)res;
        };
        return dfs(nums) - 1;
    }
};

class Solution1 {
public:
    int numOfWays(vector<int>& nums) {
        int m = nums.size();
        // Table of Pascal's triangle
        table.resize(m + 1);
        for(int i = 0; i < m + 1; ++i) {
            table[i] = vector<long long>(i + 1, 1);
            for(int j = 1; j < i; ++j) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % mod;
            }
        }
        
        return (dfs(nums) - 1) % mod;
    }
    
private:
    vector<vector<long long>> table;
    long long mod = 1e9 + 7;
    
    long long dfs(vector<int> &nums){
        int m = nums.size();
        if(m < 3) {
            return 1;
        }

        vector<int> leftNodes, rightNodes;
        for(int i = 1; i < m; ++i){
            if (nums[i] < nums[0]) {
                leftNodes.push_back(nums[i]);
            } else {
                rightNodes.push_back(nums[i]);
            }
        }
		
        long long leftWays = dfs(leftNodes) % mod;
        long long rightWays = dfs(rightNodes) % mod;
		
        return (((leftWays * rightWays) % mod) * table[m - 1][leftNodes.size()]) % mod;
    }
};

//1345. Jump Game IV
//Runtime 232 ms Beats 68.51% Memory 76.1 MB
class Solution {
public:

    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return 0;

        // creating a map each value
        std::unordered_map<int, std::vector<int>> indices;
        for (int i = 0; i < n; i++) {
            indices[arr[i]].push_back(i);
        }

        // BFS
        std::queue<int> storedIndex;
        std::vector<bool> visited(n); // fixed size
        int ret = 0;

        storedIndex.push(0);
        visited[0] = true;
        while (!storedIndex.empty()) {
            int sz = storedIndex.size();
            while (sz--) {
                int curIdx = storedIndex.front();
                storedIndex.pop();
                if (curIdx == n-1) {
                    return ret;
                }
                std::vector<int>& jumpIndices = indices[arr[curIdx]];
                jumpIndices.push_back(curIdx - 1);
                jumpIndices.push_back(curIdx + 1);
                for (int nextIdx : jumpIndices) {
                    if (nextIdx >= 0 && nextIdx < n && !visited[nextIdx]) {
                        storedIndex.push(nextIdx);
                        visited[nextIdx] = true;
                    }
                }
                jumpIndices.clear();
            }
            ret++;
        }
        return -1;
    }
};


//312. Burst Balloons
/*Runtime: 1357 ms, faster than 5.21% of C++ online submissions for Burst Balloons.
Memory Usage: 10.4 MB, less than 19.50% of C++ online submissions for Burst Balloons.*/
class Solution1 {
public:
    int maxCoins(vector<int>& nums) {
        // add 1 before & after nums
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);
        int n = nums.size();
        
        // cache results of dp
        vector<vector<int>> memo(n, vector<int>(n, 0));
        
        // 1 & n - 2 since we can't burst our fake balloons
        return dp(nums, memo, 1, n - 2);
    }
private:
    int dp(vector<int>& nums, vector<vector<int>>& memo, int left, int right) {
        // base case interval is empty, yields 0 coins
        if (right - left < 0) {
            return 0;
        }
        
        // we've already seen this, return from cache
        if (memo[left][right] > 0) {
            return memo[left][right];
        }
        
        // find the last burst in nums[left]...nums[right]
        int result = 0;
        for (int i = left; i <= right; i++) {
            // nums[i] is the last burst
            int curr = nums[left - 1] * nums[i] * nums[right + 1];
            // nums[i] is fixed, recursively call left & right sides
            int remaining = dp(nums, memo, left, i - 1) + dp(nums, memo, i + 1, right);
            result = max(result, curr + remaining);
        }
        // add to cache
        memo[left][right] = result;
        return result;
    }
};

/*Runtime: 1290 ms, faster than 10.72% of C++ online submissions for Burst Balloons.
Memory Usage: 10.4 MB, less than 19.50% of C++ online submissions for Burst Balloons.*/
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        vector<vector<int> > dp(nums.size(), vector<int>(nums.size(), 0));
        for (int i = nums.size() - 3; i >= 0; i --) {
            for (int j = i + 2; j < nums.size();j ++) {
                for (int k = i + 1; k < j; k ++)
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + nums[i] * nums[k] * nums[j]);
            }
        }
        return dp[0][nums.size() - 1];
    }
};

//76. Minimum Window Substring
/*
    Given 2 strings s & t, return min window substring
    of s such that all chars in t are included in window
    Ex. s = "ADOBECODEBANC" t = "ABC" -> "BANC"

    Sliding window + hash map {char -> count}
    Move j until valid, move i to find smaller

    Time: O(m + n)
    Space: O(m + n)
*/

class Solution {
public:
    string minWindow(string s, string t) {
        // count of char in t
        unordered_map<char, int> m;
        for (int i = 0; i < t.size(); i++) {
            m[t[i]]++;
        }
        
        int i = 0;
        int j = 0;
        
        // # of chars in t that must be in s
        int counter = t.size();
        
        int minStart = 0;
        int minLength = INT_MAX;
        
        while (j < s.size()) {
            // if char in s exists in t, decrease
            if (m[s[j]] > 0) {
                counter--;
            }
            // if char doesn't exist in t, will be -'ve
            m[s[j]]--;
            // move j to find valid window
            j++;
            
            // when window found, move i to find smaller
            while (counter == 0) {
                if (j - i < minLength) {
                    minStart = i;
                    minLength = j - i;
                }
                
                m[s[i]]++;
                // when char exists in t, increase
                if (m[s[i]] > 0) {
                    counter++;
                }
                i++;
            }
        }
        
        if (minLength != INT_MAX) {
            return s.substr(minStart, minLength);
        }
        return "";
    }
};

//127. Word Ladder
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        queue<string> todo;
        todo.push(beginWord);
        int ladder = 1;
        while (!todo.empty()) {
            int n = todo.size();
            for (int i = 0; i < n; i++) {
                string word = todo.front();
                todo.pop();
                if (word == endWord) {
                    return ladder;
                }
                dict.erase(word);
                for (int j = 0; j < word.size(); j++) {
                    char c = word[j];
                    for (int k = 0; k < 26; k++) {
                        word[j] = 'a' + k;
                        if (dict.find(word) != dict.end()) {
                            todo.push(word);
                        }
                     }
                    word[j] = c;
                }
            }
            ladder++;
        }
        return 0;
    }
};

//329. Longest Increasing Path in a Matrix
class Solution {
    int dfs(vector<vector<int>> &matrix, vector<vector<int>> &dp, int i, int j, int prev) {
        if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size() || matrix[i][j] <= prev) {
            return 0;
        }
        
        if (dp[i][j]) return dp[i][j];
        
        return dp[i][j] = 1 + std::max(dfs(matrix, dp, i + 1, j, matrix[i][j]),
                       std::max(dfs(matrix, dp, i - 1, j, matrix[i][j]),
                       std::max(dfs(matrix, dp, i, j + 1, matrix[i][j]),
                       dfs(matrix, dp, i, j - 1, matrix[i][j]))));
        
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size(), 0));
        int ret = 0;
        
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                ret = max(ret, dfs(matrix, dp, i, j, -1));       
            }
        }
        return ret;
    }
};

//191. Number of 1 Bits
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int rs = 0;
        while (n) {
            rs++;
            n &= (n-1); // erase right most 1 bit
        }
        return rs;
    }
    /*Runtime: 2 ms, faster than 62.71% of C++ online submissions for Number of 1 Bits.
Memory Usage: 5.8 MB, less than 79.07% of C++ online submissions for Number of 1 Bits.*/
    
    int hammingWeight1(uint32_t n) {
        int rs = 0;
        while (n) {
            if (n &1) {
                rs++;
            }
            n >>= 1;
        }
        return rs;
    }
    /*Runtime: 3 ms, faster than 59.20% of C++ online submissions for Number of 1 Bits.
Memory Usage: 6 MB, less than 47.87% of C++ online submissions for Number of 1 Bits.*/
};


//72. Edit Distance
class Solution {
public:
int minDistance(string word1, string word2) {

    int n=word1.length(),m=word2.length();
    int dp[n+1][m+1];
    memset(dp,-1,sizeof(dp));
    //word2 string (target) is empty
    for(int i=0;i<=n;i++)
    {
        dp[i][0]=i; // j is zero , target is empty , total operations to delete
    }
    // word1 is empty (source) , insert all element into source from target , operation will be size of target
    for(int j=0;j<=m;j++)
    {
        dp[0][j]=j;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            
            if(word1[i-1]==word2[j-1])
            {
                dp[i][j]=dp[i-1][j-1];
            }
            else //if(word1[i-1]!=word2[j-1])
            {
                dp[i][j]=min(dp[i-1][j-1] , min(dp[i][j-1] , dp[i-1][j])) +1; // replace , insert , delete
            }
        }
    }
    return dp[n][m];
}
};



//354. Russian Doll Envelopes
class Solution {
public:
    static bool comp(vector<int> &a, vector<int> &b){
        if(a[0]==b[0]){
            return a[1]>b[1];
        }
        return a[0]<b[0];
    }
        
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), comp);
        // sort(envelopes.begin(), envelopes.end(), [](const auto a, const auto b) {
        //     if(a[0]==b[0]) {
        //         return a[1]>b[1];
        //     }
        //     return a[0]<b[0];
        // });
        int i, j, n=envelopes.size();
        vector<int>lis;
        
        for(i=0; i<n; i++){
            auto it = lower_bound(lis.begin(), lis.end(), envelopes[i][1]);
            if(it==lis.end()){lis.push_back(envelopes[i][1]);}
            else{
                *it = envelopes[i][1];
            }
        }
        return lis.size();
    }
};
/*
Runtime: 673 ms, faster than 38.83% of C++ online submissions for Russian Doll Envelopes.
Memory Usage: 77.6 MB, less than 66.73% of C++ online submissions for Russian Doll Envelopes.*/



// 132. Palindrome Partitioning II
// class Solution {
//     public:
//     int minCut(string s) {
//         return minCutFrom(s, 0, s.length() - 1);
//     }
    
//     int minCutFrom(string s, int start, int end) {
//         if (start == end || isPalindrome(s, start, end)) {
//             return 0;
//         }
//         int minCut = s.length() - 1;
//         for (int i = start; i <= end; i++) {
//             if (isPalindrome(s, start, i)) {
//                 minCut = min(minCut, 1 + minCutFrom(s, i + 1, end));
//             }
//         }
//         return minCut;
//     }
    
//     bool isPalindrome(string s, int x, int y) {
//         while (x < y) {
//             if (s[x++] != s[y--])
//                 return false;
//         }
//         return true;
//     }
// };

// // Time Limit Exceeded
// // "fifgbeajcacehiicccfecbfhhgfiiecdcjjffbghdidbhbdbfbfjccgbbdcjheccfbhafehieabbdfeigbiaggchaeghaijfbjhi"


/*
Took me a while to understand. I'd like to help further explain it.

The definition of 'cut' array is the minimum number of cuts of a sub string. More specifically, cut[n] stores the cut number of string s[0, n-1].

Here is the basic idea of the solution:

Initialize the 'cut' array: For a string with n characters s[0, n-1], it needs at most n-1 cut. Therefore, the 'cut' array is initialized as cut[i] = i-1

Use two variables in two loops to represent a palindrome:
The external loop variable 'i' represents the center of the palindrome. The internal loop variable 'j' represents the 'radius' of the palindrome. Apparently, j <= i is a must.
This palindrome can then be represented as s[i-j, i+j]. If this string is indeed a palindrome, then one possible value of cut[i+j] is cut[i-j] + 1, where cut[i-j] corresponds to s[0, i-j-1] and 1 correspond to the palindrome s[i-j, i+j];

When the loops finish, you'll get the answer at cut[s.length]

*/
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<int> cut(n+1, 0);  // number of cuts for the first k characters
        for (int i = 0; i <= n; i++) cut[i] = i-1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; i-j >= 0 && i+j < n && s[i-j]==s[i+j] ; j++) // odd length palindrome
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j]);

            for (int j = 1; i-j+1 >= 0 && i+j < n && s[i-j+1] == s[i+j]; j++) // even length palindrome
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j+1]);
        }
        return cut[n];
    }
};

/*Runtime: 13 ms, faster than 97.94% of C++ online submissions for Palindrome Partitioning II.
Memory Usage: 6.4 MB, less than 97.25% of C++ online submissions for Palindrome Partitioning II.*/


//297. Serialize and Deserialize Binary Tree
// Encodes a tree to a single string.
string serialize(TreeNode* root) {
    string ans = "";
    if (root == NULL) return ans;
    
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()){
        TreeNode* currNode = q.front();
        q.pop();
        if (currNode == NULL){
            ans.append("#,");
        } 
        else {
            ans.append(to_string(currNode->val) + ',');
        }
        
        if (currNode != NULL){
            q.push(currNode->left);
            q.push(currNode->right);
        }
    }
    cout << ans << "\n";
    return ans;
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
    if (data.size() == 0) return NULL;
    stringstream s(data);
    string str;
    getline(s, str, ',');
    TreeNode *root = new TreeNode(stoi(str));
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()){
        TreeNode *node = q.front();
        q.pop();
        
        //for left subtree
        getline(s, str, ',');
        if (str == "#"){
            node->left = NULL;
        }
        else {
            TreeNode *leftNode = new TreeNode(stoi(str));
            node->left = leftNode;
            q.push(leftNode);
        }
        
        //for right subtree
        getline(s, str, ',');
        if (str == "#"){
            node->right = NULL;
        }
        else {
            TreeNode *rightNode = new TreeNode(stoi(str));
            node->right = rightNode;
            q.push(rightNode);
        } 
    }
    return root;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

	void serialize_helper(TreeNode* root , string &s){
		if(root == NULL){
			s.push_back('/');
			s.push_back(',');
			return;
		}

		string t = to_string(root -> val);
		int i = 0;
		while(i < t.size()){
			s.push_back(t[i++]);
		}
		s.push_back(',');

		serialize_helper(root -> left , s);
		serialize_helper(root -> right , s);
	}

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		 string s = "";
		 serialize_helper(root , s);
		 return s;
	}

	int idx =  0;
	TreeNode* deserialize_helper(string data){

		string t;
		while(idx < data.size() && data[idx] != ','){
			t.push_back(data[idx++]);
		}

		if(idx >= data.size() || t == "/"){
			idx++;
			return NULL;
		}

		TreeNode* root = new TreeNode(stoi(t));
		idx++;
		root -> left  = deserialize_helper(data);
		root -> right = deserialize_helper(data);
		return root;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data){
		return deserialize_helper(data);
	}
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));



// 149. Max Points on a Line
// class Solution{
// public :
    
//     int maxPoints(vector<vector<int>>& points) 
//     {
//         if(points.size()<=2) return points.size();
//         int res=0;
//         int n=points.size();
//         for(int i=0;i<n;i++){

//             for(int j=i+1;j<n;j++){

//                 int x1 = points[i][0];
//                 int x2 = points[j][0];
//                 int y1 = points[i][1];
//                 int y2 = points[j][1];    

//                 // double slope = double(y2 - y1)/double(x2 - x1);
//                 int total=2;
//                 for(int k=0;k<n && k!=i && k!=j;k++){
                    
//                     int x = points[k][0];
//                     int y = points[k][1];
//                     // third point
//                     // double(y - y1)/double(x1 - x1)
//                     if((y2 - y1)*(x - x1) == (x2 - x1)*(y - y1))
//                         total++;
//                 }
//                 res = max(res, total);
//             }
//         }
//         return res;
//     }
// };
class Solution {
public:
    
    // According to constraint we are allowed with maximum time complexity of O(n^3)
    // 1 <= points.length <= 300
    ///////   All the points are unique.
    int maxPoints(vector<vector<int>>& points) {
        
        if(points.size()<=2) return points.size(); // only two points are always on the same line, beacuse using 2 points
                                                    // line is made
        int res = 0;
        for(int i = 0; i < points.size(); i++)
        {
            unordered_map<double, int> mp;
            int duplicate = 0;
            double slope = 0.0;
            for(int j = 0; j < points.size(); j++)
            {
                int x1 = points[i][0];
                int x2 = points[j][0];
                int y1 = points[i][1];
                int y2 = points[j][1];    
                
                // slope = dy/dx.
                int dy = y2 - y1;
                int dx = x2 - x1;
                if(dy == 0 && dx == 0){  // same overlapping point --> consider 2 same point as single point
                    duplicate++; 
                    continue;
                }
                
                if(dx != 0)
                    slope = dy*1.0/dx; // store in double
                else // dx==0 means slope is infinity
                    slope = INT_MAX;
                
                mp[slope]++;
            }

            if(mp.size() == 0)
                res = duplicate;
            else
            {
                for(auto slope : mp){
                    
                    res = max(res, slope.second + duplicate);
                }
            }
        }
        return res;
    }
};


//135. Candy
int candy(vector<int>& r) {
        int ans=0;
        vector< int> dp( r.size() , 1);
        for( int i=1;i<r.size();i++){
            if( r[i] > r[i-1]) dp[i]=dp[i-1]+1;
        }
        ans=dp[r.size()-1];
        for( int i=r.size()-1;i>=1;i--){
            if( r[i-1] > r[i]) dp[i-1]=max( dp[i-1], dp[i]+1);
            ans+=dp[i-1];
        }
        
        return ans;       
    }

// 76. Minimum Window Substring
class Solution {
public:
   string minWindow(string s, string t) {
        vector<int> map(128,0);
        for(auto c: t) map[c]++;
        int counter=t.size(), begin=0, end=0, d=INT_MAX, head=0;
        while(end<s.size()){
            if(map[s[end++]]-->0) counter--; //in t
            while(counter==0){ //valid
                if(end-begin<d)  d=end-(head=begin);
                if(map[s[begin++]]++==0) counter++;  //make it invalid
            }  
        }
        return d==INT_MAX? "":s.substr(head, d);
    }
    
//     Here comes the template.

// For most substring problem, we are given a string and need to find a substring of it which satisfy some restrictions. A general way is to use a hashmap assisted with two pointers. The template is given below.

// int findSubstring(string s){
//         vector<int> map(128,0);
//         int counter; // check whether the substring is valid
//         int begin=0, end=0; //two pointers, one point to tail and one  head
//         int d; //the length of substring

//         for() { /* initialize the hash map here */ }

//         while(end<s.size()){

//             if(map[s[end++]]-- ?){  /* modify counter here */ }

//             while(/* counter condition */){ 
                 
//                  /* update d here if finding minimum*/

//                 //increase begin to make it invalid/valid again
                
//                 if(map[s[begin++]]++ ?){ /*modify counter here*/ }
//             }  

//             /* update d here if finding maximum*/
//         }
//         return d;
//   }
// One thing needs to be mentioned is that when asked to find maximum substring, we should update maximum after the inner while loop to guarantee that the substring is valid. On the other hand, when asked to find minimum substring, we should update minimum inside the inner while loop.

// The code of solving Longest Substring with At Most Two Distinct Characters is below:

// int lengthOfLongestSubstringTwoDistinct(string s) {
//         vector<int> map(128, 0);
//         int counter=0, begin=0, end=0, d=0; 
//         while(end<s.size()){
//             if(map[s[end++]]++==0) counter++;
//             while(counter>2) if(map[s[begin++]]--==1) counter--;
//             d=max(d, end-begin);
//         }
//         return d;
//     }
// The code of solving Longest Substring Without Repeating Characters is below:

// Update 01.04.2016, thanks @weiyi3 for advise.

// int lengthOfLongestSubstring(string s) {
//         vector<int> map(128,0);
//         int counter=0, begin=0, end=0, d=0; 
//         while(end<s.size()){
//             if(map[s[end++]]++>0) counter++; 
//             while(counter>0) if(map[s[begin++]]-->1) counter--;
//             d=max(d, end-begin); //while valid, update d
//         }
//         return d;
//     }
// I think this post deserves some upvotes! : )
};


//65. Valid Number ? hard? no?
/* The error conditions are:

1 More than one exponent character ('e'/'E'), or seeing an 'e'/'E' when a number has not yet been seen.
2 More than one sign, or a sign appearing after a decimal or number have been seen. This gets reset when passing an 'e'/'E'.
3 More than one decimal, or a decimal appearing after an 'e'/'E' has been seen.
4 Any other non-number character appearing.
5 Reaching the end of S without an active number.
To help with this process, we can set up some boolean flags for the different things of which we're keeping track (num, exp, sign, dec). We'll also need to remember to reset all flags except exp when we find an 'e'/'E', as we're starting a new integer expression.

Time Complexity: O(N) where N is the number of characters in S
Space Complexity: O(1)
    */
    
    
   bool isNumber(string S) {
        bool num = false, exp = false, sign = false, dec = false;
        for (auto c : S)
            if (c >= '0' && c <= '9') num = true ;    
            else if (c == 'e' || c == 'E')
                if (exp || !num) return false;
                else exp = true, sign = false, num = false, dec = false;
            else if (c == '+' || c == '-')
                if (sign || num || dec) return false;
                else sign = true;
            else if (c == '.')
                if (dec || exp) return false;
                else dec = true;
            else return false;
        return num;
    }


//60. Permutation Sequence
class Solution {
public:
    string getPermutation(int n, int k) {
        string str="",ans="";
        k--;
        for(int i=1;i<=n;i++)
            str+=('0'+i);
        int val=1;
        for(int i=2;i<=n;i++)
            val*=i;
        while(val>1){
            int slb=val/n;
            int index=k/slb;
            ans+=str[index];
            k=k%slb;
            str=str.substr(0,index)+str.substr(index+1,n-index);
            val=val/n;
            n--;
        }
        ans+=str[0];
        return ans;
    }
};

The Logic:

For the given n , we can generate a vector which would consist of all numbers from 1 to n.
Now, for every n, we get a total number of n!/n numbers in each group that start with each number in n. (This can be found by listing out some smaller test cases)
As we are interested in kth permutation, we first figure out that out of all groups, kth permutation lies in which group by k/gs (gs is group size). Now, as here we have passed k-1 in function parameter because kth permutation is actually (k-1)th permutation for us since the members of group are in the vector from 0 to n-1.
We add that element to a string, and remove it from the vector to keep our index-based logic intact. Next, we recur for the remaining elements. Here k=k%gs, since now that we had already found the group, we need to find the (k%gs)th permutation from the remaining elements, and our problem gets smaller everytime.
A dry run for the first test case will be more helpful in case of confusions. ;-)

class Solution {
    public:
    int getfactorial(int n)
    {
        if(n<1) return 0;
        int s=1;
        for(int i=1; i<=n; i++)
        {
            s=s*i;
        }
        return s;
    }
public:
    string solve(string str,vector<int> &v, int n, int k)
        
    { 
        if(n==0)//base condition
        {
            return str;
        }
        //gs is size of each sub-group
         int gs=getfactorial(n)/n;
        int ele=(k/gs);
        
        str+=to_string(v[ele]);
        auto i = v.begin()+ele;
        v.erase(i);
        k=k%gs;
        n--;
        str=solve(str,v,n,k);
        return str;
    }

public:
    string getPermutation(int n, int k) {
         
        vector<int> v(n+1,0);
        for(int i=1; i<=n; i++)
            v[i-1]=i;
        return solve("",v,n,k-1);
    }
};


// 52. N-Queens II
/*
We first create a ( n X n ) chess board and assign 0 to every index.
Whenever a queen will be placed, index will be made 1.

In this approach ,

Whenever a queen is placed, at first it is checked if it satisfies the conditions given that it is not under attack.

validMove function.
First it check there are no other queen in row the queen is filled.
As we are putting queen column wise so no need to check for column.
Then there are two diagonals to check for.

COLUMN_WISE FILLING = Only left part of the diagonals are checked as positions to the right of the present column are still unfilled.
ROW_WISE FILLING = Only upper part of the diagonals are checked as positions below of the present column are still unfilled.
If conditions satisfied, Queen is placed and we move to next column.
If no queen satisfy the problem, we backtrack and try to change the position of previous queen.

UPVOTE IF HELPFUL
*/
class Solution {
public:
    int totalNQueens(int n) {
	vector<bool> col(n), diag(2*n-1), anti_diag(2*n-1);
	return solve(col, diag, anti_diag, 0);
}
   
int solve(vector<bool>& col, vector<bool>& diag, vector<bool>& anti_diag, int row) {
	int n = size(col), count = 0;
    if(row == n) return 1;
	for(int column = 0; column < n; column++)           
		if(!col[column] && !diag[row + column] && !anti_diag[row - column + n - 1]){ 
			col[column] = diag[row + column] = anti_diag[row - column + n - 1] = true;
			count += solve(col, diag, anti_diag, row + 1); 
			col[column] = diag[row + column] = anti_diag[row - column + n - 1] = false; 
		}                                
	return count;
}
};




//44. Wildcard Matching
class Solution {
public:
//     bool isMatch(string s, string p) {
//         vector<vector<bool>> dp(s.size() + 1, vector(p.size() + 1, false));
//         dp[0][0] = true;
//         for (int j = 0; j < p.size() && p[j] == '*'; ++j) {
//             dp[0][j + 1] = true;
//         }
        
//         for (int i = 1; i <= s.size(); ++i) {
//             for (int j = 1; j <= p.size(); ++j) {
//                 if (p[j - 1] == '*') {
//                     dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
//                 } else {
//                     dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '?') && dp[i - 1][j - 1];
//                 }
//             }
//         }

//         return dp[s.size()][p.size()];
//     }
    
     bool isMatch(string s, string p) {
        vector<bool> dp(p.size() + 1, false);
        dp[0] = true;
        for (int j = 0; j < p.size() && p[j] == '*'; ++j) {
            dp[j + 1] = true;
        }
        
        for (int i = 1; i <= s.size(); ++i) {
            dp[0] = false;
            bool neighborLastRow = i == 1;
            for (int j = 1; j <= p.size(); ++j) {
                bool currLastRow = dp[j];
                if (p[j - 1] == '*') {
                    dp[j] = currLastRow || dp[j - 1];
                } else {
                    dp[j] = (s[i - 1] == p[j - 1] || p[j - 1] == '?') && neighborLastRow;
                }
                neighborLastRow = currLastRow;
            }
        }

        return dp[p.size()];
    }
};
//37. Sudoku Solver
class Solution {
public:
    bool rowCheck[9][10] = {false,}; //in ith row, j is used.
    bool colCheck[9][10] = {false, }; //in ith col, num j is used
    bool boxCheck[3][3][10] = {false,}; //in (i,j)th box num k is used
    bool rowChecker(int row, int num){
        return !rowCheck[row][num];
    }
    bool colChecker(int col, int num){
       return !colCheck[col][num];
    }
    bool boxChecker(int row, int col, int num){
        return !boxCheck[row/3][col/3][num];
    }
    
    bool solve(vector<vector<char>>& board, vector<pair<int,int>> &leftOver, int curIndex){
        if(leftOver.size() == curIndex){
            return true;
        }
        
        pair<int,int> curPos = leftOver[curIndex];
        bool isSolved = false;
        for(int i = 1; i <= 9; i++){
            if(rowChecker(curPos.first, i) && 
              colChecker(curPos.second, i) &&
              boxChecker(curPos.first, curPos.second, i)){
                
                board[curPos.first][curPos.second] = i +'0';
                rowCheck[curPos.first][i] = true;
                colCheck[curPos.second][i] = true;
                boxCheck[curPos.first/3][curPos.second/3][i] = true;
                
                isSolved = solve(board, leftOver, curIndex+1);
                
                rowCheck[curPos.first][i] = false;
                colCheck[curPos.second][i] = false;
                boxCheck[curPos.first/3][curPos.second/3][i] = false;
            }
            if(isSolved)
                return true;
            
            board[curPos.first][curPos.second] = '.';
        }
        return false;
    }
    void solveSudoku(vector<vector<char>>& board) {
        vector<pair<int,int>> leftOver;
        
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[i].size(); j++){
                if(board[i][j] == '.'){
                    leftOver.push_back({i,j});
                }else{
                    int num = board[i][j]-'0';
                    rowCheck[i][num] = true;
                    colCheck[j][num] = true;
                    boxCheck[i/3][j/3][num] = true;
                }
            }
        }
        
        solve(board, leftOver, 0);
        
    }
};

	bool isValid(vector<vector<char>>& board, int row, int col, char c){

		for(int i=0 ; i<9 ; i++){

			//First Condition
			if(board[i][col] == c)
				return false;

			//Second Condition
			if(board[row][i] == c)
				return false;

			//Third Condition
			if(board[3*(row/3) + i/3][3*(col/3) + i%3] == c)
				return false;
		}
		return true;
	}

	bool solve(vector<vector<char>>& board){

		for(int i=0 ; i<board.size() ; i++){
			for(int j=0 ; j<board[0].size() ; j++){

				if(board[i][j] == '.'){

					for(char c='1' ; c<='9' ; c++){
						if(isValid(board, i, j, c)){
							board[i][j] = c;

							if(solve(board) == true){
								return true;
							}
							else{
								board[i][j] = '.';
							}
						}
					}
					return false;
				}
			}
		}
		return true;
	}

	void solveSudoku(vector<vector<char>>& board) {
		solve(board);
	}

// 51. N-Queens
// backtrackin

  //Request you to Plaese upvote so that more people can learn backtreking
  
  //Hint
  
  //Create safe state function for row and back 2 diagonal
  //Create string with n times'.' and insert in each cell on board
  //Pass col=0 in recursive fun
  //In recursive function create loop for row and apply if backtreking
  //Thats it bro
  
  //Different forms of this question
  
  //Find matrix, Find integer array, Find This type of string
  `
  
  class Solution 
  {
   bool isSafe(vector<string> &board,int row,int col,int n)
    {
        int i=row;
        int j=col;  //Lets check first for row
        while(j>=0)
        {
            if(board[i][j]=='Q')
            {
                return false;
            }
            j--;
        }
        //No need to check for colum as we only add 1 queens in each colum
        //Lets check for diagonal
        //For diagonal only check backward up and down diagonal
        //backward up diagonal
       i=row;
       j=col;
        while(i>=0 && j>=0)
        {
            if(board[i][j]=='Q')
            {
                return false;
            }
            j--;
            i--;
        }
        
        //backward down diagonal
        i=row;
        j=col;
        while(j>=0 && i<n)
        {
            if(board[i][j]=='Q')
            {
                return false;
            }
            j--;
            i++;
        }
        
        //If all conditions is clear
        return true;
    }
    
void board_config(vector<string> &board,vector<vector<string>> &ans,int col,int n)
    {
        //Base condition
        if(col==n)
        {
          ans.push_back(board);
            return;
        }
        
        //Now think about only 1 case for 1st colum
        //Put each raw of 1st colum
        for(int row=0;row<n;row++) //Here row is for row
        {
            if(isSafe(board,row,col,n))
            {
                board[row][col]='Q';  //First put queen
                board_config(board,ans,col+1,n);  //Rest will handle by recursive function by col+1
                board[row][col]='.';  // This is called backtreking
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) 
    {
      vector<vector<string>>ans;
      string str="";
        for(int i=0;i<n;i++)
        {
            str+='.';   //Insert n times . in str string
        }
        vector<string>board(n,str);   //in eachcell it stores n time "."
        board_config(board,ans,0,n);      
        return ans;
        
    }
}; 



void swapp(int *a, int *b) {
    int c= *a;
    *a = *b;
    *b = c;
}
// 41. First Missing Positive
// https://leetcode.com/problems/first-missing-positive
class Solution {
public:
    /*We only need to keep track of which ones of the first n positive integers occur in the array. To do this with no extra space, we can treat the array like a boolean array, where sign(arr[i]) indicates whether the i-th positive integer is present or not. First, we replace all non-positive values with n + 1, since we'll only use these indices as storage space. Then, for every one of the first n positive numbers in the array, we turn the value at their corresponding index negative. Finally, all we need to do is check for the first positive value, which will give us the first missing positive. If we find no such index, then all natural numbers up to n are present, so we return n + 1.
    
    in short
we replace the negative values with n+1 values so that they will be out of the range
we make the index negative if we found that value in the array
we identify the index which is not negative and it will be the missing number

Runtime: 254 ms, faster than 52.43% of C++ online submissions for First Missing Positive.
Memory Usage: 82.9 MB, less than 77.72% of C++ online submissions for First Missing Positive.
Next challenges:
    */
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        // for (int i = 0; i < n; i++) if (nums[i] <= 0) nums[i] = n + 1;
        // for (int i = 0; i < n; i++) if (abs(nums[i]) <= n && nums[abs(nums[i]) - 1] > 0) nums[abs(nums[i]) - 1] *= -1;
        // for (int i = 0; i < n; i++) if (nums[i] > 0) return i + 1;
        // return n + 1;
        
        
        /*
        For anyone who doubts on the complexity of this algorithm: just consider position with A[i] = i+1 as a CORRECT SLOT.

        CORRECT SLOT will never be changed: for CORRECT SLOT, A[A[i] - 1] always equals to A[i], vice versa (1)
        For each swap, the number of CORRECT SLOT increases by at least 1: Position A[A[i] - 1] = A[i] becomes a CORRECT SLOT after swap, and according to (1), this must be a new CORRECT SLOT
        The maximum of CORRECT SLOT <= N
        Therefore, the complexity is O(N)

        We visit each number once, and each number will be put in its right place at most once, so it is O(n) + O(n). Although there are two nesting of cyclic (for and while), but its time complexity is still O(n).
        
        Runtime: 350 ms, faster than 24.62% of C++ online submissions for First Missing Positive.
Memory Usage: 83 MB, less than 41.35% of C++ online submissions for First Missing Positive.
        */
        for(int i = 0; i < n; ++ i)
            while(nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
                swapp(&nums[i], &nums[nums[i] - 1]);
        
        for(int i = 0; i < n; ++ i)
            if(nums[i] != i + 1)
                return i + 1;
        
        return n + 1;
    }
    
    
    
};



// 23. Merge k Sorted Lists
//https://leetcode.com/problems/merge-k-sorted-lists
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
    /*Solution 1: Brute Force*/
//     ListNode* merge(ListNode* a,ListNode* b) {
//         if(!a) return b;
//         if(!b) return a;
//         ListNode* temp=NULL;
//         if(a->val<=b->val) 
//         {
//             temp =a;
//             temp->next = merge(a->next,b);
//         }
//         else 
//         {
//             temp = b;
//             temp->next = merge(a,b->next);
//         }
//         return temp;        
//     }
    
//     ListNode* mergeKLists(vector<ListNode*>& lists) {
//         if(lists.size()==0) return NULL;
//         if(lists.size()==1) return lists[0];
//         ListNode* ans=NULL;
//         for(auto l : lists) 
//         {
//             ans = merge(ans,l);
//         }
//         return ans;
//     }
  
    /*Solution 2:Priority queue*/
     ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size()==0) return NULL;
        priority_queue<int,vector<int>,greater<int>> pq;
        
        for(int i=0;i<lists.size();i++)
        {
            ListNode* head = lists[i];
            while(head!=NULL)
            {
                pq.push(head->val);
                head = head->next;
            }
        }
        ListNode* start = NULL;
        ListNode* end = NULL;
        while(!pq.empty()) {
            if(start==NULL)
            {
                start = new ListNode(pq.top());
                end = start;
                pq.pop();
            }
            else{
                end->next = new ListNode(pq.top());
                pq.pop();
                end = end->next;
            }
        }
            return start;
    }
    /*Solution 3: Divide and Conquer*/
//     ListNode* mergesort(ListNode* a  , ListNode* b) {
//         if(!a) 
//             return b;
//         if(!b)
//             return a;
//         ListNode* ans=NULL;
//         if(a->val<=b->val)
//         {
//             ans=a;
//             ans->next = mergesort(a->next,b);
//         }
//         else
//         {
//             ans=b;
//             ans->next = mergesort(a,b->next);
//         }
//         return ans;
//     }
    
//     ListNode* mergeK(vector<ListNode*>& lists,int k) {
//         while(k!=0) {
//             int i = 0,j = k;
//             while(i<j) {
//                 lists[i]=mergesort(lists[i],lists[j]);
//                 i++;
//                 j--;
//                 if(i>=j) 
//                     k=j;
//             }
//         }
//         return lists[0];
//     }
    
//     ListNode* mergeKLists(vector<ListNode*>& lists) {
//         if(lists.size()==1)
//             return lists[0];
//         if(lists.size()==0) 
//             return NULL;
//         ListNode*newhead = mergeK(lists,lists.size()-1);
//         return newhead;
//     }
};
