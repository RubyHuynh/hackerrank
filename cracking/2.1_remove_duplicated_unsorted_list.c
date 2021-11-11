#include "../util.h"


/* 02 ways:
 * O(n) given instant lookup on O(n) arr/hash space
 * O(n^2) when no space
 * */
bool func1(Node* list) {
	Node* cur, *tmp;
	int i = 0;
	bool ret = false;
	TM_INIT
	TM_START(__func__)
	printf("====%s\n", __func__);
	ret = true;
	
	cur = list;
	while (cur && cur->next) {
		tmp = list;
		while (tmp && tmp != cur->next && tmp->val != cur->next->val) {
			tmp = tmp->next;
		}
		if (tmp != cur->next) {
			tmp = cur->next;
			cur->next = tmp->next;
			printf("\tRemoved %d at idx %d\n", tmp->val, i);
			del(tmp);
			ret = true;
		}
		cur = cur->next;
		i++;
	}
_done:
	TM_END(__func__)
	dump(list);
	printf("\t %s\n", ret ? "FOUND" : "NOT FOUND");
	return ret;
}

bool func2(Node* list) {
	Node* cur, *tmp;
	int* arr = NULL;
	int i = 0;
	bool ret = false;
	TM_INIT
	TM_START(__func__)
	printf("====%s\n", __func__);
	ret = true;
	arr = (int*) malloc(sizeof(int) *301);
	memset(arr, -1, 301);
	cur = list;
	if (cur) { 
		arr[cur->val] = 1;
	}
	while (cur && cur->next) {	
		if (arr[cur->next->val] == 1) {
			tmp = cur->next;
			cur->next = tmp->next;
			printf("\t Removed %d at idx %d\n", tmp->val, i);
			del(tmp);
			ret = true;		
		}
		else {
			arr[cur->next->val] = 1;
		}
		i++;
		cur = cur->next;
	}
_done:
	TM_END(__func__)
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
	func1(list);
	func2(list2);
	return 0;
}
