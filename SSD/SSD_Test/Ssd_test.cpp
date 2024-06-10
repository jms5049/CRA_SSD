#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD/Ssd.cpp"
#include "../SSD/Buffer.cpp"
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

TEST_F(SsdVirtualFixture, errorMessage) {
	EXPECT_THAT(device.getErrorMessage(), StrEq("Nand file open error!"));
}

TEST_F(SsdVirtualFixture, eraseIgnore1) {
	device.writeSsd(0, "0xBEEF9090");
	device.eraseSsd(0, 0);
	device.readSsd(0);
	EXPECT_THAT(device.readResult(), Eq("0xBEEF9090"));
}

TEST_F(SsdVirtualFixture, eraseIgnore2) {
	device.writeSsd(0, "0xBEEF9090");
	device.eraseSsd(0, -1);
	device.readSsd(0);
	EXPECT_THAT(device.readResult(), Eq("0xBEEF9090"));
}

TEST_F(SsdVirtualFixture, eraseValid) {
	device.writeSsd(9, "0xBEEF9090");
	device.eraseSsd(0, 10);
	device.readSsd(9);
	EXPECT_THAT(device.readResult(), Eq("0x00000000"));
}

TEST_F(SsdVirtualFixture, eraseSizeOver1) {
	device.writeSsd(11, "0xBEEF9090");
	device.eraseSsd(0, 11);
	device.readSsd(11);
	EXPECT_THAT(device.readResult(), Eq("0xBEEF9090"));
}

TEST_F(SsdVirtualFixture, eraseSizeOver2) {
	device.writeSsd(99, "0xBEEF9090");
	device.eraseSsd(95, 10);
	device.readSsd(99);
	EXPECT_THAT(device.readResult(), Eq("0x00000000"));
}