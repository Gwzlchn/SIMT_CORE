#include "FunctionUnits.h"



bool FUNC_TABLE::is_func_unit_valid(FUNC_UNIT now_op){
    if(m_func_table[now_op][Busy] == 0)
        return true;
}


void FUNC_TABLE::occupy_func_table_one(FUNC_UNIT to_occupy, INSTRUCTION now_ins){
    m_func_table[to_occupy][Busy] = 1;
    m_func_table[to_occupy][Op] = now_ins.ins_op;
    m_func_table[to_occupy][Fi] = now_ins.ins_dst;
    m_func_table[to_occupy][Fj] = now_ins.ins_src1;
    m_func_table[to_occupy][Fk] = now_ins.ins_src2;
    m_func_table[to_occupy][Rj] = 0;
    m_func_table[to_occupy][Rk] = 0;
}
