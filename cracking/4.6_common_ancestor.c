#include"../util.h"



int main() {
	int i = 0, val = 0;
	Tree* tree = NULL;
	
	srand(time(NULL));
	while (i++ < 19) {
		val = rand() % (20 + 1 - 0) + 0;
		insert(&tree, val);
	}
	
	dumpLCR(tree, true);
	printf("\nattempt1:\n");
	commonAncestor(tree, 3, 7);
	printf("\nattemp2:\n");
	commonAncestor1(tree, 3, 7);
}
