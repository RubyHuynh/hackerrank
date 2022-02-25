#include<stdlib.h>
#include<stdio.h>


/*
 *Problem: given n, find the number of different ways to write
n as the sum of 1, 3, 4
◮ Example: for n = 5, the answer is 6
5 = 1 + 1 + 1 + 1 + 1
= 1 + 1 + 3
= 1 + 3 + 1
= 3 + 1 + 1
= 1 + 4
= 4 + 1

 * */

int ways(int n) {
	int i = 0;
	int rs[n];
	memset(rs, 0, sizeof(rs));
	/* base cases */
	rs[0] = 1; /* why? */
	rs[1] = 1;
	rs[2] = 1;
	rs[3] = 2;
	for (i = 4; i <= n; i++) {
		rs[i] = rs[i-4] + rs[i-3] + rs[i-1];
	}
	return rs[n];
}

int main() {
	printf("%d\n", ways(5));
	printf("%d\n", ways(6));
	printf("%d\n", ways(10));
	return 0;
}
