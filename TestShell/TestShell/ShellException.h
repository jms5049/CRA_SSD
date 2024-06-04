#pragma once
#include <exception>

class InvalidCommandException : std::exception {
public:
	InvalidCommandException()
		: exception("Invalid Command Exception") { }
};