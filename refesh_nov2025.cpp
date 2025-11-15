//easy 
class Solution {
public:
    // O(n) O(1)
    int maxProfit1(vector<int>& prices) {
        int l =0, r = 1;
        int ret = 0;
        while (r < prices.size()) {
            if (prices[l] < prices[r]) {
                ret = max(ret, prices[r]-prices[l]);
            }
            else {
                l=r;
            }
            r++;
        }
        return ret;
    }

    // O(n) O(1)
    int maxProfit(vector<int>& prices) {
        int ret = 0;
        int min = prices[0];
        for (auto price : prices) {
            ret = max(ret, price - min);
            min = min(min, price);
        }
        return ret;
    }
};


//hard
class Solution {
public:
    // O(n) O(n)
    int trap1(vector<int>& height) {
        vector<int> maxL(height.size(), 0);
        vector<int> maxR(height.size(), 0);
        int tmp = 0;
        int ret = 0;

        for (int i = 1; i < height.size(); i++) {
            tmp = max(tmp, height[i-1]);
            maxL[i] = tmp;
        }
        tmp = 0;
        for (int i = height.size() -2; i >= 0; i--) {
            tmp = max(tmp, height[i+1]);
            maxR[i] = tmp;
        }

        for (int i = 0; i < height.size(); i++) {
            int potential = min(maxL[i], maxR[i]);
            tmp = potential - height[i];
            if (tmp > 0) {
                ret += tmp;
            }
        }
        return ret;
    }

    // O(n) O(1)
    int trap(vector<int>& height) {
        if (height.size() == 0) return 0;

        int l = 0, r = height.size() - 1;
        int maxL = height[l], maxR = height[r];
        int ret = 0;
        while (l < r) {
            if (maxL < maxR) {
                l++;
                maxL = max(maxL, height[l]);
                ret += maxL - height[l];
            }
            else {
                r--;
                maxR = max(maxR, height[r]);
                ret += maxR - height[r];
            }
        }
        return ret;
    }
};


// medium
class Solution {
public:
    // O(n) O(1)
    int maxArea(vector<int>& heights) {
        int ret = 0;
        int l = 0;
        int r = heights.size() - 1;

        while (l < r) {
            int tmp = min(heights[l], heights[r]) * (r-l);
            ret = max(ret, tmp);
            if (heights[l] < heights[r]) {
                l++;
            }
            else {
                r--;
            }
        }
        return ret;
    }
};


// medium
class Solution {
public:
    // O(n^2)
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        int prev;
        for (int i = 0; i < nums.size(); i++) {
            int l = i+1;
            int r = nums.size()-1;
            int cur = nums[i];
            if (cur > 0) break;
            if (i > 0 && cur == nums[i-1]) continue;

            while (l < r) {
                int tmp = cur + nums[l] + nums[r];
                if (tmp == 0) {
                    ret.push_back({cur, nums[l], nums[r]});
                    l++;
                    r--;
                    while (nums[l] == nums[l-1]) l++;
                    while (nums[r] == nums[r+1]) r--;
                }
                else if (tmp < 0) {
                    l++;
                }
                else if (tmp > 0) {
                    r--;
                }
            }
        }
        return ret;
    }
};


class Solution {
public:
    // O(n) O(n)
    vector<int> twoSum1(vector<int>& numbers, int target) {
        unordered_map<int, int> m;
        for (int i = 0; i < numbers.size(); i++) {
            auto item = m.find(target - numbers[i]);
            if (item != m.end()) {
                return {item->second + 1, i + 1};
            }
            m[numbers[i]] = i;
        }
        return {};
    }
    // O(n) O(1)
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0;
        int r = numbers.size() - 1;
        while (l < r) {
            int curSum = numbers[l] + numbers[r];

            if (curSum < target) {
                l++;
            }
            else if (curSum > target) {
                r--;
            }
            else {
                return {l+1, r+1};
            }
        }
        return {};
    }  

    
};


// easy
class Solution {
public:
    bool isValidChar(char c) {
        return ((c >= 'A' && c <= 'Z') 
            || (c >= 'a' && c <= 'z')
            || (c >= '0' && c <= '9'));
    }

