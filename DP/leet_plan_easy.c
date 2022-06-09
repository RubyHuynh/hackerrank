
/*
Success
Details 
Runtime: 55 ms, faster than 58.19% of C online submissions for Counting Bits.
Memory Usage: 10.6 MB, less than 35.92% of C online submissions for Counting Bits.
Next challenges:
*

/**
 * Note: The returned array must be malloced, assume caller calls free().
 https://www.techiedelight.com/brian-kernighans-algorithm-count-set-bits-integer 
 */
int* countBits(int n, int* returnSize) {
    int i = 0;
    int* rs = malloc((n + 1)* sizeof(int));
    
    rs[0] = 0;
    for(i = 1; i <= n; ++i) {
        rs[i] = rs[i&i-1] + 1;
    }
 
    /* or */
    /* for(int i = 1; i<=n; ++i)
            t[i] = t[i/2] + i%2;
    */
    *returnSize = n+1;
    return rs;
}
