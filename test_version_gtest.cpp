#include "lib.h"

#include <gtest/gtest.h>

TEST(Google_test, test_version) {
	EXPECT_GT(version(), 0);
}