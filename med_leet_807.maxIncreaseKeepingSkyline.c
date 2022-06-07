/*
Success
Details 
Runtime: 11 ms, faster than 54.29% of C online submissions for Max Increase to Keep City Skyline.
Memory Usage: 6.2 MB, less than 14.29% of C online submissions for Max Increase to Keep City Skyline.
*/

int max(int a, int b) {
    return a > b ? a : b; 
}
int min(int a, int b) {
    return a < b ? a : b; 
}
int maxIncreaseKeepingSkyline(int** grid, int n, int* gridColSize){
    int i,j, k, rs = 0;
    int* rows, * cols;
    
    if (!grid || n == 0) {
        return 0;
    }
    rows = calloc(1, sizeof(int)*n);
    cols = calloc(1, sizeof(int)*n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            rows[i] = max(rows[i], grid[i][j]);
            cols[j] = max(cols[j], grid[i][j]);
        }
    }
        
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            rs += min(rows[i], cols[j]) - grid[i][j];
        }
    }
    return rs;   
}
