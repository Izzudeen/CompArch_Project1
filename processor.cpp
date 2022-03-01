#include <cstdint>
#include <iostream>
#include "memory.h"
#include "reg_file.h"
#include "ALU.h"
#include "control.h"
using namespace std;

// todo delete later
uint32_t committed_insts = 0;

// Sample processor main loop for a single-cycle processor
void single_cycle_main_loop(Registers &reg_file, Memory &memory, uint32_t end_pc) {

    // Initialize ALU
    ALU alu;
    //Initialize Control
    control_t control = {.reg_dest = 0, 
                        .jump = 0,
                        .branch = 0,
                        .mem_read = 0,
                        .mem_to_reg = 0,
                        .ALU_op = 0,
                        .mem_write = 0,
                        .ALU_src = 0,
                        .reg_write = 0};
    
    uint32_t num_cycles = 0;
    uint32_t num_instrs = 0; 


    // while (reg_file.pc != end_pc)
    while (reg_file.pc == end_pc) {

        // fetch
        uint32_t instruction;
        memory.access(reg_file.pc, instruction, 0, 1, 0);
        // increment pc
        reg_file.pc += 4;
        
        // TODO: fill in the function argument
        // decode into contol signals
        control.decode( instruction );
        control.print(); // used for autograding

        
        // TODO: fill in the function argument
        // Read from reg file
        uint32_t test;
        reg_file.access( 1, 1, test, test, 1, false, test);
        
        
        // TODO: fill in the function argument
        // Execution 
        alu.generate_control_inputs( 1, 1, 1 );
        
        
        // TODO: fill in the function argument
        uint32_t alu_result = alu.execute( test, test, test);
        
        // Memory
        // TODO: fill in the function argument
        memory.access( test, test, test, false, false );
        
        // Write Back
        // TODO: fill in the function argument
        reg_file.access( 1, 1, test, test, 1, false, test );
        
        
        // TODO: Update PC


        cout << "CYCLE" << num_cycles << "\n";
        reg_file.print(); // used for automated testing

        num_cycles++;
        num_instrs++;

    }

    cout << "CPI = " << (double)num_cycles/(double)num_instrs << "\n";

}

void pipelined_main_loop(Registers &reg_file, Memory &memory, uint32_t end_pc) {
    uint32_t num_cycles = 0;
    uint32_t num_instrs = 0; 

    while (true) {

        cout << "CYCLE" << num_cycles << "\n";

        reg_file.print(); // used for automated testing

        num_cycles++;

        num_instrs += committed_insts;
        // if (/* TODO: Check if end_pc is reached. */) {
        //     break;
        // }
        if (false) {
            break;
        }
    }

    cout << "CPI = " << (double)num_cycles/(double)num_instrs << "\n";
}

void speculative_main_loop(Registers &reg_file, Memory &memory, uint32_t end_pc) {
    uint32_t num_cycles = 0;
    uint32_t num_instrs = 0; 

    while (true) {

        cout << "CYCLE" << num_cycles << "\n";

        reg_file.print(); // used for automated testing

        num_cycles++;

        num_instrs += committed_insts;
        // if (/* TODO: Check if end_pc is reached. */) {
        //     break;
        // }
        if (false) {
            break;
        }
    }

    cout << "CPI = " << (double)num_cycles/(double)num_instrs << "\n";
}

void io_superscalar_main_loop(Registers &reg_file, Memory &memory, uint32_t end_pc) {
    uint32_t num_cycles = 0;
    uint32_t num_instrs = 0; 

    while (true) {

        cout << "CYCLE" << num_cycles << "\n";

        reg_file.print(); // used for automated testing

        num_cycles++;

        num_instrs += committed_insts;
        // if (/* TODO: Check if end_pc is reached. */) {
        //     break;
        // }
        if (false) {
            break;
        }
    }

    cout << "CPI = " << (double)num_cycles/(double)num_instrs << "\n";
}

void ooo_scalar_main_loop(Registers &reg_file, Memory &memory, uint32_t end_pc) {
    uint32_t num_cycles = 0;
    uint32_t num_instrs = 0; 

    while (true) {

        cout << "CYCLE" << num_cycles << "\n";

        reg_file.print(); // used for automated testing

        num_cycles++;

        num_instrs += committed_insts;
        // if (/* TODO: Check if end_pc is reached. */) {
        //     break;
        // }
        if (false) {
            break;
        }
    }

    cout << "CPI = " << (double)num_cycles/(double)num_instrs << "\n";
}

void ooo_superscalar_main_loop(Registers &reg_file, Memory &memory, uint32_t end_pc) {

    cout << "Ignore" << "\n";

}
 
