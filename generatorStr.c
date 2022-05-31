#include<stdio.h>
#include<stdlib.h>

void generator(int k, int i, char* bits) {
        if (i == k) {
                printf("%s\n", bits);
                return;
        }
        bits[i] = '0';
        generator(k, i+1, bits);
        bits[i] = '1';
        generator(k, i+1, bits);
}

int main() {
        char* str = calloc(1, 10);
  
        printf("===============4\n");
        generator(4, 0, str);

        printf("===============3\n");
        memset(str, 0, 10);
        generator(3, 0, str);

        printf("===============7\n");
        memset(str, 0, 10);
        generator(7, 0, str);
        free(str);
        return 0;
}
