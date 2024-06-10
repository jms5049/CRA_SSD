#pragma once
#include <string>
#include "../TestShell.h"
#include <typeinfo>

#include "TestScenario.h"

using std::string;

class Read10AndCompare : public TestScenario {
public:
	Read10AndCompare();
	bool runTest() override;
};
