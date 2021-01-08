//# include "c:\JRTZ\boywin.h" /* 嵌入头文件, 有关部件结构信息 */
//# include "c:\JRTZ\key.h"    /* 嵌入头文件, 有关键盘扫描码信息 */
//#include "c:\JRTZ\dialog.h"
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
#include "jrtz.h"
char *Help[5] = {
	{"智能太阳能充电并网逆变器"},
	{"遥控遥测系统"},
	{"(c) V1.0"},
	{"程序编制: 冯建涛"},
	{"1998 年 5 月"}
};
int current_station=-1;
char COM=0;
char Connect=0;
char change=0;
_station *station;

int station_sum;

 void BOY_Windows(void);
 void win111(void);
 void New(void);
 void Now(void);
 void History(void);
 void del(void);
 void Setup(void);
 void Control(void);
 int CreateAboutWindows(char *Text[5]);
 SETPATH BOYPATH = {
			  "c:\\boy20\\OVL",  /* 全拼,简拼码表, BGI */
			  "c:\\boy20\\OVL",  /* 16点阵汉字及英文字库 */
			  "c:\\boy20\\FONT24",  /* 24点阵字库 */
			  "c:\\boy20\\OVL"   /* 图形临时交换文件 */
		    };

 int main(void)
  {
    char pass[sizeof(cfgfilehead)];
    FILE *cfgfile;
	strcpy(Serial,"001-0112940005");
    BOY_SETUP_ALL();       /* 系统设置 */
    BOY_DESKTOP(0,"");     /* 绘出壁纸 */
    CREATE_BOY_CHINESE();  /* 创建拚音窗口 (如不需输入汉字可删去该行)*/


    if((cfgfile= fopen ("jrtz.cfg","rb"))==NULL){
	station_sum=0;
	}
    else{
	fread(pass,1,sizeof(pass),cfgfile);
	if(strncmp(pass,cfgfilehead,sizeof(cfgfilehead))!=0){
		fclose(cfgfile);

		remove("jrtz.cfg");
		return -2;
	}
	fread(&COM,1,sizeof(COM),cfgfile);
	fread(&station_sum,1,sizeof(int),cfgfile);
	station=calloc(station_sum,sizeof(*station));
	fread(station,1,sizeof(*station)*station_sum,cfgfile);
	}
	BOY_Windows();         /* 进入用户窗口操作 */
	BOY_CLOSE_ALL();       /* 关闭系统 */
	return 1;              /* 程序结束 */
  }


 void BOY_Windows(void)        /* 一个由用户定义的窗口 */
 {
   FILE *cfgfile;
   int FLAG = 0;               /* 循环判断 */
   int CASE;                   /* 返回值 */
   static int  BOY_TOTAL = 1; /* 用户创建的部件数量 */
   static TEST BOY_TEST;       /* 动作结构 */
   static int  BOY_TAB = 0;   /* 当前激活项在此部件上 */

   /* 部件的类型:参见手册第98页 */
   static TYPE BOY_TYPE[1] = {
				 {18,0},
				};

   /* 以下为窗口和窗口中部件结构的定义
	  如想修改,请参照手册第一部份第二章 */
	static MENU BOY_MENU[15] = {
				  {"F.连接 ",8448,1,0,0,11,9,26,1},
					  {"拨号 F3",15616,1,1,0,111,9,48,0},
					  {"断开",0,1,1,0,114,9,68,0},
					  {"守候 F2",15360,1,1,0,112,9,88,0},
					  {"     ",0,-1,1,0,0,9,108,0},
					  {"新建 ",0,1,1,0,115,9,128,0},
					  {"删除 ",0,1,1,0,116,9,148,0},
					  {"     ",0,-1,1,0,0,9,168,0},
					  {"退出 ALT-X",11520,1,1,0,113,9,188,0},
				  {"V.数据",12032,1,0,0,12,81,26,1},
					  {"当前状态",0,1,1,0,121,81,48,0},
					  {"历史数据",0,1,1,0,122,81,68,0},
					  {"控制器设置",0,1,1,0,123,81,88,0},
				  {"S.设置",7936,1,0,0,13,145,26,1},
					  {"调制解调器",0,1,1,0,131,145,48,0},
				};
	static WINDOWS BOY_WINDOWS = { 0,0,639,449,"太阳能智能充电并网逆变器通讯控制系统",7,1,0,0,1,3,15,0,0,15,15,1,15,0,7,0,0};

	BOY_WINDOWS.menu= BOY_MENU;

	CREATE_WINDOWS_ALL(&BOY_WINDOWS,&BOY_TYPE[0],BOY_TOTAL,BOY_TAB);

	strcpy(DLGPATH,BOYPATH.ovl);  // 对话框资源文件的路径
    CreateAboutWindows(Help); // ABOUT 窗口


	while(!FLAG)
     {
       BOY_GET_TEST(&BOY_TEST);
       CASE=BOY_ALL_TEST(&BOY_WINDOWS,&BOY_TEST,BOY_TOTAL,&BOY_TAB,BOY_TYPE);
       switch(CASE)
       {
	 case 113:
	 case WindowsClose:FLAG=1;break;
	 case 111:win111();break;
	 case 112:waitsend();break;
	 case 114:{
		Send_String("+++");
		delay(2000);
		Send_String("ath0\r");
		CreateWarningWindows("提示","联接断开!",0);
		Connect=0;
		break;
		}
	 case 115:New();break;
	 case 116:del();break;
	 case 121:Now();break;
	 case 122:History();break;
	 case 123:Control();break;
	 case 131:Setup();break;
	}
      }
      Com_Close();
     if(change){
	cfgfile=fopen("JRTZ.CFG","wb");
	fwrite(cfgfilehead,sizeof(cfgfilehead),1,cfgfile);
	fwrite(&COM,sizeof(COM),1,cfgfile);
	fwrite(&station_sum,sizeof(int),1,cfgfile);
	fwrite(station,sizeof(*station)*station_sum,1,cfgfile);

	fclose(cfgfile);
     }
     free(station);
     BOY_CLOSE_ALL();

     CLOSE_BOY_WINDOWS(&BOY_WINDOWS);    /* 关闭窗口 */
  }


