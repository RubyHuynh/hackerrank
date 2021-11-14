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
	dumpCLR(tree, true);
	dumpLRC(tree, true);
	printf("\nsearch:\n");
	scanf("%d", &val);
	bfs(tree, val);
	isBalance(tree);
}
