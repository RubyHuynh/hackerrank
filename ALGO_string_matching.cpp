/******************************************************************************
 12/09/2021

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <ostream>


int robinKarp(std::string& name, std::string& patt) {
    if (name.size() == 0 || patt.size() == 0) {
        return -1;
    }
    
    int i = 0, j = 0, powm = 1, prime = 101;
    int pattHash =0, nameHash = 0;
    int n = name.size();
    int m = patt.size();
    printf("\n%s %s(%d) vs %s(%d)\n", __func__, name.c_str(), n, patt.c_str(), m);
    
    for (i = 0; i < m - 1; i++) {
        powm = (powm << 1) % prime;
    }
    
    for (i = 0; i < m; i++) {
        pattHash = ((pattHash << 1) + patt.at(i)) % prime;
        nameHash = ((nameHash << 1) + name.at(i)) % prime;
    }
    
    for (i = 0; i <= n - m ; i++) {
        printf("\tstart at %s...\n", name.substr(i).c_str());
        if (nameHash == pattHash) {
            for (j = 0; j < m; j++) {
                printf("\t\tcomparing %c == %c?\n"
                    , name.at(i+j), patt.at(j));
                if (name.at(i+j) != patt.at(j)) {
                    printf("\t\t\t not match\n");
                    break;
                }
            }
            
            if (j == m) {
                printf("\nFinished\n");
                return i;
            }
        }
        nameHash = (((nameHash - name.at(i)*powm)<< 1) 
                    + name.at(i+m)) %prime;
        if (nameHash < 0) {
            nameHash = (nameHash + prime);
        }
    }
    return 0;
}



/**
 * - Worst case Time Complexity of the algorithm is O(m*n), 
 * we got the pattern at the end of the text or we didn’t get the pattern at all.
 * - Best case Time Complexity of this algorithm is O(m)
 * - The average Time Complexity of this algorithm is O(n)
 */
int bruceForceSearch(std::string& name, std::string& patt) {
    if (name.size() == 0 || patt.size() == 0) {
        return -1;
    }
    
    int i = 0, j = 0;
    int n = name.size();
    int m = patt.size();
    printf("\n%s %s(%d) vs %s(%d)\n", __func__, name.c_str(), n, patt.c_str(), m);
    while (i <= n-m) {
        printf("\tstart at %s...\n", name.substr(i).c_str());
        j = 0;
        while (j < m && name.at(i+j) == patt.at(j)) {
            printf("\t\tcomparing %c == %c?\n", name.at(i+j), patt.at(j));
            j++;
        }
        if (j == m) {
            printf("\nFinished\n");
            return i;
        }
        i++;
    }
    return 0;
}

int main()
{
    printf("MATCHING STRINGS\n");
    std::string name{"Nakiri Alice"};
    std::string patt{"lice"};
    printf("RS=%d\n", bruceForceSearch(name, patt));
    
    printf("RS=%d\n", robinKarp(name, patt));
    return 0;
}
/*
MATCHING STRINGS

bruceForceSearch Nakiri Alice(12) vs lice(4)
        start at Nakiri Alice...
        start at akiri Alice...
        start at kiri Alice...
        start at iri Alice...
        start at ri Alice...
        start at i Alice...
        start at  Alice...
        start at Alice...
        start at lice...
                comparing l == l?
                comparing i == i?
                comparing c == c?
                comparing e == e?

Finished
RS=8

robinKarp Nakiri Alice(12) vs lice(4)
        start at Nakiri Alice...
        start at akiri Alice...
        start at kiri Alice...
        start at iri Alice...
        start at ri Alice...
        start at i Alice...
        start at  Alice...
        start at Alice...
        start at lice...
                comparing l == l?
                comparing i == i?
                comparing c == c?
                comparing e == e?

Finished
RS=8
*/
