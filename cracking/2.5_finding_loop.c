#include "../util.h"


/* 02 ways:
 * O(n) time, O(n) space
 * O(n^2) time no space
 * */
List* func1(List* list) {
	List* cur = NULL, *ret = NULL;
	List** checked = NULL;
	int i = 0, cnt = 0;
	TM_INIT
	TM_START(__func__)
	printf("====%s\n", __func__);	
	cur = list;
	while (cur) {
		++i;
		cur = cur->next;
	}
	checked = (List**) calloc(1, sizeof(List*)*i);
	i = 0;
	cur = list;
	while (cur) {
		i = 0;
		DEBUG(printf("\t cur=%p(%d) \n", cur, cur->val);)
		while (i < cnt && checked[i] && checked[i]->val != cur->val) {
			DEBUG(printf("\t chechedk[%d]=%p vs cur=%p \n", i, checked[i], cur);)
			i++;
		}
		if (checked[i] && checked[i]->val == cur->val) {
			ret = cur;
			printf("\t got %p = %d\n", cur, cur->val);
			goto _done;
		}
		checked[cnt++] = cur;
		cur = cur->next;
	}
			
_done:
	TM_END(__func__)
	free(checked);
	printf("\t %s\n", ret ? "FOUND" : "NOT FOUND");
	return ret;
}

int main() {
	int i = 0, val = 0;
	List* list = NULL, *list2 = NULL;
	srand(time(NULL));
	while (i++ < 45) {
		val = rand() % (300 + 1 - 0) + 0;
		add(&list, val);
		add(&list2, val);
	}
	add(&list, 1); add(&list,2);add(&list,3), add(&list,1); add(&list,4);
	dump(list);
	func1(list);
	return 0;
}
