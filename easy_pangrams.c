#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

/*
 * Complete the 'pangrams' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 * 24/05/2022 17:05-17:25
 */

char* pangrams(char* s) {
    int i = 0;
    int idx = 0;
    int len = 0;
    int mask = 0;
    char c;
    
    if (!s || (len=strlen(s)) == 0) {
        return "not pangram";
    }
    for (; i < len; i++) {
        idx = -1;
        if (s[i] >= 'A' && s[i] <= 'Z') {
           idx = s[i] - 'A';
        }
        else if (s[i] >= 'a' && s[i] <= 'z') {
            idx = s[i] - 'a';
        }
        
        if (idx >= 0) {
            mask = (mask | (1 << idx));
        }
    }
    return mask == 67108863 ? "pangram" : "not pangram";
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = pangrams(s);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}
