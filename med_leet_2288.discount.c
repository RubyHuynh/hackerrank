#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
Success
Details 
Runtime: 449 ms, faster than 6.67% of C online submissions for Apply Discount to Prices.
Memory Usage: 24.4 MB, less than 6.67% of C online submissions for Apply Discount to Prices.
*/

char * discountPrices(char * sentence, int discount){
    char* tmp = NULL, *tmp1 = NULL;
    char* tok;
    char** arr = NULL;
    int len = 0, i = 0, j=0, tokLen;
    char valStr[15];
    if (!sentence || (len = strlen(sentence)) == 0) {
        return NULL;
    }
    
    tmp1 = strdup(sentence);
    arr = calloc(1, sizeof(char*) * len);
    len = 1;
    tmp = tmp1;
    tok = strtok(tmp, " ");
    while (tok) {
        //
        j = -1;
        tokLen = strlen(tok);
        if (tok[0] == '$') {
            for (j = 1; j < tokLen; j++) {
                if (tok[j] >= '0' && tok[j] <= '9') {
                    continue;
                }
                else {
                    break;
                }
            }
        }
        //
        if (tokLen > 1 && j == tokLen) {
            memset(valStr, 0, sizeof(valStr));
            sprintf(valStr, "%s", &tok[1]);
            double val = atof(valStr);
            double real = val - (val * discount/100.);
            sprintf(valStr, "$%.2f", (real));
            arr[i] = strdup(valStr);
        }
        else {
            arr[i] = strdup(tok);
        }
        //
        len += strlen(arr[i]);
        ++i;
        tok = strtok(NULL, " ");
    }
    char *rs = calloc(1, len + i - 1);
    for (j = 0; j < i; j++) {
        strcat(rs, arr[j]);
        if (j != i -1) strcat(rs, " ");
        free(arr[j]);
    }
    
    free(tmp1);
    return rs;
}

int main() {
	char* str1 = "All we havefor this season $1 socks, $20 pancake";
	discountPrices(str1, 50);
	discountPrices(str1, 70);
	discountPrices("$7383692 5q $5870426", 64);
	return 0;
}
