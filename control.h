#ifndef CONTROL_CLASS
#define CONTROL_CLASS
#include <vector>
#include <cstdint>
#include <iostream>
#include <math.h>
using namespace std;
using std::bitset;

// Control signals for the processor
struct control_t {
    bool reg_dest;           // 0 if rt, 1 if rd
    bool jump;               // 1 if jummp
    bool branch;             // 1 if branch
    bool mem_read;           // 1 if memory needs to be read
    unsigned mem_to_reg: 2;  // 00 if wirint ALU result (no mem access), 01 if memory needs to written to reg, 10 is JAL instruction
    unsigned ALU_op : 2;     // 10 for R-type, 00 for LW/SW, 01 for BEQ/BNE, 11 for others
    bool mem_write;          // 1 if needs to be written to memory
    unsigned ALU_src: 2;     // 00 if second operand is from reg_file, 01 if imm, 10 if unsigned imm
    bool reg_write;          // 1 if need to write back to reg file

    bool jump_register;      // 1 if JR
    bool bne;                // 1 if BNE
    unsigned load_size : 2;  // 00 for Load Byte, 01 for Load Halfword, and 10 for Load Word

    
    void print() {      // Prints the generated contol signals
        cout << "REG_DEST: " << reg_dest << "\n";
        cout << "JUMP: " << jump << "\n";
        cout << "BRANCH: " << branch << "\n";
        cout << "MEM_READ: " << mem_read << "\n";
        cout << "MEM_TO_REG: " << mem_to_reg << "\n";
        cout << "ALU_OP: " << ALU_op << "\n";
        cout << "MEM_WRITE: " << mem_write << "\n";
        cout << "ALU_SRC: " << ALU_src << "\n";
        cout << "REG_WRITE: " << reg_write << "\n";

        cout << "JUMP_REGISTER: " << reg_write << "\n";
        cout << "BNE: " << reg_write << "\n";
        cout << "LOAD_SIZE: " << reg_write << "\n";
    }
    // TODO:
    // Decode instructions into control signals
    void decode(uint32_t instruction) {
        cout << "instruction " << instruction << "\n";
        // std::string binary = std::bitset<32>(instruction).to_string();
        
        int j = 2;
        string bits = "000000000000000000000000000000";
        for(int i=32; i>0; i--){
           if(instruction>(pow(j,(32-i))));
            string ins = instruction%pow((int)j,(i));
            bits[32-i] = ins;
            instruction = instruction/2;

       }

       cout << bits;
    }

};




#endif
