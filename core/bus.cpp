//Created by Tom Levy - 19.9.2020

#include "bus.h"



Bus::Bus()
{
	
	std::cout << "Connecting to bus" << std::endl;
	cpu.connectBus(this);
}

Bus::~Bus()
{
}

void Bus::write8(uint32_t addr, uint8_t data)
{
	
    if (addr <= 0xffffffff) {
        //ram.insert(std::make_pair(addr, data));
        ram[addr] = data;
    }
}

void Bus::write16(uint32_t addr, uint16_t data)
{
	uint8_t lo = data << 8;
	uint8_t hi = (uint8_t) data;
    if (addr - 1 <= 0xffffffff) {
		ram[addr] = hi;
		ram[addr + 1] = lo;
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
//	uint32_t val = (lo << 24) + (mi << 16) + (me << 8) + hi;
    if (addr - 3 <= 0xffffffff) {
		//ram.insert(std::make_pair(addr, hi));
		//ram.insert(std::make_pair(addr + 1, me));
		//ram.insert(std::make_pair(addr + 2, mi));
		//ram.insert(std::make_pair(addr + 3, lo));
		ram[addr] = hi;
		ram[addr + 1] = me;
		ram[addr + 2] = mi;
		ram[addr + 3] = lo;
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

void Bus::run()
{
	
	//test 1
    write32(100, 101);
    //write32(0x00000000,0x08400064); //ld r1, 100
	//write32(0x00000004,0xa8820001); //andi r2,r1,1
	//write32(0x00000008,0x68c3ffff); //addi r3,r1, -1
	//write32(0x0000000c,0xd9020001); //shra r4,r1,1
	//write32(0x00000010,0x31400008); //lar r5,8
	//write32(0x00000014,0x400a2002); //brzr r5,r2
	//write32(0x00000018,0x29060000); //la r4, 0(r3)
    //write32(0x0000001c,0x19000064); //st r4, 100
	//write32(0x00000020,0xf8000000); //stop
	
    write32(200, 17);
    write32(204, 4);
//	write32(0x00000000, 0x084000c8); //ld r1, 200
//	write32(0x00000004, 0x088000cc); //ld r2,204
//	write32(0x00000008, 0x28c00000); //la r3,0
//	write32(0x0000000c, 0x31000000); //lar r4,0
//	write32(0x00000010, 0x68c60001); //addi r3,r3,1
//	write32(0x00000014, 0x70422000); //sub r1,r1,r2
//	write32(0x00000018, 0x40081004); //brpl r4,r1
//	write32(0x0000001c, 0x60422000); //add r1,r1,r2
//	write32(0x00000020, 0x68c7ffff); //addi r3,r3,-1
//	write32(0x00000024, 0x184000d4); //st r1,212
//	write32(0x00000028, 0x18c000d0); //st r3,208
//	write32(0x0000002c, 0xf8000000); //stop


    while (read32(cpu.pc) != 0xf8000000) { //until stop instruciton
		cpu.execute(read32(cpu.pc));
	}
	cpu.print_registers();
	//test 1
    print_memory(100);
	//test 2

    //print_memory(212); // should be 1
    //print_memory(208); // should be 4
	
}

uint8_t Bus::read8(uint32_t addr)
{
	std::map<uint32_t, uint8_t>::iterator it;
	for (it = ram.begin(); it != ram.end(); it++) {
		if (it->first == addr)
			return it->second;
	}
	return 0;
}

uint16_t Bus::read16(uint32_t addr) {
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

uint32_t Bus::read32(uint32_t addr) {
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


void Bus::mod_pc(uint32_t amount){
    cpu.pc += amount;
}
