
#include <iostream>
#include<Instruction.h>

int main(int argc, char *argv[]) {

    INS_TIME_TABLE* ins = new INS_TIME_TABLE("ptx_ins.txt");
    ins->print_all_ins_table();
    ins->go_to_next_cycle();
    ins->print_all_ins_table();


    return 0;
}
