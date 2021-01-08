#include "jrtz.h"

// # include "c:\boy20\include\boywin.h" /* 嵌入头文件, 有关部件结构信息 */
// # include "c:\boy20\include\key.h"    /* 嵌入头文件, 有关键盘扫描码信息 */


 void Setup(void)        /* 一个由用户定义的窗口 */
 {
   extern char COM;
   extern char change;
   int FLAG = 0;               /* 循环判断 */
   int i,CASE;                   /* 返回值 */
   static int  BOY_TOTAL = 7; /* 用户创建的部件数量 */
   static TEST BOY_TEST;       /* 动作结构 */
   static int  BOY_TAB = 3;   /* 当前激活项在此部件上 */

   /* 部件的类型:参见手册第98页 */
   static TYPE BOY_TYPE[7] = {
				 {99,0},{6,0},{6,1},{6,2},{6,3},
				 {1,0},{1,1},
				};

   /* 以下为窗口和窗口中部件结构的定义
      如想修改,请参照手册第一部份第二章 */
    static KEY3D BOY_KEY3D[2] = {
				   {214,284,274,306,"",0,0,1,0,2,"确定",0,0,15,0,1},
				   {314,284,374,306,"",0,0,1,0,2,"取消",27,0,15,0,2},
				  };
    static OPTION BOY_OPTION[4] = {
				    {284,184,"COM1",0,1,0,0,7,0,1,"",0},
				    {284,204,"COM2",0,1,0,0,7,1,1,"",0},
				    {284,224,"COM3",0,1,0,0,7,0,1,"",0},
				    {284,244,"COM4",0,1,0,0,7,0,1,"",0},
				   };
    static WINDOWS BOY_WINDOWS = { 154,144,434,315,"调制解调器设置",7,1,0,0,1,3,15,0,0,0,15,1,15,0,7,0,0};

    for(i=0;i<4;i++){
	if(COM==i)BOY_OPTION[i].YN=1;
	else BOY_OPTION[i].YN=0;
    }
    BOY_WINDOWS.key = BOY_KEY3D;
    BOY_WINDOWS.opti= BOY_OPTION;

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
	 case 1:for(i=0;i<4;i++){
		if(BOY_OPTION[i].YN==1){
			if(COM!=i)change=1;
			COM=i;
			break;
		}
	 }

	 case 2:
	 case WindowsClose:FLAG=1;break;
	}
      }
     CLOSE_BOY_WINDOWS(&BOY_WINDOWS);    /* 关闭窗口 */
  }
