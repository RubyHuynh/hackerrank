#include "../util.h"

typedef struct _Tower {
	Stack		disks;
	int 		id;
	
} Tower;

void addDisk(Tower* tower, int val) {
	if (tower->disks.top && tower->disks.top->val <= val) {
		printf("\t\t%s Error placing disk %d\n", __func__, val);
	}
	else {
		push(&tower->disks, val);
		printf("\t\t%s val (%d) on tower (%d)\n", __func__, val, tower->id);
	}
}

void moveDisk(Tower* from, Tower* to) {
	int val = -1;
	Node* top = pop(&from->disks);
	if (top) {
		val = top->val;
		printf("\t%s val (%d) from tower (%d) to tower (%d)\n"
			, __func__, val, from->id, to->id);
		addDisk(to, val);
	}
	else {
		printf("%s error, nothing left in from-tower(%d)", __func__, from->id);
	}
}

void moveDisks(int n, Tower* from, Tower* to, Tower* buffer) {
	if (n > 0) {
		moveDisks(n - 1, from, buffer, to);
		moveDisk(from, to);
		moveDisks(n - 1, buffer, to, from);		
	}
}

int main() {
	int i = 0, val = 0;
	int n = 8;
	Tower* towers = (Tower*) calloc(1, sizeof(Tower) * 3);
	for (; i < 3; ++i) {
		towers[i].id = i;
	}
	
	for (i = n-1; i >= 0; --i) {
		addDisk(&towers[0], i);
	}
	moveDisks(n, &towers[0], &towers[2], &towers[1]);

	return 0;
}

