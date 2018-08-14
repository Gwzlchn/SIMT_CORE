#ifndef WARPPOOL_H
#define WARPPOOL_H


#include"Instruction.h"
#include"FunctionUnits.h"
#include"Parameters.h"



class WARP_POOL
{
public:
    static  int m_Threads_Per_Warp ;
    static  int m_Warps_Per_Poll ;
    static  int m_Can_Issue_Meantime ;


private:
    std::vector<INS_ALL_PER_WARP> m_all_warps_ins;
    std::vector<INS_ALL_PER_WARP>::iterator m_now_iter;

    int m_Cycle;
    int m_occupied_warps;

    FUNC_TABLE* m_func_table;


public:
    WARP_POOL();
	WARP_POOL(std::vector<std::pair<std::string, int>> to_launch_kernels);
    void run_all_warp();
    int launch_one_kernel(QString ins_file_name,int threads);
    void launch_all_kernel();
    void run_in_one_Cycle();
    bool is_all_warps_done() const;

	void print_cycles_occ_func_all_warp();
	void add_two_vec_pair(vector<std::pair<int, int>>& dst, const vector<std::pair<int, int>>& src);
	void print_all_warp();

};

#endif // WARPPOLL_H
