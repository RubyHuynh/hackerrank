# Here is the formal mathematical definition of Big O.

    Let T(n) and f(n) be two positive functions. We write T(n) ∊ O(f(n)), and say that T(n) has order of f(n), if there are positive constants M and n₀ such that T(n) ≤ M·f(n) for all n ≥ n₀. 

In essence:

    T(n) ∊ O(f(n)) means that T(n) doesn't grow faster than f(n). 


# Key takeaways

When analyzing algorithms you often come across the following time complexities.
Complexity 	
Θ(1) 	Good news Constant time
Θ(log n) 	
Θ(n) 	Linear time
Θ(n log n) 	

Θ(n^k), where k ≥ 2 	Bad news Quadratic time
Θ(k^n), where k ≥ 2 	
Θ(n!) 	
O(n log n) is really good

```
▪ A logarithmic algorithm – O(logn)
Runtime grows logarithmically in proportion to n.
▪ A linear algorithm – O(n)
Runtime grows directly in proportion to n.
▪ A superlinear algorithm – O(nlogn)
Runtime grows in proportion to n.
▪ A polynomial algorithm – O(nc)
Runtime grows quicker than previous all based on n.
▪ A exponential algorithm – O(cn)
Runtime grows even faster than polynomial algorithm based on n.
▪ A factorial algorithm – O(n!)
Runtime grows the fastest and becomes quickly unusable for even
small values of n. 
```
## The first four complexities indicate an excellent algorithm. An algorithm with worst-case time complexity W(n) ∊ O(n log n) scales very well, since logarithms grow very slowly.

        log2 1,000 ≈ 10
        log2 1,000,000 ≈ 20
        log2 1,000,000,000 ≈ 30
In fact, Θ(n log n) time complexity is very close to linear – it takes roughly twice the time to solve a problem twice as big.

Ω(n2) is pretty bad

## The last three complexities typically spell trouble. Algorithms with time complexity Ω(n2) are useful only for small input: n shouldn’t be more than a few thousand.

    10,0002 = 100,000,000

An algorithm with quadratic time complexity scales poorly – if you increase the input size by a factor 10, the time increases by a factor 100.

# Ω and Θ notation

Big Omega is used to give a lower bound for the growth of a function. It’s defined in the same way as Big O, but with the inequality sign turned around:

    Let T(n) and f(n) be two positive functions. We write T(n) ∊ Ω(f(n)), and say that T(n) is big omega of f(n), if there are positive constants m and n₀ such that T(n) ≥ m(f(n)) for all n ≥ n₀. 

Big Theta is used to indicate that a function is bounded both from above and below.

    T(n) ∊ Θ(f(n)) if T(n) is both O(f(n)) and Ω(f(n)). 

Example

T(n) = 3n3 + 2n + 7 ∊ Θ(n3)

    If n ≥ 1, then T(n) = 3n3 + 2n + 7 ≤ 3n3 + 2n3 + 7n3 = 12n3. Hence T(n) ∊ O(n3).
    On the other hand, T(n) = 3n3 + 2n + 7 > n3 for all positive n. Therefore T(n) ∊ Ω(n3).
    And consequently T(n) ∊ Θ(n3).
    
# Algorithmic Examples of Runtime Analysis:
```
Logarithmic algorithm – O(logn) – Binary Search.
▪ Linear algorithm – O(n) – Linear Search.
▪ Superlinear algorithm – O(nlogn) – Heap Sort, Merge Sort.
▪ Polynomial algorithm – O(n^c) – Strassen’s Matrix Multiplication, Bubble Sort, Selection Sort, Insertion Sort, Bucket Sort.
▪ Exponential algorithm – O(c^n) – Tower of Hanoi.
▪ Factorial algorithm – O(n!) – Determinant Expansion by Minors, Brute force Search algorithm for Traveling Salesman Problem. 
```
```
Ideal algorithm - O(1) - Linear Search, Binary Search,
    Bubble Sort, Selection Sort, Insertion Sort, Heap Sort, Shell Sort.
▪ Logarithmic algorithm - O(log n) - Merge Sort.
▪ Linear algorithm - O(n) - Quick Sort.
▪ Sub-linear algorithm - O(n+k) - Radix Sort.
```
## Math
```
If n = 10,                  If n=20,
    log(10) = 1;                log(20) = 2.996;
    10 = 10;                    20 = 20;
    10log(10)=10;               20log(20)=59.9;
    102=100;                    202=400;
    210=1024;                    220=1048576;
    10!=3628800;                20!=2.432902e+1818;
```

# Sample
```
int g(int k) {
  int i=0;

  while(k>0) {
    i += k;
    k= k/2;
  }

  return i;
}

int f(int n) {
  int m = 0;

  for (int i=0; i<n; ++i) {
    for (int j=i; j<n; ++j) {
      m += g(j);
    }
  }

  return m;
}
```
As, the function g's complexity depends on the parameter k (logarithmic), you have to consider it while calling it from function f. In case, if g's worst case operation has constant time complexity, then you may not need to consider it explicitly.

In this case, f's complexity is O(n2) & g's complexity is O(lg(n)), yielding an overall complexity of O(n2lg(n))


# multi loops
Nested loops means that the outer loop will execute the inner one completely for each iteration (of the outer). This means O(n^2) in your case, because for each i from 0 to n we do n operations.
```
i = 0 => inner loop runs n iterations
i = 1 => inner loop runs n iterations
...
i = n - 1 => inner loop runs n iterations
```
n iterations n times means n^2 total iterations, so O(n^2).

2 loops without nesting will each iterate n times, for a total of 2n times. Big-oh ignores constants, so 2n = O(n).

Since they are not nested, the number of times each one runs will not depend on the other. So you add the number of iterations, not multiply them.

A nested loop followed by a non-nested loop
= O(max(O(n), O(n^2)))
