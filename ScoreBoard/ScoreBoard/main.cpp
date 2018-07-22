#include "Ins_Table.h"
#include <iostream>
#include <conio.h>
using namespace std;
#include <stdlib.h>
bool judge1(int m,int count,Ins_Table a[]);
bool judge2(int m,int count,Ins_Table a[]);

bool judge4(int m,int count,Ins_Table a[]);
int main()
{
    bool judge_1=false,judge_2=false,judge_4=false;
	Ins_Table ins_obj[20];//最多20条指令0-19
  //初始化表2
	for(int i=0;i<6;i++)
		for (int j=0;j<10;j++)
		{
			function_status[i][j]=0;
			/*enum REGISTER{F1=1,F2,F3,F4,F5,F6,F7,F8,F9,F10};//请注意，不使用F0这个寄存器
			enum OP_NAME{LD=1,MULTD,SUBD,DIVD,ADDD};*/
			//由此可知，0只对于Busy和Rj,Rk有意义，对于其他并没有意义。

		}
 //初始化表3
	for(int i=0;i<30;i++)
		register_status[i]=0;//例如，register[F1]=INTEGER,如同regist[1]=1,表示F1由乘法部件产生。
//刚好也没有0这个部件


/*************************************************************************************************/
//输入模块
	 int count=0;
	 char name[21]=" ",r1[21]=" ",r2[21]=" ",r3[21]=" ";
	 cout<<"输入操作名字：(以end结束)";
	 cin>>name;
	 
     while (strcmp(name,"end")!=0)//这里根据输入界面的，完成或者增加，按键来写判别条件
     { 
		 cout<<"输入3个寄存器名字(数字0表示为空操作数)：\n寄存器1:";
		 cin>>r1;cout<<"\n寄存器2:";cin>>r2;cout<<"\n寄存器3:";cin>>r3;
		 ins_obj[++count].Input(name,r1,r2,r3);//如果某一个操作数字段没有，则构造函数会赋0值
         cout<<"继续输入操作名字：(以end结束)";
		 cin>>name;
     }
 /************************************************************************/
//进入执行模块
	
	// int m=1;
    /* while(m<=count)
	 {   
		 judge_1=judge1(m,count,ins_obj);
		 judge_2=judge2(m,count,ins_obj);
		 judge_4=judge4(m,count,ins_obj);
		 ins_obj[m].goToNextCycle(judge_1,judge_2,judge_3,judge_4);
         //m++;

	 }*/
	bool judge[21][21];
	 for (int v=0;v<21;v++)
	 {
		 for (int c=0;c<21;c++)
		 {
			 judge[v][c]=0;
		 }
	 }
   int flag=1;

	 while (flag)//只要最后一条指令的写操作没完成，就要继续执行。这里重要的是按时间驱动在执行！实现了并行
	 {
		 for (int var=1;var<=count;var++)
		 {
			 judge[var][1]=judge1(var,count,ins_obj);
			 judge[var][2]=judge2(var,count,ins_obj);
			 judge[var][3]=judge4(var,count,ins_obj);
			 ins_obj[var].goToNextCycle(judge[var][1],judge[var][2],judge[var][3]);
		 
		 if(ins_obj[var].s[WR]!=0)
		     {
			 //这条指令已经执行结束，要添加修改表2的代码
			 int temp1=ins_obj[var].getFunc();
			/* for (int temp2=1;temp2<10;temp2++)
			 {
				 function_status[temp1][temp2]=0;//复位操作
			 }*/
			 function_status[temp1][1]=0;

			 ins_obj[var].exc=0;
			 
	    	 }
		 }
		 //只要有未执行完的语句，继续执行到底
		 int r;
		 for ( r=1;r<=count;r++)
		 {
			 if(ins_obj[r].s[WR]==0)
			 {
				 flag=1;
				 break;
			 }
		 }
		 if (r>count)
		 {
			 flag=0;
		 }
		 ++Cycle;
	 }

    /************************************************************************/
    /* 输出模块                                                                     */
    /*输出表1*/
	 cout<<"\n这是表1：\n";
	 for (int x=1;x<=count;x++)
	 {
		 for(int t=1;t<5;t++)
		     cout<<ins_obj[x].s[t]<<"\t";
		 cout<<"\n";
	 }
	 cout<<"这是表2:\n";
	 for (int x=1;x<=5;x++)
     {
		 for (int t=1;t<=9;t++)
		 {
			 cout<<function_status[x][t]<<"\t";
		 }
		 cout<<"\n";
	 }
	 cout<<"这是表3\n";
    for (int y=1;y<=29;y++)
    {
		cout<<register_status[y]<<"\t";
    }
   cout<<"\n";
system("Pause"); 
return 0;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
bool judge1(int m,int count,Ins_Table a[])
{
   
   for(int k=1;k<=m;k++)
   {
	   if (a[k].ins->destination==a[m].ins->source1||a[k].ins->destination==a[m].ins->source2)//判断任意前一条执行的与本指令相关的指令，必须IS跟它的WR相差1个周期
	   {
		   if (Cycle-a[k].s[WR]<=0)
		   {
			   return false;
		   }
	   }
   }

   int x=m-1; 
   switch (a[m].ins->name)
   {
   case LD:
	   
       if (function_status[INTEGER][Busy]==no&&(a[m].s[IS]==0))//本指令并没有执行，即第一次发射才具有修改下面内容的权限
       {   
		   if((x>0&&(a[x].s[IS]!=0)&&(Cycle>a[x].startIS)/*&&(Cycle!=a[x].startWR)*/)||x==0)//保证必须在上一条已发射下才执行现在的。而且现在的时钟Cycle必须大于上一条的startIs才能保证IS顺序执行
		   {
		   a[m].setFunc(INTEGER);
		   for(int k=1;k<=count;k++)
		   {
               if(a[k].exc!=0)//正在执行
		          {
                    if(a[k].ins->destination==a[m].ins->destination)
					{
						return false;//不执行IS就不用修改表2表3，直接返回
					}
		          }
		   }
	       //对表2进行修改
		   function_status[INTEGER][Busy]=yes;
		   function_status[INTEGER][Op]=LD;
		   function_status[INTEGER][Fi]=a[m].ins->destination;
		   function_status[INTEGER][Fj]=a[m].ins->source1;
		   function_status[INTEGER][Fk]=a[m].ins->source2;
		   if (function_status[INTEGER][Fj]>10||function_status[INTEGER][Fj]==0)//大于10就为R寄存器,等于0则说明没有这个操作字段
		   {
			   function_status[INTEGER][Rj]=yes;
		   }
		   if (function_status[INTEGER][Fk]>10||function_status[INTEGER][Fk]==0)//大于10就为R寄存器，-1是为空
		   {
			   function_status[INTEGER][Rk]=yes;
		   }
		    //对表3进行修改
		  register_status[a[m].ins->destination]=INTEGER;
		  return true;
		  }
		   else return false;

       }
	   else  return false;

	 
   case MULTD:

	   if (function_status[MULT1][Busy]==no&&(a[m].s[IS]==0))
	   {
		   if((x>0&&(a[x].s[IS]!=0)&&(Cycle>a[x].startIS)&&(Cycle!=a[x].startWR))||x==0)//保证必须在上一条以发射下才执行现在的。保证IS顺序执行
		   {
		   a[m].setFunc(MULT1);
		   for(int k=1;k<=count;k++)
		   {

			   if(a[k].exc!=0)//前面流出的指令，且正在执行
			   {
				   if(a[k].ins->destination==a[m].ins->destination)
				   {
					   return false;//不执行IS就不用修改表2表3，直接返回
				   }
			   }
		   }
		   //对表2进行修改
		   function_status[MULT1][Busy]=yes;
		   function_status[MULT1][Op]=a[m].ins->name;
		   function_status[MULT1][Fi]=a[m].ins->destination;
		   function_status[MULT1][Fj]=a[m].ins->source1;//you wen ti
		   //cout<<function_status[MULT1][Fj]<<"\t"<<a[m].ins->source1;
		   function_status[MULT1][Fk]=a[m].ins->source2;//you wen ti
		   if (function_status[MULT1][Fj]>10||function_status[MULT1][Fj]==0)//大于10就为R寄存器
		   {
			   function_status[MULT1][Rj]=yes;
		   }
		   if (function_status[MULT1][Fk]>10||function_status[MULT1][Fk]==0)//大于10就为R寄存器
		   {
			   function_status[MULT1][Rk]=yes;
		   }
		   //对表3进行修改
		   register_status[a[m].ins->destination]=MULT1;
		   return true;
		   }
		   else return false;
	   }
	   else if (function_status[MULT2][Busy]==no&&(a[m].s[IS]==0))
	   {
		   if((x>0&&(a[x].s[IS]!=0)&&(Cycle>a[x].startIS)&&(Cycle!=a[x].startWR))||x==0)//保证必须在上一条以发射下才执行现在的。保证IS顺序执行
		   {
		    a[m].setFunc(MULT2);
		   for(int k=1;k<=count;k++)
		   {

			   if(a[k].exc!=0)//前面流出的指令，且正在执行
			   {
				   if(a[k].ins->destination==a[m].ins->destination)
				   {
					   return false;//不执行IS就不用修改表2表3，直接返回
				   }
			   }
		   }
		   //对表2进行修改
		   
		   function_status[MULT2][Busy]=yes;
		   function_status[MULT2][Op]=a[m].ins->name;
		   function_status[MULT2][Fi]=a[m].ins->destination;
		   function_status[MULT2][Fj]=a[m].ins->source1;
		   function_status[MULT2][Fk]=a[m].ins->source2;
		   if (function_status[MULT2][Fj]>10||function_status[MULT2][Fj]==0)//大于10就为R寄存器
		   {
			   function_status[MULT2][Rj]=yes;
		   }
		   if (function_status[MULT2][Fk]>10||function_status[MULT2][Fk]==0)//大于10就为R寄存器
		   {
			   function_status[MULT2][Rk]=yes;
		   }
		   //对表3进行修改
		   register_status[a[m].ins->destination]=MULT2;
		   return true;
		   }
		   else return false;
	   }
		   
		   
		else		   
		   return false;
				   
	 	   
	  


   case SUBD:
	   if (function_status[ADD][Busy]==no&&(a[m].s[IS]==0))
	   {
		   if((x>0&&(a[x].s[IS]!=0)&&(Cycle>a[x].startIS)&&(Cycle!=a[x].startWR))||x==0)//保证必须在上一条以发射下才执行现在的。保证IS顺序执行
		   {
		    a[m].setFunc(ADD);
		   for(int k=1;k<=count;k++)
		   {

			   if(a[k].exc!=0)//正在执行
			   {
				   if(a[k].ins->destination==a[m].ins->destination)
				   {
					   return false;//不执行IS就不用修改表2表3，直接返回
				   }
			   }
		   }
		   //对表2进行修改
		   function_status[ADD][Busy]=yes;
		   function_status[ADD][Op]=SUBD;
		   function_status[ADD][Fi]=a[m].ins->destination;
		   function_status[ADD][Fj]=a[m].ins->source1;
		   function_status[ADD][Fk]=a[m].ins->source2;
		   if (function_status[ADD][Fj]>10||function_status[ADD][Fj]==0)//大于10就为R寄存器
		   {
			   function_status[ADD][Rj]=yes;
		   }
		   if (function_status[ADD][Fk]>10||function_status[ADD][Fk]==0)//大于10就为R寄存器
		   {
			   function_status[ADD][Rk]=yes;
		   }
		   //对表3进行修改
		   register_status[a[m].ins->destination]=ADD;
		   return true;
		   }
		   else return false;
	   }
	   else  return false;


	  
   case DIVD:

	   if (function_status[MULT1][Busy]==no&&(a[m].s[IS]==0))
	   {    
		   if((x>0&&(a[x].s[IS]!=0)&&(Cycle>a[x].startIS)&&(Cycle!=a[x].startWR))||x==0)//保证必须在上一条以发射下才执行现在的。保证IS顺序执行
		   {
		   a[m].setFunc(MULT1);
		   for(int k=1;k<=count;k++)
		   {

			   if(a[k].exc!=0)//前面流出的指令，且正在执行
			   {
				   if(a[k].ins->destination==a[m].ins->destination)
				   {
					   return false;//不执行IS就不用修改表2表3，直接返回
				   }
			   }
		   }
		   //对表2进行修改
		   function_status[MULT1][Busy]=yes;
		   function_status[MULT1][Op]=a[m].ins->name;
		   function_status[MULT1][Fi]=a[m].ins->destination;
		   function_status[MULT1][Fj]=a[m].ins->source1;
		   function_status[MULT1][Fk]=a[m].ins->source2;
		   if (function_status[MULT1][Fj]>10||function_status[MULT1][Fj]==0)//大于10就为R寄存器
		   {
			   function_status[MULT1][Rj]=yes;
		   }
		   if (function_status[MULT1][Fk]>10||function_status[MULT1][Fk]==0)//大于10就为R寄存器
		   {
			   function_status[MULT1][Rk]=yes;
		   }
		   //对表3进行修改
		   register_status[a[m].ins->destination]=MULT1;
		   return true;
		   }
		   else return false;
	   }
	   else
	   if (function_status[MULT2][Busy]==no&&(a[m].s[IS]==0))
	   {   
		   if((x>0&&(a[x].s[IS]!=0)&&(Cycle>a[x].startIS)&&(Cycle!=a[x].startWR))||x==0)//保证必须在上一条以发射下才执行现在的。保证IS顺序执行
		   {  
		   a[m].setFunc(MULT2);
		   for(int k=1;k<=count;k++)
		   {

			   if(a[k].exc!=0)//前面流出的指令，且正在执行
			   {
				   if(a[k].ins->destination==a[m].ins->destination)
				   {   
					   return false;//不执行IS就不用修改表2表3，直接返回
				   }
			   }
		   }
		   //对表2进行修改
		   function_status[MULT2][Busy]=yes;
		   function_status[MULT2][Op]=a[m].ins->name;
		   function_status[MULT2][Fi]=a[m].ins->destination;
		   function_status[MULT2][Fj]=a[m].ins->source1;
		   function_status[MULT2][Fk]=a[m].ins->source2;
		   if (function_status[MULT2][Fj]>10||function_status[MULT2][Fj]==0)//大于10就为R寄存器
		   {
			   function_status[MULT2][Rj]=yes;
		   }
		   if (function_status[MULT2][Fk]>10||function_status[MULT2][Fk]==0)//大于10就为R寄存器
		   {
			   function_status[MULT2][Rk]=yes;
		   }
		   //对表3进行修改
		   register_status[a[m].ins->destination]=MULT2;
		  
		   return true;
		   }
		   else return false;
	   }

       else		   
		   return false;
         
   case ADDD:
	   if (function_status[ADD][Busy]==no&&(a[m].s[IS]==0))
	   {
		   if((x>0&&(a[x].s[IS]!=0)&&(Cycle>a[x].startIS)&&(Cycle!=a[x].startWR))||x==0)//保证必须在上一条以发射下才执行现在的。保证IS顺序执行
		   {
		   a[m].setFunc(ADD);
		   for(int k=1;k<=count;k++)
		   {

			   if(a[k].exc!=0)//正在执行
			   {
				   if(a[k].ins->destination==a[m].ins->destination)
				   {
					   return false;//不执行IS就不用修改表2表3，直接返回
				   }
			   }
		   }
		   //对表2进行修改
		   function_status[ADD][Busy]=yes;
		   function_status[ADD][Op]=ADDD;
		   function_status[ADD][Fi]=a[m].ins->destination;
		   function_status[ADD][Fj]=a[m].ins->source1;
		   function_status[ADD][Fk]=a[m].ins->source2;
		   if (function_status[ADD][Fj]>10||function_status[ADD][Fj]==0)//大于10就为R寄存器
		   {
			   function_status[ADD][Rj]=yes;
		   }
		   if (function_status[ADD][Fk]>10||function_status[ADD][Fk]==0)//大于10就为R寄存器
		   {
			   function_status[ADD][Rk]=yes;
		   }
		   //对表3进行修改
		   register_status[a[m].ins->destination]=ADD;
		   return true;
		   }
		   else return false;
	   }
	   else  return false;

	  
   default:
	   return false;
	  
   }
return false;
}
bool judge2(int m,int count,Ins_Table a[])
{
	 
	 
	 
	int temp1=a[m].getFunc();//功能部件号
	int RJ=function_status[temp1][Rj];
	int RK=function_status[temp1][Rk];

	for(int k=1;k<m;k++)
	{
        if(a[k].exc!=0)//前面流出且正在执行的指令，不对本指令的源进行写入
	      {
	         if((a[k].ins->destination==a[m].ins->source1)||(a[k].ins->destination==a[m].ins->source2)||RJ==0||RK==0)
	           {
	              return false;//不执行IS就不用修改表2表3，直接返回
	           }
			
	      }//这个模块是对于已经执行完的指令的目的，恰好是本指令的源的情况，对相应的寄存器赋值
		else 
		if((a[k].ins->destination==a[m].ins->source1)||(a[k].ins->destination==a[m].ins->source2))
		{
			//if ((a[k].ins->destination==a[m].ins->source1)&&(Cycle - a[k].startWR>0))
			if (a[k].ins->destination==a[m].ins->source1)
			{
				function_status[temp1][Rj]=yes;
			}
			//if ((a[k].ins->destination==a[m].ins->source2)&&(Cycle - a[k].startWR>0))
			if (a[k].ins->destination==a[m].ins->source2)
			{
				function_status[temp1][Rk]=yes;
			}
			
		}
		if (((a[k].ins->destination==a[m].ins->source1)||(a[k].ins->destination==a[m].ins->source2))&&(a[k].exc==0))
		{
			if (Cycle-a[k].startWR<=0)
			{
				return false;
			}
			
		}
	}
	 
	return true;
	 
}
bool judge4(int m,int count,Ins_Table a[])
{
	 
	for(int k=1;k<m;k++)
	{
		if(a[k].exc!=0 )//前面流出且正在执行的指令，还没有读取本指令的目的操作数。仔细理解，这是为并行考虑！！
		{
			if((a[k].ins->source1==a[m].ins->destination)||(a[k].ins->source2==a[m].ins->destination))
			{
				return false;//不执行IS就不用修改表2表3，直接返回
			}
		}
	}
	return true;

}										