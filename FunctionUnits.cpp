#include "FunctionUnits.h"
#include"Instruction.h"
#include<iostream>
#include<QMetaObject>
#include<QMetaEnum>

std::map<INS_OP,std::string> INS_FUNC_MAP{
	{LD,"MEMPIPE"},{ST,"MEMPIPE"},
	{MULTD,"SFU"},{DIVD,"SFU"},
	{ADDD,"SP"},{SUBD,"SP"}
};

map<FUNC_UNIT, int> FUNC_UNIT_CNT_MAP{
	{ FUNC_UNIT_CLASS::MEMPIPE1,32 },
	{ FUNC_UNIT_CLASS::SFU1,8 },{ FUNC_UNIT_CLASS::SFU2,16 },{ FUNC_UNIT_CLASS::SFU3,16 },
	{ FUNC_UNIT_CLASS::SP1,32 },{ FUNC_UNIT_CLASS::SP2,16 },{ FUNC_UNIT_CLASS::SP3,16 }
};





FUNC_TABLE:: FUNC_TABLE(){
	int func_count = QMetaEnum::fromType<FUNC_UNIT>().keyCount();
   m_func_table = vector<vector<int>>(func_count,vector<int>(9));
}


void FUNC_TABLE::print_func_table_busy_bit()
{
	for (auto iter = m_func_table.begin(); iter != m_func_table.end(); iter++) {
		std::cout << (*iter)[Busy] << "\t";
	}
	std::cout << std::endl;
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
	m_func_table[to_clr][Op] = 0;
	m_func_table[to_clr][Fi] = 0;
	m_func_table[to_clr][Fj] = 0;
	m_func_table[to_clr][Fk] = 0;
	m_func_table[to_clr][Rj] = 0;
	m_func_table[to_clr][Rk] = 0;
    return;
}




int FUNC_TABLE::get_extra_ex_time(FUNC_UNIT now_func_unit, int threads_per_warp){
    if(threads_per_warp == 0)
        return 0;

    auto it = FUNC_UNIT_CNT_MAP.find(now_func_unit);
    int now_op_cnt = (*it).second;
    double extra_ex = (threads_per_warp / double(now_op_cnt))  -1;
    return int(ceil(extra_ex));
}

bool FUNC_TABLE::find_func_unit_valid(INS_OP ins_op, FUNC_UNIT & to_occ)
{
	QMetaEnum func_enum = QMetaEnum::fromType<FUNC_UNIT>();
	int func_count =func_enum.keyCount();

	auto iter = INS_FUNC_MAP.find(ins_op);
	QString op_str = QString::fromStdString(iter->second);

	for (int i = 0; i < func_count; i++) {
		FUNC_UNIT now_unit = FUNC_UNIT(func_enum.value(i));
		QString now_func = QString::fromLocal8Bit(func_enum.valueToKey(i));
		now_func.chop(1);
		if (now_func == op_str && is_func_unit_valid(now_unit)) {
			to_occ = now_unit;
			return true;
		}
	}

	
	
	
	return false;
}
