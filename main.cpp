
#include <iostream>
#include<Instruction.h>

int main(int argc, char *argv[]) {

    INS_ALL_PER_WARP* ins = new INS_ALL_PER_WARP("ptx_ins.txt",32);
    ins->print_all_ins_table();
    ins->go_to_this_cycle(1);
    ins->print_all_ins_table();


    return 0;
}
