#include <string>
#include <stdexcept>
using namespace std;

int readindex(string input) {
	if (input[0] != 'R') {
		throw std::invalid_argument("Invalid Input Format! Must start with R");
	}
	if (input.size() > 4 || input[1] != ' ') {
		throw std::invalid_argument("Invalid read input format");
	}
	if (!isdigit(input[2]) || !isdigit(input[3])) {
		throw std::invalid_argument("Invalid index format! Index must be 0 to 99");
	}
	return stoi(input.substr(2, 2));
}

string printresult(string input) {
	int idx = readindex(input);

	return " ";
}
