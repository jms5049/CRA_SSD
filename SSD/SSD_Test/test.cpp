#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD/read.cpp"
using namespace testing;

TEST(ReadTest, validinputtest1) {
	string input = "abcd 20";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(ReadTest, validinputtest2) {
	string input = "read  40";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(ReadTest, validinputtest3) {
	string input = "read25";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(ReadTest, validinputtest4) {
	string input = "read !#";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(ReadTest, validinputtest5) {
	string input = "read 23";
	EXPECT_THAT(readIndex(input), 23);
}