#include<iostream>
#include<ostream>
#include<string.h>
#include<limits.h>
using namespace std;


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
