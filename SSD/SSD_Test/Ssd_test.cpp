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
	device.readSsd(0);
	EXPECT_THAT(device.readResult(), Eq("0x00000000"));
}

TEST_F(SsdVirtualFixture, writeNandDataIndex0) {
	device.writeSsd(0, "0x12345678");
	device.readSsd(0);
	EXPECT_THAT(device.readResult(), Eq("0x12345678"));
}

TEST_F(SsdVirtualFixture, writeNandDataIndex4) {
	device.writeSsd(4, "0xBEEF9090");
	device.readSsd(4);
	EXPECT_THAT(device.readResult(), Eq("0xBEEF9090"));
}