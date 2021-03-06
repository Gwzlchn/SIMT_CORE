#include "Instruction.h"
#include "FunctionUnits.h"
#include<QFile>
#include<QDebug>
#include<QStringList>
#include<QTextStream>
#include<iostream>



using std::cout;
using std::endl;


std::map<REGISTER,std::string> REGISTER_MAP{
    {F1,"F1"},{F2,"F2"},{F3,"F3"},{F4,"F4"},{F5,"F5"},
    {F6,"F6"},{F7,"F7"},{F8,"F8"},{F9,"F9"},{F10,"F10"},
	{R0,"R1"}, {R1,"R1"},{R2,"R2"},{R3,"R3"},{R4,"R4"}
};





INSTRUCTION::INSTRUCTION(QString one_ins)
{
    one_ins = one_ins.simplified();
    std::string ins_op_str = one_ins.section(' ',0,0).toStdString();
    std::string ins_dst_str =  one_ins.section(' ',1,1).section(',',0,0).toStdString();
    std::string ins_src1_str = one_ins.section(' ',1,1).section(',',1,1).toStdString();
    std::string ins_src2_str =one_ins.section(' ',1,1).section(',',2,2).toStdString();
    
    this->set_one_ins(ins_op_str,ins_dst_str,ins_src1_str,ins_src2_str);
}

void INSTRUCTION::set_one_ins(std::string one_ins_op, std::string one_ins_dst, std::string one_ins_src1, std::string one_ins_src2){

	ins_dst = get_reg_from_str(one_ins_dst);
	ins_src1 = get_reg_from_str(one_ins_src1);
	ins_src2 = get_reg_from_str(one_ins_src2);

	ins_op = get_op_from_str(one_ins_op);


	ins_cycle = get_op_cycles(ins_op);
	//ins_cycle = 1;

	//为了好看
	ins_op_str = one_ins_op;
	ins_dst_str = one_ins_dst;
	ins_src1_str = one_ins_src1;
	ins_src2_str = one_ins_src2;



}

void INSTRUCTION::print_one_ins() const{
    std::cout<<"ENUM type: " <<" OP "<<ins_op_str <<" CYCLES:"<<ins_cycle<<" dst:"<<ins_dst_str<<" src1:"<<ins_src1_str<<"src2:"<<ins_src2_str<<"\t";
}

REGISTER INSTRUCTION::get_reg_from_str(std::string reg_str)
{
	auto it = REGISTER_MAP.end();
	it = std::find_if(REGISTER_MAP.begin(), REGISTER_MAP.end(), [reg_str](auto item)
	{
		return item.second == reg_str;
	});
	if (it != REGISTER_MAP.end())
		return  (*it).first;
}


bool INS_ONE_LINE::is_active() const
{
	if ((this->m_issue_time != 0 && this->m_wb_time == 0) || this->m_is_ex)
		return true;
	return false;
}

INS_ONE_LINE::INS_ONE_LINE(QString one_line){
    m_one_ins = new INSTRUCTION(one_line);
    m_is_ex = false;
    m_issue_time = 0;
    m_ex_time = 0;
    m_oc_time = 0;
    m_wb_time = 0;
	m_waw_wait_time = 0;
	m_func_unit_wait_time = 0;
	 m_raw_wait_time = 0;
	m_war_wait_time = 0;

	 m_occ_func_unit = "0";
	 m_i_cache_hint = is_cache_hint();
	 m_i_cache_wait_time = I_Cache_Miss_Cycles ;
	 m_extra_wait_in_pipe = 0;
}




void INS_ONE_LINE::print_one_ins_time() const{
    m_one_ins->print_one_ins();
	//cout << "ISSUE TIME: " << m_issue_time << "\t OC TIME:" << m_oc_time << "\t EX TIME: " << m_ex_time
	//	<< "\tWB TIME: " << m_wb_time;
	//cout << " m_waw_time: " << m_waw_wait_time << "\tFUNC_WAIT time" << m_func_unit_wait_time << "\t raw wait " << m_raw_wait_time << "\t war wait " << m_war_wait_time;
	cout<<"Cache hint "<<m_i_cache_hint<<" Occ Func "<<m_occ_func_unit<<"\tExtra time "<<m_extra_wait_in_pipe;

	cout << endl;
}



