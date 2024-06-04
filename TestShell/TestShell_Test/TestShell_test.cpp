#pragma once
#include "../TestShell/TestShell.cpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace testing;

TEST(ShellTest, inputArgsCountException) {
	TestShell* shell = new TestShell();
	string userInput = "write 0x3 0x4 0x5";
	EXPECT_THROW(shell->inputParser(userInput), std::invalid_argument);

	userInput = "write 0x3";
	EXPECT_THROW(shell->inputParser(userInput), std::invalid_argument);

	userInput = "read 0x3 0x4";
	EXPECT_THROW(shell->inputParser(userInput), std::invalid_argument);

	userInput = "read 0x3 0x4 0x5";
	EXPECT_THROW(shell->inputParser(userInput), std::invalid_argument);

	userInput = "exit 0x3";
	EXPECT_THROW(shell->inputParser(userInput), std::invalid_argument);

	userInput = "help 0x3 0x4 0x5";
	EXPECT_THROW(shell->inputParser(userInput), std::invalid_argument);
}

TEST(ShellTest, inputArgTypeException) {
	TestShell* shell = new TestShell();
	string userInput = "write write write";
	EXPECT_THROW(shell->inputParser(userInput), std::invalid_argument);

	userInput = "read read";
	EXPECT_THROW(shell->inputParser(userInput), std::invalid_argument);
}