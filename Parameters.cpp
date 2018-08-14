
#include<QObject>
#include<map>
#include<string>
#include"Parameters.h"
#include<QMetaEnum>







const int Threads_Per_Warp = 32;
const int Can_Issue_Meantime = 2;
const int Warps_Per_Poll = 16;
const double I_Cache_Miss_Rate = 0.2;
const int I_Cache_Miss_Cycles = 20;

enum INS_OP {
	LD, ST, MULTD, SUBD, DIVD, ADDD
};


std::map<INS_OP, int> INS_EX_CYCLE{
	{ LD,20 },{ ST,4 },{ MULTD,20 },{ DIVD,40 },{ ADDD,4 },{ SUBD,10 }
};

std::map<INS_OP, std::string> INS_FUNC_MAP{
	{ LD,"MEMPIPE" },{ ST,"MEMPIPE" },
	{ MULTD,"SFU" },{ DIVD,"SFU" },
	{ ADDD,"SP" },{ SUBD,"SP" }
};

std::map<FUNC_UNIT, int> FUNC_UNIT_CNT_MAP{
	{ FUNC_UNIT_CLASS::MEMPIPE1,32 },{ FUNC_UNIT_CLASS::MEMPIPE2,32 },
	{ FUNC_UNIT_CLASS::SFU1,8 },{ FUNC_UNIT_CLASS::SFU2,16 },{ FUNC_UNIT_CLASS::SFU3,16 },
	{ FUNC_UNIT_CLASS::SP1,32 },{ FUNC_UNIT_CLASS::SP2,16 },{ FUNC_UNIT_CLASS::SP3,16 },{ FUNC_UNIT_CLASS::SP4,16 }
};





//不需要修改


std::map<INS_OP, std::string> INS_OP_MAP{
	{ LD,"LD" },{ ST,"ST" },{ MULTD,"MULTD" },{ SUBD,"SUBD" },{ DIVD,"DIVD" },{ ADDD,"ADDD" }
};









int get_func_cnt_from_func(FUNC_UNIT func) {
	auto it = FUNC_UNIT_CNT_MAP.find(func);
	return it->second;
}




std::string get_op_str_from_enum(INS_OP ins_op) {
	auto iter = INS_FUNC_MAP.find(ins_op);
	return iter->second;

}



INS_OP get_op_from_str(std::string op_str) {
	auto it2 = std::find_if(INS_OP_MAP.begin(), INS_OP_MAP.end(), [op_str](auto item)
	{
		return item.second == op_str;
	});
	if (it2 != INS_OP_MAP.end())
		return  it2->first;
}



std::string get_func_str_from_enum(FUNC_UNIT func_occ) {
	QMetaEnum func_enum = QMetaEnum::fromType<FUNC_UNIT>();
	return   std::string(func_enum.valueToKey(func_occ));

}


int FUNC_UNIT_CLASS::get_enum_count()
{
	return  QMetaEnum::fromType<FUNC_UNIT>().keyCount();
}


int get_op_cycles(INS_OP ins_op) {
	auto it3 = INS_EX_CYCLE.find(ins_op);
	return it3->second;
}




bool is_cache_hint() {
	return ((double)rand() / RAND_MAX > I_Cache_Miss_Rate) ? true : false;
}