void INS_ONE_LINE::set_all_time(bool n_can_issue,bool n_can_oc,
                                bool n_can_wb,int now_cycle){
   

    if(n_can_issue && this->m_issue_time == 0){
        this->m_issue_time = now_cycle;
        return;
    }
    if(n_can_oc && this->m_oc_time == 0){
        this->m_oc_time = now_cycle  ;
        this->m_is_ex = true;
		m_raw_wait_time = (m_oc_time - 1 == m_issue_time) ? 0 : m_oc_time - m_issue_time;
        return;
    }
    if((now_cycle - this->m_oc_time == this->m_one_ins->ins_cycle)&&
            (this->m_ex_time == 0) &&(this->m_oc_time!=0)){
        this->m_ex_time = now_cycle;
        return;
    }
    if(n_can_wb && this->m_wb_time == 0 && this->m_ex_time!=0){
        this->m_wb_time = now_cycle;
		m_war_wait_time = (m_wb_time - 1 == m_ex_time) ? 0 : m_wb_time - m_ex_time;
        return;
    }
}

FUNC_TRUE_ALL INS_ONE_LINE::get_cycles_occ_func_unit() const
{
	return{ m_func_unit,{m_one_ins->ins_cycle, m_wb_time - m_issue_time + 1} };
}







INS_ALL_PER_WARP::INS_ALL_PER_WARP(const QString &file_name, int threads_pre_warp, FUNC_TABLE *func_in_pool){
    this->read_all_ins_from_file(file_name);
    this->m_func_table = func_in_pool;
    this->m_reg_status =  vector<int>(14);
    //this->m_now_cycle = 1;
    this->m_active_threads_this_warp = threads_pre_warp;
    this->m_is_issued = false;
}



void INS_ALL_PER_WARP::read_all_ins_from_file(QString file_name){
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        m_ins_table.push_back(INS_ONE_LINE(str));

    }
    file.close();
}


int INS_ALL_PER_WARP::active_threads_this_warp() const
{
    return m_active_threads_this_warp;
}

void INS_ALL_PER_WARP::setActive_threads_this_warp(int active_threads_this_warp)
{
    m_active_threads_this_warp = active_threads_this_warp;
}


//所有指令均执行完
bool INS_ALL_PER_WARP::is_all_ins_done() const{

    for(int j = 0;j<m_ins_table.size();j++){
        if(m_ins_table[j].m_wb_time == 0){
            return false;
        }
    }
    return true;

}





bool INS_ALL_PER_WARP::is_all_ins_issued() const{

    for(int j = 0;j<m_ins_table.size();j++){
        if(m_ins_table[j].m_issue_time == 0){
			return false;
        }
    }
    return true;
}

bool INS_ALL_PER_WARP::have_issued_not_wb() const{

    for(int j = 0;j<m_ins_table.size();j++){
        if(m_ins_table[j].m_issue_time != 0 && m_ins_table[j].m_wb_time == 0)
			return true;
    }
	return false;
}




//指令从0开始计数！
//当前指令可否流出？无结构冒险，无WAW

