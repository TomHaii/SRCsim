#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "core/bus.h"


class Assembler
{
public:
    Assembler();
    ~Assembler();

private:
    enum Opcode {
        NOP = 0, LD = 1, LDR = 2, ST = 3, STR = 4, LA = 5,
        LAR = 6, BR = 8, BRL = 9, EEN = 10, EDI = 11, ADD = 12,
        ADDI = 13, SUB = 14, NEG = 15, SVI = 16, RI = 17, AND = 20,
        ANDI = 21, OR = 22, ORI = 23, NOT = 24, SHR = 26, SHRA = 27,
        SHL = 28, SHC = 29, RFI = 30, STOP = 31
    };

    enum Registers {
        R0 = 0, R1 = 1, R2 = 2, R3 = 3, R4 = 4, R5 = 5,
        R6 = 6, R7 = 7, R8 = 8, R9 = 9, R10 = 10, R11 = 11,
        R12 = 12, R13 = 13, R14 = 14, R15 = 15, R16 = 16, R17 = 17,
        R18 = 18, R19 = 19, R20 = 20, R21 = 21, R22 = 22, R23 = 23,
        R24 = 24, R25 = 25, R26 = 26, R27 = 27, R28 = 28, R29 = 29,
        R30 = 30, R31 = 31
    };

    enum Conditions{
        JUMP = 1, JUMP_ZERO = 2, JUMP_NOT_ZERO = 3,
        JUMP_POSITIVE = 4, JUMP_NEGATIVE = 5
    };

    struct instr {
        std::string instr_name;
        std::string in_1 = "";
        std::string in_2 = "";
        std::string in_3 = "";
        std::string he = "";
    };
    Bus bus;
    instr nInstruction;
    std::vector<std::string> s_instructions;
    //std::vector<instr> instructions;

public:

    void assemble();
    void parse(std::string instr);
    void reset_program();
    unsigned int print_memory(uint32_t address);
    void write_to_memory(uint32_t address, uint32_t val);
    unsigned int p_register(int index);
    unsigned int p_pc();

private:
    uint32_t mWord_instruction();
    void build_instruction(std::string in);
    void splitString(std::string instr);
    uint32_t decode_operands(std::string op);

    //break instruction to format
    uint32_t format1();
    uint32_t format2();
    uint32_t format3();
    uint32_t format4();
    uint32_t format5();
    uint32_t format6();
    uint32_t format7();
    uint32_t format8();
};

