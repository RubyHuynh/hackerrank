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


int main() {
	TM_INIT
	TM_START("recursive")
	printf("fibo(40) = %d\n", fibo(40));
	TM_STOP("recursive")
	TM_START("iterative")
	printf("fibo(40) = %d\n", fibo1(40));
	TM_STOP("iterative");
}
