#include "src.h"

int main() {
	SRC* src = new SRC();
	//here we need to read a file and start executing the commands

	//LA TEST
	src->execute(0x28000000);
	src->print_registers();
	src->execute(0x28400001);
	src->print_registers();
	src->execute(0x2841FFFF);
	src->print_registers();


	getchar();
	return 0;
}