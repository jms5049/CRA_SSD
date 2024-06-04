#pragma once

#include <string>

#include "../TestShell/TestShell.cpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;
using std::string;

class SsdMock : public SsdApi {
public:
	MOCK_METHOD(int, read, (int lba), (override));
	MOCK_METHOD(void, write, (int lba, string data), (override));
};

class SsdMockRead : public SsdApi {
public:
	MOCK_METHOD(int, read, (int idx), (override));
	MOCK_METHOD(void, write, (int idx, string input), (override));
};


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

TEST(TestShellRead, ReadSuccess) {
	SsdMockRead ssd;
	TestShell* app = new TestShell(&ssd);

	EXPECT_CALL(ssd, read(23))
		.Times(1);

	app->read("read 23");
}

TEST(TestShellRead, ReadInputError) {
	SsdMockRead ssd;
	TestShell* app = new TestShell(&ssd);

	EXPECT_THROW(app->read("abcd 20"), std::invalid_argument);
	EXPECT_THROW(app->read("read  40"), std::invalid_argument);
	EXPECT_THROW(app->read("read25"), std::invalid_argument);
	EXPECT_THROW(app->read("read !#"), std::invalid_argument);
	EXPECT_THROW(app->read("read $"), std::invalid_argument);
	EXPECT_THROW(app->read("read 2*"), std::invalid_argument);
	EXPECT_THROW(app->read("read  4"), std::invalid_argument);
}

TEST(AppTest, Help) {
	SsdMock ssd;
	TestShell* app = new TestShell(&ssd);
	app->help("write");
	app->help("");
	//do not need Test for Help function
}

TEST(AppTest, Exit) {
	SsdMock ssd;
	TestShell* app = new TestShell(&ssd);
	EXPECT_TRUE(app != nullptr);
	app->exitApp();
	EXPECT_TRUE(app == nullptr);
}