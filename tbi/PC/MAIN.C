//# include "c:\JRTZ\boywin.h" /* Ƕ��ͷ�ļ�, �йز����ṹ��Ϣ */
//# include "c:\JRTZ\key.h"    /* Ƕ��ͷ�ļ�, �йؼ���ɨ������Ϣ */
//#include "c:\JRTZ\dialog.h"
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
#include "jrtz.h"
char *Help[5] = {
	{"����̫���ܳ�粢�������"},
	{"ң��ң��ϵͳ"},
	{"(c) V1.0"},
	{"�������: �뽨��"},
	{"1998 �� 5 ��"}
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
			  "c:\\boy20\\OVL",  /* ȫƴ,��ƴ���, BGI */
			  "c:\\boy20\\OVL",  /* 16�����ּ�Ӣ���ֿ� */
			  "c:\\boy20\\FONT24",  /* 24�����ֿ� */
			  "c:\\boy20\\OVL"   /* ͼ����ʱ�����ļ� */
		    };

 int main(void)
  {
    char pass[sizeof(cfgfilehead)];
    FILE *cfgfile;
	strcpy(Serial,"001-0112940005");
    BOY_SETUP_ALL();       /* ϵͳ���� */
    BOY_DESKTOP(0,"");     /* �����ֽ */
    CREATE_BOY_CHINESE();  /* ������������ (�粻�����뺺�ֿ�ɾȥ����)*/


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
	BOY_Windows();         /* �����û����ڲ��� */
	BOY_CLOSE_ALL();       /* �ر�ϵͳ */
	return 1;              /* ������� */
  }


 void BOY_Windows(void)        /* һ�����û�����Ĵ��� */
 {
   FILE *cfgfile;
   int FLAG = 0;               /* ѭ���ж� */
   int CASE;                   /* ����ֵ */
   static int  BOY_TOTAL = 1; /* �û������Ĳ������� */
   static TEST BOY_TEST;       /* �����ṹ */
   static int  BOY_TAB = 0;   /* ��ǰ�������ڴ˲����� */

   /* ����������:�μ��ֲ��98ҳ */
   static TYPE BOY_TYPE[1] = {
				 {18,0},
				};

   /* ����Ϊ���ںʹ����в����ṹ�Ķ���
	  �����޸�,������ֲ��һ���ݵڶ��� */
	static MENU BOY_MENU[15] = {
				  {"F.���� ",8448,1,0,0,11,9,26,1},
					  {"���� F3",15616,1,1,0,111,9,48,0},
					  {"�Ͽ�",0,1,1,0,114,9,68,0},
					  {"�غ� F2",15360,1,1,0,112,9,88,0},
					  {"     ",0,-1,1,0,0,9,108,0},
					  {"�½� ",0,1,1,0,115,9,128,0},
					  {"ɾ�� ",0,1,1,0,116,9,148,0},
					  {"     ",0,-1,1,0,0,9,168,0},
					  {"�˳� ALT-X",11520,1,1,0,113,9,188,0},
				  {"V.����",12032,1,0,0,12,81,26,1},
					  {"��ǰ״̬",0,1,1,0,121,81,48,0},
					  {"��ʷ����",0,1,1,0,122,81,68,0},
					  {"����������",0,1,1,0,123,81,88,0},
				  {"S.����",7936,1,0,0,13,145,26,1},
					  {"���ƽ����",0,1,1,0,131,145,48,0},
				};
	static WINDOWS BOY_WINDOWS = { 0,0,639,449,"̫�������ܳ�粢�������ͨѶ����ϵͳ",7,1,0,0,1,3,15,0,0,15,15,1,15,0,7,0,0};

	BOY_WINDOWS.menu= BOY_MENU;

	CREATE_WINDOWS_ALL(&BOY_WINDOWS,&BOY_TYPE[0],BOY_TOTAL,BOY_TAB);

	strcpy(DLGPATH,BOYPATH.ovl);  // �Ի�����Դ�ļ���·��
    CreateAboutWindows(Help); // ABOUT ����


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
		CreateWarningWindows("��ʾ","���ӶϿ�!",0);
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

     CLOSE_BOY_WINDOWS(&BOY_WINDOWS);    /* �رմ��� */
  }

