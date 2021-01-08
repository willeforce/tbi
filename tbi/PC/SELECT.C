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

 void win111(void)        /* һ�����û�����Ĵ��� */
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
   int FLAG = 0;               /* ѭ���ж� */
   int i;
   int CASE;                   /* ����ֵ */
   static int  BOY_TOTAL = 7; /* �û������Ĳ������� */
   static TEST BOY_TEST;       /* �����ṹ */
   static int  BOY_TAB = 3;   /* ��ǰ�������ڴ˲����� */

   /* ����������:�μ��ֲ��98ҳ */
   static TYPE BOY_TYPE[7] = {
				 {99,0},{1,0},{1,1},{12,0},{3,0},
				 {3,1},{3,2},
				};

   /* ����Ϊ���ںʹ����в����ṹ�Ķ���
      �����޸�,������ֲ��һ���ݵڶ��� */
    extern _station *station;

    static KEY3D BOY_KEY3D[2] = {
				   {450,180,510,202,"",0,0,1,0,2,"ȷ��",13,0,15,0,1},
				   {450,240,510,262,"",0,0,1,0,2,"ȡ��",27,0,15,0,2},
				  };
    static LABEL BOY_LABEL[3] = {
				    {110,130,150,150,0,0,0,0,0,0,7,0,0,1,"վ��",0,""},
				    {180,130,220,150,0,0,0,0,0,0,7,0,0,1,"˵��",0,""},
				    {320,130,400,150,0,0,0,0,0,0,7,0,0,1,"�绰����",0,""},
				   };
    static LISTED BOY_LISTED[1] = {
				    {110,155,412,337,sizeof(*station),10,1,9,0,1,0,255,0,10,sizeof(*station),""},
				   };
    static WINDOWS BOY_WINDOWS = { 100,100,540,350,"ѡ������",7,1,0,0,1,3,15,0,0,0,15,1,15,0,7,0,0};

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
    /* �������ڼ����� */

    while(!FLAG)
     { /* �õ�ϵͳ�¼� */
       BOY_GET_TEST(&BOY_TEST);
       CASE=BOY_ALL_TEST(&BOY_WINDOWS,&BOY_TEST,BOY_TOTAL,&BOY_TAB,BOY_TYPE);
       /* �õ�����ֵ */
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
			CreateErrorWindows("���ƽ����δ��Ӧ!");
			break;
		}
		strset(DLL_openname,'\0');
		strcpy(DLL_openname,DLGPATH);
		strcat(DLL_openname,"\\Warning1.Dlg");

		ReadDialogWindows(DLL_openname);
		strcpy(DialogLabel[0].text,"���ڲ���,��ȴ�...");
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
				CreateWarningWindows("��ʾ","��������!",0);
				Connect=1;
				break;
			}
			case 3:{
				CreateErrorWindows("�Է�δӦ��!");
				break;
			}
			case 6:{
				CreateErrorWindows("û�в�����!");
				break;
			}
			case 7:{
				CreateErrorWindows("��·��æ!");
				break;
			}
			default:{
				CreateErrorWindows("δ֪����.");
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
			       if(i==5)strcpy(result,"������1200bps.");
			       if(i==10)strcpy(result,"������2400bps.");
			       if(i==11)strcpy(result,"������4800bps.");
			       if(i==12)strcpy(result,"������9600bps.");
			       if(i==13)strcpy(result,"������14400bps.");
			       if(i==14)strcpy(result,"������19200bps.");
			       if(i==18)strcpy(result,"������57600bps.");
			       if(i==24)strcpy(result,"������7200bps.");
			       if(i==28)strcpy(result,"������38400bps.");
			       CreateWarningWindows("��������",result,0);
			       Connect=1;
			}
		}
	 }
	 case 2:
	 case WindowsClose:FLAG=1;break;
	}
      }
     CLOSE_BOY_WINDOWS(&BOY_WINDOWS);    /* �رմ��� */
  }