//#include<string.h>
//#include<stdio.h>
//#include<ctype.h>
//#include<alloc.h>
#include"jrtz.h"

// # include "c:\boy20\include\boywin.h" /* 嵌入头文件, 有关部件结构信息 */
// # include "c:\boy20\include\key.h"    /* 嵌入头文件, 有关键盘扫描码信息 */

int CreateErrorWindows(char *text);
extern char change;
extern station_sum;
extern _station *station;
int test(char *string)
{
	int len,i;
	len=strlen(string);
	if(len<3)return 0;
	for(i=0;i<len;i++){
		if(!isdigit(string[i]))return 0;
	}
	for(i=0;i<station_sum;i++){
		if(strncmp(station[i].NO,string,len)==0)return 0;
	}

	return 1;
}

 void New(void)        /* 一个由用户定义的窗口 */
 {
   FILE *cfgfile;
   int FLAG = 0;               /* 循环判断 */
   int i,CASE;                   /* 返回值 */
   static int  BOY_TOTAL = 9; /* 用户创建的部件数量 */
   static TEST BOY_TEST;       /* 动作结构 */
   static int  BOY_TAB = 6;   /* 当前激活项在此部件上 */

   /* 部件的类型:参见手册第98页 */
   static TYPE BOY_TYPE[9] = {
				 {99,0},{1,0},{1,1},{3,0},{3,1},
				 {3,2},{5,0},{5,1},{5,2},
				};

   /* 以下为窗口和窗口中部件结构的定义
      如想修改,请参照手册第一部份第二章 */
    static KEY3D BOY_KEY3D[2] = {
				   {180,280,240,302,"",0,0,1,0,2,"确定",0,0,15,0,1},
				   {280,280,340,302,"",0,0,1,0,2,"取消",27,0,15,0,2},
				  };
    static LABEL BOY_LABEL[3] = {
				    {100,150,150,170,0,0,0,0,0,0,7,0,0,1,"编号:",0,""},
				    {100,180,180,200,0,0,0,0,0,0,7,0,0,1,"电话号码:",0,""},
				    {100,210,150,230,0,0,0,0,0,0,7,0,0,1,"说明:",0,""},
				   };
    static INPUTBOX BOY_INPUTBOX[3] = {
					{200,150,6,0,3,1,0,0,0,15,15,0,3,1,0,0,"","",0,1},
					{200,180,12,0,12,1,0,0,0,15,15,0,11,1,0,0,"","",11,-3},
					{200,210,20,0,20,1,0,0,0,15,15,0,12,1,0,0,"","",12,-7},
				      };
    static WINDOWS BOY_WINDOWS = { 50,100,440,350,"新建",7,1,0,0,1,3,15,0,0,0,15,1,15,0,7,0,0};

    BOY_WINDOWS.key = BOY_KEY3D;
    BOY_WINDOWS.lab = BOY_LABEL;
    BOY_WINDOWS.inp = BOY_INPUTBOX;

    CREATE_WINDOWS_ALL(&BOY_WINDOWS,&BOY_TYPE[0],BOY_TOTAL,BOY_TAB);
    /* 建立窗口及部件 */

    while(!FLAG)
     { /* 得到系统事件 */
       BOY_GET_TEST(&BOY_TEST);
       CASE=BOY_ALL_TEST(&BOY_WINDOWS,&BOY_TEST,BOY_TOTAL,&BOY_TAB,BOY_TYPE);
       /* 得到返回值 */
       switch(CASE)
       {
	 /* 选中窗口项部菜单之关闭窗口项 */
	 case 1:{
		if(!test(BOY_WINDOWS.inp[0].text)){
			CreateErrorWindows("编号必须是001-255非重复数字!");
			BOY_TAB=6;
			break;
		}
		if(!test(BOY_WINDOWS.inp[1].text)){
			CreateErrorWindows("电话号码必须是数字!");
			BOY_TAB=7;
			break;
		}
		station_sum++;
		if((station=realloc(station,sizeof(*station)*station_sum))==NULL)CreateErrorWindows("内存不够!");
		strncpy(station[station_sum-1].NO,BOY_WINDOWS.inp[0].text,3);
		strncpy(station[station_sum-1].phone,BOY_WINDOWS.inp[1].text,12);
		strncpy(station[station_sum-1].comment,BOY_WINDOWS.inp[2].text,20);
		change=1;
	 }
	 case 2:
	 case WindowsClose:FLAG=1;break;
	}
      }
     CLOSE_BOY_WINDOWS(&BOY_WINDOWS);    /* 关闭窗口 */
  }

