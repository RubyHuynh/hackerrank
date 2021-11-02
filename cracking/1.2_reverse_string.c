#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<sys/time.h>
#include "../util.h"

/* 02 ways:
 * O(n) 
 * O(n/2) 
 * */
char* func1(char* ss) {
	int i = 0;
	int len = strlen(ss);
	int mid = len/2;
	char* s = strdup(ss);
	char tmp;
	TM_INIT
	TM_START(__func__)
	printf("====%s %s\n", __func__, s);
	while (i < mid) {
		tmp = s[len - i - 1];
		s[len - i - 1] = s[i];
		s[i] = tmp;
		printf("\t %d %s\n", i, s);
		i++;
	}
_done:
	TM_END(__func__)
	printf("\t%s\n", s);
	return s;
}


char* func2(char* ss) {
	int i = 0;
	int len = strlen(ss);
	int mid = len/2;
	char* s = (char*)malloc(sizeof(char) * (len +1));
	char tmp;
	TM_INIT
	TM_START(__func__)
	printf("====%s %s\n", __func__, s);
	while (i < len) {
		s[i] = ss[len - i - 1];
		printf("\t %d %s\n", i, s);
		i++;
	}
	s[len] = '\0';
_done:
	TM_END(__func__)
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
