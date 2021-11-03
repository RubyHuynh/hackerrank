#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<sys/time.h>
#include "../util.h"

void dump(int arr[][5], int m, int n) {
	int i, j;
	printf("%s %p %d\n", __func__, arr, n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
}

/* 01 ways:
 * O(2n^2) AKA O(n^2) time + O(m+n) space
 * */
void func1(int arr[][5], int m, int n) {
	int i = 0;
	int j = 0;
	int tmp;
	int* checkedR = NULL;
	int* checkedC = NULL;
	
	dump(arr, m, n);
	TM_INIT
	TM_START(__func__)
	checkedR = (int*)calloc(1, sizeof(int) * m);
	checkedC = (int*)calloc(1, sizeof(int) * n);
	
	for (; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (arr[i][j] == 0) {
				checkedR[i] = 1;
				checkedC[j] = 1;
			}
		}
	}

	for (i = 0; i < m; ++i) {
		for (j = 0; j< n; ++j) {
			if (checkedR[i] == 1 || checkedC[j] == 1) {
				arr[i][j] = 0;
			}
		}
	}
_done:
	TM_END(__func__)
	dump(arr, m, n);
}


int main() {
	int i = 0;
	int arr[6][5] = {{1,0,3,4,5}, {6,7,0,9,10}, {11,12,13,14,15}, {16,17,18,70,20}, {10,70,23,24,25}, {26,27,28,29,30}};
	printf("%p\n", arr);
	func1(arr, 6, 5);
	return 0;
}
