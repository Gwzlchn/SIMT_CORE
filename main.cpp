
#include <iostream>
#include<Instruction.h>
#include"WarpPool.h"
#include<QDebug>
#include<QTextStream>
int main(int argc, char *argv[]) {




	WARP_POOL* pool = new WARP_POOL({
		{"ptx_ins.txt",32} ,
	 });
    pool->run_all_warp();
	pool->print_cycles_occ_func_all_warp();

    return 0;
}
