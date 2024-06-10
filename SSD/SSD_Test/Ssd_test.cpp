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
	void checkReadAndExpect(int index, string expected) {
		device.readSsd(index);
		EXPECT_THAT(device.readResult(), Eq(expected));
	}
	void writeMassDataWithIndex(int start, int end) {
		for (int i = start; i < end; i++) {
			if(i < 10)  device.writeSsd(i, "0xFFFFFFF" + to_string(i));
			else device.writeSsd(i, "0xFFFFFF" + to_string(i));
		}
	}
};

TEST_F(SsdVirtualFixture, readNandDataIndex0) {
	checkReadAndExpect(0, "0x00000000");
}

TEST_F(SsdVirtualFixture, writeNandDataIndex0) {
	device.writeSsd(0, "0x12345678");
	checkReadAndExpect(0, "0x12345678");
}

TEST_F(SsdVirtualFixture, writeNandDataIndex4) {
	device.writeSsd(4, "0xBEEF9090");
	checkReadAndExpect(4, "0xBEEF9090");
}

TEST_F(SsdVirtualFixture, errorMessage) {
	EXPECT_THAT(device.getErrorMessage(), StrEq("Nand file open error!"));
}

TEST_F(SsdVirtualFixture, eraseIgnore1) {
	device.writeSsd(0, "0xBEEF9090");
	device.eraseSsd(0, 0);
	checkReadAndExpect(0, "0xBEEF9090");
}

TEST_F(SsdVirtualFixture, eraseIgnore2) {
	device.writeSsd(0, "0xBEEF9090");
	device.eraseSsd(0, -1);
	checkReadAndExpect(0, "0xBEEF9090");
}

TEST_F(SsdVirtualFixture, eraseValid) {
	device.writeSsd(9, "0xBEEF9090");
	device.eraseSsd(0, 10);
	checkReadAndExpect(9, "0x00000000");
}

TEST_F(SsdVirtualFixture, eraseSizeOver1) {
	device.writeSsd(11, "0xBEEF9090");
	device.eraseSsd(0, 11);
	checkReadAndExpect(11, "0xBEEF9090");
}

TEST_F(SsdVirtualFixture, eraseSizeOver2) {
	device.writeSsd(99, "0xBEEF9090");
	device.eraseSsd(95, 10);
	checkReadAndExpect(99, "0x00000000");
}

TEST_F(SsdVirtualFixture, flush) {
	writeMassDataWithIndex(0, 5);
	device.flush();
	checkReadAndExpect(4, "0xFFFFFFF4");
	checkReadAndExpect(5, "0x00000000");
}

TEST_F(SsdVirtualFixture, writeEraseMix1) {
	writeMassDataWithIndex(0, 5);
	device.eraseSsd(0, 4);
	checkReadAndExpect(4, "0xFFFFFFF4");
	writeMassDataWithIndex(6, 12);
	device.eraseSsd(6, 5);
	device.eraseSsd(11, 1);
	checkReadAndExpect(11, "0x00000000");
}

TEST_F(SsdVirtualFixture, writeEraseMix2) {
	writeMassDataWithIndex(0, 9);
	device.eraseSsd(0, 9);
	writeMassDataWithIndex(10, 18);
	device.eraseSsd(10, 7);
	writeMassDataWithIndex(20, 28);
	device.eraseSsd(20, 8);
	writeMassDataWithIndex(30, 38);
	device.eraseSsd(30, 8);
	writeMassDataWithIndex(40, 48);
	device.eraseSsd(40, 8);
	checkReadAndExpect(49, "0x00000000");
}

TEST_F(SsdVirtualFixture, writeEraseMix3) {
	writeMassDataWithIndex(0, 99);
	device.eraseSsd(91, 9);
	device.eraseSsd(50, 30);
	device.eraseSsd(0, 30);
	checkReadAndExpect(10, "0x00000000");
	checkReadAndExpect(40, "0xFFFFFF40");
	checkReadAndExpect(50, "0x00000000");
	checkReadAndExpect(79, "0x00000000");
	checkReadAndExpect(80, "0xFFFFFF80");
	checkReadAndExpect(90, "0xFFFFFF90");
	checkReadAndExpect(91, "0x00000000");
}