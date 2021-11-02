#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<sys/time.h>
#include "../util.h"

/* 01 ways:
 * O(n) time + O(n+k) space 
 * */
char* func1(char* ss) {
	int i = 0;
	int j = 0;
	int n = strlen(ss);
	int cnt = 0;
	char* s = NULL;
	TM_INIT
	TM_START(__func__)
	printf("====%s<%s>\n", __func__, ss);
	while (i < n) {
		if (ss[i] == ' ') {
			++cnt;
		}
		i++;
	}
	s = (char*) malloc(sizeof(char) * (n + cnt*2));
	
	for (i = 0; i < n; i++) {
		if (ss[i] == ' ') {
			s[j++] = '%';
			s[j++] = '2';
			s[j++] = '0';
		}
		else {
			s[j++] = ss[i];
		}
		printf("\t\t %d %s\n", i, s);
	}
	s[j] = '\0';
_done:
	TM_END(__func__)
	printf("\t%s\n", s);
	return s;
}

int main() {
	int i = 0;
	char* arr[] = {"asd fgh   k", "  a n d s s dewc", "sabd", "a", " skfjoiwqewj  " };
	while (i < sizeof(arr)/sizeof(arr[i])) {
		printf("\n");
		func1(arr[i]);
		i++;
	} 
}
