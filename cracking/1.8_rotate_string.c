#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<sys/time.h>
#include "../util.h"



/* 02 ways:
 * O(n) with cat string & 1 isSub()
 * O(n) by finding base point & 2 isSub(head) & isSub(tail)
 * */
bool func1(char* ss1, char* ss2) {
	int len1 = strlen(ss1);
	int len2 = strlen(ss2);
	char* s1 = (char*)malloc(len1*2 +1);
	char* s2 = strdup(ss2);
	bool ret = false;
	TM_INIT
	TM_START(__func__)
	printf("====%s <%s> vs <%s>\n", __func__, ss1, s2);
	if (len1 != len2) goto _done;
	sprintf(s1, "%s%s", ss1, ss1);
	if (!strstr(s1, s2)) goto _done;
	ret = true;	
_done:
	TM_STOP(__func__)
	printf("\t %s\n", ret ? "YES" : "NO");
	return ret;
}

bool func2(char* ss1, char* ss2) {
	int len1 = strlen(ss1);
	int len2 = strlen(ss2);
	char* s1 = strdup(ss1);
	char* s2 = strdup(ss2);
	char* tmp = (char*)calloc(1, len1 +1);
	char* start = NULL;
	bool ret = false;
	int i = 0, j = 0;
	TM_INIT
	TM_START(__func__)
	printf("====%s <%s> vs <%s>\n", __func__, ss1, s2);
	if (len1 != len2) goto _done;

	start = strchr(ss2, ss1[0]);
	if (!start) goto _done;
	printf("\tstart = %p len = %d\n", start, strlen(start));
	s2[start-ss2] = '\0';
	if (strstr(ss1,start) && strstr(ss1, s2)) ret = true;
_done:
	TM_STOP(__func__)
	printf("\t %s\n", ret ? "YES" : "NO");
	return ret;
}


int main() {
	int i = 0;
	char* arr[] = {"waterbottle", "erbottlewat", "abcd", "bcda", "abcd", "cbad"};
	while (i < sizeof(arr)/sizeof(arr[i])) {
		printf("\n");
		func1(arr[i], arr[i+1]);
		func2(arr[i], arr[i+1]);
		i+=2;
	} 
}
