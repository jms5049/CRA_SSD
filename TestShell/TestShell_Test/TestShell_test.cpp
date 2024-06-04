#pragma once
#include <string>

#include "gmock/gmock.h"
#include "../TestShell/TestShell.cpp"

using std::string;

class SsdMock : public SsdApi {
public:
	MOCK_METHOD(int, read, (int lba), (override));
	MOCK_METHOD(void, write, (int lba, int data), (override));
};

TEST(TestShellWrite, WriteSuccess) {
	SsdMock ssd;
	TestShell testShell(&ssd);
	
	EXPECT_CALL(ssd, write(3, 0xAAAABBBB))
		.Times(1);

	testShell.write("3 0xAAAABBBB");
}

TEST(TestShellWrite, WriteInputError) {
	SsdMock ssd;
	TestShell testShell(&ssd);

	EXPECT_THROW(testShell.write("1 djf"), InvalidCommandException);
	EXPECT_THROW(testShell.write("100 0xAAAAAAAA"), InvalidCommandException);
	EXPECT_THROW(testShell.write("1 AAAAAAAA"), InvalidCommandException);
	EXPECT_THROW(testShell.write("1 AAAAAAAA"), InvalidCommandException);
}
