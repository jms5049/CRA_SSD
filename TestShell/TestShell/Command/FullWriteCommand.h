#pragma once

class FullWriteCommand : public WriteCommand {
public:
	FullWriteCommand(vector<string> options)
		: WriteCommand(options) {
	}

	void verifyOptions() override;
	void execute() override;
<<<<<<< HEAD
=======
private:
	void log();
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
};