    // O(n) O(1)
    bool isPalindrome(string s) {
        if (!s.size()) return true;

        int r = s.size() -1;
        int l = 0;

        while (l < r) {
            while (l <r && !isValidChar(s[l])) {
                l++;
            }
            while (l < r && !isValidChar(s[r])) {
                r--;
            }
            if (tolower(s[l]) != tolower(s[r])) return false;
            l++;
            r--;
        }
        return true;
    }
};


// medium
class Solution {
public:
    // O(n^2) O(n)
    int longestConsecutive1(vector<int>& nums) {
        int ret = 0;
        unordered_set<int> m(nums.begin(), nums.end());

        for (int num : nums) {
            int streak = 0, cur = num;
            while (m.find(cur) != m.end()) {
                streak++;
                cur++;
            }
            ret = max(ret, streak);
        }
        return ret;
    }

    // O(nlogn) O(1)
    int longestConsecutive2(vector<int>& nums) {
        if (nums.empty()) return 0;
        sort(nums.begin(), nums.end());
        
        int ret = 0, streak = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i-1]) continue;

            if (nums[i] == nums[i-1] + 1) {
                streak++;
            }
            else {
                
                streak = 1;
            }
            ret = max(ret, streak);
        }
        return ret;
    }

    // O(n)
    int longestConsecutive3(vector<int>& nums) {
        unordered_set<int> m(nums.begin(), nums.end());
        int ret = 0;

        for (int num : nums) {
            if (m.find(num-1) == m.end()) {
                int streak = 1;
                while (m.find(num+streak) != m.end()) {
                    streak++;
                }
                ret = max(ret, streak);
            }
        }
        return ret;

    }
    // O(n)  O(n)
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> m;
        int ret = 0;

        for (int num : nums) {
            if (!m[num]) {
                m[num] = m[num-1] + m[num+1] + 1;
                m[num - m[num-1]] = m[num];
                m[num + m[num+1]] = m[num];
                ret = max(ret, m[num]);
            }
        }
        return ret;

    }

};

//medium
class Solution {
public:
    // bruceforce O(n^2) O(n)
    bool isValidSudoku1(vector<vector<char>>& board) {
        for (int row = 0; row <9; row++) {
            unordered_set<char> seen;
            for (int i = 0; i < 9; i++) {
                auto item = board[row][i];
                if (item == '.') continue;
                if (seen.count(item)) return false;
                seen.insert(item);
            }
        }
        for (int col = 0; col < 9; col++) {
            unordered_set<char> seen;
            for (int i = 0; i < 9; i++) {
                auto item = board[i][col];
                if (item == '.') continue;
                if (seen.count(item)) return false;
                seen.insert(item);
            }
        }

        for (int square = 0; square <9; square++) {
            unordered_set<char> seen;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j <3; j++) {
                    int row = (square/3)*3 + i;
                    int col = (square%3)*3 + j;
                    auto item = board[row][col];
                    if (item == '.') continue;
                    if (seen.count(item)) return false;
                    seen.insert(item);
                }
            }
        }
        return true;
    }


    // O(n^2) O(n^2)
     bool isValidSudoku2(vector<vector<char>>& board) {
        unordered_map<int, unordered_set<char>> rows, cols;
        map<pair<int,int>, unordered_set<char>> squares;

        for (int r = 0; r < 9;  r++) {
            for (int c = 0; c < 9; c++) {
                char item = board[r][c];
                if (item == '.') continue;

                pair<int, int> key = {r/3, c/3};
                if (rows[r].count(item) ||
                    cols[c].count(item) ||
                    squares[key].count(item)) {
                        return false;
                }
                rows[r].insert(item);
                cols[c].insert(item);
                squares[key].insert(item);
            }
        }
        return true;
     }


        //O(n^2) O(n)
     bool isValidSudoku3(vector<vector<char>>& board) {
        for (int row = 0; row <9; row++) {
            unordered_set<char> seen;
            for (int i = 0; i < 9; i++) {
                auto item = board[row][i];
                if (item == '.') continue;
                if (seen.count(item)) return false;
                seen.insert(item);
            }
        }
        for (int col = 0; col < 9; col++) {
            unordered_set<char> seen;
            for (int i = 0; i < 9; i++) {
                auto item = board[i][col];
                if (item == '.') continue;
                if (seen.count(item)) return false;
                seen.insert(item);
            }
        }
        vector<vector<int>> starts = {{0,0}, {0,3}, {0,6},
                                      {3,0}, {3,3}, {3,6},
                                      {6,0}, {6,3}, {6,6}
                                    };
        for (auto& start : starts) {
            unordered_set<char> seen;
            for (int r = start[0]; r < start[0] + 3; r++) {
                for (int c = start[1]; c < start[1] + 3; c++) {
                    int item = board[r][c];
                    if (item == '.') continue;
                    if (seen.count(item)) return false;
                    seen.insert(item);
                }
            }
        }
        return true;
     }


        bool isValidSudoku(vector<vector<char>>& board) {
            int rows[9] = {0};
            int cols[9] = {0};
            int squares[9] = {0};

            for (int r = 0; r < 9; ++r) {
                for (int c = 0; c < 9; ++c) {
                    if (board[r][c] == '.') continue;

                    int val = board[r][c] - '1';

                    if ((rows[r] & (1 << val)) || (cols[c] & (1 << val)) ||
                        (squares[(r / 3) * 3 + (c / 3)] & (1 << val))) {
                        return false;
                    }

                    rows[r] |= (1 << val);
                    cols[c] |= (1 << val);
                    squares[(r / 3) * 3 + (c / 3)] |= (1 << val);
                }
            }
            return true;
        }
};



