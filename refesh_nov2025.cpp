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
