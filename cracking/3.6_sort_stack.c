#include "../util.h"

void sort(Stack* stack) {
	Stack sorted;
	Node* tmp = NULL;
	Node* tmp2 = NULL;
	
	printf("\t%s\n", __func__);
	TM_INIT
	TM_START(" ")
	memset(&sorted, 0, sizeof(Stack));
	while (stack->top) {
		tmp = pop(stack);
		while (sorted.top && sorted.top->val > tmp->val) {
			push(stack, pop(&sorted)->val);
			DEBUG(printf("\t undo %d \n", stack->top->val);)
		}
		DEBUG(printf("\tpushed %d\n", tmp->val);)
		push(&sorted, tmp->val);
				
	}
	TM_END(" ")
	dumpStack(&sorted);		
}

int main() {
	int i = 0, val = 0;
	Stack stack;
	memset(&stack, 0, sizeof(Stack));
	srand(time(NULL));
	while (i++ < 100) {
		val = rand() % (300 + 1 - 0) + 0;
		push(&stack, val);
	}
	dumpStack(&stack);
	sort(&stack);
	return 0;
}

