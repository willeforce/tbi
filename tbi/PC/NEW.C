//#include<string.h>
//#include<stdio.h>
//#include<ctype.h>
//#include<alloc.h>
#include"jrtz.h"

// # include "c:\boy20\include\boywin.h" /* Ƕ��ͷ�ļ�, �йز����ṹ��Ϣ */
// # include "c:\boy20\include\key.h"    /* Ƕ��ͷ�ļ�, �йؼ���ɨ������Ϣ */

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

 void New(void)        /* һ�����û�����Ĵ��� */
 {
   FILE *cfgfile;
   int FLAG = 0;               /* ѭ���ж� */
   int i,CASE;                   /* ����ֵ */
   static int  BOY_TOTAL = 9; /* �û������Ĳ������� */
   static TEST BOY_TEST;       /* �����ṹ */
   static int  BOY_TAB = 6;   /* ��ǰ�������ڴ˲����� */

   /* ����������:�μ��ֲ��98ҳ */
   static TYPE BOY_TYPE[9] = {
				 {99,0},{1,0},{1,1},{3,0},{3,1},
				 {3,2},{5,0},{5,1},{5,2},
				};

   /* ����Ϊ���ںʹ����в����ṹ�Ķ���
      �����޸�,������ֲ��һ���ݵڶ��� */
    static KEY3D BOY_KEY3D[2] = {
				   {180,280,240,302,"",0,0,1,0,2,"ȷ��",0,0,15,0,1},
				   {280,280,340,302,"",0,0,1,0,2,"ȡ��",27,0,15,0,2},
				  };
    static LABEL BOY_LABEL[3] = {
				    {100,150,150,170,0,0,0,0,0,0,7,0,0,1,"���:",0,""},
				    {100,180,180,200,0,0,0,0,0,0,7,0,0,1,"�绰����:",0,""},
				    {100,210,150,230,0,0,0,0,0,0,7,0,0,1,"˵��:",0,""},
				   };
    static INPUTBOX BOY_INPUTBOX[3] = {
					{200,150,6,0,3,1,0,0,0,15,15,0,3,1,0,0,"","",0,1},
					{200,180,12,0,12,1,0,0,0,15,15,0,11,1,0,0,"","",11,-3},
					{200,210,20,0,20,1,0,0,0,15,15,0,12,1,0,0,"","",12,-7},
				      };
    static WINDOWS BOY_WINDOWS = { 50,100,440,350,"�½�",7,1,0,0,1,3,15,0,0,0,15,1,15,0,7,0,0};

    BOY_WINDOWS.key = BOY_KEY3D;
    BOY_WINDOWS.lab = BOY_LABEL;
    BOY_WINDOWS.inp = BOY_INPUTBOX;

    CREATE_WINDOWS_ALL(&BOY_WINDOWS,&BOY_TYPE[0],BOY_TOTAL,BOY_TAB);
    /* �������ڼ����� */

    while(!FLAG)
     { /* �õ�ϵͳ�¼� */
       BOY_GET_TEST(&BOY_TEST);
       CASE=BOY_ALL_TEST(&BOY_WINDOWS,&BOY_TEST,BOY_TOTAL,&BOY_TAB,BOY_TYPE);
       /* �õ�����ֵ */
       switch(CASE)
       {
	 /* ѡ�д�����˵�֮�رմ����� */
	 case 1:{
		if(!test(BOY_WINDOWS.inp[0].text)){
			CreateErrorWindows("��ű�����001-255���ظ�����!");
			BOY_TAB=6;
			break;
		}
		if(!test(BOY_WINDOWS.inp[1].text)){
			CreateErrorWindows("�绰�������������!");
			BOY_TAB=7;
			break;
		}
		station_sum++;
		if((station=realloc(station,sizeof(*station)*station_sum))==NULL)CreateErrorWindows("�ڴ治��!");
		strncpy(station[station_sum-1].NO,BOY_WINDOWS.inp[0].text,3);
		strncpy(station[station_sum-1].phone,BOY_WINDOWS.inp[1].text,12);
		strncpy(station[station_sum-1].comment,BOY_WINDOWS.inp[2].text,20);
		change=1;
	 }
	 case 2:
	 case WindowsClose:FLAG=1;break;
	}
      }
     CLOSE_BOY_WINDOWS(&BOY_WINDOWS);    /* �رմ��� */
  }
