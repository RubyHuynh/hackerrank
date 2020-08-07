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
