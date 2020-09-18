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
	
	if (addr >= 0x00000000 && addr <= 0xffffffff) {
		ram.insert(std::make_pair(addr, data));
		ram_index++;
	}
}

void Bus::write16(uint32_t addr, uint16_t data)
{
	uint8_t lo = data << 8;
	uint8_t hi = (uint8_t) data;
	if (addr >= 0x00000000 && addr < 0xffffffff) {
		ram[addr] = hi;
		ram[addr + 1] = lo;
		ram_index++;
	}
	else {
		std::cout << "Memory out of range" << std::endl;
	}
}


void Bus::write32(uint32_t addr, uint32_t data)
{
	uint8_t lo = data >> 24;
	uint8_t mi = data >> 16;
	uint8_t me = data >> 8;
	uint8_t hi = data;
	uint32_t val = (lo << 24) + (mi << 16) + (me << 8) + hi;
	if (addr >= 0x00000000 && addr - 3 <= 0xffffffff) {
		//ram.insert(std::make_pair(addr, hi));
		//ram.insert(std::make_pair(addr + 1, me));
		//ram.insert(std::make_pair(addr + 2, mi));
		//ram.insert(std::make_pair(addr + 3, lo));
		ram[addr] = hi;
		ram[addr + 1] = me;
		ram[addr + 2] = mi;
		ram[addr + 3] = lo;
		ram_index++;  
	}
	else {
		std::cout << "Memory out of range" << std::endl;
	}
}



void Bus::print_memory(uint32_t addr)
{
	uint8_t hi = 0, me = 0, mi = 0, lo = 0;
	std::map<uint32_t, uint8_t>::iterator it;
	for (it = ram.begin(); it != ram.end(); it++) {
		if (it->first == addr)
			hi = it->second;
		if (it->first == addr + 1)
			me = it->second;
		if (it->first == addr + 2)
			mi = it->second;
		if (it->first == addr + 3)
			lo = it->second;
	}
	signed int val = (lo << 24) + (mi << 16) + (me << 8) + hi;
	std::cout << "Value at " << std::hex << addr << " is " << std::dec << val << std::endl;
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
	//cpu.execute(0x2881ffff);
	//cpu.execute(0x188001ff);
	//cpu.execute(0x084001ff);
	//cpu.execute(0x188001ff);
	//cpu.print_registers();
	//print_memory(0x1ff);

	//big test 1
	write32(200, 101);
	write32(0x00000000,0x084000c8); //ld r1, 200
	write32(0x00000004,0xa8820001); //andi r2,r1,1
	write32(0x00000008,0x68c3ffff); //addi r3,r1, -1
	write32(0x0000000c,0xd9020001); //shra r4,r1,1
	write32(0x00000010,0x31400008); //lar r5,8
	write32(0x00000014,0x400a2002); //brzr r5,r2
	write32(0x00000018,0x29060000); //la r4, 0(r3)
	write32(0x0000001c,0x190000c8); //st r4, 200
	write32(0x00000020,0xf8000000); //stop
	while (read32(cpu.pc) != 0xf8000000) {
		cpu.execute(read32(cpu.pc));
	}
	cpu.print_registers();
	print_memory(200);
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

uint16_t Bus::read16(uint32_t addr, bool readOnly) {
	uint8_t hi = 0, lo = 0;
	std::map<uint32_t, uint8_t>::iterator it;
	for (it = ram.begin(); it != ram.end(); it++) {
		if (it->first == addr)
			hi = it->second;
		if (it->first == addr + 1)
			lo = it->second;
	}
	signed short val = (lo << 8) + hi;
	return val;
}

uint32_t Bus::read32(uint32_t addr, bool readOnly) {
	uint8_t hi = 0, me = 0, mi = 0, lo = 0;
	std::map<uint32_t, uint8_t>::iterator it;
	for (it = ram.begin(); it != ram.end(); it++) {
		if (it->first == addr)
			hi = it->second;
		if (it->first == addr + 1)
			me = it->second;
		if (it->first == addr + 2)
			mi = it->second;
		if (it->first == addr + 3)
			lo = it->second;
	}
	uint32_t val = (lo << 24) + (mi << 16) + (me << 8) + hi;
	return val;
}