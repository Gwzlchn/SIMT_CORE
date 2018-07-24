#ifndef WARPPOOL_H
#define WARPPOOL_H


#include"Instruction.h"
#include"FunctionUnits.h"




class WARP_POOL
{
public:
    static  int Threads_Per_Warp ;
    static  int Warps_Per_Poll ;
    static  int Can_Issue_Meantime ;


private:
    std::vector<INS_ALL_PER_WARP> m_all_warps_ins;
    std::vector<INS_ALL_PER_WARP>::iterator m_now_iter;

    int m_Cycle;
    int m_occupied_warps;

    FUNC_TABLE* m_func_table;


public:
    WARP_POOL();
    void run_all_warp();
    int launch_one_kernel(QString ins_file_name,int threads);
    void launch_all_kernel();
    void run_in_one_Cycle();
    bool is_all_warps_done() const;

};

#endif // WARPPOLL_H
