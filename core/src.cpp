//Created by Tom Levy - 19.9.2020

#include "src.h"
#include "bus.h"

SRC::SRC() {
	std::cout << "starting CPU" << std::endl;
	for (auto &i: registers) i = 0x00000000;
}

SRC::~SRC()
{
}

void SRC::execute(uint32_t li)
{
	decode(li);
	uint32_t opcode = fetched.opcode;

    if (opcode > 31 || opcode == 7 || opcode == 18 || opcode == 19 || opcode == 25) {
		std::cout << "Invalid opcode" << std::endl;
		return;
	}


	//tests
	//signed int c2 = extend_c2_sign(fetched.c2);
	//std::cout << "c2 value " << std::dec << c2 << std::endl;
	//for debugging
	//std::bitset<32> y(fetched.value);
	//std::bitset<32> x(opcode);
	//std::cout << "Fetched value " << std::hex << fetched.value << std::endl;
	//std::cout << "Binary representation of value " << y << std::endl;
	//std::cout << "Binary representation of opcode " << x << std::endl;

	std::cout << "Executing " << std::dec << fetched.opcode << std::endl;
	
	switch (opcode) {
		case 0:
			NOP();
			break;
		case 1:
			LD();
			break;
		case 2:
			LDR();
			break;
		case 3:
			ST();
			break;
		case 4:
			STR();
			break;
		case 5:
			LA();
			break;
		case 6:
			LAR();
			break;
		// opcode 7 doesn't exist
		case 8:
			//we are in brunch commands tree
			BR();
			break;
		case 9:
			//TODO
			BRL();
			break;
		case 10:
			//TODO
			EEN();
			break;
		case 11:
			//TODO
			EDI();
			break;
		case 12:
			ADD();
			break;
		case 13:
			ADDI();
			break;
		case 14:
			SUB();
			break;;
		case 15:
			NEG();
			break;
		case 16:
			//TODO
			SVI();
			break;
		case 17:
			//TODO
			RI();
			break;
		//opcode 18 and 19 doesn't exist
		case 20:
			AND();
			break;
		case 21:
			ANDI();
			break;
		case 22:
			OR();
			break;
		case 23:
			ORI();
			break;
		case 24:
			NOT();
			break;
		//opcode 25 doesn't exist
		case 26:
			SHR();
			break;
		case 27:
			SHRA();
			break;
		case 28:
			SHL();
			break;
		case 29:
			SHC();
			break;
		case 30:
			RFI();
			break;
		case 31:
			STOP();
			break;
	}

	//increasing pc
	pc = nPc;
	nPc += 4;
	
}

void SRC::print_registers()
{
	int c = 0;
	for (auto& i : registers) {
		std::cout << "R[" << c << "] value is " << std::dec <<  i << std::endl;
		c++;
	}
}

void SRC::decode(uint32_t addr)
{
	fetched.value = addr;
	fetched.opcode = addr >> 27;
	//registers
	fetched.ra = (addr >> 22) & 0x1f;
	fetched.rb = (addr >> 17) & 0x1f;
	fetched.rc = (addr >> 12) & 0x1f;

	//immediates
	fetched.c1 = addr & 0x1fffff;
	fetched.c2 = addr & 0x1ffff;

	fetched.count = addr & 0x1f;
	fetched.cond = addr & 0x7;
}

signed int SRC::extend_c1_sign(uint32_t c1)
{
	signed short sign = (c1 >> 21);
	if (sign)
		return c1 | 0xffc00000;
	return c1;
}


signed int SRC::extend_c2_sign(uint32_t c2)
{
	signed short sign = (c2 >> 16);
	if(sign)
		return c2 | 0xfffe0000;
	return c2;
}

void SRC::NOP() { return; }

void SRC::LD() {
	uint32_t ra = fetched.ra;
	uint32_t rb = fetched.rb;
	if (rb == 0) {
		registers[ra] = bus->read32(fetched.c2);
	}
	else {
		registers[ra] = bus->read32(fetched.c2 + registers[rb]);
	}
}

void SRC::LDR()
{
	signed int sC1 = extend_c1_sign(fetched.c1);
	registers[fetched.ra] = bus->read32(sC1 + nPc);
}

void SRC::ST()
{
	bus->write32(fetched.c2, registers[fetched.ra]);
}

void SRC::STR()
{
	signed int sC1 = extend_c1_sign(fetched.c1);
	bus->write32(sC1 + nPc, registers[fetched.ra]);
}

