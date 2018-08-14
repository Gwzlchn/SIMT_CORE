

#include <iostream>
#include<Instruction.h>
#include"WarpPool.h"
#include<QDebug>
#include<QTextStream>

int main(int argc, char *argv[]) {

	/*
	BETTER_ENUM(Channel, int, Red, Green = 2, Blue)
	for (size_t index = 0; index < Channel::_size(); ++index) {
		const char  *name = Channel::_names()[index];
		std::cout << name << " ";
	}
	std::cout << std::endl;*/


	WARP_POOL* pool = new WARP_POOL({
		{"ptx_ins.txt",64},{"ptx_ins-1.txt",64}
	 });
    pool->run_all_warp();
	std::cout << "真占用周期\t" << "假占用周期\n";
	pool->print_cycles_occ_func_all_warp();
	pool->print_all_warp();
	system("pause");
    return 0;
}
