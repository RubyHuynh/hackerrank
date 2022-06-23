class Solution {
public:
    /*
    Reverse an Integer
 n	n != 0	reverse
2345	true	0 * 10 + 5 = 5
234	true	5 * 10 + 4 = 54
23	true	54 * 10 + 3 = 543
2	true	543 * 10 + 2 = 5432
    */
    int reverse(int x) {
         if (x == INT_MIN)
            return 0;
        if (x < 0)
            return -reverse(-x);
        
        int rx = 0; // store reversed integer
        while (x != 0) {
            // check overflow
            if (rx > INT_MAX / 10 || 10 * rx > INT_MAX - x % 10) return 0;
            rx = rx * 10 + x % 10;
            x = x / 10;
        }
        return rx;
        
    }
};
