#ifndef FUNC_UNITS_H
#define FUNC_UNITS_H

#include"Instruction.h"
enum FUNC_UNIT{
    INTEGER=0,MULT1,MULT2,ADD1,ADD2,DIVIDE1
};


enum FUNC_TABLE_PART{
    Busy=0,Op,Fi,Fj,Fk,Qj,Qk,Rj,Rk
};


class FUNC_TABLE{

    int m_func_table[6][9]={0};
public:

    bool is_func_unit_valid(FUNC_UNIT now_op);
    void occupy_func_table_one(FUNC_UNIT to_occupy,INSTRUCTION now_ins);

}







#endif // FUNC_UNITS_H
