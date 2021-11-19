#include "../util.h"


#define SZ 	300

/* 
fixed size or free growth (node with prev idx)
 * */
int findStart(int* arr, int idx) {
	switch (idx) {
		case 1:
			return 0;
		case 2: 
			return SZ/3;
		default:
			return SZ/3 * 2;
	}
}

void pushArr(int* arr, int idx, int val) {
	int start = findStart(arr, idx);
	int i = start;
	int top = arr[start];
	if (top == -1) {
		top = start;
	}
	arr[++top] = val;
	arr[start] = top;

	while (i <= top) {
		printf("%d \t", arr[i]);
		i++;
	}
	printf("\n");
}


int popArr(int* arr, int idx) {
	int start = findStart(arr, idx);
	int i = start;
	int top = arr[start];
	int ret = arr[top];

	arr[top--] = -1;
	arr[start] = top;
	while (i <= top) {
		printf("%d\t", arr[i]);
		i++;
	}
	printf("\n");
	return ret;
}


Node* func1(Node* list) {
	Node* p1 = NULL, *ret = NULL;
	Node* p2 = NULL, *tmp = NULL;
	int i = 0, cnt = 0;
	TM_INIT
	TM_START(__func__)
	printf("====%s\n", __func__);	
	p1 = list;
	p2 = list;
	while (p2->next) {
		p1 = p1->next;
		p2 = p2->next->next;
		
		if (p1 == p2) {
			break;
		}
	}
	if (!p2->next) {
		goto _done;
	}

	p1 = list;
	while (p1 != p2) {
		p1 = p1->next;
		p2 = p2->next;
	}
	ret = p2;
			
	printf("\t %p(%d)\n", ret, ret->val);
_done:
	TM_STOP(__func__)
	printf("\t %s\n", ret ? "FOUND" : "NOT FOUND");
	return ret;
}



int main() {
	int i = 0, val = 0;
	Stack stack;
	memset(&stack, 0, sizeof(Stack));
	srand(time(NULL));
	while (i++ < 45) {
		val = rand() % (300 + 1 - 0) + 0;
		push(&stack, val);
	}
	dumpStack(&stack);
	
	{
		int arr[SZ];
		int i = 0;

		memset(arr, -1, sizeof(arr));
		pushArr(arr, 1, 1);
		pushArr(arr, 1, 2);
		pushArr(arr, 1, 3);
		popArr(arr, 1);
		pushArr(arr,1,7);

	
		pushArr(arr, 2, 21);
		pushArr(arr, 2, 22);
		pushArr(arr, 2, 23);
		pushArr(arr, 2, 27);


		pushArr(arr, 3, 32);
		pushArr(arr, 3, 34);
		pushArr(arr, 3, 36);
		pushArr(arr, 3, 39);
		pushArr(arr, 3, 38);
		
		while (i < SZ) {
			printf("%d\t", arr[i++]);
		}
		printf("\n");
	}
/*	func1(list);*/
	return 0;
}
