#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD/read.cpp"
using namespace testing;

TEST(ReadTest, validinputtest1) {
	string input = "A 20";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(ReadTest, validinputtest2) {
	string input = "RR  40";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(ReadTest, validinputtest3) {
	string input = "R40";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(ReadTest, validinputtest4) {
	string input = "R !#";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(ReadTest, validinputtest5) {
	string input = "R 23";
	EXPECT_THAT(readIndex(input), 23);
}