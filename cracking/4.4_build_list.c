#include"../util.h"



int main() {
	int i = 0, val = 0;
	Tree* tree = NULL;
	Node** list = (Node**) calloc(1, sizeof(Node*) * 7);
	srand(time(NULL));
	while (i++ < 7) {
		val = rand() % (10 + 1 - 0) + 0;
		insert(&tree, val);
	}
	dumpLCR(tree, true);
	printf("??\n");
	buildList(tree, list);
	dump(list[0]);
}
