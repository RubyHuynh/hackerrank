// C++ program to find n'th Ugly number
#include <bits/stdc++.h>
using namespace std;

// Function to get the nth ugly number
unsigned getNthUglyNo(unsigned n)
{
	// To store ugly numbers
	unsigned ugly[n];
	unsigned i2 = 0, i3 = 0, i5 = 0;
	unsigned next_multiple_of_2 = 2;
	unsigned next_multiple_of_3 = 3;
	unsigned next_multiple_of_5 = 5;
	unsigned next_ugly_no = 1;

	ugly[0] = 1;
	for (int i = 1; i < n; i++) {
		next_ugly_no = min(
			next_multiple_of_2,
			min(next_multiple_of_3, next_multiple_of_5));
		ugly[i] = next_ugly_no;
		if (next_ugly_no == next_multiple_of_2) {
			i2 = i2 + 1;
			next_multiple_of_2 = ugly[i2] * 2;
		}
		if (next_ugly_no == next_multiple_of_3) {
			i3 = i3 + 1;
			next_multiple_of_3 = ugly[i3] * 3;
		}
		if (next_ugly_no == next_multiple_of_5) {
			i5 = i5 + 1;
			next_multiple_of_5 = ugly[i5] * 5;
		}
	}

	return next_ugly_no;
}

#include<set>
unsigned setUgly(int n) {
	set<long long int> rs;
	rs.insert(1);
	if (n <= 0)
		return n;
	while (--n) {
		auto it = rs.begin();
		long long int x = *it;
		rs.erase(it);
		rs.insert(x*2);
		rs.insert(x*3);
		rs.insert(x*5);
	}
	cout << " { ";
	for (auto it = rs.begin(); it != rs.end(); it++) {
		cout << *it << ", ";
	}
	cout << " }";
	return *rs.begin();
}

// Driver Code
int main()
{
	int n = 150;
	for (int i = 0; i < n +1; i++) {
		cout << getNthUglyNo(i);
		cout << "\t" << setUgly(i);
	        cout << "\n";
    	}
	return 0;
}
