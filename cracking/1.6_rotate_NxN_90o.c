#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<sys/time.h>
#include "../util.h"

void dump(int arr[][5], int n) {
	int i, j;
	printf("%s %p %d\n", __func__, arr, n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
}

/* 02 ways:
 * O(n^2) time + O(n^2) space 
 * O((n/2)^2) time + no space
 * */
void func1(int arr[5][5], int n) {
	int i = 0;
	int j = 0;
	int (*ret)[][5] = NULL;

	dump(arr, n);
	TM_INIT
	TM_START(__func__)
 	ret = (int (*)[][5]) malloc(sizeof (int[5][5]));
	for (; i < n; i++) {
		for (j = 0; j < n; j++) {
			(*ret)[i][j] = arr[n-j-1][i];
			printf("[%d][%d] = %d \n", i, j, (*ret)[i][j]);
		}
	}
_done:
	TM_STOP(__func__)
	dump(*ret, n);
}


void func2(int arr[5][5], int n) {
	int i = 0;
	int j = 0;
	dump(arr, n);
	TM_INIT
	TM_START(__func__)
	for (; i < n/2; ++i) {
		int first = i;
		int last = n - i -1;
		printf("\t i=%d first=%d last=%d\n", i, first, last);
		for (j = first; j < last; ++j) {
			int offset = j - i;
			int top = arr[first][j];
			DEBUG(printf("\t\tj=%d offset=%d top=%d\n", j, offset, top);)
			/* left->top */
			DEBUG(printf("\t\t swap %d][%d with %d][%d\n", first, j, last-offset,first);)
			arr[first][j] = arr[last -offset][first];
			/* bottom->left */
			DEBUG(printf("\t\t swap %d][%d with %d][%d\n"
				, last-offset, first, last, last-offset);)
			arr[last-offset][first] = arr[last][last-offset];
			/* right->bottom */
			DEBUG(printf("\t\t swap %d][%d with %d][%d\n", last, last-offset, j, last);)
			arr[last][last-offset] = arr[j][last];
			/* top->right */
			DEBUG(printf("\t\t swap %d][%d with %d\n", j, last, top);)
			arr[j][last] = top;
	
		}
	}
_done:
	TM_STOP(__func__)
	dump(arr, n);
}

int main() {
	int i = 0;
	int arr[5][5] = {{1,2,3,4,5}, {6,7,8,9,10}, {11,12,13,14,15}, {16,17,18,19,20}, {21,22,23,24,25}};
	printf("%p\n", arr);
	func1(arr, sizeof(arr)/sizeof(arr[0]));
	printf("\n\n");
	func2(arr, sizeof(arr)/sizeof(arr[0]));
	return 0;
}
