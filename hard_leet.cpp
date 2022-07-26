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
