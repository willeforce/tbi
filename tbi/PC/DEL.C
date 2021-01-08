//#include<string.h>

// # include "c:\boy20\include\boywin.h" /* 嵌入头文件, 有关部件结构信息 */
// # include "c:\boy20\include\key.h"    /* 嵌入头文件, 有关键盘扫描码信息 */
 # include "jrtz.h"

 void del(void)        /* 一个由用户定义的窗口 */
 {
   int FLAG = 0;               /* 循环判断 */
   int i;
   int CASE;                   /* 返回值 */
   static int  BOY_TOTAL = 7; /* 用户创建的部件数量 */
   static TEST BOY_TEST;       /* 动作结构 */
   static int  BOY_TAB = 3;   /* 当前激活项在此部件上 */

   /* 部件的类型:参见手册第98页 */
   static TYPE BOY_TYPE[7] = {
				 {99,0},{1,0},{1,1},{12,0},{3,0},
				 {3,1},{3,2},
				};

   /* 以下为窗口和窗口中部件结构的定义
      如想修改,请参照手册第一部份第二章 */
    extern _station *station;

    static KEY3D BOY_KEY3D[2] = {
				   {450,180,510,202,"",0,0,1,0,2,"删除",13,0,15,0,1},
				   {450,240,510,262,"",0,0,1,0,2,"取消",27,0,15,0,2},
				  };
    static LABEL BOY_LABEL[3] = {
				    {110,130,150,150,0,0,0,0,0,0,7,0,0,1,"站号",0,""},
				    {180,130,220,150,0,0,0,0,0,0,7,0,0,1,"说明",0,""},
				    {320,130,400,150,0,0,0,0,0,0,7,0,0,1,"电话号码",0,""},
				   };
    static LISTED BOY_LISTED[1] = {
				    {110,155,412,337,sizeof(*station),10,1,9,0,1,0,255,0,10,sizeof(*station),""},
				   };
    static WINDOWS BOY_WINDOWS = { 100,100,540,350,"删除站点",7,1,0,0,1,3,15,0,0,0,15,1,15,0,7,0,0};

    extern int station_sum;
    extern char change;
    char *p;
    BOY_LISTED[0].sl=station_sum;
    p=(char *)station;
    for(i=0;i<station_sum;i++){
	station[i].NO[3]=station[i].phone[12]=station[i].comment[20]=' ';
    }
    for(i=0;i<sizeof(*station)*station_sum;i++)
	if(!p[i])p[i]=' ';
    BOY_LISTED[0].text=(char *)station;

    BOY_WINDOWS.key = BOY_KEY3D;
    BOY_WINDOWS.lab = BOY_LABEL;
    BOY_WINDOWS.lst = BOY_LISTED;

    CREATE_WINDOWS_ALL(&BOY_WINDOWS,&BOY_TYPE[0],BOY_TOTAL,BOY_TAB);
    /* 建立窗口及部件 */

    while(!FLAG)
     { /* 得到系统事件 */
       BOY_GET_TEST(&BOY_TEST);
       CASE=BOY_ALL_TEST(&BOY_WINDOWS,&BOY_TEST,BOY_TOTAL,&BOY_TAB,BOY_TYPE);
       /* 得到返回值 */
       switch(CASE)
       {

	 case 1:{
		i=CreateWarningWindows("确认删除","确定删除此站点?",1);
		if(i!=30)break;
		for(i=BOY_LISTED[0].to;i<station_sum;i++){
			strncpy(station[i].NO,station[i+1].NO,3);
			strncpy(station[i].phone,station[i+1].phone,12);
			strncpy(station[i].comment,station[i+1].comment,20);
		}
		station_sum--;
		change=1;
	 }
	 case 2:
	 case WindowsClose:FLAG=1;break;
	}
      }
     CLOSE_BOY_WINDOWS(&BOY_WINDOWS);    /* 关闭窗口 */
  }
