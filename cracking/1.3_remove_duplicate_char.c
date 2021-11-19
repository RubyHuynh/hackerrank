#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<sys/time.h>
#include "../util.h"

/* 02 ways:
 * O(nlogn) 
 * O(n^2) 
 * */
char* func1(char* ss) {
	int i = 0;
	int j = 0;
	int n = strlen(ss);
	char* s = strdup(ss);
	TM_INIT
	TM_START(__func__)
	printf("====%s %s\n", __func__, s);
	while (i < n) {
		j = i + 1;
		while (j < n) {
			if (s[i] == s[j]) {
				memcpy(&s[j], &s[j+1], n - j);
				n--;
				printf("\t\t %d %s\n", i, s);
			}
			else {
				j++;
			}
		}
		printf("\t %d %s\n", i, s);
		i++;
	}
_done:
	TM_STOP(__func__)
	printf("\t%s\n", s);
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
	TM_STOP(__func__)
	printf("\t%s\n", s);
	return s;
}


int main() {
	int i = 0;
	char* arr[] = {"asdfghjklpoiuytrwxbmk","andssdewc", "kdjlkajdawq", "sabd", "a", "djflskfjoiwqewj" };
	while (i < sizeof(arr)/sizeof(arr[i])) {
		printf("\n");
		func1(arr[i]);
		func2(arr[i]);
		i++;
	} 
}
