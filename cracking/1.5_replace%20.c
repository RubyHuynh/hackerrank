#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<sys/time.h>
#include "../util.h"

/* 02 ways:
 * O(n) time + O(n+k) space 
 * O(n) time, given that input array already has enough n+k space
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
	TM_STOP(__func__)
	printf("\t%s\n", s);
	return s;
}

char* func2(char* ss) {
	int i = 0;
	int j = 0;
	int n = strlen(ss);
	int cnt = 0;
	TM_INIT
	TM_START(__func__)
	printf("====%s<%s>\n", __func__, ss);
	while (i < n) {
		if (ss[i] == ' ') {
			++cnt;
		}
		i++;
	}
	if (cnt == 0) goto _done;
	cnt = n + cnt*2;
	ss[cnt--] = '\0';
	for (i = n-1; i >=0; i--) {
		if (ss[i] == ' ') {
			ss[cnt--] = '0';
			ss[cnt--] = '2';
			ss[cnt--] = '%';
		}
		else {
			ss[cnt--] = ss[i];
		}
		printf("\t\t %d %s\n", i, ss);
	}
_done:
	TM_STOP(__func__)
	printf("\t%s\n", ss);
	return ss;
}

int main() {
	int i = 0;
	char* arr[] = {"asd fgh   k", "  a n d s s dewc", "sabd", "a", " skfjoiwqewj  " };
	char* tmp;
	while (i < sizeof(arr)/sizeof(arr[i])) {
		printf("\n");
		func1(arr[i]);
		tmp = (char*)malloc(sizeof(char)*100);
		sprintf(tmp, "%s", arr[i]);
		func2(tmp);
		free(tmp);
		i++;
	} 
}
