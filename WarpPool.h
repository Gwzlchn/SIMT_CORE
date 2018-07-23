#ifndef WARPPOOL_H
#define WARPPOOL_H


#include"Instruction.h"





class WARP_POOL
{
private:
    std::vector<INS_ALL_PER_WARP> warps_ins_all;
    static const int Threads_Per_Warp = 32;
    static const int Warps_Per_Poll = 16;
    int m_Cycle;

public:
    WARP_POOL();
    void run_all_warp();
    void launch_one_kernel(QString ins_file_name,int threads);

};

#endif // WARPPOLL_H