bool INS_ALL_PER_WARP::n_th_ins_can_issue(int n,int now_cycle) const {


    //越界
    if (n>=m_ins_table.size())
        return false;

    //当前指令
    INSTRUCTION* n_ins = m_ins_table[n].m_one_ins;

    //本条指令已流出
    int n_is_time = m_ins_table[n].m_issue_time;
    if(n_is_time !=0){
        return false;
    }

    //上一条指令未流出，且其流出周期比当前周期大
    if(n!=0){
        if(m_ins_table[n-1].m_issue_time==0)
            return false;
        if(m_ins_table[n-1].m_issue_time >= now_cycle)
            return false;

    }



	if (!m_ins_table[n].m_i_cache_hint && m_ins_table[n].m_i_cache_wait_time != 0) {
		if(this->m_cycle_changed)
			m_ins_table[n].m_i_cache_wait_time--;
		return false;
	}

    //判断是否存在WAW
    REGISTER n_dst = m_ins_table[n].m_one_ins->ins_dst;
	
    for(int i = 0;i<n;i++){
        if(m_ins_table[i].is_active()){
			if (m_ins_table[i].m_one_ins->ins_dst == n_dst) {
				if (this->m_cycle_changed)
					m_ins_table[n].m_waw_wait_time = (m_ins_table[n].m_waw_wait_time == 0)? 2 : m_ins_table[n].m_waw_wait_time+1;
				return false;
			}
				
        }
    }
	
	


    /* //判断是否有RAW
     REGISTER m_src1 = m_ins_table[n].one_ins->ins_src1;
     REGISTER m_src2 = m_ins_table[n].one_ins->ins_src2;

    for(int i =0;i<n;i++){
        REGISTER now_dst =  m_ins_table[i].one_ins->ins_dst;
        if(now_dst==m_src1 || now_dst==m_src2){
            if(now_cycle - m_ins_table[i].m_issue_time<=0)
                return false;
        }
    }
    */

    //结构冒险
    INS_OP m_op = n_ins->ins_op;

	FUNC_UNIT to_occ;
	if (m_func_table->find_func_unit_valid(m_op, to_occ)) {
		m_func_table->occupy_func_table_one(to_occ, n_ins);
		m_ins_table[n].m_func_unit = to_occ;
		n_ins->ins_cycle += m_func_table->get_extra_ex_time(to_occ, m_active_threads_this_warp);
		m_ins_table[n].m_occ_func_unit = get_func_str_from_enum(to_occ);
		m_ins_table[n].m_extra_wait_in_pipe = m_func_table->get_extra_ex_time(to_occ, m_active_threads_this_warp);

		return true;
	}


    /*switch (m_op) {
    case LD:
    case ST:
        if(m_func_table->is_func_unit_valid(MEMPIPE)){
            m_func_table->occupy_func_table_one(MEMPIPE,n_ins);
            //m_reg_status[n_dst] = MEMPIPE;
            m_ins_table[n].m_func_unit = MEMPIPE;

            n_ins->ins_cycle += m_func_table->get_extra_ex_time(MEMPIPE,m_active_threads_this_warp);

            return true;
        }

        break;
    case MULTD:
	case DIVD:
        if(m_func_table->is_func_unit_valid(SFU1)){
            m_func_table->occupy_func_table_one(SFU1,n_ins);
            //m_reg_status[n_dst] = SFU1;
            m_ins_table[n].m_func_unit = SFU1;
            n_ins->ins_cycle += m_func_table->get_extra_ex_time(SFU1,m_active_threads_this_warp);
            return true;
        }
        else if(m_func_table->is_func_unit_valid(SFU2)){
            m_func_table->occupy_func_table_one(SFU2,n_ins);
            //m_reg_status[n_dst] = SFU2;
            m_ins_table[n].m_func_unit =  SFU2;
            n_ins->ins_cycle += m_func_table->get_extra_ex_time(SFU2,m_active_threads_this_warp);
            return true;
        }
        if(m_func_table->is_func_unit_valid(SFU3)){
            m_func_table->occupy_func_table_one(SFU3,n_ins);
           // m_reg_status[n_dst] = SFU3;
            m_ins_table[n].m_func_unit = SFU3;
            n_ins->ins_cycle += m_func_table->get_extra_ex_time(SFU3,m_active_threads_this_warp);
            return true;
        }
        break;
    case ADDD:
    case SUBD:
        if(m_func_table->is_func_unit_valid(SP1)){
            m_func_table->occupy_func_table_one(SP1,n_ins);
            //m_reg_status[n_dst] = SP1;
            m_ins_table[n].m_func_unit = SP1;
            n_ins->ins_cycle += m_func_table->get_extra_ex_time(SP1,m_active_threads_this_warp);
            return true;
        }
        else if(m_func_table->is_func_unit_valid(SP2)){
            m_func_table->occupy_func_table_one(SP2,n_ins);
            //m_reg_status[n_dst] = SP2;
            m_ins_table[n].m_func_unit = SP2;
            n_ins->ins_cycle += m_func_table->get_extra_ex_time(SP2,m_active_threads_this_warp);
            return true;
        }
        break;
    default:
        return false;
    }*/
	if (this->m_cycle_changed)
		m_ins_table[n].m_func_unit_wait_time = (m_ins_table[n].m_func_unit_wait_time == 0)? 2: m_ins_table[n].m_func_unit_wait_time + 1;
    return false;
}

//当前指令可否读操作数？无RAW
bool INS_ALL_PER_WARP::n_th_ins_can_oc(int n,int now_cycle) const {
    //越界
    if (n>=m_ins_table.size())
        return false;

    //当前指令
    INSTRUCTION* n_ins = m_ins_table[n].m_one_ins;
    INS_ONE_LINE n_ins_line = m_ins_table[n];
    //未流出
    if(n_ins_line.m_issue_time == 0 || n_ins_line.m_issue_time == now_cycle){
        return false;
    }

    //本条指令已收集数
    int n_oc_time = m_ins_table[n].m_oc_time;
    if(n_oc_time !=0){
        return false;
    }

    //当前指令占用功能部件号
    FUNC_UNIT n_func = m_ins_table[n].m_func_unit;

    int n_func_Rj = m_func_table->get_table_Rj(n_func);
    int n_func_Rk = m_func_table->get_table_Rk(n_func);


    //当前指令源寄存器
    REGISTER n_src1 = m_ins_table[n].m_one_ins->ins_src1;
    REGISTER n_src2 = m_ins_table[n].m_one_ins->ins_src2;

    for(int i=0;i<n;i++){
        REGISTER i_dst = m_ins_table[i].m_one_ins->ins_dst;
        if(m_ins_table[i].is_active()){
            if((i_dst == n_src1 || i_dst==n_src2))
                return false;
          /*  if(i_dst == n_src1 || i_dst==n_src2 || n_func_Rj==0||n_func_Rk==0){
                return false;*/
            //}

        }


      /*  else if(i_dst == n_src1 || i_dst==n_src2){
            if(i_dst == n_src1)
                m_func_table->set_table_Rj(n_func,1);
            if(i_dst == n_src2)
                m_func_table->set_table_Rk(n_func,1);
*/
        //}
        if((i_dst == n_src1 || i_dst==n_src2) && (!m_ins_table[i].m_is_ex)){
            if(now_cycle - m_ins_table[i].m_wb_time <= 0)
                return false;
        }

    }
	
    return true;

}


