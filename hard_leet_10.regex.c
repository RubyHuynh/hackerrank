#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


bool matchFirst(const char *s, const char *p){
	printf ("\t%s p=%c c=%c\n", __func__, *p, *s);
        return (*p == *s || (*p == '.' && *s != '\0'));
    }

bool isMatch(char *s, char *p) {
	printf ("%s p=%c c=%c\n", __func__, *p, *s);
	if (*p == '\0') return *s == '\0';	//empty

	if (*(p + 1) != '*') {//without *
		if(!matchFirst(s,p)) return false;
		return isMatch(s + 1, p + 1);
	} else { //next: with a *
	    	if(isMatch(s, p + 2)) return true;    //try the length of 0
		while ( matchFirst(s,p) )       //try all possible lengths 
			if (isMatch(++s, p + 2)) return true;
	}
	printf("%s failed\n", __func__);
    return false;
}

/*
bool isMatch(char * s, char * p){
    int len = 0, len1 = 0;
    int i=0, j =0, matched = 0;
    bool enable = false;
	printf("=======\n%s %s\n", s, p);
    if (!s || !p || (len=strlen(s)) == 0 || (len1=strlen(p)) == 0 ) {
        return false;
    }
    
    for (i = 0; i < len1 && j < len; i++, j++) {
	printf("i=%d, j=%d\n", i, j);
        if (i < len1 -1 && p[i+1] == '*') {
            if (s[j] == p[i] || p[i] == '.') {
                matched++;
                enable = true;
            }
            else {
                enable = false;
		--j;
            }
        }
        else if (p[i] == '*') {
            if (enable) {
                if (s[j] == p[i-1] || p[i-1] == '.') {
                    ++matched;
                    --i;
                }
                else {
                    enable = false;
                    --j;
                }
            }
            else {
                --j;
            }
        }
        else if (p[i] == '.') {
            ++matched;
        }
        else {
            if (s[j] == p[i]) {
                ++matched;
            }
            else {
                return false;
            }
        }
	printf("\t matched = %d\n", matched);
    }
	printf("rs = %d vs %d\n", matched, len);
    return matched == len ? true : false;
}
*/
int main() {
	isMatch("ab", ".*c");	
	isMatch("aab", "c*a*b*");	
	isMatch("aa", ".*");	
	return 0;
}
