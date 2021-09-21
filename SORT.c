#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

int steps = 0;
typedef struct _Arr {
	int	arr[100];
	int 	sz;
} Arr;

#define SZ(_arr) sizeof(_arr)/sizeof(_arr[0])

void swap(int* x, int* y) {
	int z = *x;
	*x = *y;
	*y = z;
}

void dump(int* arr, int sz) {
	int i = 0;
	printf("\t after %d steps(%d): ", steps, sz);
	for (; i < sz; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void bubble(Arr ar) {
	int* arr = ar.arr;
	int sz = ar.sz;
	int i = 0;
	bool sorted = false;
	int lastUnsorted = sz -1;

	printf("%s()\n", __func__);
	steps = 0;
	dump(arr, sz);
	while (!sorted) {
		sorted = true;
		for (i = 0; i < lastUnsorted; i++) {
			if (arr[i] > arr[i+1]) {
				swap(&arr[i], &arr[i+1]);
				sorted = false;
			}
			steps++;
		}
		lastUnsorted--;
	}
	dump(arr, sz);
}

void bubble1(Arr ar) {
	int* arr = ar.arr;
	int sz = ar.sz;
	int i = 0;
	bool sorted = false;
	printf("%s()\n", __func__);
	steps = 0;

	dump(arr, sz);
	while (!sorted) {
		sorted = true;
		for (i = 0; i < sz - 1; i++) {
			if (arr[i] > arr[i+1]) {
				swap(&arr[i], &arr[i+1]);
				sorted = false;
			}
			steps++;
		}
	}
	dump(arr, sz);
}

/*
 Complexity Analysis:
 Worst case performance O(n^2)
 Average case performance O(n^2)
 Space Complexity O(1)
 Adaptive: When array is nearly sorted O(n)
 Stable Sorting Yes
*/
void bubble2(Arr ar) {
	int* arr = ar.arr;
	int sz = ar.sz;
	int i = 0, j = 0;
	bool sorted = true;
	printf("%s()\n", __func__);
	steps = 0;
		
	dump(arr, sz);
	for (i = 0; i < sz - 1 && sorted ; i++) {
		sorted = false;
		for (j = 0; j < sz - 1 - i; j++) {
			if (arr[j] > arr[j+1]) {
				swap(&arr[j], &arr[j + 1]);
				sorted = true;
			}
			steps++;
		}
	}
	
	dump(arr, sz);
}


/*
 *Complexity Analysis:
 Worst case Time Complexity O(n^2)
 Best case Time Complexity O(n)
 Average case Time Complexity O(n^2)
 Space Complexity O(1)
 Stable sorting Yes
 *
 * */
void insert(Arr ar) {
	int* arr = ar.arr;
	int sz = ar.sz;
	int i = 0, j = 0, temp = 0;
	bool sorted = true;
	printf("%s()\n", __func__);
	steps = 0;
		
	dump(arr, sz);
	for (i = 1; i < sz; i++) {
		temp = arr[i];
		for (j = i; j > 0 && arr[j-1] > temp; j--) {
			arr[j] = arr[j-1];
			steps++;
		}
		arr[j] = temp;
	}
	
	dump(arr, sz);
}


/*
 Complexity Analysis:
 Worst Case Time Complexity O(n2)
 Best Case Time Complexity O(n2)
 Average case Time Complexity O(n2)
 Space Complexity O(1)
 Stable Sorting No
 */
void selection(Arr ar) {
	int* arr = ar.arr;
	int sz = ar.sz;
	int i = 0, j = 0, temp = 0, max = 0;
	bool sorted = true;
	printf("%s()\n", __func__);
	steps = 0;
		
	dump(arr, sz);
	for (i = 0; i < sz -1; i++) {
		max = 0; /* index of greatest number */
		for (j = 1; j < sz - 1 - i; j++) {
			if (arr[j] > arr[max]) {
				max = j;
			}
			steps++;
		}
		swap(&arr[sz-1-i], &arr[max]);
	}
	
	dump(arr, sz);
}


void selection1(Arr ar) {
	int* arr = ar.arr;
	int sz = ar.sz;
	int i = 0, j = 0, temp = 0, min = 0;
	bool sorted = true;
	printf("%s()\n", __func__);
	steps = 0;
		
	dump(arr, sz);
	for (i = 0; i < sz -1; i++) {
		min = 0;
		for (j = i + 1; j < sz; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
			steps++;
		}
		swap(&arr[i], &arr[min]);
	}
	
	dump(arr, sz);
}

void mergeHaves(int* arr, int* tmpArr, int left, int mid, int right) {
	int start1 = left;
	int stop1 = mid;
	int start2 = mid + 1;
	int stop2 = right;
	int count = left;
	int i = 0;
	printf("\n\t\t%s() left=%d mid%d right =%d", __func__, left, mid, right);
	while (start1 <= stop1 && start2 <= stop2) {
		if (arr[start1] < arr[start2]) {
			tmpArr[count++] = arr[start1++];
		}
		else {
			tmpArr[count++] = arr[start2++];
		}
	}
	while (start1 <= stop1) {
		tmpArr[count++] = arr[start1++];
	}
	while (start2 <= stop2) {
		tmpArr[count++] = arr[start2++];
	}

	for (i = left; i <= right; i++) {
		arr[i] = tmpArr[i];
	}
}

void mergeSort(int* arr, int* tmpArr, int left, int right) {
	int middle = (left + right)/2;
	printf("\n\t%s() left=%d right =%d", __func__, left, right);
	if (left >= right) {
		printf("\n\t%s() done");
		return;
	}
	mergeSort(arr, tmpArr, left, middle);
	mergeSort(arr, tmpArr, middle + 1, right);
	mergeHaves(arr, tmpArr, left, middle, right);
}

/*
 Complexity Analysis:
 Worst Case Time Complexity O(nlogn)
 Best Case Time Complexity O(nlogn)
 Average Time Complexity O(nlogn)
 Space Complexity O(n)
 Stable Sorting Yes
 */
void merge(Arr ar) {
	int* arr = ar.arr;
	int sz = ar.sz;
	int* tmpArr = (int*) malloc(sizeof(int) * sz);
	int i = 0, j = 0, temp = 0, min = 0;
	bool sorted = true;
	printf("%s()\n", __func__);
	steps = 0;
		
	dump(arr, sz);
	mergeSort(arr, tmpArr, 0, sz -1);
	
	dump(arr, sz);
}


int main() {
	int arr[] = {6,7,3,2,1,4,9,231,213,1,0,13, 8, 6, 5};
	Arr ar;
        memcpy(ar.arr, arr, SZ(arr) * sizeof(int));
	ar.sz = SZ(arr);
	printf("SORT THIS ARRAY\n");
	dump(arr, SZ(arr));
	dump(ar.arr, ar.sz);
	bubble(ar);
	bubble1(ar);
	bubble2(ar);
	insert(ar);
	selection(ar);
	selection1(ar);
	merge(ar);
	
	return 0;
}
