#include"../util.h"



int main() {
	int i = 0, j, val = 0, n = 6;
	int arr[n];
	memset(arr, 0, sizeof(arr));
	srand(time(NULL));
	while (i < n) {
		arr[i] = i + 1;
		++i;
	}
	dumpArr(arr, n);
	
	{
		Tree tree;
		memset(&tree, 0, sizeof(Tree));
		buildTree(arr, 0, n-1, &tree);
		dumpLCR(&tree, "heee");
	}
}
