#include "../util.h"


/* 03 ways:
 * O(2n) find length, then look again until i == n-nth
 * O(1n) + O(n) space as array
 * O(1n) create a gap, using 2 pointer 
 * */
bool func1(Node* list, int nth) {
	Node* cur, *tmp;
	int des = nth;
	int i = 0;
	bool ret = false;
	TM_INIT
	TM_START(__func__)
	printf("====%s\n", __func__);
	ret = false;
	
	cur = list;
	tmp = list;
	while (tmp && i++ < des) {
		tmp = tmp->next;
	}
	if (!tmp) {
		printf("\t length < nth, stopped at %d", i);
		goto _done;
	}
	while (tmp) {
		cur = cur->next;
		tmp = tmp->next;
	}
	printf("\t got %d\n", cur->val);
	ret = true;
_done:
	TM_STOP(__func__)
	dump(list);
	printf("\t %s\n", ret ? "FOUND" : "NOT FOUND");
	return ret;
}

bool func2(Node* list, int nth) {
	Node* cur, *tmp;
	int des = 0;
	int n = 0;
	int i = 0;
	bool ret = false;
	TM_INIT
	TM_START(__func__)
	printf("====%s\n", __func__);
	ret = false;
	
	cur = list;
	while (cur) {
		n++;
		cur = cur->next;
	}
	des = n - nth;
	if (des < 0) {
		printf("\t length < nth, stopped at %d\n", n);
		goto _done;
	}
	cur = list;
	while (cur) {
		if (i++ == des) break;
		cur = cur->next;
	}
	printf("\t got %d\n", cur->val);
	ret = true;
_done:
	TM_STOP(__func__)
	dump(list);
	printf("\t %s\n", ret ? "FOUND" : "NOT FOUND");
	return ret;
}


int main() {
	int i = 0, val = 0;
	Node* list = NULL, *list2 = NULL;
	srand(time(NULL));
	while (i++ < 45) {
		val = rand() % (300 + 1 - 0) + 0;
		add(&list, val);
		add(&list2, val);
	}
	dump(list);
	func1(list, 13);
	func2(list2, 13);
	return 0;
}