//能否写回
bool INS_ALL_PER_WARP::n_th_ins_can_wb(int n,int now_cycle) const {
    //越界
    if (n>=m_ins_table.size())
        return false;

    //当前指令,目的
    INSTRUCTION* n_ins = m_ins_table[n].m_one_ins;
    INS_ONE_LINE n_one_line = m_ins_table[n];
    if(n_one_line.m_ex_time == 0 ||n_one_line.m_oc_time == 0 || n_one_line.m_issue_time == 0)
        return false;
    if(n_one_line.m_ex_time == now_cycle ||n_one_line.m_oc_time == now_cycle || n_one_line.m_issue_time == now_cycle)
        return false;



    REGISTER n_dst = n_ins->ins_dst;
    for(int i=0;i<n;i++){
        //之前指令源
        REGISTER i_src1 = m_ins_table[i].m_one_ins->ins_src1;
        REGISTER i_src2 = m_ins_table[i].m_one_ins->ins_src2;
        bool WAR = (n_dst == i_src1) || (n_dst == i_src2);
        if(m_ins_table[i].m_is_ex && WAR)
            return false;
    }
	//if(m_ins_table[n].m_wb_time == 0)
	//	m_ins_table[n].m_war_wait_time = now_cycle - m_ins_table[n].m_ex_time - 1;
    return true;

}


void INS_ALL_PER_WARP::go_to_this_cycle(int now_cycle){
	m_cycle_changed = (now_cycle == m_now_cycle) ? false : true;
	m_now_cycle = now_cycle;
   
	m_is_issued = false;
    for(int i = 0;i<m_ins_table.size();i++){
        bool i_ins_can_is = n_th_ins_can_issue(i,now_cycle);
        if( i_ins_can_is){
            m_is_issued = true;
        }
        bool i_ins_can_oc = n_th_ins_can_oc(i,now_cycle);
        bool i_ins_can_wb = n_th_ins_can_wb(i,now_cycle);
        m_ins_table[i].set_all_time(i_ins_can_is,i_ins_can_oc,i_ins_can_wb,now_cycle);
		

    }


       // std::cout<<"now_CYCLE:"<<now_cycle<<"  ISSUED?\t"<<m_is_issued<<std::endl;
       // this->print_all_ins_table();
	
}


void INS_ALL_PER_WARP::clear_func_table(int now_cycles){
    for(int i = 0;i<m_ins_table.size();i++){
        if(m_ins_table[i].m_wb_time!=0 &&(now_cycles -1 == m_ins_table[i].m_wb_time ) ){
            m_func_table->clear_func_one_line(m_ins_table[i].m_func_unit);
            m_ins_table[i].m_is_ex = false;
        }

    }
}



void INS_ALL_PER_WARP::print_all_ins_table() const{
    for(INS_ONE_LINE one_line : m_ins_table){
        one_line.print_one_ins_time();
    }
}


void INS_ALL_PER_WARP::get_cycles_occ_func_per_warp(vector<std::pair<int,int>>& cycles_true_all_per_warp,int size) {

	if (!is_all_ins_done())
		return;

	//cycles_true_all_per_warp.clear();
	cycles_true_all_per_warp = vector<std::pair<int, int >>(size);

	for (auto iter = m_ins_table.begin(); iter != m_ins_table.end(); iter++) {
		cycles_true_all_per_warp[int(iter->get_cycles_occ_func_unit().first)].first += iter->get_cycles_occ_func_unit().second.first;
		cycles_true_all_per_warp[int(iter->get_cycles_occ_func_unit().first)].second += iter->get_cycles_occ_func_unit().second.second;

	}
	return;



}