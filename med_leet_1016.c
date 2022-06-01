/*Success
Details 
Runtime: 44 ms, faster than 20.00% of C online submissions for Binary String With Substrings Representing 1 To N.
Memory Usage: 127.7 MB, less than 40.00% of C online submissions for Binary String With Substrings Representing 1 To N.
*/
bool susu(char* s, int n, int i, char* tmp) {
    if (i == n) {
        printf("\t %s vs %s\n", s, tmp);
        if (!strstr(s, tmp)) {
            return false;
        }
        return true;
    }
    tmp[i] = '0';
    if (!susu(s, n, i+1, tmp)) return false;
    tmp[i] = '1';
    return susu(s, n, i+1, tmp);
}

bool queryString(char * s, int n) {
    char* tmp = NULL;
    int len = 0; int i = 0;
    bool rs = false;

    if (!s || (len=strlen(s)) == 0) {
        return false;
    }
    tmp = calloc(1, len);
    for (i = 1; i <= n; i++) {
        rs = susu(s, i, 0, tmp);
        if (!rs) break;
    }
    free(tmp);
    return rs;
}

bool queryString1(char * s, int n) {
    char* tmp = NULL;
    int len = 0;
    bool rs = false;

    if (!s || (len=strlen(s)) == 0) {
        return false;
    }
    tmp = malloc(len);
    rs = susu(s, n, 0, tmp);
    free(tmp);
    return rs;
}

int b2d(char* s, int n) {
    int rs = 0, i = 0;

    for(n; n >= 0; n--, i++) {
        if (s[i] == '1') {
            rs |= (1<< i);
        }
    }
    printf("\t %s(%d)\n", s, rs);
    return rs;
}


bool queryString2(char * s, int n) {
    char* tmp = NULL;
    int len = 0, i = 0, j = 0, val = 0;
    bool rs = false;
    bool arr[n+1];

    printf("working on %s and %d\n", s, n);
    if (!s || (len=strlen(s)) == 0 || n == 0) {
        return false;
    }
    tmp = calloc(1, len + 1);
    memset(arr, 0, sizeof(arr));
    for (i = 0; i < len; i++) {
        memset(tmp, 0, len + 1);
        for (j = i+1; j <= len; j++) {
            strncpy(tmp, &s[i], j-i);
            val = b2d(tmp, j-i);
            if (val >= 1 && val <= n) {
                printf(" >>>>> savinng");
                arr[val] = true;
            }
        }
    }
    for (i = 1; i <= n; i++) {
        printf("working on %i\n", i);
        if (!arr[i]) {
            printf("missing %d\n", i);
            return false;
        }
    }

    free(tmp);
    return true;
}

char* n2s(int n) {
    bool* arr = calloc(1, n*sizeof(bool));
    int i = 0, j = 0;
    char* rs = NULL;
    while (n) {
        if (n%2) {
            arr[i] = true;
        }
        n /= 2;
        i++;
    }
    rs = calloc(1, i+1);
    n = 0;
    for(j = i-1; j >=0; j--) {
        if (arr[j]) {
            rs[n] = '1';
        }
        else {
            rs[n] = '0';
        }
        n++;
    }
    free(arr);
    return rs;
    // int k = n,i = 0, j = 0;
    // char* rs = NULL;
    // while (k >=0) {
    //     i++;
    //     k >>= 1;
    // }
    // rs = calloc(1, i+1);
    // k = 0;
    // while (n >= 0) {
    //     if (n & 1) {
    //         rs[k] = '1';
    //     }
    //     else {
    //         rs[k] = '0';
    //     }
    //     k++;
    //     n >>= 1;
    // }
    // return rs;
}

bool queryString(char* s, int n) {
  while (n > 0) {
    char* sub = n2s(n--);
    if (!strstr(s, sub)) {
        free(sub);
        return false;
    }
      free(sub);
  }
  return true;
}
