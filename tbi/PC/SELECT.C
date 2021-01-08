 # include "jrtz.h"

 #define ALTE 0x12
 #define ALTQ 0x10

 #define WAITTIME 60
extern char Connect;
extern int  DialogTotal;
extern  int  DialogTab;
extern  int  CS_Dialog ;
extern char DialogPath[MaxPath];
extern  char DLGPATH[MaxPath];
extern char BOY_FILE_NAME[MaxPath];

extern char DLL_openname[MaxPath];
extern TEST DLL_test;

extern TYPE  DialogType[15];
extern KEY3D DialogKey3d[5] ;
extern LABEL DialogLabel[5] ;
extern INPUTBOX DialogInputbox[3] ;
extern ICON DialogIcon[1] ;
extern PICTURE DialogPicture[1] ;
extern WINDOWS DialogWindows ;

 void win111(void)        /* 一个由用户定义的窗口 */
 {
   union{
	int status;
	char result[2];
	_status bits;
   }rs232;
   extern char COM;
   extern int current_station;
   char Phone[13];
   char result[20];
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
				   {450,180,510,202,"",0,0,1,0,2,"确定",13,0,15,0,1},
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
    static WINDOWS BOY_WINDOWS = { 100,100,540,350,"选择联接",7,1,0,0,1,3,15,0,0,0,15,1,15,0,7,0,0};

    extern int station_sum;
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
		current_station=BOY_LISTED[0].to;
		strncpy(Phone,station[current_station].phone,12);
		for(i=0;i<13;i++)if(Phone[i]==' ')Phone[i]=0;
		Com_Init(COM,4,8,1,3);
		Recvice_String(result);
		Send_String("\rat&fv0e0\r");
		delay(500);
		Recvice_String(result);
		if((strcmp(result,"0\r"))&&(strcmp(result,"at&fv0e0\r0\r"))){
			CreateErrorWindows("调制解调器未响应!");
			break;
		}
		strset(DLL_openname,'\0');
		strcpy(DLL_openname,DLGPATH);
		strcat(DLL_openname,"\\Warning1.Dlg");

		ReadDialogWindows(DLL_openname);
		strcpy(DialogLabel[0].text,"正在拨号,请等待...");
		SetDialogPath(DLGPATH);
		CreateDialogWindows();
		Send_String("ATDP");
		Send_String(Phone);
		Send_String("\r");
		for(i=0;i<WAITTIME*10;i++){
			delay(100);
			if(recvice_r())break;
		}

		CloseDialogWindows();

		Recvice_String(result);
		i=atoi(result);
		switch(i){
			case 1:{
				CreateWarningWindows("提示","建立联接!",0);
				Connect=1;
				break;
			}
			case 3:{
				CreateErrorWindows("对方未应答!");
				break;
			}
			case 6:{
				CreateErrorWindows("没有拨号音!");
				break;
			}
			case 7:{
				CreateErrorWindows("线路正忙!");
				break;
			}
			default:{
				CreateErrorWindows("未知错误.");
				break;
			}
			case 5:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 18:
			case 24:
			case 28:{
			       if(i==5)strcpy(result,"联接于1200bps.");
			       if(i==10)strcpy(result,"联接于2400bps.");
			       if(i==11)strcpy(result,"联接于4800bps.");
			       if(i==12)strcpy(result,"联接于9600bps.");
			       if(i==13)strcpy(result,"联接于14400bps.");
			       if(i==14)strcpy(result,"联接于19200bps.");
			       if(i==18)strcpy(result,"联接于57600bps.");
			       if(i==24)strcpy(result,"联接于7200bps.");
			       if(i==28)strcpy(result,"联接于38400bps.");
			       CreateWarningWindows("建立联接",result,0);
			       Connect=1;
			}
		}
	 }
	 case 2:
	 case WindowsClose:FLAG=1;break;
	}
      }
     CLOSE_BOY_WINDOWS(&BOY_WINDOWS);    /* 关闭窗口 */
  }
