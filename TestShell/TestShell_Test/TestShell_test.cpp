#pragma once
#include "../TestShell/TestShell.cpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace testing;

using std::string;


TEST(AppTest, Help) {
	TestShell* app = new TestShell();
	app->help("write");
	//do not need Test for Help function
}

TEST(AppTest, Exit) {
	TestShell* app = new TestShell();
	EXPECT_TRUE(app != nullptr);
	app->exitApp();
	EXPECT_TRUE(app == nullptr);
}