//medium
class Solution {
public:
    // O(n^2)
    vector<int> productExceptSelf1(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret;
        
        for (int i = 0; i <n; i++) {
            int tmp = 1;
            for (int j = 0; j <n; j++) {
                if (i !=j) {
                    tmp*= nums[j];
                }
            }
            ret.push_back(tmp);
        }
        return ret;
    }

    //O(n) O(1)
    vector<int> productExceptSelf2(vector<int>& nums) {
        int total =1;
        int zeroCnt = 0;
        for (int num : nums) {
            if (num != 0) {
                total *= num;
            }
            else {
                zeroCnt++;
            }
        }
        if (zeroCnt > 1) {
            return vector<int>(nums.size(), 0);
        }
        vector<int> ret;
        for (auto num : nums) {
            if (zeroCnt == 1) {
                if (num == 0) ret.push_back(total);
                else ret.push_back(0);
            }
            else {
                ret.push_back(total/num);
            }
        }
        return ret;
    }

    //O(n) O(n)
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n);
        vector<int> ltr(n);
        vector<int> rtl(n);

        ltr[0] = 1;
        rtl[n-1] = 1;
        for (int i = 1; i < n; i++) {
            ltr[i] = nums[i-1] * ltr[i-1];
        }
        for (int i = n-2; i >=0; i--) {
            rtl[i] = nums[i+1] * rtl[i+1];
        }
        for (int i = 0; i < n; i++) {
            ret[i] = ltr[i] * rtl[i];
        }
        return ret;
    }

    // O(n)
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, 1);

        for (int i = 1; i < n; i++) { 
            ret[i] = ret[i-1] * nums[i-1];
        }
        int r = 1;
        for (int i = n-1; i >= 0; i--) {
            ret[i] *= r;
            r *= nums[i];
        }
    }
};


//medium
class Solution {
public:

    // O(n)
    string encode(vector<string>& strs) {
        string ret;
        for (auto s : strs) {
            ret+= to_string(s.size()) + "#" + s;
        }
        return ret;
    }

    // O(n)
    vector<string> decode(string s) {
        vector<string> ret;
        int i = 0;
        while (i < s.size()) {
            int j = i;
            while (s[j] != '#') {
                j++;
            }
            int sz = stoi(s.substr(i,j-i));
            i = j+1;
            j = i + sz;
            ret.push_back(s.substr(i, sz));
            i = j;
        }
        return ret;
    }
};


