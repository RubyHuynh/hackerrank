#include"../util.h"



int main() {
	int i = 0, val = 0;
	Tree* tree = NULL;
	
	srand(time(NULL));
	while (i++ < 7) {
		val = rand() % (10 + 1 - 0) + 0;
		insert(&tree, val);
	}
	
	dumpLCR(tree, true);
	printf("\n??\n");
	inorderSuccessor(tree, 3);
}
