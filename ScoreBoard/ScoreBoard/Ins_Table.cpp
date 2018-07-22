#include "Ins_Table.h"
int function_status[6][10];//����function_status[1][1]=0,���ʾ����������busyλ��no��������Ӧ�ý�
//[0-4][0]��ʼ��Ϊ0,����ע��00��û��ʹ��
 int register_status[30];//���磬register[F1]=INTEGER,��ͬregist[1]=1,��ʾF1�ɳ˷�����������
int Cycle=1;
void Ins_Table::Input(char name[],char r1[],char r2[],char  r3[])
{   
	//ȡָ����
	char s1[5]="LD",s2[7]="MULTD",s3[7]="SUBD",s4[7]="DIVD",s5[7]="ADDD";
  
	if( !strcmp(name,s1))
	{
		
		ins->name=1;
		
	   ins->cycle=1;
	}
	if( !strcmp(name,s2))
	{
		ins->name=MULTD;
		ins->cycle=10;
	}
	if( !strcmp(name,s3))
	{
		ins->name=SUBD;
	    ins->cycle=2;
	}
	if( !strcmp(name,s4))
	{
		
		ins->name=DIVD;
		ins->cycle=40;
	}
	if( !strcmp(name,s5))
	{
		
		ins->name=ADDD;
		ins->cycle=2;
	}
	
	/*******************************************************************************/

	//ȡĿ�Ĵ�����
	//char *ss1="F1",*ss2="F2",*ss3="F3",*ss4="F4",*ss5="F5",*ss6="F6",*ss7="F7",*ss8="F8",*ss9="F9",*ss10="F10",
		//*ss11="R1",*ss12="R2",*ss13="R3",*ss14="R4";
	char  ss1[5]="F1",ss2[5]="F2",ss3[5]="F3",ss4[5]="F4",ss5[5]="F5",ss6[5]="F6",ss7[5]="F7",ss8[5]="F8",ss9[5]="F9",ss10[5]="F10",
		ss11[5]="R1",ss12[5]="R2",ss13[5]="R3",ss14[5]="R4";
	if(!strcmp(ss1,r1) )			
		ins->destination=F1;
	if(!strcmp(ss2,r1) )			
		ins->destination=F2;
	if(!strcmp(ss3,r1) )	
		ins->destination=F3;
	if(!strcmp(ss4,r1) )
		ins->destination=F4;
	if(!strcmp(ss5,r1) )
		ins->destination=F5;
	if(!strcmp(ss6,r1) )
		ins->destination=F6;
	if(!strcmp(ss7,r1) )
		ins->destination=F7;
	if(!strcmp(ss8,r1) )
		ins->destination=F8;
	if(!strcmp(ss9,r1) )
		ins->destination=F9;
	if(!strcmp(ss10,r1) )
		ins->destination=F10;
	if(!strcmp(ss11,r1) )
		ins->destination=R1;
	if(!strcmp(ss12,r1) )
		ins->destination=R2;
	if(!strcmp(ss13,r1) )
		ins->destination=R3;
	if(!strcmp(ss14,r1) )
		ins->destination=R4;
  /*******************************************************************************************/
	//ȡԴ�Ĵ���1������
	if(!strcmp(ss1,r2) )
		ins->source1=F1;
	if(!strcmp(ss2,r2) )
		ins->source1=F2;
	if(!strcmp(ss3,r2) )
		ins->source1=F3;
	if(!strcmp(ss4,r2) )
		ins->source1=F4;
	if(!strcmp(ss5,r2) )
		ins->source1=F5;
	if(!strcmp(ss6,r2) )
		ins->source1=F6;
	if(!strcmp(ss7,r2) )
		ins->source1=F7;
	if(!strcmp(ss8,r2) )
		ins->source1=F8;
	if(!strcmp(ss9,r2) )
		ins->source1=F9;
	if(!strcmp(ss10,r2) )
		ins->source1=F10;
	if(!strcmp(ss11,r2) )
		ins->source1=R1;
	if(!strcmp(ss12,r2) )
		ins->source1=R2;
	if(!strcmp(ss13,r2) )
		ins->source1=R3;
	if(!strcmp(ss14,r2) )
		ins->source1=R4;
/*******************************************************************************************/
	//ȡԴ�Ĵ���2������
	if(!strcmp(ss1,r3) )
		ins->source2=F1;
	if(!strcmp(ss2,r3) )
		ins->source2=F2;
	if(!strcmp(ss3,r3) )
		ins->source2=F3;
	if(!strcmp(ss4,r3) )
		ins->source2=F4;
	if(!strcmp(ss5,r3) )
		ins->source2=F5;
	if(!strcmp(ss6,r3) )
		ins->source2=F6;
	if(!strcmp(ss7,r3) )
		ins->source2=F7;
	if(!strcmp(ss8,r3) )
		ins->source2=F8;
	if(!strcmp(ss9,r3) )
		ins->source2=F9;
	if(!strcmp(ss10,r3) )
		ins->source2=F10;
	if(!strcmp(ss11,r3) )
		ins->source2=R1;
	if(!strcmp(ss12,r3) )
		ins->source2=R2;
	if(!strcmp(ss13,r3) )
		ins->source2=R3;
	if(!strcmp(ss14,r3) )
		ins->source2=R4;
/**********************************************************************/
	if (!strcmp("0",r2))//���ڶ���������Ϊ��,judge1�����Ѿ���׼��
	{
		ins->source1=0;
	}
	if (!strcmp("0",r3))//��������������Ϊ��,judge1�����Ѿ���׼��
	{
		ins->source2=0;
	}
	
}

