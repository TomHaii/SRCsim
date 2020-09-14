#pragma once
#include <array>
#include <map>
#include <cstdint>
class Bus
{
public:
	Bus();
	~Bus();

private:

	struct MEM {
		uint32_t addr;
		uint8_t data;
	};

	std::array<MEM, 2 * 1000 * 1024> ram;  //fake 2mb ram
	uint32_t ram_index;

public:
	void write32(uint32_t addr, uint32_t data);
	void write16(uint32_t addr, uint16_t data);
	void write8(uint32_t addr, uint8_t data);

	uint32_t read32(uint32_t addr, bool readOnly = false);
	uint16_t read16(uint32_t addr, bool readOnly = false);
	uint8_t read8(uint32_t addr, bool readOnly = false);


};

