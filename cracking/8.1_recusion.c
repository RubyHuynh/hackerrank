#include"../util.h"


/*8.1 fibo */
int fibo(int n) {
	if (n ==0) return 0;
	else if (n == 1) return 1;
	else if (n > 1) return fibo(n-1) + fibo(n-2);
	else return -1;
}

int fibo1(int n) {
	int a = 1, b = 1, c = 0, i = 0;
	if (n < 0) return -1;
	if (n == 0) return 0;
	
	for (i = 3; i <= n; i++) {
		c = a + b;
		a = b;
		b = c;
	}
	return b;
}

/*8.2 paths in NxN */
int numberOfPaths(int m, int n) {
	if (m == 1 || n == 1) return 1;

	return numberOfPaths(m, n-1) + numberOfPaths(m-1, n);
}
int numberOfPaths1(int m, int n) {
	int i = 0, j = 0;
	int count[m][n];

	for (; i < m; i++) {
		count[i][0] = 1;
	}


	for (; j < n; j++) {
		count[0][j] = 1;
	}

	for (i = 1; i < m; i++) {
		for (j = 1; j < n; j++) {
			count[i][j] = count[i-1][j] + count[i][j-1];
		}
	}
	return count[m-1][n-1];
}

int numberOfPaths2(int m, int n) {
	int dp[20] = { 1 };
	int i = 0, j = 1;
	dp[0] = 1;
	           
	for (; i < m; i++) {
	    	for (; j < n; j++) {
			dp[j] += dp[j - 1];
		}
	}
	return dp[n-1];
}

int numberOfPaths3(int m, int n) {
	    // We have to calculate m+n-2 C n-1 here
	    //     // which will be (m+n-2)! / (n-1)! (m-1)!
	int path = 1;
	int i = n;
	for (; i < (m + n - 1); i++) {
		path *= i;
		path /= (i - n + 1);
	}
	return path;
}

int main() {
	TM_INIT
	TM_START("recursive")
	printf("fibo(40) = %d\n", fibo(40));
	TM_STOP("recursive")
	TM_START("iterative")
	printf("fibo(40) = %d\n", fibo1(40));
	TM_STOP("iterative");


	TM_START("number of paths")
	printf("7x4 = %d\n", numberOfPaths(7, 14));
	TM_STOP("number of paths");


	TM_START("number of paths, DP")
	printf("7x4 = %d\n", numberOfPaths1(7, 14));
	TM_STOP("number of paths, DP")


	TM_START("number of paths, DP2")
	printf("7x4 = %d\n", numberOfPaths2(7, 14));
	TM_STOP("number of paths, DP2")

	TM_START("number of paths, Math")
	printf("7x4 = %d\n", numberOfPaths3(7, 14));
	TM_STOP("number of paths, Math")
}
