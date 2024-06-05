#pragma once
#include <exception>

class InvalidCommandException : std::exception {
public:
	InvalidCommandException()
		: exception("Invalid Command Exception") { }
};

class InvalidArgumentException : std::exception {
public:
	InvalidArgumentException()
		: exception("Invalid Argument Exception : Use Help Command to See Detail") { }
};