//medium 
class Solution {
public:
    // bruceforce O(k*n) O(n)
    vector<int> topKFrequent1(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        unordered_map<int, int> m2;
        vector<int> ret;
        int max = -1;
        for (auto item : nums) {
            max = max > m[item] ? max : m[item];
        }
        while (max > 0) {
            for (auto item : m) {
                if (item.second == max) {
                    ret.push_back(item.first);
                    if (ret.size() == k) return ret;
                }
            }
            max--;
        }
        
        return ret;
    }

    // O(nlogn) O(n)
     vector<int> topKFrequent2(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for (auto num : nums) {
            m[num]++;
        }

        vector<pair<int, int>> m2;
        for (auto item : m) {
            m2.push_back({item.second, item.first});
        }
        std::sort(m2.rbegin(), m2.rend());

        vector<int> ret;
        for (int i = 0; i <k; i++) {
            ret.push_back(m2[i].second);
        }
        return ret;
     }

    // TODO heap

    // bucket O(n) O(n)
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        vector<vector<int>> freq(nums.size() + 1);

        for (auto num : nums) {
            m[num]++;
        }

        for (auto item : m) {
            freq[item.second].push_back(item.first);
        }

        vector<int> ret;
        for (int i = freq.size() -1; i >0; i--) { 
            for (int n : freq[i]) {
                ret.push_back(n);
                if (ret.size() == k) return ret;
            }
        }
        return ret;
    }

};


//medium
class Solution {
public:
    // O(m*nlogn) O(m*n)
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        vector<vector<string>> ret;
        for (auto s : strs) {
            string tmp = s;
            std::sort(tmp.begin(), tmp.end());
            m[s].push_back(s);
        }

        for (auto item : m) {
            ret.push_back(item.second);
        }
        return ret;
    }
    // 0(m*n) O(m)
    vector<vector<string>> groupAnagrams1(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        for (auto s : strs) {
            vector<int> count(26, 0);
            for (auto c : s) {
                count[c - 'a']++;
            }
            string key = to_string(count[0]);
            for (int i = 1; i < 26; i++) {
                key += ',' + to_string(count[i]);
            }
            m[key].push_back(s);
        }

        vector<vector<string>> ret;
        for (auto item : m) {
            ret.push_back(item.second);
        }
        return ret;
    }
};



//easy
class Solution {
public:
    // O(n) O(n)
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ret(2,-1);
        unordered_map<int, int> m;

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            auto item = m.find(complement);
            if (item != m.end() && item->second != i) {
                ret[0] =  item->second;
                ret[1] = i;
                return ret;
            }
            m.insert({nums[i], i});
        }
        return ret;
    }
};


//easy 
class Solution {
public:
    // O(m+n)
    bool isAnagram1(string s, string t) {
        vector<int> m(26,0);
        if (s.size() != t.size()) return false;

        for (int i = 0; i < s.size(); i++) {
            m[s[i] - 'a']++;
        }
        for (int i = 0; i < t.size(); i++) {
            m[t[i] - 'a']--;
        }
        for (int i = 0; i < m.size(); i++){
            if (m[i] != 0) return false;
        }

        return true;
    }

    // O(nlogn + mlogm)
    bool isAnagram(string s, string t) {
        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());
        return s == t;
    }
};


//easy
class Solution {
public:
    // O(nlogn)
    bool hasDuplicate1(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i-1]) {
                return true;
            }
        }
        return false;
    }
    // O(n)
    bool hasDuplicate2(vector<int>& nums) {
        std::unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            if (m.find(nums[i])!= m.end()) {
                return true;
            }
            m.insert({nums[i], 1});
        }
        return false;
    }
    // O(n)
    bool hasDuplicate(vector<int>& nums) {
        std::unordered_set<int> m;
        for (int i = 0; i < nums.size(); i++) {
            if (m.find(nums[i])!= m.end()) {
                return true;
            }
            m.insert(nums[i]);
        }
        return false;
    }
};
