  /*
			�Ի�����ƹ���ʹ��˵��

    �ڴ��ڽ�����, ʹ�������ǶԻ��򴰿�, �ڶԻ��򴰿���, ϵͳ��ʾһЩ
    ��Ϣ���û�, �û����԰�����ʾ���в���. ����: �˳�����, ���־�����Ϣ
    ���ڵȵ�. �� BoyWindows �е������汾��, û�жԻ����ר�Ź���, ����
    ���汾��, �صؼ�����һ����. �û������ڶԻ����м��밴ť, ��ǩ, ͼ��
    , ͼ��. ��������һ����Դ�ļ�.

    BoyWindows �жԻ�����ص�:

    1. �ڴ濪����С
    ʹ�öԻ�����ƹ��߿����Ի���, ������ƶ��ٸ��Ի��򴰿�, �ڴ濪����
    Ϊ 4K �Ӹ����Ͻ���� BoyWindows �ڴ��ռ�ô������.

    2. �޸ķ���
    ʹ�öԻ�����ƹ��߿����ĶԻ���, ���Ҫ�޸Ľ���Ч��, ����. ��������
    Ҫ�޸ĳ���, ֻ���öԻ�����ƹ����޸ļ���.


һ, �Ի�����˵��

    �Ի����������ڴ���, �ı�, ���Ժ�����Ի���, ���ڶԻ����ڽ��п���.
�Ի����� BoyWindows Ϊ����Ŀ�ĵ���������������ʱ����, ����ʹ�ú�������
�����. Ӧ�ó��򳣳��öԻ�����û���ʾ�йص�ǰ����ѡ��ĸ�����Ϣ, �±�
��Ҫ�����˸����Ի�����.


       ��    ��             ʹ    ��

    ReadDialogWindows    ����Ի�����Դ�ļ�
    CreateDialogWindows  �����Ի���
    GetDialogWindows     �Ի�����
    CloseDialogWindows   �رնԻ����ͷ��ڴ�
    SetDialogPath        ������Դ��·��
    GetDialogPath        ��ȡ�����õ���Դ·��

1.1 �����Ի���

    �Ի�����Դ�ļ��ԶԻ����������, ��ʹ�ÿ����߿��Ըı�ģ������ظĶ�
Դ�������. ReadDialogWindows �� CreateDialogWindows ���������ڴ����Ի�
��ʱ����Դװ���ڴ�, Ȼ��ʹ�öԻ���ģ�����Ϣ�����Ի���, �����Ի���λ,
Ϊ�Ի��򴴽��ͷ��ÿ���.

1.2 �Ի���ķ���ֵ

    �����Ի���֮��Ҫ�ȵ����� CloseDialogWindows �����Ž���. ��ʱ���޷�
��ֵ. �û�Ҫ�õ�����ֵ����� GetDialogWindows ����. ����ֵ�����û�����Դ
�ļ��и�������������ķ���ֵ.

    ReadDialogWindows
    ����:   ����Ի�����Դ�ļ�
    �÷�:   # include "dialog.h"
	    int  ReadDialogWindows(char *fn);
    ˵��:   ��һ���Ի������Դ�ļ�, �����뵽�ڴ�.
	    fn ��Դ�ļ���.
    ����ֵ: 1:  ����ɹ�
	    0:  ���㹻�ڴ������Դ
	    -1: �ļ��������
	    -2: �� BoyWindows DialogTools 1.0a ����Դ�ļ�

1.3 ����Ŀ¼

   ���ڰ���ĸ˳����� BoyWindows ���ṩ�ĶԻ��������ƽӿڵĸ�������.

   CreateDialogWindows
   ����:   �����Ի���
   �÷�:   # include "dialog.h"
	   void CreatDialogWindows(void);
   ˵��:   �����Ѵ򿪵���Դ�ļ�����Ļ�ϴ���һ���Ի���.
	   �䴴���ṹΪ
	   int   DialogTotal           ��Դ����
	   int   DialogTab             �Ի��򼤻������λ��
	   TYPE  DialogType[15]        �����ṹ
	   KEY3D DialogKey3d[5]        �Ի����еİ�ť�ṹ
	   LABEL DialogLabel[5]        �Ի����еı�ǩ�ṹ
	   INPUTBOX DialogInputbox[3]  �Ի����е������ṹ
	   ICON DialogIcon[1]          �Ի����е�ͼ��ṹ
	   PICTURE DialogPicture[1]    �Ի����е�ͼ�νṹ
	   WINDOWS DialogWindows       �Ի���Ĵ��ڽṹ
   �μ�:   ����������Ľṹ����μ���һ�½�.
   ����ֵ: ��

   CloseDialogWindows
   ����:   �رնԻ����ͷ��ڴ�
   �÷�:   # include "dialog.h"
           void CloseDialogWindows(void);
   ����ֵ: ��

   GetDialogPath
   ����:   ��ȡ�����õ���Դ·��
   �÷�:   # include "dialog.h"
           char *SetDialogPath(void);
   ����ֵ: ���������õ���Դ·���ַ���.

   GetDialogWindows
   ����:   �Ի�����
   �÷�:   # include "dialog.h"
	   int  GetDialogWindows(TEST *);
   ˵��:   ���Ѵ򿪵ĶԻ�����м��, ������ֵ.
	   TEST * Ϊһ����Ϣ�ṹ.
	   ����ͨ������ BOY_GET_TEST ��ȡ.
   ����ֵ: -1: �޶�Ӧ����
	   -2: ��ǰû�жԻ��򴰿ڴ�
	   xxxx: �Ի��򴰿��в����ķ���ֵ

   SetDialogPath
   ����:   ������Դ��·��
   �÷�:   # include "dialog.h"
	   int  SetDialogPath(char *);
   ˵��:   char *�Ѵ򿪵ĶԻ�����Դ��·��.
	   ��Ϊ����Դ�ļ����кܶ����Դ, ����: ͼ��, ͼ��, ���Ƕ���
	   ������, ���û������Ի���֮����Ҫ������Ʒ��, �п�����Ϊ
	   �����ı仯�����Ҳ�����Դ��ʱ��, ����ʹ�ñ��������Խ���Щ
	   ��Դͳһ�����ͬһĿ¼��, �Դﵽ��Ʒ����Ч��.
	   ���û���������֮��, ����������ָ����Ŀ¼�в�����Դ.
   ����ֵ: 1: ���óɹ�
	   0: ��ǰû�жԻ��򴰿ڵ����ڴ�
	   ����: �����õ���Դ·��������ȫ�̱���DialogPath��.

1.4 ȫ�̱������ṹ����

   CS_DIALOG
   ����:   1 �Ѿ���һ���Ի�������ڴ�
	   0 û�жԻ���

   WM_CLOSE
   ����:   �Ի���ر���

   WM_MOVE
   ����:   �Ի����ƶ���ı��С

   DialogPath[MaxPath];
   ����:   �򿪶Ի�����Դ�ļ���·��

   DLGPATH[MaxPath];
   ����:   BoyWindows ϵͳ�ṩ�ֳɵĶԻ�����Դ���·��
	   �� ABOUT �Ի���, ��ʾ��Ϣ�Ի���, ������Ϣ�Ի����.
	   �û�����ֱ��ʹ��. �μ���һ�ڵĴ��ڿ�

   int      DialogTotal           ��Դ����
   int      DialogTab             �Ի��򼤻������λ��
   TYPE     DialogType[15]        �����ṹ
   KEY3D    DialogKey3d[5]        �Ի����еİ�ť�ṹ
   LABEL    DialogLabel[5]        �Ի����еı�ǩ�ṹ
   INPUTBOX DialogInputbox[3]     �Ի����е������ṹ
   ICON     DialogIcon[1]         �Ի����е�ͼ��ṹ
   PICTURE  DialogPicture[1]      �Ի����е�ͼ�νṹ
   WINDOWS  DialogWindows         �Ի���Ĵ��ڽṹ

1.5, ʵ��

    1.5.1. ����һ�� ABOUT ͨ�öԻ�����

    ����Ʒ�������ж���һ�� ABOUT ����, ����������п�����ʾ��������
    �����Ϣ. ����: ��Ȩ��Ϣ, ��ϵ�취�ȵ�.
    ����, ������ Dialog Tools ������һ�� ABOUT �Ի���. ������Ի���
    ����һ����ť, ��������(��ǩ)��һ��ͼ��. ��������һ����Դ�ļ�:
    ABOUT.DLG

    # include "boywin.h"
    # include "key.h"
    # include "dialog.h"

    int  UserAboutWindows(char *text[5]);

    SETPATH BOYPATH = {"C:\\BOY\\OVL",
		       "C:\\BOY\\OVL",
		       "C:\\BOY\\FONT24",
		       "C:\\BOY\\OVL"};
    char *Help[5] = {
		      {"�Ի�����ƹ��� Dialog Tools 1.0a"},
		      {"������ѧ�����˹�˾ ����ռ���ҵ��"},
		      {"����ռ���������Ⱥ"},
		      {"��������: �� ��"},
		      {"1994 �� 12 ��"}
		     };

   int main(void)
   {
     BOY_SETUP_ALL();         // ϵͳ����
     strcpy(DLGPATH,"C:\\DIALOG");  // �Ի�����Դ�ļ���·��
     UserAboutWindows(Help); // ABOUT ����
     BOY_CLOSE_ALL();          // �ر�ϵͳ
     return 1;                 // �������
    }

    int  UserAboutWindows(char *text[5])
    {
     int FLAG = 0;
     int CASE;
     int i;
     char openname[MAXPATH];
     TEST Test;

     strset(openname,'\0');
     strcpy(openname,DLGPATH);
     strcat(openname,"\\ABOUT.DLG");  // ָ����Դ�ļ���·��

     ReadDialogWindows(openname);     // ����Դ�ļ������ڴ�
     for(i=0;i<5;i++)
	strcpy(DialogLabel[i].text,text[i]);  // ABOUT ��������

     // ��Ϊ���ǵ�����һ��ͨ�õĶԻ������Խ��ж�̬���޸�,
     // �����һ��ר�öԻ������� Dialog Tools ��ֱ��ָ���Ϳ�����.
     // ͬ��: �����Դ�ļ�����֮���������ж�̬�޸Ŀ�ֱ�ӶԶԻ���
     //       �Ľṹ�޸�, �ṹ���Ʋμ�ǰһ��ȫ�̱������ṹ����.
     // ע��: ���ж�̬�޸�ʱҪһ��Ҫ��ReadDialogWindows����֮��, ����
     //	      ���ᱻ����.

     SetDialogPath(DLGPATH);          // ָ����Դ�ļ��и�����Դ��·��
     CreateDialogWindows();           // ����Ļ�Ͻ����Ի���

    while(!FLAG)
    {
     BOY_GET_TEST(&Test);             // �õ�ϵͳ�¼�
     CASE=GetDialogWindows(&Test);    // �ԶԻ�����м��
     switch(CASE)
     {
      case 100:break;                 // ������ť<����> �й����Լ�����ֵ
				      // ����� Dialog Tools �ۿ�
      case WM_CLOSE:FLAG=1;break;     // ѡ�񴰿ڽǲ˵�:�˳�
     }
    }
    CloseDialogWindows();
    return (CASE);
   }

   1.5.2. һ������Ի���
   ����Ի����ǳ����бز����ٵ�, �����û���ʾһЩ��Ҫ����Ϣ, ���û�����ѡ��.
   ����Ҫ��һ��������ѡ��ľ���Ի��� (����������ť, һ��Ϊȷ��, һ��Ϊ����).
   ����, ���������� Dialog Tools ������һ������Ի���. ������Ի������ж�����
   ť, һ������(��ǩ)��һ��ͼ��. ��������һ����Դ�ļ�: WARNING.DLG

    # include "boywin.h"
    # include "key.h"
    # include "dialog.h"

    int  UserErrorWindows(char *text);

    SETPATH BOYPATH = {"C:\\BOY\\OVL",
		       "C:\\BOY\\OVL",
		       "C:\\BOY\\FONT24",
		       "C:\\BOY\\OVL"};

    int main(void)
    {
     BOY_SETUP_ALL();         // ϵͳ����
     strcpy(DLGPATH,"C:\\DIALOG");  // �Ի�����Դ�ļ���·��
     while(UserErrorWindows("�Ƿ�Ҫ�˳� DialogTools?")==100)
     BOY_CLOSE_ALL();          // �ر�ϵͳ
     return 1;                 // �������
    }

   int  UserErrorWindows(char *text)
   {
    int FLAG = 0;
    int CASE;
    char openname[MAXPATH];
    TEST Test;

    strset(openname,'\0');
    strcpy(openname,DLGPATH);
    strcat(openname,"\\Warning.Dlg");

    ReadDialogWindows(openname);
    strcpy(DialogLabel[0].text,text);
    SetDialogPath(DLGPATH);
    CreateDialogWindows();

    while(!FLAG)
    {
     BOY_GET_TEST(&Test);
     CASE=GetDialogWindows(&Test);
     switch(CASE)
     {
      case 100:FLAG=1;break;
      case 101:
      case WM_CLOSE:FLAG=1;break;
     }
    }
   CloseDialogWindows();
   return (CASE);
  }
*/

 # define WM_CLOSE -7
 # define WM_MOVE -9

 void CloseDialogWindows(void);
 int  CreateAboutWindows(char *text[5]);
 void CreateDialogWindows(void);
 int  CreateErrorWindows(char *text);
 int  CreateFileWindows(char *find,int Style);
 int  CreateInputWindows(char *text1,char *text2);
 int  CreateWarningWindows(char *name,char *text,int type);
 int  CreateFileWindows(char *,int);
 int  GetDialogWindows(TEST *);
 int  ReadDialogWindows(char *);
 int  SetDialogPath(char *);

 extern int  CS_Dialog;
 extern int  DialogTotal;
 extern int  DialogTab;
 extern char DialogPath[MaxPath];
 extern char DLGPATH[MaxPath];
 extern char BOY_FILE_NAME[MaxPath];

 extern TYPE  	 DialogType[15];
 extern KEY3D 	 DialogKey3d[5];
 extern LABEL 	 DialogLabel[5];
 extern INPUTBOX DialogInputbox[3];
 extern ICON     DialogIcon[1];
 extern PICTURE  DialogPicture[1];
 extern WINDOWS  DialogWindows;
