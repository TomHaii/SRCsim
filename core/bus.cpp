#include "bus.h"



Bus::Bus()
{
	
	ram_index = 0;
	std::cout << "Connecting to bus" << std::endl;
	cpu.connectBus(this);

}

Bus::~Bus()
{
}

void Bus::write8(uint32_t addr, uint8_t data)
{
	
	if (addr > 0x00000000 && addr <= 0xffffffff) {
		ram.insert(std::make_pair(addr, data));
		ram_index++;
	}
}

void Bus::write16(uint32_t addr, uint16_t data)
{

	if (addr > 0x00000000 && addr <= 0xffffffff) {
		ram.insert(std::make_pair(addr, data));
		ram_index++;
	}
}


void Bus::write32(uint32_t addr, uint32_t data)
{
	if (addr >= 0x00000000 && addr <= 0xffffffff) {
		ram.insert(std::make_pair(addr, data));
		ram_index++;  
	}
}


uint8_t Bus::read8(uint32_t addr, bool readOnly)
{
	std::map<uint32_t, uint8_t>::iterator it;
	for (it = ram.begin(); it != ram.end(); it++) {
		if (it->first == addr)
			return it->second;
	}
	return 0;
}

void Bus::print_memory(uint32_t addr, int size)
{
	int amount_to_print = size;
	std::map<uint32_t, uint8_t>::iterator it;
	for (it = ram.begin(); it != ram.end(); it++) {
		if (it->first == addr) {
			signed int n = 0;
			do {
				uint8_t temp = it->second;
				amount_to_print--;
			} while (amount_to_print != 0);
			std::cout << "Value at " << std::hex << addr << " is " << std::dec << it->second << std::endl;
			return;
		}
	}
	std::cout << "Nothing is in (0) " << std::hex << addr << std::endl;
}

void Bus::tests()
{
	//here we need to read a file and start executing the commands

	//LA TEST
	//src.execute(0x28000000);
	//src.print_registers();
	//src.execute(0x28400001);
	//src.print_registers();
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
	//src->execute(0x2881fffe);
	//src->execute(0xd8440001);
	//	src.print_registers();

	//st tests
	cpu.execute(0x2881ffff);
	cpu.execute(0x188001ff);
	cpu.execute(0x084001ff);
	//cpu.execute(0x188001ff);
	cpu.print_registers();

	print_memory(0x1ff);
}

uint16_t Bus::read16(uint32_t addr, bool readOnly) {
	std::map<uint32_t, signed int>::iterator it;
	for (it = ram.begin(); it != ram.end(); it++) {
		if (it->first == addr)
			return it->second;
	}
	return 0;
}

uint32_t Bus::read32(uint32_t addr, bool readOnly) {
	std::map<uint32_t, signed int>::iterator it;
	for (it = ram.begin(); it != ram.end(); it++) {
		if (it->first == addr)
			return it->second;
	}
	return 0;
}