#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD/Ssd.cpp"
using namespace testing;

class SsdVirtualFixture : public Test {
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