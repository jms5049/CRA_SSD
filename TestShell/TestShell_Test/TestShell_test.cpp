#pragma once

#include <string>

#include "../TestShell/TestShell.cpp"
#include "../TestShell/Ssd.cpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;
using std::string;

class SsdMock : public SsdApi {
public:
	MOCK_METHOD(int, read, (int lba), (override));
	MOCK_METHOD(void, write, (int lba, string data), (override));
};

class TestShellFixture : public Test {
public:
	SsdMock ssd;
	TestShell* app = new TestShell(&ssd);
};

TEST_F(TestShellFixture, WriteSuccess) {
	EXPECT_CALL(ssd, write(3, "0xAAAABBBB"))
		.Times(1);

	app->write("3 0xAAAABBBB");
}

TEST_F(TestShellFixture, WriteInputError) {
	EXPECT_THROW(app->write("1 djf"), InvalidCommandException);
	EXPECT_THROW(app->write("100 0xAAAAAAAA"), InvalidCommandException);
	EXPECT_THROW(app->write("1 AAAAAAAA"), InvalidCommandException);
	EXPECT_THROW(app->write("1 0xeeepppp"), InvalidCommandException);
}

TEST_F(TestShellFixture, FullWriteSuccess) {
	EXPECT_CALL(ssd, write(_, "0xAAAABBBB"))
		.Times(100);

	app->fullWrite("0xAAAABBBB");
}

TEST_F(TestShellFixture, FullWriteInputError) {
	EXPECT_THROW(app->fullWrite("1 0xAAAAA"), InvalidCommandException);
	EXPECT_THROW(app->fullWrite("AA"), InvalidCommandException);
	EXPECT_THROW(app->fullWrite("0xB"), InvalidCommandException);
	EXPECT_THROW(app->fullWrite("adtt"), InvalidCommandException);
}

TEST_F(TestShellFixture, ReadSuccess) {
	EXPECT_CALL(ssd, read(23))
		.Times(1);

	app->read("read 23");
}

TEST_F(TestShellFixture, ReadInputError) {
	EXPECT_THROW(app->read("abcd 20"), std::invalid_argument);
	EXPECT_THROW(app->read("read  40"), std::invalid_argument);
	EXPECT_THROW(app->read("read25"), std::invalid_argument);
	EXPECT_THROW(app->read("read !#"), std::invalid_argument);
	EXPECT_THROW(app->read("read $"), std::invalid_argument);
	EXPECT_THROW(app->read("read 2*"), std::invalid_argument);
	EXPECT_THROW(app->read("read  4"), std::invalid_argument);
}

TEST_F(TestShellFixture, fullReadSuccess) {
	for (int i = 0; i < 100; i++) {
		EXPECT_CALL(ssd, read(i))
			.Times(1);
	}

	app->fullRead();
}

TEST_F(TestShellFixture, Help) {
	app->help("write");
	app->help("");
	//do not need Test for Help function
}

TEST_F(TestShellFixture, inputArgsCountException) {
	string userInput = "write 0x3 0x4 0x5";
	EXPECT_THROW(app->inputParser(userInput), std::invalid_argument);

	userInput = "write 0x3";
	EXPECT_THROW(app->inputParser(userInput), std::invalid_argument);

	userInput = "read 0x3 0x4";
	EXPECT_THROW(app->inputParser(userInput), std::invalid_argument);

	userInput = "read 0x3 0x4 0x5";
	EXPECT_THROW(app->inputParser(userInput), std::invalid_argument);

	userInput = "exit 0x3";
	EXPECT_THROW(app->inputParser(userInput), std::invalid_argument);

	userInput = "help 0x3 0x4 0x5";
	EXPECT_THROW(app->inputParser(userInput), std::invalid_argument);
}

TEST_F(TestShellFixture, inputArgTypeException) {
	string userInput = "write write write";
	EXPECT_THROW(app->inputParser(userInput), std::invalid_argument);

	userInput = "read read";
	EXPECT_THROW(app->inputParser(userInput), std::invalid_argument);
}