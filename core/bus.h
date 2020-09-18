//Created by Tom Levy - 19.9.2020

#pragma once
#include <map>
#include <cstdint>
#include "src.h"
#include <array>

//TODO: make all the read and write generic so we won't need to make different functions for different sizes.


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

	uint32_t read32(uint32_t addr, bool readOnly = false);
	uint16_t read16(uint32_t addr, bool readOnly = false);
	uint8_t read8(uint32_t addr, bool readOnly = false);


	//for debugging
	
	void print_memory(uint32_t addr);
	void tests();
};

