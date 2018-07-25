
#include <iostream>
#include<Instruction.h>
#include"WarpPool.h"
#include<QDebug>
#include<QTextStream>
int main(int argc, char *argv[]) {





    /*qDebug()<<"INPUT ASM CODE FILE \t AND THREADS TO RUN"<<endl;
    QTextStream qtin(stdin);
    QString file_name;
    QString threads_str;
    qtin >> file_name;
    qtin >> threads_str;
    int threads = threads_str.toInt();


    while(file_name !="end" ){

        qDebug()<<QString::fromUtf8("CONTINUE TO INPUT ASM CODE FILE \tend to stop \t AND THREADS TO RUN")<<endl;
        qtin >> file_name;
        qtin >> threads_str;
        threads = threads_str.toInt();


    }*/
    //INS_ALL_PER_WARP* ins = new INS_ALL_PER_WARP("ptx_ins.txt",32);
    //ins->print_all_ins_table();
    //ins->go_to_this_cycle(1);
    //ins->print_all_ins_table();



	WARP_POOL* pool = new WARP_POOL({
		{"ptx_ins.txt",32} });
    pool->run_all_warp();

    return 0;
}
