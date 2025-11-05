
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
    // O(logn)
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
