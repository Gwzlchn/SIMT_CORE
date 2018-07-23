#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include<string>

#include<map>
#include<QString>
#include<vector>
#include"FunctionUnits.h"


enum INS_OP{
    LD ,ST,MULTD,SUBD,DIVD,ADDD
};
extern std::map<INS_OP,std::string> INS_OP_MAP;



//寄存器、指令周期不允许修改
enum REGISTER{
    F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,R1,R2,R3,R4
};

extern std::map<REGISTER,std::string> REGISTER_MAP;

enum STAGE{
    IS ,OC,EX,WB
};
extern std::map<STAGE,std::string> STAGE_MAP;



//指令执行周期
extern std::map<INS_OP,int> INS_EX_CYCLE;





struct INSTRUCTION
{
    int ins_cycle;
    INS_OP ins_op;
    REGISTER ins_dst;
    REGISTER ins_src1;
    REGISTER ins_src2;

    INSTRUCTION(QString one_ins);
    void set_one_ins(std::string one_ins_op,std::string one_ins_dst,std::string one_ins_src1,std::string one_ins_src2);
    void print_one_ins();
};



class INS_ONE_LINE{

public:
    INSTRUCTION *m_one_ins;
    FUNC_UNIT m_func_unit;
    bool m_is_ex;
    int m_issue_time;
    int m_oc_time;
    int m_ex_time;
    int m_wb_time;

    int m_extra_ex_time;

    INS_ONE_LINE(QString one_line);
    void print_one_ins_time();

    void set_all_time(bool n_can_issue,bool n_can_oc,
                      bool n_can_wb,int now_cycle);


};

class INS_ALL_PER_WARP{
private:
    //寄存器一共14个
   vector<int> m_reg_status;
    std::vector<INS_ONE_LINE> m_ins_table;
    FUNC_TABLE* m_func_table;
    int m_threads_per_warp;

public:
    bool m_is_issued;
    //INS_ALL_PER_WARP(QString file_name);
    bool is_all_ins_done();
    INS_ALL_PER_WARP(QString file_name,int thread_per_warp);
    void read_all_ins_from_file(QString file_name, int threads_pre_warp);
    bool n_th_ins_can_issue(int n, int now_cycle);
    bool n_th_ins_can_oc(int n, int now_cycle);
    bool n_th_ins_can_wb(int n, int now_cycle);
    void go_to_this_cycle(int now_cycle);
    void print_all_ins_table();
    //记录当前第n周期
    //int m_now_cycle;
};
#endif // INSTRUCTIONS_H
