#include"../util.h"



/*5.1 set bit */
int setBit(int n, int m, unsigned int i, unsigned int j) {
	int max = ~0; /* all 1's */
	int bits = sizeof(int) * 8;
	int left = max - ((1<<j)-1); /* -1 */
	int right = ((1<<i)-1);
	int mask = left | right;
	int ret;
	printf("\n\n%s\n", __func__);
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



/*5.3 (n & (n-1)) == 0
 * What does it mean if A & B == 0?
 * It means that A and B never have a 1 bit in the same place So if n & (n-1) == 0, then n and
 * n-1 never share a 1
 * What does n-1 look like (as compared with n)?
 * Try doing subtraction by hand (in base 2 or 10) What happens?
 * 1101011000 [base 2]
 * - 1
 *   = 1101010111 [base 2]
 *   593100 [base 10]
 *   - 1
 *   = 593099 [base 10]
 *   When you subtract 1 from a number, you look at the least significant bit If it’s a 1 you change
 *   it to zero and you are done If it’s a zero, you must “borrow” from a larger bit So, you go to
 *   increasingly larger bits, changing each bit from a 0 to a 1, until you find a 1 You flip that one
 *   to a 0 and you are done
 *   Thus, n-1 will look like n, except that n’s initial 0s will be 1’s in n-1, and n’s least significant 1
 *   will be a 0 in (n-1) That is:
 *   if n = abcde1000
 *   then n-1 = abcde0111
 *   So what does n & (n-1) == 0 indicate?
 *   n and (n-1) must have no 1s in common Given that they look like this:
 *   if n = abcde1000
 *   then n-1 = abcde0111
 *   abcde must be all 0s, which means that n must look like this: 00001000 n is therefore a
 *   power of two
 *   So, we have our answer: ((n & (n-1)) == 0) checks if n is a power of 2 (or 0)
 *   */

/* 5.4 A to B */
int bitSwapCnt(int a, int b) {
	int cnt = 0;
	int c = a ^ b;
	int i = 0;

	printf("\n\n%s\n", __func__);
	dumpBits(sizeof(a), &a);
	dumpBits(sizeof(b), &b);
	dumpBits(sizeof(c), &c);
	for ( ;c != 0; c >>= 1) {
		cnt += c & 1;
		if (c & 1) printf("\tcnt++\n");
		printf("\t cnt %d\n", cnt);
	}
	return cnt;
}

int swapOddEven(int x) {
	int swOdd = x & 0xaaaaaaaa;
	int swEven = x & 0x55555555;
	int ret = 0;

	printf("\n\n%s x %d\n", __func__, x);
	dumpBits(sizeof(x), &x);
	dumpBits(sizeof(swOdd), &swOdd);
	dumpBits(sizeof(swEven), &swEven);
	swOdd >>= 1;
	swEven <<= 1;
	printf("\nafter >> , <<\n");
	dumpBits(sizeof(swOdd), &swOdd);
	dumpBits(sizeof(swEven), &swEven);
	ret = swOdd | swEven;
	dumpBits(sizeof(ret), &ret);
	printf("ret %d\n", ret);
	return ret;
}



int main() {
	int x = 1;
	if(*(char *)&x == 1) {
		printf("LITLLE ENDIAN\n");
	}
	else {
		printf("BIG ENDIAN\n");
	}

	int n = ((1<<20) | 1);
	setBit(n, 5, 3, 7);

	bitSwapCnt(3, 4519);

	swapOddEven(1219231);
}
