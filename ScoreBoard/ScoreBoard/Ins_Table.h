#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
enum REGISTER{F1=1,F2,F3,F4,F5,F6,F7,F8,F9,F10,R1,R2,R3,R4};//请注意，不使用F0这个寄存器
enum OP_NAME{LD=1,MULTD,SUBD,DIVD,ADDD};
enum STAGE{IS=1,RO,EC,WR};
/**************************************************************/
//下面是关于第二个表的参数

enum FUNCTION_UNIT{INTEGER=1,MULT1,MULT2,ADD,DIVIDE};
enum FUNCTION{Busy=1,Op,Fi,Fj,Fk,Qj,Qk,Rj,Rk};
#define no 0
#define yes 1//这里是用来表示Busy位的
extern int function_status[6][10];//例如function_status[1][1]=0,则表示整数部件的busy位是no，主函数应该将
//[0-4][0]初始化为0,尤其注意00并没有使用.注意！！！！访问【6】【10】是越界的！int f[10]不能访问f[10]

/*********************************************************************/

//关于表3
extern int register_status[30];//例如，register[F1]=INTEGER,如同regist[1]=1,表示F1由乘法部件产生。
extern int Cycle;
struct INSTRUCTION//纯指令
{
	
	int name;
	int cycle;//通过查找对应操作的值，来赋这个值
	REGISTER destination;
	//REGISTER source1;
	int source1;
	//REGISTER source2;
	int source2;
};
class Ins_Table
{
public:
	INSTRUCTION *ins;
	int s[5];//为了使用方便,s[0]不用。所以后面一定要注意：不要使用未赋值的s[0]。这里是0-4,只使用1-4
	int fu;//标记该指令所使用的表2的功能部件
	int exc;//标志该指令是否正在执行EC阶段！0没有，1正在
	int startRO;//用于记录执行RO的开始时间，因为RO与EX之间要相差cycle
	int startIS;//记录每一条指令开始IS的时间。后一条必须大于前一条，这样就控制了IS顺序执行。
	int startWR;
public:
	Ins_Table()
	{
		this->ins=new INSTRUCTION;
		this->s[0]=0;
		this->s[1]=0;
		this->s[2]=0;
		this->s[3]=0;
		this->s[4]=0;
		this->fu=0;//在主函数的judge1函数中，再给这个赋值
		this->exc=0;
		this->startIS=0;
		this->startWR=0;
	}
	void setFunc(FUNCTION_UNIT f);
	int getFunc();
	void Input(char name[],char r1[],char r2[],char  r3[]);
	void goToNextCycle(bool,bool,bool);
    ~Ins_Table()
	{
		delete ins;
	}

};
