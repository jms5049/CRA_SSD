#pragma once

#include <string>

#include "../TestShell/TestShell.cpp"
#include "../TestShell/read.cpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;
using std::string;

class SsdMock : public SsdApi {
public:
	MOCK_METHOD(int, read, (int lba), (override));
	MOCK_METHOD(void, write, (int lba, string data), (override));
};

TEST(ReadTest, validinputtest1) {
	string input = "abcd 20";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(ReadTest, validinputtest2) {
	string input = "read  40";
	EXPECT_THROW(printResult(input), std::invalid_argument);
}

TEST(TestShellWrite, WriteSuccess) {
	SsdMock ssd;
	TestShell* app = new TestShell(&ssd);

	EXPECT_CALL(ssd, write(3, "0xAAAABBBB"))
		.Times(1);

	app->write("3 0xAAAABBBB");
}

TEST(TestShellWrite, WriteInputError) {
	SsdMock ssd;
	TestShell* app = new TestShell(&ssd);

	EXPECT_THROW(app->write("1 djf"), InvalidCommandException);
	EXPECT_THROW(app->write("100 0xAAAAAAAA"), InvalidCommandException);
	EXPECT_THROW(app->write("1 AAAAAAAA"), InvalidCommandException);
	EXPECT_THROW(app->write("1 0xeeepppp"), InvalidCommandException);
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
	SsdMock ssd;
	TestShell* app = new TestShell(&ssd);
	app->help("write");
	app->help("");
	//do not need Test for Help function
}

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