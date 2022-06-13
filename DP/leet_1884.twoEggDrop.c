//Egg Drop With 2 Eggs and N Floors

// int twoEggDrop(int n)
// {
// 	vector m{0};
// 	for(auto i{1}; i<=n; ++i) 
// 	{
// 		int out{INT_MAX};
// 		for(auto j{1}; j<=i; ++j)              
// 			out = min(out, 1+max(m[i-j], j-1));
// 		m.push_back(out);
// 	}
// 	return m.back();    
// }
// If you change variables j=i-j you can get arguably simpler formula

// int twoEggDrop(int n)
// {
// 	vector m{0};
// 	for(auto i{1}; i<=n; ++i) 
// 	{
// 		int out{INT_MAX};
// 		for(auto j{0}; j<i; ++j)              
// 			out = min(out, 1+max(m[j], i-j-1));  
// 		m.push_back(out);
// 	}
// 	return m.back();    
// }

// int twoEggDrop(int n)
// {
//     int i = 0;
// 	int out = 0;
// 	for(i; n--; ++i>out ? out=i, i=1 : 0);           
// 	return out;    
// }
// or maybe like this

// int twoEggDrop(int n)
// {
// 	auto out{0};
// 	for(auto i{0}; n; --n)
// 		if(++i>out) out=i, i=1;
// 	return out;    
// }
// Solution 3
// time O(1); space O(1)

// Using some math magic you can come up with the formula to solve the problem in O(1).
// The key is to derive integer inverse function of the triangular numbers trinv(n) and to shift it by 1.


// image

int twoEggDrop(int n)
{
	return (1+sqrt(8.0*n-7))/2;    
}
// also you can use this formula

// int twoEggDrop(int n)
// {
// 	return floor(sqrt(2.0*n) + 0.5);    
// }
