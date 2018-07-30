#ifndef FUNC_UNITS_H
#define FUNC_UNITS_H


#include<vector>
#include<map>
#include<QObject>

using std::map;
using std::vector;
struct INSTRUCTION;


//唯一允许修改的，功能部件个数
enum INS_OP {
	LD, ST, MULTD, SUBD, DIVD, ADDD
};




class FUNC_UNIT_CLASS :public QObject {

	Q_OBJECT
public:
	enum FUNC_UNITS{
    MEMPIPE1=0,SFU1,SFU2,SFU3,SP1,SP2,SP3
	};
	Q_ENUM(FUNC_UNITS)

};


typedef FUNC_UNIT_CLASS::FUNC_UNITS  FUNC_UNIT;

extern map<FUNC_UNIT, int> FUNC_UNIT_CNT_MAP;





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
