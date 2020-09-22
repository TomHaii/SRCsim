#include "assembler.h"
#include "core/bus.h"

Assembler::Assembler(){
    bus.tests();
}

Assembler::~Assembler(){
}

void Assembler::assemble(){

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
    return 0;
}

uint32_t Assembler::format1(){
    return 0;
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

//uint32_t Assembler::mWord_instruction(){
//    std::string name = nInstruction.instr_name;
//    if(name.compare("nop") == 0)
//        return NOP;
//    else if(name.compare("LD") == 0)
//        return LD;
//    else if(name.compare("r2") == 0)
//        return R2;
//    else if(name.compare("r3") == 0)
//        return R1;
//    else if(name.compare("r4") == 0)
//        return R1;
//    else if(name.compare("r5") == 0)
//        return R1;
//    else if(name.compare("r6") == 0)
//        return R1;
//    else if(name.compare("r7") == 0)
//        return R1;

//}
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
    getline(f, s);
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
