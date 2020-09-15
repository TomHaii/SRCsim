#include "core/src.h"

int main() {
	SRC* src = new SRC();
	//here we need to read a file and start executing the commands

	//LA TEST
	//src->execute(0x28000000);
	//src->print_registers();
	//src->execute(0x28400001);
	//src->print_registers();
	//src->execute(0x2841FFFF);
	//src->print_registers();

	//and test
	//src->execute(0x2841ffff);
	//src->execute(0x2881fffe);
	//src->execute(0xa0c41000);
	//src->print_registers();


	//shl tests
	//src->execute(0x2881ffff);
	//src->execute(0xe0440001);
	//src->print_registers();

	//shr tests
	src->execute(0x2881fffe);
	src->execute(0xd8440001);
	src->print_registers();

	getchar();
	return 0;
}