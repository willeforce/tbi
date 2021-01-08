  /*
			对话框设计工具使用说明

    在窗口界面中, 使用最多的是对话框窗口, 在对话框窗口中, 系统提示一些
    信息给用户, 用户可以按照提示进行操作. 例如: 退出窗口, 各种警告信息
    窗口等等. 在 BoyWindows 中的以往版本中, 没有对话框的专门工具, 在这
    个版本中, 特地加入这一工具. 用户可以在对话框中加入按钮, 标签, 图形
    , 图标. 并且生成一个资源文件.

    BoyWindows 中对话框的特点:

    1. 内存开销极小
    使用对话框设计工具开发对话框, 不论设计多少个对话框窗口, 内存开销均
    为 4K 从根本上解决了 BoyWindows 内存的占用大的问题.

    2. 修改方便
    使用对话框设计工具开发的对话框, 如果要修改界面效果, 布局. 根本不需
    要修改程序, 只需用对话框设计工具修改即可.


一, 对话框函数说明

    对话框函数可用于创建, 改变, 测试和清除对话框, 并在对话框内进行控制.
对话框是 BoyWindows 为特殊目的的输入所创建的临时窗口, 并在使用后立即将
它清除. 应用程序常常用对话框给用户揭示有关当前命令选择的附加信息, 下表
简要描述了各个对话函数.


       函    数             使    用

    ReadDialogWindows    读入对话框资源文件
    CreateDialogWindows  建立对话框
    GetDialogWindows     对话框检测
    CloseDialogWindows   关闭对话框并释放内存
    SetDialogPath        设置资源的路径
    GetDialogPath        获取已设置的资源路径

1.1 创建对话框

    对话框资源文件对对话框进行描述, 这使得开发者可以改变模板而不必改动
源程序代码. ReadDialogWindows 和 CreateDialogWindows 函数用于在创建对话
框时把资源装进内存, 然后使用对话框模板的信息创建对话框, 并将对话框定位,
为对话框创建和放置控制.

1.2 对话框的返回值

    创建对话框之后要等到调用 CloseDialogWindows 函数才结束. 此时并无返
回值. 用户要得到返回值需调用 GetDialogWindows 函数. 返回值等于用户在资源
文件中给各个部件定义的返回值.

    ReadDialogWindows
    功能:   读入对话框资源文件
    用法:   # include "dialog.h"
	    int  ReadDialogWindows(char *fn);
    说明:   打开一个对话框的资源文件, 并读入到内存.
	    fn 资源文件名.
    返回值: 1:  读入成功
	    0:  无足够内存分配资源
	    -1: 文件读入出错
	    -2: 非 BoyWindows DialogTools 1.0a 的资源文件

1.3 函数目录

   本节按字母顺序介绍 BoyWindows 所提供的对话框程序设计接口的各个函数.

   CreateDialogWindows
   功能:   建立对话框
   用法:   # include "dialog.h"
	   void CreatDialogWindows(void);
   说明:   根据已打开的资源文件在屏幕上创建一个对话框.
	   其创建结构为
	   int   DialogTotal           资源数量
	   int   DialogTab             对话框激活框所在位置
	   TYPE  DialogType[15]        创建结构
	   KEY3D DialogKey3d[5]        对话框中的按钮结构
	   LABEL DialogLabel[5]        对话框中的标签结构
	   INPUTBOX DialogInputbox[3]  对话框中的输入框结构
	   ICON DialogIcon[1]          对话框中的图标结构
	   PICTURE DialogPicture[1]    对话框中的图形结构
	   WINDOWS DialogWindows       对话框的窗口结构
   参见:   其各个部件的结构定义参见上一章节.
   返回值: 无

   CloseDialogWindows
   功能:   关闭对话框并释放内存
   用法:   # include "dialog.h"
           void CloseDialogWindows(void);
   返回值: 无

   GetDialogPath
   功能:   获取已设置的资源路径
   用法:   # include "dialog.h"
           char *SetDialogPath(void);
   返回值: 返回已设置的资源路径字符串.

   GetDialogWindows
   功能:   对话框检测
   用法:   # include "dialog.h"
	   int  GetDialogWindows(TEST *);
   说明:   对已打开的对话框进行检测, 并返回值.
	   TEST * 为一个消息结构.
	   可以通过函数 BOY_GET_TEST 获取.
   返回值: -1: 无对应操作
	   -2: 当前没有对话框窗口打开
	   xxxx: 对话框窗口中部件的返回值

   SetDialogPath
   功能:   设置资源的路径
   用法:   # include "dialog.h"
	   int  SetDialogPath(char *);
   说明:   char *已打开的对话框资源的路径.
	   因为在资源文件中有很多的资源, 例如: 图形, 图标, 它们都是
	   分立的, 在用户设计完对话框之后是要进行商品化, 有可能因为
	   环境的变化而有找不到资源的时候, 所以使用本函数可以将这些
	   资源统一归放在同一目录中, 以达到商品化的效果.
	   在用户进行设置之后, 函数将在其指定的目录中查找资源.
   返回值: 1: 设置成功
	   0: 当前没有对话框窗口调入内存
	   操作: 将设置的资源路径保存至全程变量DialogPath中.

1.4 全程变量及结构定义

   CS_DIALOG
   描述:   1 已经有一个对话框调入内存
	   0 没有对话框

   WM_CLOSE
   描述:   对话框关闭项

   WM_MOVE
   描述:   对话框移动或改变大小

   DialogPath[MaxPath];
   内容:   打开对话框资源文件的路径

   DLGPATH[MaxPath];
   内容:   BoyWindows 系统提供现成的对话框资源库的路径
	   如 ABOUT 对话框, 提示信息对话框, 警告信息对话框等.
	   用户可以直接使用. 参见后一节的窗口库

   int      DialogTotal           资源数量
   int      DialogTab             对话框激活框所在位置
   TYPE     DialogType[15]        创建结构
   KEY3D    DialogKey3d[5]        对话框中的按钮结构
   LABEL    DialogLabel[5]        对话框中的标签结构
   INPUTBOX DialogInputbox[3]     对话框中的输入框结构
   ICON     DialogIcon[1]         对话框中的图标结构
   PICTURE  DialogPicture[1]      对话框中的图形结构
   WINDOWS  DialogWindows         对话框的窗口结构

1.5, 实例

    1.5.1. 开发一个 ABOUT 通用对话框函数

    在商品化软件中都有一个 ABOUT 窗口, 在这个窗口中可以显示出软件的
    相关信息. 例如: 版权信息, 联系办法等等.
    首先, 我们用 Dialog Tools 建立了一个 ABOUT 对话框. 在这个对话框
    中有一个按钮, 五行正文(标签)和一个图标. 并生成了一个资源文件:
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
		      {"对话框设计工具 Dialog Tools 1.0a"},
		      {"北京大学火星人公司 幻想空间事业部"},
		      {"幻想空间软件创作群"},
		      {"程序主编: 吴 刚"},
		      {"1994 年 12 月"}
		     };

   int main(void)
   {
     BOY_SETUP_ALL();         // 系统设置
     strcpy(DLGPATH,"C:\\DIALOG");  // 对话框资源文件的路径
     UserAboutWindows(Help); // ABOUT 窗口
     BOY_CLOSE_ALL();          // 关闭系统
     return 1;                 // 程序结束
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
     strcat(openname,"\\ABOUT.DLG");  // 指定资源文件的路径

     ReadDialogWindows(openname);     // 将资源文件读入内存
     for(i=0;i<5;i++)
	strcpy(DialogLabel[i].text,text[i]);  // ABOUT 文字内容

     // 因为考虑到这是一个通用的对话框所以进行动态的修改,
     // 如果是一个专用对话框则在 Dialog Tools 中直接指定就可以了.
     // 同理: 如果资源文件建立之后想对其进行动态修改可直接对对话框
     //       的结构修改, 结构名称参见前一节全程变量及结构定义.
     // 注意: 进行动态修改时要一定要在ReadDialogWindows函数之后, 否则
     //	      将会被覆盖.

     SetDialogPath(DLGPATH);          // 指定资源文件中各个资源的路径
     CreateDialogWindows();           // 在屏幕上建立对话框

    while(!FLAG)
    {
     BOY_GET_TEST(&Test);             // 得到系统事件
     CASE=GetDialogWindows(&Test);    // 对对话框进行检测
     switch(CASE)
     {
      case 100:break;                 // 按动按钮<返回> 有关属性及返回值
				      // 请进入 Dialog Tools 观看
      case WM_CLOSE:FLAG=1;break;     // 选择窗口角菜单:退出
     }
    }
    CloseDialogWindows();
    return (CASE);
   }

   1.5.2. 一个警告对话框
   警告对话框是程序中必不可少的, 它向用户提示一些重要的信息, 让用户做出选择.
   我们要做一个有两个选项的警告对话框 (既有两个按钮, 一个为确认, 一个为返回).
   首先, 我们我们用 Dialog Tools 建立了一个警告对话框. 在这个对话框中有二个按
   钮, 一则正文(标签)和一个图标. 并生成了一个资源文件: WARNING.DLG

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
     BOY_SETUP_ALL();         // 系统设置
     strcpy(DLGPATH,"C:\\DIALOG");  // 对话框资源文件的路径
     while(UserErrorWindows("是否要退出 DialogTools?")==100)
     BOY_CLOSE_ALL();          // 关闭系统
     return 1;                 // 程序结束
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

