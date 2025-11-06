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
