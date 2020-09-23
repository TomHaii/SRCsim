#include "assembler.h"
#include "core/bus.h"

Assembler::Assembler(){
}

Assembler::~Assembler(){
}

void Assembler::assemble(){
    uint32_t machine_word = mWord_instruction();
    std::cout << " Machine word is " << std::hex << machine_word << std::endl;
    //bus.run();

}



void Assembler::parse(std::string instr){
    splitString(instr);
    for(std::string &s: s_instructions){
        build_instruction(s);
        std::cout << "in name " << nInstruction.instr_name << std::endl;
        std::cout << "input 1 name " << nInstruction.in_1 << std::endl;
        std::cout << "input 2 name " << nInstruction.in_2 << std::endl;
        std::cout << "input 3 name " << nInstruction.in_3 << std::endl;
    }
    assemble();
}

uint32_t Assembler::mWord_instruction(){
    std::string name = nInstruction.instr_name;
    if(name == "ld" || name == "st" || name == "la" || name == "addi" || name == "andi" || name == "ori")
        return format1();
    else if(name == "ldr" || name == "str" || name == "lar")
        return format2();
    else if(name == "neg" || name == "not")
        return format3();
    else if(name == "br" || name == "brzr" || name == "brnz" || name == "brpl" || name == "brmi")
        return format4();
    else if(name == "brlnv" || name == "brl" || name == "brlzr" || name == "brlnz" || name == "brlpl" || name == "brlmi")
        return format5();
    else if(name == "add" || name == "sub" || name == "and" || name == "or")
        return format6();
    else if(name == "shr" || name == "shra" || name == "shl" || name == "shc")
        return format7();
    else if(name == "nop" || name == "stop")
        return format8();
    else {
        std::cout << "invalid opcode" << std::endl;
    }
    return 0;
}

uint32_t Assembler::format1(){
    uint32_t res = 0, opCode = 0;
    std::string name = nInstruction.instr_name;
    if(name == "ld")
        opCode = LD;
    else if(name == "st")
        opCode = ST;
    else if(name == "la")
        opCode = LA;
    else if(name == "addi")
        opCode = ADDI;
    else if(name == "andi")
        opCode = ANDI;
    else if(name == "ori")
        opCode = ORI;
    uint32_t r1M = decode_operands(nInstruction.in_1);
    std::cout << "first operand value is " << std::dec << r1M << std::endl;
    uint32_t r2M = decode_operands(nInstruction.in_2);
    std::cout << "second operand value is " << std::dec << r2M << std::endl;
    uint32_t c = 0;
    try {
    c = stoi(nInstruction.in_3);
    }
    catch (std::exception e){
        std::cout << "illegal immediate" << std::endl;
    }
    std::cout << "c value is " << std::dec << c << std::endl;

    res = (c & 0x1ffff) + (r2M << 17) + (r1M << 22) + (opCode << 27);
    std::cout << "Instruction machine word value is " << std::hex << res << std::endl;
    return res;
}

uint32_t Assembler::format2(){
    return 0;
}

uint32_t Assembler::format3(){
    return 0;
}

uint32_t Assembler::format4(){
    return 0;
}

uint32_t Assembler::format5(){
    return 0;
}

uint32_t Assembler::format6(){
    return 0;
}

uint32_t Assembler::format7(){
    return 0;
}

uint32_t Assembler::format8(){
    return 0;
}

uint32_t Assembler::decode_operands(std::string op){
    std::string name = op;
    if(name.compare("r0") == 0)
        return R0;
    else if (name.compare("r1") == 0)
        return R1;
    else if(name.compare("r2") == 0)
        return R2;
    else if(name.compare("r3") == 0)
        return R3;
    else if(name.compare("r4") == 0)
        return R4;
    else if(name.compare("r5") == 0)
        return R5;
    else if(name.compare("r6") == 0)
        return R6;
    else if(name.compare("r7") == 0)
        return R7;
    else if(name.compare("r8") == 0)
        return R8;
    else if(name.compare("r9") == 0)
        return R9;
    else if(name.compare("r10") == 0)
        return R10;
    else if(name.compare("r11") == 0)
        return R11;
    else if(name.compare("r12") == 0)
        return R12;
    else if(name.compare("r13") == 0)
        return R13;
    else if(name.compare("r14") == 0)
        return R14;
    else if(name.compare("r15") == 0)
        return R15;
    else if(name.compare("r16") == 0)
        return R16;
    else if(name.compare("r17") == 0)
        return R17;
    else if(name.compare("r18") == 0)
        return R18;
    else if(name.compare("r19") == 0)
        return R19;
    else if(name.compare("r20") == 0)
        return R20;
    else if(name.compare("r21") == 0)
        return R21;
    else if(name.compare("r22") == 0)
        return R22;
    else if(name.compare("r23") == 0)
        return R23;
    else if(name.compare("r24") == 0)
        return R24;
    else if(name.compare("r25") == 0)
        return R25;
    else if(name.compare("r26") == 0)
        return R26;
    else if(name.compare("r27") == 0)
        return R27;
    else if(name.compare("r28") == 0)
        return R28;
    else if(name.compare("r29") == 0)
        return R29;
    else if(name.compare("r30") == 0)
        return R30;
    else if(name.compare("r31") == 0)
        return R31;
    else
        return 0;
}
void Assembler::build_instruction(std::string in){
    //TODO: Take care of of bracket instructions

    std::istringstream f(in);
    std::string s;
    getline(f, s, ' '); //instruction name
    nInstruction.instr_name = s;
    getline(f, s, ','); //input 1
    nInstruction.in_1 = s;
    getline(f, s, ','); //input 2
    nInstruction.in_2 = s;
    getline(f, s);      //input 3
    nInstruction.in_3 = s;
}

void Assembler::splitString(std::string instr){
    std::istringstream f(instr);
    std::string s;
    while(getline(f, s, '\n')){
        std::cout << "instr " << s << std::endl;
        s_instructions.push_back(s);
    }
}
