#include<iostream>
#include<ostream>
#include<vector>
#include "gtest/gtest.h"

using namespace std;

long long minimumTime(vector<int>& time, int totalTrips) {
	long long left = 1;
	long long right = 1e14;
	while (left <= right) {
		long long mid = left + (right - left) / 2;
		long long taken = 0;

		for (auto it : time) {
			taken += mid/it;
		}
		if (taken < totalTrips) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return left;
}

class Test : public ::testing::Test {
	protected:
};

TEST_F(Test, case1) {
	std::vector<int> a{1, 2, 3};
	EXPECT_EQ(3, minimumTime(a, 5));
}

TEST_F(Test, case2) {
	std::vector<int> a{1, 2, 3};
	EXPECT_EQ(6, minimumTime(a, 9));
}


int main(int argc, char** argv) {
        ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



