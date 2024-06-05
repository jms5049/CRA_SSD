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

class InvalidLbaException : std::exception {
public:
	InvalidLbaException()
		: exception("Invalid LBA Input Exception") { }
};

class InvalidDataException : std::exception {
public:
	InvalidDataException()
		: exception("Invalid Data Input Exception") { }
};