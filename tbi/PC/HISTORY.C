// # include <dos.h>
// # include <stdio.h>

// # include "c:\boy20\include\boywin.h" /* Ƕ��ͷ�ļ�, �йز����ṹ��Ϣ */
// # include "c:\boy20\include\key.h"    /* Ƕ��ͷ�ļ�, �йؼ���ɨ������Ϣ */
 # include "jrtz.h"
// # include <string.h>
extern char Connect;
 int  CreateErrorWindows(char *text);

 void History(void)        /* һ�����û�����Ĵ��� */
 {
	struct {
		char day[5];
		char Voltage_Max[10];
		char Voltage_Min[10];
		char Charge_Ah[10];
		char Discharge_Ah[10];
	}h[32];

	int *p;
   char *c;
   struct date date;
   struct time time;
   _History history;
   extern int current_station;
   extern _station *station;
   int FLAG = 1,i;               /* ѭ���ж� */
   FILE *fp;
   char savefile[13];
   int CASE;                   /* ����ֵ */
   static int  BOY_TOTAL = 10; /* �û������Ĳ������� */
   static TEST BOY_TEST;       /* �����ṹ */
   static int  BOY_TAB = 9;   /* ��ǰ�������ڴ˲����� */

   /* ����������:�μ��ֲ��98ҳ */
   static TYPE BOY_TYPE[10] = {
				 {99,0},{12,0},{3,0},{3,1},{3,2},
				 {3,3},{3,4},{1,0},{1,1},{1,2},

				};

   /* ����Ϊ���ںʹ����в����ṹ�Ķ���
      �����޸�,������ֲ��һ���ݵڶ��� */
    static KEY3D BOY_KEY3D[3] = {
				   {500,180,560,210,"",0,0,1,0,2,"����",0,0,15,0,1},
				   {500,250,560,280,"",0,0,1,0,2,"����",0,0,15,0,2},
				   {500,320,560,350,"",0,0,1,0,2,"����",27,0,15,0,3},
                                  };
    static LABEL BOY_LABEL[5] = {
				    {60,98,100,118,0,0,0,0,0,0,7,0,0,1,"����",0,""},
				    {100,98,170,118,0,0,0,0,0,0,7,0,0,1,"��ߵ�ѹ",0,""},
				    {170,98,240,118,0,0,0,0,0,0,7,0,0,1,"��͵�ѹ",0,""},
				    {245,98,315,118,0,0,0,0,0,0,7,0,0,1,"������",0,""},
				    {320,98,390,118,0,0,0,0,0,0,7,0,0,1,"�ŵ����",0,""},
				   };
	static LISTED BOY_LISTED[1] = {
				    {60,120,466,410,45,16,4,15,0,1,0,15,0,32,45,""},
				   };
    static WINDOWS BOY_WINDOWS = { 50,60,590,430,"��ʷ����",7,1,0,0,1,3,15,0,0,0,15,1,15,0,7,0,0};

    if(current_station==-1){
	strcpy(BOY_WINDOWS.text,"��ʷ����:δ����");
    }
    else{
	strcpy(BOY_WINDOWS.text,"��ʷ����:");
	strncat(BOY_WINDOWS.text,(char *)&station[current_station],sizeof(*station));
    }
    p=(int *)&history;
    FLAG=Connect;
    while(FLAG){
		sender(HistoryData);
		ReceviceData((char *)&history,sizeof(history));
		CASE=0;
		for(i=0;i<sizeof(history)/2-1;i++)CASE+=p[i];	//��У���
		if(CASE==p[sizeof(history)/2-1])FLAG=0;
	}
	c=(char *)h;
	for(i=0;i<sizeof(h);i++)c[i]='\0';

	for(i=0;i<32;i++){
	itoa(i,h[i].day,10);
	strcpy(h[i].Voltage_Min,hex(history.Data[(i+history.Data_Index)%32].Voltage_Min,1,"V"));
	strcpy(h[i].Voltage_Max,hex(history.Data[(i+history.Data_Index)%32].Voltage_Max,1,"V"));
	strcpy(h[i].Charge_Ah,hex(history.Data[(i+history.Data_Index)%32].Charge_Ah,0,"AH"));
	strcpy(h[i].Discharge_Ah,hex(history.Data[(i+history.Data_Index)%32].Discharge_Ah,0,"AH"));
    }
    c=(char *)h;
    for(i=0;i<sizeof(h);i++)c[i]=c[i]?c[i]:' ';
    BOY_LISTED[0].text=(char *)&h;


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
	 case 1:
	 case 2:{
		getdate(&date);
		gettime(&time);
		for(i=0;i<13;i++)savefile[i]='\0';
		strncpy(savefile,"H",1);
		strncat(savefile,station[current_station].NO,3);
		savefile[4]=date.da_mon/10+'0';
		savefile[5]=date.da_mon%10+'0';
		savefile[6]=date.da_day/10+'0';
		savefile[7]=date.da_day%10+'0';
		strcat(savefile,".TXT");
		if((fp=fopen(savefile,"wt"))==NULL){
			CreateErrorWindows("δ�ܽ����ļ�!");
			break;
		}
		fprintf(fp,"	��ʷ���ݼ�¼\n");
		fprintf(fp,"\nվ��:%s	�绰����:%s	˵��:%s\n",station[current_station].NO,station[current_station].phone,station[current_station].comment);
		fprintf(fp,"��¼ʱ��:%d��%d��%d�� %dʱ%d��\n",date.da_year,date.da_mon,date.da_day,time.ti_hour,time.ti_min);
		fprintf(fp,"����	��ߵ�ѹ	��͵�ѹ	������	�ŵ����\n");
		c=(char *)h;
		for(i=0;i<32;i++){
			fprintf(fp,"��%d��	%dV		%dV		%dAH		%dAH\n",i,history.Data[(i+history.Data_Index)%32].Voltage_Max/10,history.Data[(i+history.Data_Index)%32].Voltage_Min/10,history.Data[(i+history.Data_Index)%32].Charge_Ah,history.Data[(i+history.Data_Index)%32].Discharge_Ah);
		}
		fprintf(fp,"**********�ļ�����**********");
		fclose(fp);
		CreateWarningWindows("��ʾ","�洢���.",0);
		break;
	 }

	 case 3:
	 case WindowsClose:FLAG=1;break;
	}
      }
     CLOSE_BOY_WINDOWS(&BOY_WINDOWS);    /* �رմ��� */
  }