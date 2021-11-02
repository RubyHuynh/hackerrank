#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<sys/time.h>
#include "../util.h"

/* 01 ways:
 * O(n) 
 * */
bool func1(char* ss, char* ss1) {
	int i = 0;
	int j = 0;
	int n = strlen(ss);
	int k = strlen(ss1);
	char* s = strdup(ss);
	char* t = strdup(ss1);
	bool ret = false;
	TM_INIT
	TM_START(__func__)
	printf("====%s %s\n", __func__, s);
	if (n != k) goto _done;

	while (i < n) {
		if (s[i] != t[n-i-1]) {
			printf("\t\t %d %c vs %c\n", i, s[i], t[n-i-1]);
			goto _done;
		}
		printf("\t %d %c\n", i, s[i]);
		i++;
	}
	ret = true;
_done:
	TM_END(__func__)
	printf("\t%s\n", ret ? "YES" : "NO");
	return s;
}

int cmp(const void* a, const void* b) {
	return (*(const char*)a) > (*(const char*)b);
}

char* sort(char* a) {
	int n = strlen(a);
	char* rs = strdup(a);
	qsort(rs, n, sizeof(const char), cmp);
	printf("\t after sorted %s\n", rs);
	return rs;
}

char* func2(char* ss) {
	int i = 0;
	int n = strlen(ss);
	char* s = NULL;
	TM_INIT
	TM_START(__func__)
	printf("====%s %s\n", __func__, s);
	s = sort(ss);
	while (i < n) {
		if (s[i] == s[i+1]) {
			memcpy(&s[i+1], &s[i+2], n-i);
			printf("\t\t %d %s", i, s);
			n--;
		}
		i++;
	}
	s[n] = '\0';
_done:
	TM_END(__func__)
	printf("\t%s\n", s);
	return s;
}


int main() {
	int i = 0;
	char* arr[] = {"asdfghjklpoiuytrwxbmk","andssdewc", "kdjlkajdawq", "sabd", "abc", "cba", "abcd", "dcbe", "ee", "djflskfjoiwqewj" };
	while (i < sizeof(arr)/sizeof(arr[i])) {
		printf("\n");
		func1(arr[i], arr[i+1]);
		i+=2;
	} 
}
