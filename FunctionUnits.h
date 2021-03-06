#ifndef FUNC_UNITS_H
#define FUNC_UNITS_H


#include<vector>
#include<map>
#include<QObject>
#include"Parameters.h"

using std::map;
using std::vector;
struct INSTRUCTION;







enum FUNC_UNIT_STATE{
    Busy=0,Op,Fi,Fj,Fk,Qj,Qk,Rj,Rk
};


class FUNC_TABLE{

    vector<vector<int>> m_func_table;
public:

    FUNC_TABLE();

	void print_func_table_busy_bit();
    bool is_func_unit_valid(FUNC_UNIT now_op);
    void occupy_func_table_one(FUNC_UNIT to_occupy,INSTRUCTION* now_ins);

    int get_table_Rj(FUNC_UNIT now_func_unit);
    int get_table_Rk(FUNC_UNIT now_func_unit);
    void set_table_Rj(FUNC_UNIT now_func_unit, int to_set);
    void set_table_Rk(FUNC_UNIT now_func_unit,int to_set);

    void clear_func_one_line(FUNC_UNIT to_clr);

    int get_extra_ex_time(FUNC_UNIT now_func_unit,int threads_per_warp);

	bool find_func_unit_valid(INS_OP ins_op, FUNC_UNIT& to_occ);
};






#endif // FUNC_UNITS_H
