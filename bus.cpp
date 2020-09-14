#include "bus.h"


void Bus::write8(uint32_t addr, uint8_t data)
{
	MEM allo = { allo.addr = addr, allo.data = data };
	if (addr > 0x00000000 && addr <= 0xffffffff) {
		ram[ram_index] = allo;
		ram_index++;
	}
}

uint8_t Bus::read8(uint32_t addr, bool readOnly)
{
	for (uint32_t i = 0; i < ram_index; i++) {
		if (ram[i].addr = addr)
			return ram[i].data;
	}
	return 0;
}
