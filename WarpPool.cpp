#include "WarpPool.h"
#include <iostream>
#include<QTextStream>
#include<QDebug>

using namespace std;


int WARP_POOL::Threads_Per_Warp = 32;
int WARP_POOL::Can_Issue_Meantime = 2;
int WARP_POOL::Warps_Per_Poll = 4;








WARP_POOL::WARP_POOL()
{

    m_Cycle = 1;
    m_occupied_warps = 0;
    m_func_table = new FUNC_TABLE();
    launch_all_kernel();
    if(!m_all_warps_ins.empty())
        m_now_iter = m_all_warps_ins.begin();

}

WARP_POOL::WARP_POOL(std::vector<std::pair<std::string, int>> to_launch_kernels)
{
	m_Cycle = 1;
	m_occupied_warps = 0;
	m_func_table = new FUNC_TABLE();
	for (auto iter = to_launch_kernels.begin(); iter != to_launch_kernels.end(); iter++) {
		launch_one_kernel(QString::fromStdString(iter->first), iter->second);
	}
	if (!m_all_warps_ins.empty())
		m_now_iter = m_all_warps_ins.begin();
}










void WARP_POOL::launch_all_kernel(){
    qDebug()<<"INPUT ASM CODE FILE \t AND THREADS TO RUN"<<endl;
    QTextStream qtin(stdin);
    QString file_name = "ptx_ins.txt";
    QString threads_str="32";
    //qtin >> file_name;
    //qtin >> threads_str;
    int threads = threads_str.toInt();

    int n_warp = int(ceil(threads / Threads_Per_Warp));

    //launch_one_kernel(file_name,threads);

    file_name = "ptx_ins-1.txt";
    launch_one_kernel(file_name,threads);



//    while(file_name.compare("end")!=0 &&  n_warp <= Warps_Per_Poll){
//        qDebug()<<threads;


//        //qDebug()<<QString::fromUtf8("CONTINUE TO INPUT ASM CODE FILE \tend to stop \t AND THREADS TO RUN")<<endl;
//        //qtin >> file_name;
//        //qtin >> threads_str;
//        file_name="end";
//        threads = threads_str.toInt();
//        n_warp = int(ceil(threads / Threads_Per_Warp));

//    }
}



//返回>0 占据了多少个warp
int WARP_POOL::launch_one_kernel(QString ins_file_name, int threads){
    int n_warp = int(ceil(threads / Threads_Per_Warp));
    if(m_occupied_warps + n_warp > Warps_Per_Poll){
        return 0;
    }
    int last_warp_threads = threads - Threads_Per_Warp*(n_warp-1) ;
    for(int i = 1;i<=n_warp;i++){
        INS_ALL_PER_WARP* one_warp;
        if(i!=n_warp)
             one_warp = new INS_ALL_PER_WARP(ins_file_name,Threads_Per_Warp,m_func_table);
        if(i == n_warp)
            one_warp = new INS_ALL_PER_WARP(ins_file_name,last_warp_threads,m_func_table);
        m_all_warps_ins.push_back(*one_warp);
    }
    m_occupied_warps +=n_warp;
    return n_warp;
}




bool WARP_POOL::is_all_warps_done() const{

    for(int i=0;i<m_all_warps_ins.size();i++){
        if(!m_all_warps_ins[i].is_all_ins_done()){
            return false;
        }
    }
    return true;
}


void WARP_POOL::run_all_warp(){
    bool all_warps_not_yet = true;
    while(all_warps_not_yet){
        for(int i=0;i<m_all_warps_ins.size();i++){
            run_in_one_Cycle();
            if(is_all_warps_done()){
                all_warps_not_yet = false;
                break;
            }
        }
         m_Cycle++;
         for(int i=0;i<m_all_warps_ins.size();i++){
             m_all_warps_ins[i].clear_func_table(m_Cycle);
         }
    }
}


void WARP_POOL::run_in_one_Cycle(){
    //已流出的，必走下一个周期
	for (int i = 0; i < m_all_warps_ins.size(); i++) {
        if(m_all_warps_ins[i].have_issued_not_wb())
			m_all_warps_ins[i].go_to_this_cycle(m_Cycle);
    }

    //未流出的，循环优先级决定谁流出

    int this_cycle_issued = 0;

    std::vector<INS_ALL_PER_WARP>::iterator temp_iter = m_now_iter;
    for(;m_now_iter!=m_all_warps_ins.end();m_now_iter++){
        if(this_cycle_issued<Can_Issue_Meantime){
            m_now_iter->go_to_this_cycle(m_Cycle);
            if(m_now_iter->m_is_issued)
                this_cycle_issued++;
        }
        if(this_cycle_issued>=Can_Issue_Meantime){
            return;
        }
    }
    m_now_iter = m_all_warps_ins.begin();
    for(;m_now_iter!=temp_iter;m_now_iter++){
        if(this_cycle_issued<Can_Issue_Meantime){
            m_now_iter->go_to_this_cycle(m_Cycle);
            if(m_now_iter->m_is_issued)
                this_cycle_issued++;
        }
        if(this_cycle_issued>Can_Issue_Meantime){
            return;
        }
    }


    return;
}

