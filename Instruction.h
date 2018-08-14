#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include<string>

#include<map>
#include<QString>
#include<vector>
#include"FunctionUnits.h"
#include"Parameters.h"





//寄存器、指令周期不允许修改
enum REGISTER{
    F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,R0,R1,R2,R3,R4
};

extern std::map<REGISTER,std::string> REGISTER_MAP;




//指令执行周期






struct INSTRUCTION
{
    int ins_cycle;
    INS_OP ins_op;
    REGISTER ins_dst;
    REGISTER ins_src1;
    REGISTER ins_src2;
	std::string ins_op_str, ins_dst_str, ins_src1_str, ins_src2_str;
    INSTRUCTION(QString one_ins);
    void set_one_ins(std::string one_ins_op,std::string one_ins_dst,std::string one_ins_src1,std::string one_ins_src2);
    void print_one_ins() const;
	REGISTER get_reg_from_str(std::string);
};

//部件号 真 假
typedef std::pair<int, std::pair<int, int>>  FUNC_TRUE_ALL;

class INS_ONE_LINE{

public:
    INSTRUCTION *m_one_ins;
    mutable FUNC_UNIT m_func_unit;
    bool m_is_ex;
	bool is_active() const ;
    int m_issue_time;
    int m_oc_time;
    int m_ex_time;
    int m_wb_time;

	mutable int m_waw_wait_time;
	mutable int m_func_unit_wait_time;
	int m_raw_wait_time;
	int m_war_wait_time;

	mutable std::string m_occ_func_unit;
	mutable int m_extra_wait_in_pipe;
	mutable bool m_i_cache_hint;
	mutable int m_i_cache_wait_time;

    INS_ONE_LINE(QString one_line);
    void print_one_ins_time() const;

    void set_all_time(bool n_can_issue,bool n_can_oc,
                      bool n_can_wb,int now_cycle);




	//计算占用部件周期数
	//真占用 假占用
	FUNC_TRUE_ALL get_cycles_occ_func_unit() const;


};

class INS_ALL_PER_WARP{
private:
    //寄存器一共14个
    vector<int> m_reg_status;
    std::vector<INS_ONE_LINE> m_ins_table;
    FUNC_TABLE* m_func_table;
    int m_active_threads_this_warp;

	int m_now_cycle;
	bool m_cycle_changed;
public:

    INS_ALL_PER_WARP(const QString& file_name,int thread_per_warp, FUNC_TABLE* func_in_pool);
    bool m_is_issued;
    //INS_ALL_PER_WARP(QString file_name);
    bool is_all_ins_done()const;
    bool is_all_ins_issued() const;
    bool have_issued_not_wb() const;

    void read_all_ins_from_file(QString file_name);
    bool n_th_ins_can_issue(int n, int now_cycle) const;
    bool n_th_ins_can_oc(int n, int now_cycle)  const;
    bool n_th_ins_can_wb(int n, int now_cycle) const ;
    void go_to_this_cycle(int now_cycle);
    void print_all_ins_table() const;

	void get_cycles_occ_func_per_warp(vector<std::pair<int, int>>& cycles_true_all_per_warp, int size);

    void clear_func_table(int now_cycles);
    int active_threads_this_warp() const;
    void setActive_threads_this_warp(int active_threads_this_warp);

};
#endif // INSTRUCTIONS_H
