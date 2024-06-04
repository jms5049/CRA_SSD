#pragma once
#include "../TestShell/TestShell.cpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace testing;

TEST(AppTest, Exit) {
	TestShell* app = new TestShell();
	EXPECT_TRUE(app != nullptr);
	app->exitApp();
	EXPECT_TRUE(app == nullptr);
}