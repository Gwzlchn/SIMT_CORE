#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
enum REGISTER{F1=1,F2,F3,F4,F5,F6,F7,F8,F9,F10,R1,R2,R3,R4};//��ע�⣬��ʹ��F0����Ĵ���
enum OP_NAME{LD=1,MULTD,SUBD,DIVD,ADDD};
enum STAGE{IS=1,RO,EC,WR};
/**************************************************************/
//�����ǹ��ڵڶ�����Ĳ���

enum FUNCTION_UNIT{INTEGER=1,MULT1,MULT2,ADD,DIVIDE};
enum FUNCTION{Busy=1,Op,Fi,Fj,Fk,Qj,Qk,Rj,Rk};
#define no 0
#define yes 1//������������ʾBusyλ��
extern int function_status[6][10];//����function_status[1][1]=0,���ʾ����������busyλ��no��������Ӧ�ý�
//[0-4][0]��ʼ��Ϊ0,����ע��00��û��ʹ��.ע�⣡���������ʡ�6����10����Խ��ģ�int f[10]���ܷ���f[10]

/*********************************************************************/

//���ڱ�3
extern int register_status[30];//���磬register[F1]=INTEGER,��ͬregist[1]=1,��ʾF1�ɳ˷�����������
extern int Cycle;
struct INSTRUCTION//��ָ��
{
	
	int name;
	int cycle;//ͨ�����Ҷ�Ӧ������ֵ���������ֵ
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
	int s[5];//Ϊ��ʹ�÷���,s[0]���á����Ժ���һ��Ҫע�⣺��Ҫʹ��δ��ֵ��s[0]��������0-4,ֻʹ��1-4
	int fu;//��Ǹ�ָ����ʹ�õı�2�Ĺ��ܲ���
	int exc;//��־��ָ���Ƿ�����ִ��EC�׶Σ�0û�У�1����
	int startRO;//���ڼ�¼ִ��RO�Ŀ�ʼʱ�䣬��ΪRO��EX֮��Ҫ���cycle
	int startIS;//��¼ÿһ��ָ�ʼIS��ʱ�䡣��һ���������ǰһ���������Ϳ�����IS˳��ִ�С�
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
		this->fu=0;//����������judge1�����У��ٸ������ֵ
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
