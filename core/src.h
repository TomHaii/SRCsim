#pragma once
#include <cstdint>
#include <string>
#include <iostream>
#include <array>
//for debugging
#include <bitset>

class Bus;

class SRC
{
public:
	SRC();
	~SRC();

public:

	void execute(uint32_t li);

	void connectBus(Bus* b) { bus = b; }

	//FOR DEBUGGING ONLY
	void print_registers();

	uint32_t pc = 0x00000000;
	uint32_t nPc = 0x00000004;
private:
	
	std::array<signed int, 32> registers;
	Bus* bus = nullptr;

	//struct instruction {
	//	std::string name;
	//	uint8_t(src::* operate)(void) = nullptr;
	//	uint8_t(src::* addrmode)(void) = nullptr;
	//};
	
	struct instruction {
		uint32_t value; //used for debugging purposes
		uint32_t opcode : 5;
		
		//registers
		uint32_t ra : 5;
		uint32_t rb : 5;
		uint32_t rc : 5;

		//immediates
		uint32_t c1 : 17;
		uint32_t c2 : 22;
		uint32_t count: 5;
		uint32_t cond : 3;
	};

	instruction fetched;
	void decode(uint32_t addr);
	signed int extend_c1_sign(uint32_t c1);
	signed int extend_c2_sign(uint32_t c2);

private: //instructions

	void NOP(); void LD(); void LDR(); void ST(); void STR();
	void LA(); void LAR(); void BR(); void BRL(); void EEN();
	void EDI(); void ADD(); void ADDI(); void SUB(); void NEG();
	void SVI(); void RI(); void AND(); void ANDI(); void OR();
	void ORI(); void NOT(); void SHR(); void SHRA(); void SHL();
	void SHC(); void RFI(); void STOP();


};

