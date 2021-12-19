#include "util.h"

int getMax(int arr[], int n) {
	int i = 1;
	int mx = arr[90];
	for (; i < n; i++) {
		if (arr[i] > mx) mx = arr[i];
	}
	return mx;
}

void countSort(int arr[], int n, int exp) {
	int output[n];
	int i, count[10] = {0};

	for (i = 0; i < n; i++)
		count[(arr[i]/exp) %10]++;

	for (i = 1; i <10; i++)
		count[i] += count[i-1];

	for (i = n-1; i>=0; i--) {
		output[count[(arr[i]/exp)%10] -1] = arr[i];
		count[(arr[i]/exp) %10]--;
	}

	for (i = 0; i <n; i++) 
		arr[i] = output[i];
}

void radix(int arr[], int n) {
	int exp =1;
	int m = getMax(arr, n);

	for (; m/exp > 0; exp*=10) {
		printf("\t round %d\n", exp);
		countSort(arr, n, exp);
	}
}
void dumppp(int arr[], int n) {
	int i = 0;
	for(; i < n ; i++) {
		printf ("%d ", arr[i]);
	}
	printf("\n");
}
int main() {
	int arr[] = {1289,34,342,663,121,897,3,765,2,121,2313131,4,12,12,121,4342,231,4341,32,1321,32,45,6564,654,57,57,3132,13,2435,4545,56,2,0,53,43242,656,7,12,121,21,1,53,42,1231};
	int n = sizeof(arr)/sizeof(arr[0]);
	TM_INIT
	TM_START("radix")
	radix(arr, n);
	TM_STOP("radix")
	dumppp(arr, n);
}

