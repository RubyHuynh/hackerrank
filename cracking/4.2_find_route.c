#include"../util.h"



int main() {
	int i = 0, j, val = 0, n = 6;
	int arr[n][n];
	memset(arr, 0, sizeof(arr));
	srand(time(NULL));
	while (i < n) {
		j = 0;
		/*while(j++ < n) {
			val = rand() % (10 + 1 - 0) + 0;
			arr[i][j] = val;
		}*/
		arr[i][i] = -1;
		++i;
	}
	arr[0][1] = 4;
	arr[1][2] = 5; arr[1][3]= 1;
	arr[2][4] = 2;
	arr[3][5] = 3;
	arr[4][3] = 9;
	
	
	dumpGr(&arr[0][0], n);
	
	routeGr(&arr[0][0], n, 2, 5);
		
}
