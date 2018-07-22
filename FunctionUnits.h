#ifndef FUNC_UNITS_H
#define FUNC_UNITS_H


#include<vector>
using std::vector;
struct INSTRUCTION;

enum FUNC_UNIT{
    INTEGER=0,MULT1,MULT2,ADD1,ADD2,DIVIDE1
};


enum FUNC_UNIT_STATE{
    Busy=0,Op,Fi,Fj,Fk,Qj,Qk,Rj,Rk
};


class FUNC_TABLE{

    vector<vector<int>> m_func_table;
public:
    FUNC_TABLE();
    bool is_func_unit_valid(FUNC_UNIT now_op);
    void occupy_func_table_one(FUNC_UNIT to_occupy,INSTRUCTION* now_ins);

    int get_table_Rj(FUNC_UNIT now_func_unit);
    int get_table_Rk(FUNC_UNIT now_func_unit);
    void set_table_Rj(FUNC_UNIT now_func_unit, int to_set);
    void set_table_Rk(FUNC_UNIT now_func_unit,int to_set);

    void clear_func_one_line(FUNC_UNIT to_clr);


};






#endif // FUNC_UNITS_H
