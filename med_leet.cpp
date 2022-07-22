#include<iostream>
#include<ostream>
#include<string.h>
#include<limits.h>
using namespace std;

//86. Partition List
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