/************************************************************************/
/* ���������ԣ�ָ��ִ����������������û�в��У�  ������ʱ���������ɲ��У�����������������������������        */
/************************************************************************/
//void Ins_Table::goToNextCycle(bool judge_1,bool judge_2,/*bool judge_3,*/bool judge_4) 
/*{   
	int temp=0;
	int flag1=0,flag2=0,flag3=0,flag4=0;//ǰ�������������EC������ִ�У���judge_3������
	while (this->s[WR]==0)//Ϊ0����û��д����
	{
		if (judge_1&&(flag1==0))//ִ��IS(ע�⣡���������������judge�ǲ��������ģ�Ӧ�ð�main�е�judge�����ķ���ֵ��һ��������goToNextCycle())
		{
			//���ﻹҪ�Ա�2��3�����޸�
			this->s[IS]=Cycle;
			++Cycle;flag1=1;
		}
		if (judge_2&&flag1&&(flag2==0))//ִ��RO
		{   
			temp=Cycle;
			this->s[RO]=Cycle;
			++Cycle;flag2=1;
		}
		//ִ��EC
		if (flag2&&((Cycle-temp)==this->ins->cycle)&&(flag3==0))//�����ֵ��������
		{
			this->s[EC]=Cycle;
			++Cycle;flag3=1;
		}
		else if (((Cycle-temp)!=this->ins->cycle)&&flag2&&(flag3==0))
		{
			++Cycle;
		}
		//ִ��WR
		if(judge_4&&flag3&&(flag4==0))
		{
			this->s[WR]=Cycle;
			++Cycle;flag4=1;
			//���ﻹҪ�Ա�2��3�����޸�
		}
	}
	//��ָ����ȫִ�н�����Ϊ�˱���judge1 judge2���жϣ���������s[IS]Ϊ0
	this->s[IS]=0;
	this->s[RO]=0;    
}*/ 
void Ins_Table::goToNextCycle(bool judge_1,bool judge_2,/*bool judge_3,*/bool judge_4) 
{   
	
  //ǰ�������������EC������ִ�У���judge_3������
	
		if (judge_1&&(this->s[IS]==0))//ִ��IS(ע�⣡���������������judge�ǲ��������ģ�Ӧ�ð�main�е�judge�����ķ���ֵ��һ��������goToNextCycle())
		{
			//���ﻹҪ�Ա�2��3�����޸�

			this->startIS=Cycle;
			this->s[IS]=Cycle;
			return;
		
		}
		if (judge_2&&(this->s[RO]==0)&&(this->s[IS]!=0))//ִ��RO
		{   
			this->startRO=Cycle;
			this->s[RO]=Cycle;
			this->exc=1;//������ִ�е�ָ�ֵ1
			return;
		}
		//ִ��EC
		if (((Cycle-this->startRO)==this->ins->cycle)&&(this->s[EC]==0)&&(this->s[RO]!=0))//�����ֵ��������
		{
			this->s[EC]=Cycle;
			
            return;
		}
		//ִ��WR
		if(judge_4&&(this->s[WR]==0)&&(this->s[EC]!=0))
		{
			this->s[WR]=Cycle;
			this->startWR=Cycle;
			return;
			//���ﻹҪ�Ա�2��3�����޸�
		}
	
	//��ָ����ȫִ�н�����Ϊ�˱���judge1 judge2���жϣ���������s[IS]Ϊ0
   
} 

void Ins_Table::setFunc(FUNCTION_UNIT f)//����������������ڷ���judge1����
{
	this->fu=f;
}
int Ins_Table::getFunc()
{
	return this->fu;
}


//void Ins_Table::update_func_satus()

//void Ins_Table::register_status()
