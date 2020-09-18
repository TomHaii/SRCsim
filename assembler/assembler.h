#pragma once
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
public:
    void decode();

private:


};

