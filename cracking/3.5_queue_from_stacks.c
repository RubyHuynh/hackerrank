#include "../util.h"

typedef struct Queue {
	Stack		s1;
	Stack		s2;
} Queue;

void sw(Queue* queue) {
	Node* tmp;
	if (!queue->s1.top) {
		while ((tmp = pop(&queue->s2))!=NULL) {
			push(&queue->s1, tmp->val);
		}
	}
}	
	

void queue(Queue* queue, int val) {
	push(&queue->s2, val);
	printf("\t\t%s val (%d)\n", __func__, val);
}

Node* dequeue(Queue* queue) {
	Node* ret = NULL;
	
	sw(queue);
	ret = pop(&queue->s1);
	printf("\t\t%s val (%d)\n", __func__, ret ? ret->val : -1);
	return ret;
}


int main() {
	int i = 0, val = 0;
	int n = 8;
	Queue q;
	memset(&q, 0, sizeof(Queue));
	queue(&q, 1);
	queue(&q, 2);
	queue(&q, 3);
	dequeue(&q);
	queue(&q, 4);
	queue(&q, 5);
	
	dequeue(&q);
	dequeue(&q);
	dequeue(&q);
	dequeue(&q);
	dequeue(&q);
	return 0;
}

