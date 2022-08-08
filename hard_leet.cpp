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
