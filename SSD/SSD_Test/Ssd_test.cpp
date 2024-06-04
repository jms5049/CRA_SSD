#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD/Ssd.cpp"
using namespace testing;

class SsdVirtualFixture : public Test {
protected:
	void TearDown() override {
		for(int i = 0; i < 100; i++)
			device.writeSsd(i, "00000000");
	}
public:
	Ssd device;
	string validFileName = "../nand.txt";
	string invalidFileName = "../flash.txt";
};

TEST_F(SsdVirtualFixture, readNandDataFileNameError) {
	EXPECT_THAT(device.readNandData(invalidFileName), Eq(device.getErrorMessage()));
}

TEST_F(SsdVirtualFixture, readNandDataNandSizeError) {
	EXPECT_THAT(device.readNandData(validFileName).size(), Eq(800));
}

TEST_F(SsdVirtualFixture, readNandDataIndex0) {
	EXPECT_THAT(device.readSsd(0), StartsWith("0x00000000"));
}

TEST_F(SsdVirtualFixture, writeNandDataIndex0) {
	device.writeSsd(0, "12345678");
	EXPECT_THAT(device.readSsd(0), Eq("0x12345678"));
}

TEST_F(SsdVirtualFixture, writeNandDataIndex4) {
	device.writeSsd(4, "BEEF9090");
	EXPECT_THAT(device.readSsd(4), Eq("0xBEEF9090"));
}