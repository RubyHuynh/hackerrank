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

class StrStrTest : public ::testing::Test {
	protected:
};

TEST_F(StrStrTest, EmptyNeedle) {
	EXPECT_EQ(-1, strStr("hello", ""));
}

TEST_F(StrStrTest, NeedleNotFoundd) {
	EXPECT_EQ(-1, strStr("hello", "helloooo"));
}

TEST_F(StrStrTest, NeedleNotFound) {
	EXPECT_EQ(-1, strStr("hello", "world"));
}

TEST_F(StrStrTest, NeedleFound) {
	EXPECT_EQ(5, strStr("helloworld", "world"));
}

int main(int argc, char** argv) {
        ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
