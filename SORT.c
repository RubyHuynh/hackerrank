#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

int steps = 0;
#define SZ(_arr) sizeof(_arr)/sizeof(_arr[0])

void swap(int* x, int* y) {
	int z = *x;
	*x = *y;
	*y = z;
}

void dump(int* arr, int sz) {
	int i = 0;
	printf("\t after %d steps: ", steps);
	for (; i < sz; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void bubble(int* arr, int sz) {
	int i = 0;
	bool sorted = false;
	int lastUnsorted = sz -1;

	printf("%s()\n", __func__);
	steps = 0;
	while (!sorted) {
		sorted = true;
		for (i = 0; i < lastUnsorted; i++) {
			if (arr[i] < arr[i+1]) {
				swap(&arr[i], &arr[i+1]);
				sorted = false;
			}
		}
		lastUnsorted--;
		steps++;
	}
	dump(arr, sz);
}

void bubble1(int* arr, int sz) {
	int i = 0;
	bool sorted = false;
	printf("%s()\n", __func__);
	steps = 0;
	while (!sorted) {
		sorted = true;
		for (i = 0; i < sz - 1; i++) {
			if (arr[i] > arr[i+1]) {
				swap(&arr[i], &arr[i+1]);
				sorted = false;
			}
		}
		steps++;
	}
	dump(arr, sz);
}


int main() {
	int arr[] = {6,7,3,2,1,4,9,231,213,1,0,13, 8, 6, 5};
	printf("SORT THIS ARRAY\n");
	dump(arr, SZ(arr));
	bubble(arr, SZ(arr));
	bubble1(arr, SZ(arr));
	
	return 0;
}
