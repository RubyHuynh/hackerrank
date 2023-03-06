#include <iostream>
#include <ostream>
#include "gtest/gtest.h"
using namespace std;
// The function under test
int strStr(string haystack, string needle) {
int szH = haystack.size();
int szN = needle.size();
int j = 0;

if (szH == 0)
return 0;
for (int i = 0; i < szH; i++) {
if (haystack[i] == needle[j]) {
j++;
}
else {
i -= j;
j = 0;
}
if (j == szN) {
return i - j + 1;
}
}
return -1;
}

// The test case class
class StrStrTest : public ::testing::Test {
protected:
// You can define any objects you need here
};

// The first test
TEST_F(StrStrTest, EmptyNeedle) {
// Check if the function returns zero when needle is empty
EXPECT_EQ(0, strStr("hello", ""));
}

// The second test
TEST_F(StrStrTest, NeedleFound) {
// Check if the function returns the correct index when needle is found
EXPECT_EQ(2, strStr("hello", "ll"));
}

// The third test
TEST_F(StrStrTest, NeedleNotFound) {
// Check if the function returns -1 when needle is not found
EXPECT_EQ(-1, strStr("hello", "world"));
}

int main(int argc, char** argv) {
        ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
