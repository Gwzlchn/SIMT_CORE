#include "FunctionUnits.h"
#include"Instruction.h"


map<FUNC_UNIT,int> FUNC_UNIT_CNT_MAP{
    {INTEGER,16},{MULT1,8},{MULT2,16},{ADD1,32},{ADD2,16},{DIVIDE1,16}
};


FUNC_TABLE:: FUNC_TABLE(){
   m_func_table = vector<vector<int>>(6,vector<int>(9));
}


bool FUNC_TABLE::is_func_unit_valid(FUNC_UNIT now_op){
    if(m_func_table[now_op][Busy] == 0)
        return true;
    return false;
}


void FUNC_TABLE::occupy_func_table_one(FUNC_UNIT to_occupy, INSTRUCTION* now_ins){
    m_func_table[to_occupy][Busy] = 1;
    m_func_table[to_occupy][Op] = now_ins->ins_op;
    m_func_table[to_occupy][Fi] = now_ins->ins_dst;
    m_func_table[to_occupy][Fj] = now_ins->ins_src1;
    m_func_table[to_occupy][Fk] = now_ins->ins_src2;
    m_func_table[to_occupy][Rj] = 0;
    m_func_table[to_occupy][Rk] = 0;
}


int FUNC_TABLE::get_table_Rj(FUNC_UNIT now_func_unit){
   return m_func_table[now_func_unit][Rj];
}

int FUNC_TABLE::get_table_Rk(FUNC_UNIT now_func_unit){
   return m_func_table[now_func_unit][Rk];
}

void FUNC_TABLE::set_table_Rj(FUNC_UNIT now_func_unit,int to_set){
    if(to_set==0 || to_set == 1)
        m_func_table[now_func_unit][Rj] = to_set;
    return;
}


void FUNC_TABLE::set_table_Rk(FUNC_UNIT now_func_unit,int to_set){
    if(to_set==0 || to_set == 1)
        m_func_table[now_func_unit][Rk] = to_set;
    return;
}


void FUNC_TABLE::clear_func_one_line(FUNC_UNIT to_clr){
    m_func_table[to_clr][Busy] = 0;
    return;
}




int FUNC_TABLE::get_extra_ex_time(FUNC_UNIT now_func_unit, int threads_per_warp){
    auto it = FUNC_UNIT_CNT_MAP.find(now_func_unit);
    int now_op_cnt = (*it).second;
    double extra_ex = (threads_per_warp / double(now_op_cnt))  -1;
    return int(ceil(extra_ex));
}
