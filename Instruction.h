#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include<string>

#include<map>
#include<QString>
#include<vector>

//唯一允许修改的，功能部件个数
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


class INSTRUCTIONS_ALL{
private:
    std::vector<INSTRUCTION> all_instrucs;
public:
    INSTRUCTIONS_ALL(QString file_name);

    void print_all_ins();
};




class INS_TIME_TALBE_ONE_LINE{

public:
    INSTRUCTION *one_ins;



    int m_issue_time;
    int m_oc_time;
    int m_ex_time;
    int m_wb_time;
    void go_to_next_cycle(bool );
};


#endif // INSTRUCTIONS_H
