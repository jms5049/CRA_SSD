#pragma once
#include "../TestShell/TestShell.cpp"
#include "../TestShell/read.cpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace testing;
using std::string;

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
	string input = "read $";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(ReadTest, validinputtest6) {
	string input = "read 2*";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(ReadTest, validinputtest7) {
	string input = "read 23";
	EXPECT_THAT(readIndex(input), 23);
}

TEST(ReadTest, validinputtest8) {
	string input = "read 7";
	EXPECT_THAT(readIndex(input), 7);
}

TEST(ReadTest, validinputtest9) {
	string input = "read  4";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(AppTest, Help) {
	TestShell* app = new TestShell();
	app->help("write");
	app->help("");
	//do not need Test for Help function
}

TEST(AppTest, Exit) {
	TestShell* app = new TestShell();
	EXPECT_TRUE(app != nullptr);
	app->exitApp();
	EXPECT_TRUE(app == nullptr);
}