class Solution {
public:
    
    /*Runtime:
    3 ms, faster than 89.02% of C++ online submissions for Longest Valid Parentheses.
    Memory Usage: 7.4 MB, less than 42.64% of C++ online submissions for Longest Valid Parentheses.
    */
    int longestValidParentheses(string s) {
        stack<int> stack;
        int rs = 0;
        int len = s.size();
        stack.push(-1);
        
        for (int i = 0; i < len; i++) {
            if (s[i] == '(') {
                stack.push(i);
            }
            else {
                stack.pop();
                if (stack.empty()) {
                    stack.push(i);
                }
                else {
                    int tmp = i - stack.top();
                    rs = rs > tmp ? rs : tmp;
                }
            }
        }
        return rs;
    }
};
