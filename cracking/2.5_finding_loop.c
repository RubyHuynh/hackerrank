#include "../util.h"


/* 02 ways:
 * O(n) time, O(n) space
 * O(n^2) time no space
 * */
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
	Node* list = NULL, *list2 = NULL, *tmp = NULL;
	srand(time(NULL));
	while (i++ < 45) {
		val = rand() % (300 + 1 - 0) + 0;
		add(&list, val);
	}
	Node* lo = (Node*) malloc(sizeof(Node));
	lo->val = 1;
	lo->next = (Node*) malloc(sizeof(Node));
	lo->next->val = 2;
	lo->next->next =  (Node*) malloc(sizeof(Node));
	lo->next->next->val = 3;
	lo->next->next->next =  (Node*) malloc(sizeof(Node));
	lo->next->next->next->val = 4;
	lo->next->next->next->next =  (Node*) malloc(sizeof(Node));
	lo->next->next->next->next->val = 5;
	tmp = list->next;
	list->next = lo;
	lo->next->next->next = lo;/*tmp;*/

	//add(&list,4);
	//dump(list);
	func1(list);
	return 0;
}
