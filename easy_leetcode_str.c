
/* 23/05/2022 Monday 17:18-17:56
Runtime: 3 ms, faster than 48.53% of C online submissions for Word Pattern.
Memory Usage: 5.5 MB, less than 95.59% of C online submissions for Word Pattern.
*/
bool wordPattern(char * pattern, char * s) {
    char* maps[26] = {NULL};
    int i = 0, j = 0;
    int len = 0;
    int idx = 0;
    char* token = NULL;
    
    if (!s || !pattern) {
        return false;
    }
    
    len = strlen(pattern);
    token = strtok(s, " ");
    i = 0;
    while (i < len && token) {
        idx = pattern[i]-'a';
        /* CASE 1: ADD */
        if (maps[idx] == NULL) {
            /* CHECK IF THIS TOKEN IS ALREADY ASSIGNED TO A PATTERN CHARACTER */
            j = 0;
            while (j < 26) {
                if (maps[j] && strcmp(maps[j], token) == 0) {
                    return false; /* OCCUPIED */
                }
                ++j;
            }
            maps[idx] = token;
        }
        /* CASE 2: COMPARE */
        else if (strcmp(maps[idx], token) != 0) {
            return false;
        }
        token = strtok(NULL, " ");
        ++i;
    }

    if (i == len && !token) return true;
    return false;

}
