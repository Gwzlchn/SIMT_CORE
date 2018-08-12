#pragma once

#include<QObject>
#include<map>
#include<string>
#include<string>
class FUNC_UNIT_CLASS :public QObject {

	Q_OBJECT
public:
	enum FUNC_UNITS{MEMPIPE1 = 0, SFU1, SFU2, SFU3, SP1, SP2, SP3, SP4};
	Q_ENUM(FUNC_UNITS)
		static int get_enum_count();

};

typedef FUNC_UNIT_CLASS::FUNC_UNITS  FUNC_UNIT;




extern enum INS_OP;

extern std::map<INS_OP, int> INS_EX_CYCLE;

extern std::map<INS_OP, std::string> INS_FUNC_MAP;

extern std::map<FUNC_UNIT, int> FUNC_UNIT_CNT_MAP;


int get_func_cnt_from_func(FUNC_UNIT func);
std::string get_op_str_from_enum(INS_OP ins_op);

std::string get_func_str_from_enum(FUNC_UNIT func_occ);

INS_OP get_op_from_str(std::string);

int get_op_cycles(INS_OP);


extern std::map<INS_OP, std::string> INS_OP_MAP;