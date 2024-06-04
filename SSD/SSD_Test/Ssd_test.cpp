#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD/Ssd.cpp"
using namespace testing;

class SsdVirtualFixture : public Test {
protected:
	void TearDown() override {
		device.initializeResourceFile();
	}
public:
	Ssd device;
};

TEST_F(SsdVirtualFixture, readNandDataIndex0) {
	EXPECT_THAT(device.readSsd(0), StartsWith("0x00000000"));
}

TEST_F(SsdVirtualFixture, writeNandDataIndex0) {
	device.writeSsd(0, "0x12345678");
	EXPECT_THAT(device.readSsd(0), Eq("0x12345678"));
}

TEST_F(SsdVirtualFixture, writeNandDataIndex4) {
	device.writeSsd(4, "0xBEEF9090");
	EXPECT_THAT(device.readSsd(4), Eq("0xBEEF9090"));
}