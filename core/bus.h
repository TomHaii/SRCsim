//Created by Tom Levy - 19.9.2020

#pragma once
#include <map>
#include <cstdint>
#include <array>

#include "src.h"

class Bus
{
public:
	Bus();
	~Bus();
	
public:
	SRC cpu;

private:

	std::map<uint32_t, uint8_t> ram;

public:
	void write32(uint32_t addr, uint32_t data);
	void write16(uint32_t addr, uint16_t data);
	void write8(uint32_t addr, uint8_t data);

    uint32_t read32(uint32_t addr);
    uint16_t read16(uint32_t addr);
    uint8_t read8(uint32_t addr);

    void reset();
    void mod_pc(uint32_t amount);
	//for debugging
	void print_memory(uint32_t addr);
    void run();
};

