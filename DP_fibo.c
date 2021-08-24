/******************************************************************************
Up up up 24/08/2021 :D

*******************************************************************************/

#include <stdio.h>
#include <math.h>

double fibo1(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibo1(n-2) + fibo1(n-1);
}


double fibo2(int n) {
    static double rs[200] = {0};
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    else if (rs[n]) {
        return rs[n];
    }
    else {
        rs[n] = fibo1(n-2) + fibo1(n-1);
        return rs[n];
    }
}



double fibo3(int n) {
    static double rs[200] = {0};
    int i = 2;
    rs[0] = 0;
    rs[1] = 1;
    for (; i <= n ; i++) {
        rs[i] = rs[i-2] + rs[i-1];
    }
    return rs[n];
}


double fibo3up(int n) {
    int i = 2, x2 = 0, x1 = 1, rs = 0;
    
    if (n == 1) {
        return 1;
    }
    for (; i <= n ; i++) {
        rs = x1 + x2;
        x2 = x1;
        x1 = rs;
    }
    return rs;
}

double fibo4(int n) {
  double phi = (1 + sqrt(5)) / 2;
  return round(pow(phi, n) / sqrt(5));
}

int main()
{
    /*printf("Recursive Fibo = %f\n", fibo1(35));*/
    /*Compilation time: 0.27 sec, absolute running time: 0.46 sec, cpu time: 0.18 sec, memory peak: 5 Mb, absolute service time: 0,79 sec
Recursive Fibo = 9227465.000000
    */
    
    /*printf("Memory Fibo = %f\n", fibo2(35));*/
    /*Compilation time: 0.12 sec, absolute running time: 0.19 sec, cpu time: 0.08 sec, memory peak: 5 Mb, absolute service time: 0,46 sec
Memory Fibo = 9227465.000000
    */
    
     /*printf("DP Fibo = %f\n", fibo3(35));*/
    /*Compilation time: 0.14 sec, absolute running time: 0.18 sec, cpu time: 0.01 sec, memory peak: 5 Mb, absolute service time: 0,37 sec
DP Fibo = 9227465.000000
    */
    
     /*printf("DP UP Fibo = %f\n", fibo3up(35));*/
    /*
    Compilation time: 0.12 sec, absolute running time: 0.16 sec, cpu time: 0 sec, memory peak: 5 Mb, absolute service time: 0,35 sec
DP UP Fibo = 9227465.000000
    */
    
    printf("Math Fibo = %f\n", fibo4(35));
    /*Compilation time: 0.22 sec, absolute running time: 0.18 sec, cpu time: 0.01 sec, memory peak: 5 Mb, absolute service time: 0,42 sec
Math Fibo = 9227465.000000
    */
    return 0;
}
