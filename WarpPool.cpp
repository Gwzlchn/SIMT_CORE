﻿#include "WarpPool.h"
#include <iostream>
#include<QTextStream>
#include<QDebug>
#include<QMetaEnum>
using namespace std;


int WARP_POOL::m_Threads_Per_Warp = Threads_Per_Warp;
int WARP_POOL::m_Can_Issue_Meantime = Can_Issue_Meantime;
int WARP_POOL::m_Warps_Per_Poll = Warps_Per_Poll;








WARP_POOL::WARP_POOL()
{

    m_Cycle = 0;
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
    int n_warp = (int)(ceil((double)threads / Threads_Per_Warp));
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

void WARP_POOL::print_cycles_occ_func_all_warp()
{
	int func_count = FUNC_UNIT_CLASS::get_enum_count();
	vector<std::pair<int, int>> total_cycles(func_count), temp_cycles(func_count);

	for (auto iter = m_all_warps_ins.begin(); iter != m_all_warps_ins.end(); iter++) {
		iter->get_cycles_occ_func_per_warp(temp_cycles,func_count);
		add_two_vec_pair(total_cycles, temp_cycles);

	}

	for (auto iter = total_cycles.begin(); iter != total_cycles.end(); iter++) {
		cout << iter->first << "\t" << iter->second << endl;
	}

	



}


void WARP_POOL::add_two_vec_pair(vector<std::pair<int, int>>& dst, const vector<std::pair<int, int>>& src) {
	auto srciter = src.begin();
	for (auto iter = dst.begin(); iter != dst.end(); iter++,srciter++) {
		iter->first += srciter->first;
		iter->second += srciter->second;
	}
	return;
}



void WARP_POOL::run_all_warp(){
    //bool all_warps_not_yet = true;
    while(!is_all_warps_done()){
        for(int i=0;i<m_all_warps_ins.size();i++){
            run_in_one_Cycle();
            
        }
         m_Cycle++;
         for(int i=0;i<m_all_warps_ins.size();i++){
             m_all_warps_ins[i].clear_func_table(m_Cycle);
         }
		 this->m_func_table->print_func_table_busy_bit();
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
	//记录之前被循环调度的最后一个Warp指针
    auto temp_iter = m_now_iter;
	//从该Warp走到最后一个Warp指针，轮询是否有可以流出的
	//如果当前流出的Warp数大于每周期可同时流出总数，则返回
	//(一个Warp一个周期之能流出一条指令)
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
	//从第一个Warp轮询到临时Warp指针的前一个,实现循环优先级
	//如果当前流出的Warp数大于每周期可同时流出总数，则返回
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


void WARP_POOL::print_all_warp() {
	for (auto iter = m_all_warps_ins.begin(); iter != m_all_warps_ins.end(); iter++) {
		iter->print_all_ins_table();
		std::cout << std::endl;
	}
}