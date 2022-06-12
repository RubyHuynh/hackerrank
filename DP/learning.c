#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define LOG(_X) printf("%d\n", _X);
#define MAX_MAX (5000000 * sizeof(int))

int* _arr;

bool canSum(int target, int* arr, int n, int* memo) {
	int i;
	if (target == 0) return true;
	if (target < 0) return false;
	if (memo[target]) return memo[target];
	for (i = 0; i < n; i++) {
		int remainder = target - arr[i];
		if (canSum(remainder, arr, n, memo)) {
			printf("\t %d\n", arr[i]);
			memo[arr[i]] = true;
			return true;
		}
	}
 	memo[target] = false;
	return false;
}


/*top-down*/
int fibo(int n, int* memo) {
	if (n <= 2) return 1;
	if (memo[n]) return memo[n];
	memo[n] = fibo(n-1, memo) + fibo(n-2, memo);
	return memo[n];
}

/* bottom-up */
int fibo0(int n, int* memo) {
	int i;

	memo[0] = 0;
	memo[1] = 1;

	for (i = 2; i <=n; i++) {
		memo[i] = memo[i-1] + memo[i-2];
	}
	return memo[n];
}
 
/*optimized bottom-up */
int fibo1(int n) {
	int a = 0, b = 1, rs, i;
	if (n == 0) return 0;
	
	for (i = 2; i <= n; i++) {
		rs = a + b;
		a = b;
		b = rs;
	}
	return rs;
}

/*Math*/
/*
#include<math.h>
int fib(int n) {
  double phi = (1 + sqrt(5)) / 2;
  return round(pow(phi, n) / sqrt(5));
}
*/
int main() {	
 	_arr = calloc(1, MAX_MAX);
	LOG(fibo(5, _arr));
	memset(_arr, 0, MAX_MAX);
	LOG(fibo(7, _arr));
	memset(_arr, 0, MAX_MAX);
	LOG(fibo(30, _arr));
	memset(_arr, 0, MAX_MAX);
	LOG(fibo0(30, _arr));
	LOG(fibo1(30));

	printf("===\n");
	{
		int arr[] = {3, 4,5, 25, 1};
		memset(_arr, 0, MAX_MAX);
		LOG(canSum(100, arr, 5, _arr))
	}
	return 0;
}
