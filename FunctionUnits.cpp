#include "FunctionUnits.h"
#include"Instruction.h"




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
