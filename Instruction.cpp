#include "Instruction.h"
#include<QFile>
#include<QStringList>
#include<QTextStream>
#include<iostream>

std::map<REGISTER,std::string> REGISTER_MAP{
    {F1,"F1"},{F2,"F2"},{F3,"F3"},{F4,"F4"},{F5,"F5"},
    {F6,"F6"},{F7,"F7"},{F8,"F8"},{F9,"F9"},{F10,"F10"},
    {R1,"R1"},{R2,"R2"},{R3,"R3"},{R4,"R4"}
};

std::map<STAGE,std::string> STAGE_MAP{
    {IS,"IS"},{OC,"OC"},{EX,"EX"},{WB,"WB"}
};
std::map<INS_OP,std::string> INS_OP_MAP{
    {LD,"LD"},{ST,"ST"},{MULTD,"MULTD"},{SUBD,"SUBD"},{DIVD,"DIVD"},{ADDD,"ADDD"}
};
std::map<INS_OP,int> INS_EX_CYCLE{
    {LD,2},{ST,4},{MULTD,20},{DIVD,40},{ADDD,10},{SUBD,10}
};




INSTRUCTION::INSTRUCTION(QString one_ins)
{

    std::string ins_op_str = one_ins.section(' ',0,0).toStdString();
    std::string ins_dst_str =  one_ins.section(' ',1,1).section(',',0,0).toStdString();
    std::string ins_src1_str = one_ins.section(' ',1,1).section(',',1,1).toStdString();
    std::string ins_src2_str =one_ins.section(' ',1,1).section(',',2,2).toStdString();
   /* ins_dst = R4;
    ins_src1 = R4;
    ins_src2 = R4;
    ins_op = MULTD;*/
    this->set_one_ins(ins_op_str,ins_dst_str,ins_src1_str,ins_src2_str);
}

void INSTRUCTION::set_one_ins(std::string one_ins_op, std::string one_ins_dst, std::string one_ins_src1, std::string one_ins_src2){

    auto it = REGISTER_MAP.end();
    it = std::find_if(REGISTER_MAP.begin(), REGISTER_MAP.end(), [one_ins_dst](auto item)
       {
           return item.second == one_ins_dst;
       });
    if (it!=REGISTER_MAP.end())
        ins_dst = (*it).first;

    it = std::find_if(REGISTER_MAP.begin(), REGISTER_MAP.end(), [one_ins_src1](auto item)
       {
           return item.second == one_ins_src1;
       });
    if (it!=REGISTER_MAP.end())
        ins_src1 = (*it).first;

    auto it4 = REGISTER_MAP.end();
    it4 = std::find_if(REGISTER_MAP.begin(), REGISTER_MAP.end(), [one_ins_src2](auto item)
       {
           return item.second == one_ins_src2;
       });
    if (it4!=REGISTER_MAP.end())
        ins_src2 = (*it4).first;


    auto it2 =std::find_if(INS_OP_MAP.begin(), INS_OP_MAP.end(), [one_ins_op](auto item)
    {
        return item.second == one_ins_op;
    });
    if (it2!=INS_OP_MAP.end())
        ins_op = (*it2).first;



    auto it3 =INS_EX_CYCLE.find(ins_op);
    ins_cycle = (*it3).second;
}

void INSTRUCTION::print_one_ins(){
    std::cout<<"ENUM type: " <<" OP "<<ins_op <<"\tCYCLES: "<<ins_cycle<<"\t dst: "<<ins_dst<<"\t src1 "<<ins_src1<<"\t src2 "<<ins_src2<<std::endl;
}

INSTRUCTIONS_ALL::INSTRUCTIONS_ALL(QString file_name){
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);

       INSTRUCTION* one_ins = new INSTRUCTION(str.simplified());
       all_instrucs.push_back(*one_ins);
    }
    file.close();
}


void INSTRUCTIONS_ALL::print_all_ins(){
    for(INSTRUCTION  i:all_instrucs){
        i.print_one_ins();
    }
}
