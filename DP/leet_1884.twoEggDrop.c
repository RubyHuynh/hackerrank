#include<limits.h>
//Egg Drop With 2 Eggs and N Floors

int max(int a, int b) {
    return a > b ? a : b;
}
int _maxFloor = 0;


int eggDrop(int k, int n) {
    /* A 2D table where entry
    eggFloor[i][j] will represent
    minimum number of trials needed for
    i eggs and j floors. */
    int eggFloor[n + 1][k + 1];
    int res;
    int i, j, x;
 
    // We need one trial for one floor and 0
    // trials for 0 floors
    for (i = 1; i <= n; i++) {
        eggFloor[i][1] = 1;
        eggFloor[i][0] = 0;
    }
 
    // We always need j trials for one egg
    // and j floors.
    for (j = 1; j <= k; j++)
        eggFloor[1][j] = j;
 
    // Fill rest of the entries in table using
    // optimal substructure property
    for (i = 2; i <= n; i++) {
        for (j = 2; j <= k; j++) {
            eggFloor[i][j] = INT_MAX;
            for (x = 1; x <= j; x++) {
                res = 1 + max(
                              eggFloor[i - 1][x - 1],
                              eggFloor[i][j - x]);
                if (res < eggFloor[i][j])
                    eggFloor[i][j] = res;
            }
        }
    }
 
    // eggFloor[n][k] holds the result
    return eggFloor[n][k];
}

int eggDrop1(int k, int n) {
    int min = INT_MAX, x, tmp, i;

    if (k == 1|| k == 0) return k;
    
    if (n == 1) return k;
    
    for (i = 1; i <= k; ++i) {
        tmp = max(eggDrop(i-1, n-1), eggDrop(k-i, n));
        if (tmp < min) min = tmp;
    }
    
    return min + 1;
}

int twoEggDrop(int k) {
	return eggDrop(k, 2);
}

// int eggDrop(int n)
// {
// 	vector m{0};
// 	for(auto i{1}; i<=n; ++i) 
// 	{
// 		int out{INT_MAX};
// 		for(auto j{1}; j<=i; ++j)              
// 			out = min(out, 1+max(m[i-j], j-1));
// 		m.push_back(out);
// 	}
// 	return m.back();    
// }
// If you change variables j=i-j you can get arguably simpler formula

// int eggDrop(int n)
// {
// 	vector m{0};
// 	for(auto i{1}; i<=n; ++i) 
// 	{
// 		int out{INT_MAX};
// 		for(auto j{0}; j<i; ++j)              
// 			out = min(out, 1+max(m[j], i-j-1));  
// 		m.push_back(out);
// 	}
// 	return m.back();    
// }i

// int eggDrop(int n)
// {
//     int i = 0;
// 	int out = 0;
// 	for(i; n--; ++i>out ? out=i, i=1 : 0);           
// 	return out;    
// }
// or maybe like this

// int eggDrop(int n)
// {
// 	auto out{0};
// 	for(auto i{0}; n; --n)
// 		if(++i>out) out=i, i=1;
// 	return out;    
// }
// Solution 3
// time O(1); space O(1)

// Using some math magic you can come up with the formula to solve the problem in O(1).
// The key is to derive integer inverse function of the triangular numbers trinv(n) and to shift it by 1.


// image

//int eggDrop(int n)
//{
//	return (1+sqrt(8.0*n-7))/2;    
//}
// also you can use this formula

// int eggDrop(int n)
// {
// 	return floor(sqrt(2.0*n) + 0.5);    
// }

int main() {
	printf("\n====\n%d floors, %d trials\n", 1, twoEggDrop(1));
	printf("\n====\n%d floors, %d trials\n", 2, twoEggDrop(2));
	printf("\n====\n%d floors, %d trials\n", 2, twoEggDrop(3));
	return 0;
}
