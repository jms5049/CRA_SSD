#include <stdlib.h>
#include "TestShell.h""

using std::string;

void TestShell::exitApp() {
	exit(0);
}

int TestShell::help(string command) {
	if (command == "write") {
		printf("write:\n\t write [address] [value] => write 3 0xaabbccdd\n");
	}
	else if (command == "read") {
		printf("read:\n\t read [address] => read 3 \n");
	}
	else if (command == "exit") {
		printf("exit:\n\t you can exit the program \n");
	}
	else if (command == "fullwrite") {
		printf("fullwrite:\n\t you can write overall region at once \n\t fullwrite [value] => fullwrite 0xabcdffff \n");
	}
	else if (command == "fullread") {
		printf("fullread:\n\t fullread overall region at once\n");
	}
	else {
		printf("write:\n\t write [address] [value] => write 3 0xaabbccdd\n");
		printf("read:\n\t read [address] => read 3 \n");
		printf("exit:\n\t you can exit the program \n");
		printf("fullwrite:\n\t you can write overall region at once \n\t fullwrite [value] => fullwrite 0xabcdffff \n");
		printf("fullread:\n\t fullread overall region at once\n");
	}
	return 0;
}