void SRC::LA()
{
	uint32_t ra = fetched.ra;
	uint32_t rb = fetched.rb;
	signed int c2 = extend_c2_sign(fetched.c2);
	if (rb == 0)
		registers[ra] = c2;
	else
		registers[ra] = c2 + registers[rb];
}

void SRC::LAR()
{
	signed int sC1 = extend_c1_sign(fetched.c1);
	registers[fetched.ra] = sC1 + nPc;
}

void SRC::BR()
{
	uint32_t cond = fetched.cond;
	signed int rb_data = registers[fetched.rb];
	signed int rc_data = registers[fetched.rc];
	bool isCond = false;
	switch (cond) {
	case 1:
		isCond = true;
		break;
	case 2:
		if (rc_data == 0)
			isCond = true;
		break;
	case 3:
		if (rc_data != 0)
			isCond = true;
		break;
	case 4:
		if (rc_data >= 0)
			isCond = true;
		break;
	case 5:
		if (rc_data < 0)
			isCond = true;
		break;
	default:
		isCond = false;
		break;
	}
	if (isCond)
		nPc = rb_data;
}

void SRC::BRL()
{
	registers[fetched.ra] = nPc;
	if(fetched.cond != 0)
		BR();
}

void SRC::EEN() {}

void SRC::EDI() {}

void SRC::ADD()
{
	signed int rb_data = registers[fetched.rb];
	signed int rc_data = registers[fetched.rc];
	registers[fetched.ra] = rb_data + rc_data;
}

void SRC::ADDI()
{
	signed int rb_data = registers[fetched.rb];
	signed int c2 = extend_c2_sign(fetched.c2);
	registers[fetched.ra] = rb_data + c2;
}

void SRC::SUB()
{
	signed int rb_data = registers[fetched.rb];
	signed int rc_data = registers[fetched.rc];
	registers[fetched.ra] = rb_data - rc_data;
}

void SRC::NEG()
{
	registers[fetched.ra] = -registers[fetched.rc];
}

void SRC::SVI() {}

void SRC::RI() {}

void SRC::AND()
{
	signed int rb_data = registers[fetched.rb];
	signed int rc_data = registers[fetched.rc];
	registers[fetched.ra] = rb_data & rc_data;
}

void SRC::ANDI()
{
	signed int rb_data = registers[fetched.rb];
	signed int c2 = extend_c2_sign(fetched.c2);
	registers[fetched.ra] = rb_data & c2;
}

void SRC::OR()
{
	signed int rb_data = registers[fetched.rb];
	signed int rc_data = registers[fetched.rc];
	registers[fetched.ra] = rb_data | rc_data;
}

void SRC::ORI()
{
	signed int rb_data = registers[fetched.rb];
	signed int c2 = extend_c2_sign(fetched.c2);
	registers[fetched.ra] = rb_data | c2;
}

void SRC::NOT()
{
	registers[fetched.ra] = ~registers[fetched.rc];
}

void SRC::SHR()
{
	uint32_t rb_data = registers[fetched.rb];
	uint32_t amount;
	if (fetched.count != 0)
		amount = fetched.count;
	else
		amount = registers[fetched.rc] & 0x1f;
	for (uint32_t i = 0; i < amount; i++) {
		rb_data = rb_data >> 1;
	}
	registers[fetched.ra] = (signed int) rb_data;
}

void SRC::SHRA()
{
	signed int rb_data = registers[fetched.rb];
	uint32_t amount;
	if (fetched.count != 0)
		amount = fetched.count;
	else
		amount = registers[fetched.rc] & 0x1f;
	for (uint32_t i = 0; i < amount; i++) {
		rb_data = rb_data >> 1;
	}

	registers[fetched.ra] = rb_data;
	
}

void SRC::SHL()
{
	uint32_t rb_data = registers[fetched.rb];
	uint32_t amount;
	if (fetched.count != 0)
		amount = fetched.count;
	else
		amount = registers[fetched.rc] & 0x1f;
	for (uint32_t i = 0; i < amount; i++) {
		rb_data = rb_data << 1;
	}
	registers[fetched.ra] = (signed int) rb_data;
}

void SRC::SHC()
{
	//TODO
}

void SRC::RFI() {}

void SRC::STOP() {
	std::cout << "Stopping Program..." << std::endl;
	return;
}
