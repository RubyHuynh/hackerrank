#include"../util.h"



int main() {
	int i = 0, val = 0;
	Tree* tree = NULL;
	Tree* tree1 = NULL;
	
	srand(time(NULL));
	while (i++ < 19) {
		val = rand() % (20 + 1 - 0) + 0;
		insert(&tree, val);
		insert(&tree1, val);
	}
	
	dumpLCR(tree, true);
	dumpLCR(tree1, true);
	printf("\nattempt1:\n");
	/*commonAncestor(tree, 3, 7);*/
	printf("\nattemp2:\n");
	containTree(tree, tree1);
}
