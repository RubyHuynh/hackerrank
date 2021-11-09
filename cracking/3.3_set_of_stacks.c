#include "../util.h"


/**
*/
#define SZ 	300

typedef struct _Chain {
	Stack*		cur;
	Stack*		next;
} Chain;

void attach(Chain* chain, Stack* val) {
	Stack* tmp = NULL;

	tmp = chain->cur;
	chain->cur = val;
	chain->next = tmp;
}

Stack* detach(Chain* chain) {
	Stack* tmp = NULL;

	tmp = chain->cur;
	chain->cur = chain->next;
	return tmp;
}

typedef struct _SetStacks {
	Stack*		cur;
	int 		sz;
	int 		maxSz;
	int 		setNb;
	Chain		chain;
} SetStacks;

void pushSet(SetStacks* set, int val) {
_begin:
	if (!set->cur) {
		set->cur = (Stack*) malloc(sizeof(Stack));
	}

	if (set->sz < set->maxSz) {
		push(set->cur, val);
		set->sz++;
	}
	else {
		attach(&set->chain, set->cur);
		set->cur = NULL;
		set->sz = 0;
		set->setNb++;
		goto _begin;
	}
	printf("\t%s %d (sz=%d)\n", __func__, val, set->sz);
}

Node* popSet(SetStacks* set) {
	Node* ret = NULL;
	if (!set->cur) {
		return ret;
	}

	ret = pop(set->cur);
	set->sz--;
	
	if (set->sz == 0) {
		set->cur = detach(&set->chain);
		set->setNb--;
		set->sz = set->maxSz;
	}
	printf("\t%s %d (sz=%d)\n", __func__, ret->val, set->sz);
	return ret;
}

int main() {
	int i = 0, val = 0;
	SetStacks set;
	memset(&set, 0, sizeof(SetStacks));
	set.maxSz = 5;
	srand(time(NULL));
	while (i++ < 45) {
		val = rand() % (300 + 1 - 0) + 0;
		pushSet(&set, val);
	}
	popSet(&set);
	popSet(&set);
	popSet(&set);
	popSet(&set);
	popSet(&set);
	popSet(&set);
	
	return 0;
}

