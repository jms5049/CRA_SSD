#pragma once
#include "../TestShell/TestShell.cpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace testing;

using std::string;

TEST(AppTest, Exit) {
	TestShell* app = new TestShell();
	EXPECT_TRUE(app != nullptr);
	app->exitApp();
	EXPECT_TRUE(app == nullptr);
}

TEST(AppTest, Help1) {
	TestShell* app = new TestShell();
	app->help("");
	//Help는 TDD는 불필요하다고 생각됩니다. 
}
