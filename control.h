#ifndef CONTROL_CLASS
#define CONTROL_CLASS
#include <vector>
#include <cstdint>
#include <iostream>
#include <math.h>
using namespace std;

// Control signals for the processor
struct control_t {
    bool reg_dest;           // 0 if rt, 1 if rd
    bool jump;               // 1 if jummp
    bool branch;             // 1 if branch
    bool mem_read;           // 1 if memory needs to be read
    unsigned mem_to_reg: 2;  // 00 if wirint ALU result (no mem access), 01 if memory needs to written to reg, 10 is JAL instruction
    unsigned ALU_op : 2;     // 10 for R-type, 00 for LW/SW/JR, 01 for BEQ/BNE, 11 for others
    bool mem_write;          // 1 if needs to be written to memory
    unsigned ALU_src: 2;     // 00 if second operand is from reg_file, 01 if imm, 10 if unsigned imm
    bool reg_write;          // 1 if need to write back to reg file

    bool jump_register;      // 1 if JR
    bool bne;                // 1 if BNE
    unsigned load_size : 2;  // 00 for Load Byte, 01 for Load Halfword, and 10 for Load Word
    bool lui;                // 1 if lui

    
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
        cout << "LUI: " << lui << "\n";
    }
    // TODO:
    // Decode instructions into control signals
    void decode(uint32_t instruction) {
        cout << "Instruction: " << "\n";

        instruction = 156;
        // std::cout << std::hex << 156 << "\n";

        // extract segment
        int opcode = instruction >> 26;
        int rs = instruction << 6 >> 27;
        int rt = instruction << 11 >> 27;
        int rd = instruction << 16 >> 27;
        int shamt = instruction << 21 >> 27;
        int funct = instruction << 26 >> 26;
        int immediate = instruction << 16 >> 16;
        int address = instruction << 6 >> 6;

        // compare to existing opcodes (switch statement)
        if (opcode == 0) { // R-type (JR and shift are special cases)
            if (funct == 8) { // JR
                jump_register = 1;
                reg_write = 0;
                reg_dest = 0;
                ALU_op = 00;
                jump = 0;
            }
            // else if (funct == 0) { // shift left logical

            // }
            // else if (funct == 2) { // shift right logical

            // } 
            else { // all other R-types
                mem_read = 0;
                mem_write = 0;
                reg_dest = 1;
                ALU_src = 0;
                reg_write = 1;
                ALU_op = 2;
            }
        } else if (opcode == 2) { // J
            jump = 1;
            jump_register = 0;
        } else if (opcode == 3) { // JAL
            jump = 1;
            jump_register = 0;
            mem_to_reg = 2;
            lui = 0;
        }
        else { // I-type (branch, store, load, others)
            if (opcode == 4) { //BEQ
                branch = 1;
                bne = 0;
                ALU_src = 0;
                ALU_op = 1; 
                jump = 0;
                jump_register = 0;
            } else if (opcode == 5) { // BNE
                branch = 0;
                bne = 1;
                ALU_src = 0;
                ALU_op = 1; 
                jump = 0;
                jump_register = 0;
            } else if (opcode == 40 | opcode == 41 | opcode == 43) { // stores
                ALU_src = 1;
                reg_write = 0;
                mem_read = 0;
                mem_write = 1;
                branch = 0;
                ALU_op = 0;
            } else if (opcode == 35 | opcode == 37 | opcode == 36) { // loads
                if (opcode == 35) { // load word
                    ALU_src = 1;
                    reg_write = 1;
                    mem_read = 1;
                    mem_write = 0;
                    branch = 0;
                    ALU_op = 0;
                    reg_dest = 0;
                    mem_to_reg = 1;
                    load_size = 2;
                } else if (opcode == 37) { // load halfword
                    ALU_src = 2;
                    reg_write = 1;
                    mem_read = 1;
                    mem_write = 0;
                    branch = 0;
                    ALU_op = 0;
                    reg_dest = 0;
                    mem_to_reg = 1;
                    load_size = 1;
                } else { // load byte
                    ALU_src = 2;
                    reg_write = 1;
                    mem_read = 1;
                    mem_write = 0;
                    branch = 0;
                    ALU_op = 0;
                    reg_dest = 0;
                    mem_to_reg = 1;
                    load_size = 0;
                }
            }
        }


    }

};




#endif
