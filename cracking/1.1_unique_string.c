#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "../util.h"

/* 03 ways:
 * O(n) if marking bit, ensure that idx is u
 * O(n^2) if comparing character by character
 * O(nLogn) is sorting the string then compare neighboring, but may allocate extra space
 * */
bool is_unique(char* s) {
	int i = 0;
	int total = 0;
	int len = strlen(s);
	int idx = 0;
	bool ret = false;
	printf("====%s %s\n", __func__, s);
	TM_INIT
	TM_START(__func__)
	while (i < len) {
		idx = s[i] - 'a';
		printf("\t idx = %d (%c)\n", idx, s[i]);
		if (total & (1 << idx)) {
			printf("\tNOPE total=%d %c\n", total, s[i]);
			goto _done;
		}
		total |= 1 << idx;
		i++;
	}
	ret = true;
	printf("\tYES total=%d\n", total);
_done:
	TM_END(__func__)
	return ret;
}

static int myCompare(const void* a, const void* b) {
	return (*(const char*)a) > (*(const char*)b);
}
  
char* sort(char* a) {
	char* rs = strdup(a);
	int i = 0;
	int len = strlen(rs);
	qsort(rs, len, sizeof(const char), myCompare);
	printf("\tafter sorted: %s\n", rs);
	return rs;
}

bool is_unique1(char* s) {
	int i = 0;
	int len = strlen(s);
	char* tmp = NULL;
	bool ret = false;

	printf("=====%s %s\n", __func__, s);
	TM_INIT
	TM_START(__func__)
	tmp = sort(s);
	TM_END(__func__)
	TM_START(__func__)
	while (i < len) {
		if (tmp[i] == tmp[i-1]) {
			printf("\tNOPE %c\n", s[i]);
			goto _done;
		}
		i++;
	}
	ret = true;
_done:
	free(tmp);
	printf("\tYES\n");
	TM_END(__func__)
	return ret;
}



int main() {
	int i = 0;
	char* arr[] = {"asdfghjklpoiuytrwxbmk","andssdewc", "kdjlkajdawq", "sabd", "a", "djflskfjoiwqewj" };
	while (i < sizeof(arr)/sizeof(arr[i])) {
		printf("\n");
		is_unique(arr[i]);
		is_unique1(arr[i]);
		i++;
	} 
}
