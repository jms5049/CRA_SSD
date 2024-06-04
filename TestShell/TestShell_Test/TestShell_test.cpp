#pragma once
#include <string>

#include "gmock/gmock.h"
#include "../TestShell/TestShell.cpp"

using namespace testing;
using std::string;

class SsdMock : public SsdApi {
public:
	MOCK_METHOD(int, read, (int lba), (override));
	MOCK_METHOD(void, write, (int lba, string data), (override));
};

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
