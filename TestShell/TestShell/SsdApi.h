#define interface struct

interface SsdApi {
	virtual void write(int lba, int data) = 0;
	virtual int read(int lba) = 0;
};
