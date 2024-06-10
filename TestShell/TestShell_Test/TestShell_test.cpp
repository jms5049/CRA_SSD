#pragma once

#include <string>

#include "../TestShell/TestShell.cpp"
#include "../TestShell/Ssd.cpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;
using std::string;

class SsdMock : public ssdApi {
public:
	MOCK_METHOD(string, read, (int lba), (override));
	MOCK_METHOD(void, write, (int lba, string data), (override));
};

class SsdTestShellFixture : public Test {
public:
	Ssd ssd;
	TestShell* app = new TestShell(&ssd);

	void TearDown() {
		app->fullWrite("0x00000000");
	}
};

class TestShellFixture : public Test {
public:
	SsdMock ssd;
	TestShell* app = new TestShell(&ssd);
};

TEST_F(SsdTestShellFixture, readwriteSuccess) {
	std::cout << "test\n";
	app->write("3", "0xAAAABBBB");
	app->read("3");
}

TEST_F(SsdTestShellFixture, fullReadWriteSuccess) {
	app->fullWrite("0xFFFFFFFF");
	app->fullRead();
}

TEST_F(TestShellFixture, WriteSuccess) {
	EXPECT_CALL(ssd, write(3, "0xAAAABBBB"))
		.Times(1);

	app->write("3", "0xAAAABBBB");
}

TEST_F(TestShellFixture, WriteInputError) {
	EXPECT_THROW(app->write("1", "djf"), std::exception);
	EXPECT_THROW(app->write("100","0xAAAAAAAA"), std::exception);
	EXPECT_THROW(app->write("1", "AAAAAAAA"), std::exception);
	EXPECT_THROW(app->write("1", "0xeeepppp"), std::exception);
}

TEST_F(TestShellFixture, FullWriteSuccess) {
	EXPECT_CALL(ssd, write(_, "0xAAAABBBB"))
		.Times(100);

	app->fullWrite("0xAAAABBBB");
}

TEST_F(TestShellFixture, FullWriteInputError) {
	EXPECT_THROW(app->fullWrite("1 0xAAAAA"), std::exception);
	EXPECT_THROW(app->fullWrite("AA"), std::exception);
	EXPECT_THROW(app->fullWrite("0xB"), std::exception);
	EXPECT_THROW(app->fullWrite("adtt"), std::exception);
}

TEST_F(TestShellFixture, ReadSuccess) {
	EXPECT_CALL(ssd, read(_))
		.Times(2);

	app->read("23");
	app->read("2");
}

TEST_F(TestShellFixture, ReadInputError) {
	EXPECT_THROW(app->read("a20"), std::exception);
	EXPECT_THROW(app->read("-1"), std::exception);
	EXPECT_THROW(app->read("!#"), std::exception);
	EXPECT_THROW(app->read("2$"), std::exception);
}

TEST_F(TestShellFixture, fullReadSuccess) {
	for (int i = 0; i < 100; i++) {
		EXPECT_CALL(ssd, read(i))
			.Times(1);
	}

	app->fullRead();
}

TEST_F(TestShellFixture, inputArgsCountException) {
	EXPECT_THROW(app->inputParser("write 0x3 0x4 0x5"), std::exception);
	EXPECT_THROW(app->inputParser("write 0x3"), std::exception);
	EXPECT_THROW(app->inputParser("read 0x3 0x4"), std::exception);
	EXPECT_THROW(app->inputParser("read 0x3 0x4 0x5"), std::exception);
	EXPECT_THROW(app->inputParser("exit 0x3"), std::exception);
	EXPECT_THROW(app->inputParser("help 0x3 0x4 0x5"), std::exception);
	EXPECT_THROW(app->inputParser("fullwrite 0x3 0x4"), std::exception);
	EXPECT_THROW(app->inputParser("fullread 0x3 0x4"), std::exception);
}

TEST_F(TestShellFixture, inputArgTypeException) {
	EXPECT_THROW(app->inputParser("write write write write"), std::exception);
	EXPECT_THROW(app->inputParser("read read read"), std::exception);
}

TEST_F(TestShellFixture, HelpSuccess) {
	EXPECT_NO_THROW(app->inputParser("help write"));
	EXPECT_NO_THROW(app->help("write"));
	EXPECT_NO_THROW(app->help("read"));
	EXPECT_NO_THROW(app->help("exit"));
	EXPECT_NO_THROW(app->help("fullwrite"));
	EXPECT_NO_THROW(app->help("fullread"));
	EXPECT_NO_THROW(app->help(""));
}

TEST_F(TestShellFixture, ExitSuccess) {
	EXPECT_NO_THROW(app->inputParser("exit"));
}