#include"../util.h"


/*5.1 set bit */
int setBit(int n, int m, unsigned int i, unsigned int j) {
	int max = ~0; /* all 1's */
	int bits = sizeof(int) * 8;
	int left = max - ((1<<j)-1); /* -1 */
	int right = ((1<<i)-1);
	int mask = left | right;
	int ret;
	dumpBits(sizeof(n), &n);
	dumpBits(sizeof(m), &m);
	printf("left=%d\n", left);
	dumpBits(sizeof(left), &left);
	printf("right=%d\n", right);
	dumpBits(sizeof(right), &right);
	ret = (n&mask) | (m << i);
	dumpBits(sizeof(ret), &ret);
	printf("%s ret=%d\n", __func__, ret);
	return ret;
}


int main() {
	int n = ((1<<20) | 1);
	setBit(n, 5, 3, 7);
}
