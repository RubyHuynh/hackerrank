#include "../util.h"


/* 02 ways:
 * O(n + 2m) convert to number then convert to linkedlist
 * O(n + m) scan or recursive calls, sum digit by digit and remember carry, oops. recursive cost!
 * */
Node* func1(Node* list1, Node* list2) {
	Node* ret = NULL;
	Node* tmp = NULL;
	int no1 = 0, no2 = 0, sum = 0;
	int i = 0;
	TM_INIT
	TM_START(__func__)
	printf("====%s\n", __func__);
		
	tmp = list1;
	while (tmp) {
		no1 += tmp->val * pow(10,i);
		tmp = tmp->next;
		i++;
	}

	tmp = list2; i = 0;
	while (tmp) {
		no2 += tmp->val * pow(10,i);
		tmp = tmp->next;
		i++;
	}
	sum = no1 + no2;
	printf("\t got %d\n", sum);
	while (sum > 0) {
		add(&ret, sum%10);
		sum/=10;
	}
_done:
	TM_END(__func__)
	dump(ret);
	return ret;
}


Node* func2(Node* list1, Node* list2) {
	Node* ret = NULL;
	int carry = 0, sum = 0, val = 0;
	TM_INIT
	TM_START(__func__)
	printf("====%s\n", __func__);
	
	while (list1 || list2) {
		sum = (list1 ? list1->val : 0) + (list2? list2->val : 0) + carry;
		val = sum % 10;
		carry = sum / 10;
		add(&ret, val);
		printf("\t got %d & carry %d \n", sum, carry);
		list1 = list1 ? list1->next : NULL;
		list2 = list2 ? list2->next : NULL;
	}
_done:
	TM_END(__func__)
	dump(ret);
	return ret;
}


int func3(Node* list1, Node* list2, Node** ret, int carry) {
	int sum = 0, val = 0;
	TM_INIT
	TM_START(__func__)
	printf("====%s\n", __func__);
	
	if (!list1 && !list2) return 0;
	
	sum = (list1 ? list1->val : 0) + (list2 ? list2->val : 0) + carry;
	val = sum % 10;
	carry = sum / 10;
	add(ret, val);
	dump(*ret);
	TM_END(__func__)
	return func3(list1 ? list1->next : NULL, list2 ? list2->next : NULL, ret, carry);
}

int main() {
	int i = 0, val = 0;
	Node* list = NULL, *list2 = NULL;
	add(&list, 3); add(&list, 1); add(&list, 5);
	add(&list2, 5); add(&list2, 9); add(&list2, 2); add(&list2,8);
	dump(list); dump(list2);
	func1(list, list2);
	func2(list, list2);
	{
		Node* ret = NULL;
		int carry = 0;
		TM_INIT
		TM_START("RECURSIVE")
		func3(list, list2, &ret, 0);
		TM_END("RECURSIVE")
	}
	return 0;
}
