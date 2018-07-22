
#include <iostream>
#include<Instruction.h>

int main(int argc, char *argv[]) {

    INSTRUCTIONS_ALL* ins_all =new INSTRUCTIONS_ALL("ptx_ins.txt");

    ins_all->print_all_ins();


    return 0;
}
