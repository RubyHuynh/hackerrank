#include "../util.h"


/**
- 02 ways, either keep min in each node or another chain of min to be replaced
*/
#define SZ 	300

typedef struct _Node1 {
	int 		val;
	int 		curMin;
	struct _Node1*	next;
} Node1;

typedef struct _Stack1 {
	Node1*		top;
} Stack1;

void pushStack1(Stack1* stack, int val) {
	Node1* item = (Node1*) malloc(sizeof(Node1));
	int oldMin = stack->top ? stack->top->curMin : 400;

	item->val = val;
	item->curMin = val > oldMin ? oldMin : val;
	item->next = stack->top;
	stack->top = item;
}


Node1* popStack1(Stack1* stack) {
	Node1* ret = stack->top;
	stack->top = ret->next;
	ret->next = NULL;
	printf("%s popped %d\n", __func__, ret->val);
	return ret;
}

int minStack1(Stack1* stack) {
	if (stack->top) {
		printf("%s min is %d\n", __func__, stack->top->curMin);
	}
	return stack->top ? stack->top->curMin : 400;
}


typedef struct _Stack2 {
	Node*		top;
	Stack		min;
} Stack2;


void pushStack2(Stack2* stack, int val) {
	Node* item = (Node*) malloc(sizeof(Node));
	item->val = val;
	item->next = stack->top;
	stack->top = item;
	/* must have counter */
	if (!stack->min.top || stack->min.top->val > val) {
		push(&stack->min, val);
	}
}


Node* popStack2(Stack2* stack) {
	Node* ret = stack->top;
	stack->top = ret->next;
	ret->next = NULL;
	/* assume it's unique, anw */
	if (stack->min.top->val == ret->val) {
		pop(&stack->min);
	}
	printf("%s popped %d\n", __func__, ret->val);
	return ret;
}

int minStack2(Stack2* stack) {
	printf("%s min is %d\n", __func__, stack->min.top->val);
	
	return stack->min.top->val;
}

int main() {
	int i = 0, val = 0;
	Stack1 stack;
	Stack2 stack2;
	memset(&stack, 0, sizeof(Stack));
	memset(&stack2, 0, sizeof(Stack2));
	srand(time(NULL));
	while (i++ < 45) {
		val = rand() % (300 + 1 - 0) + 0;
		pushStack1(&stack, val);
		pushStack2(&stack2, val);
		minStack1(&stack);
		minStack2(&stack2);
	}
	popStack1(&stack);
	minStack1(&stack);

	popStack2(&stack2);
	minStack2(&stack2);
	
	popStack1(&stack);
	popStack1(&stack);
	popStack1(&stack);
	minStack1(&stack);

	
	return 0;
}

