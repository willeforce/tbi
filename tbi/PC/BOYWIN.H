/*  名称: BOYWIN.H
    用途: BOYWINDOWS 1.1 系统库函数头文件.
    制作: 幻想空间软件创作群 ( Illusion Space Software Design ).
    日期: 1994 年 1 月.
    版权: 幻想空间软件创作群. ( 一切权利保留! )
    注意: 必需使用大或巨型模式进行编译.
*/

#if !defined(__LARGE__) && !defined(__HUGE__)
   #error BoyWindows Library will run only in LARGE or HUGE memory model.
#endif

#if !defined(__BOY_WIN_H)
#define __BOY_WIN_H

/* 当窗口移动或改变大小时,由 BOY_ALL_TEST 函数返回该事件值*/
# define WindowsChange -9
# define WindowsMove  -8
# define WindowsClose -7

/* 输入框文本最大长度 */
#define MaxInputTextLen 128

/* 目录项文本最大长度 */
#define MaxPath        80

/* 文本最大长度 */
#define MaxTextLen     81

/* 窗口高度最小值 */
extern int WINDOWS_Minh;
extern int WINDOWS_Minl;
extern int MAX_X,MAX_Y;
extern int ReDrawWindows;
extern char Serial[15];
/*
   特别注意: 此变量用于函数库的使用校验.
   必须在程序开始时, 将内容设置成函数库的序列号.
   例: strcpy(Serial,"018-2512950056");
   如果校验错误, 程序将自动退出.
 */

/* 系统事件结构 */
typedef struct {
	int key;    /* 按键键值 */
	int keys;   /* 扩展键值 */
	int mousex; /* 鼠标横坐标 */
	int mousey; /* 鼠标纵坐标 */
	int button; /* 鼠标按键状态 (1:左键按下 2:右键按下 4:中键按下) */
       } TEST;

/* 窗口部件顺序结构 */
typedef struct {
	int type; /* 部件类型号 */
	int num;  /* 部件顺序号 */
       } TYPE;

/* 当输入法窗口被创建后, 该值为一. */
extern int _CHINESE;

/* 鼠标初始化成功, 该值为一, 否则为零. */
extern char _MOUSE;

/* 当前鼠标光标形状号. */
extern int MOUSE_TYPE_TAB;

/* 系统路径结构 */
typedef struct _setup_boy{
	char ovl[MaxPath];        /* 全拼,简拼码表, BGI */
	char font16[MaxPath];     /* 16点阵汉字及英文字库 */
	char font24[MaxPath];     /* 24点阵字库 */
	char boyswp[MaxPath];     /* 图形临时交换文件 */
       }SETPATH;
extern SETPATH BOYPATH;

/**************************部件结构定义************************************/

/* 三维按键结构定义 (类型值为 1) */
typedef struct _key3d {
	int x1,y1;              /* 按键左上角坐标 */
	int x2,y2;              /* 按键右下角坐标 */
	char ico[MaxPath];      /* 按键中图标文件名 */
	int icox,icoy;          /* 图标在按键中的坐标 */
	int enable;             /* 是否允许激活 */
	int font;               /* 按键中使用汉字字体 (0:宋 1:楷) */
	int h;                  /* 按键三维高度 (0-8) */
	char text[MaxTextLen];  /* 按键中汉字正文 */
	int hotkey;             /* 热键 */
	int fontchar;           /* 正文三维效果 (0:正常 1:凸 2:凹) */
	int bkcolor;            /* 环境背景色 */
        int style;              /* 按钮效果 2.0+ */
	int index;              /* 返回值 */
       }KEY3D;

/* 滚动条结构定义 (类型值为 2) */
typedef struct _scroll{
	int x1,y1;              /* 滚动条的左上角坐标 */
	int x2,y2;              /* 滚动条的右下角坐标 */
	int bkcolor;            /* 滚动条的颜色 */
	int mx;                 /* 逻辑最大值 */
	int mi;                 /* 逻辑最小值 */
	int bm;                 /* 小改动步长 */
	int sm;                 /* 大改动步长 */
	int v;                  /* 当前滚动条逻辑位置 */
	int pd;                 /* 横竖判断(0:横 1:竖) */
	int index;              /* 返回值 */
	int enable;             /* 是否允许激活 */
	int boxbkcolor;         /* 环境背景色   */
       }SCROLL;

/* 标签结构定义 (类型值为 3) */
typedef struct _label{
	int x1,y1;              /* 起始座标                                 */
	int x2,y2;              /* 结束座标                                 */
	int alignment;          /* 文本排列方示(0:左 1:中 2:右)             */
	int board;              /* 边框类型(0:无 1:有)                      */
	int boardcolor;         /* 边框颜色(0-15)                           */
	int textfont;           /* 正文字体(0:16点阵宋体 1:16点阵楷体       */
				/* 2:24点阵仿宋体 3:24点阵宋体 4:24点阵楷体 */
				/* 5:24点阵黑体 6:12点阵仿宋体 7:12点阵宋体 */
				/* 8:12点阵楷体 9:12点阵黑体)               */
	int textcolor;          /* 正文字体颜色(0-15)                       */
	int textstyle;          /* 正文修饰(0:正常 1:凹 2:凸 3:深凹 4:深凸) */
	int labelbkcolor;       /* 背景色(0-15)                             */
	int  hotkey;            /* 热键                                     */
	int  index;             /* 返回值                                   */
	int  enable;            /* 是否允许激活                             */
	char text[MaxTextLen];  /* 内容                                     */
	int small;              /* (保留)                                   */
	char smallfontname[MaxPath]; /* (保留)                              */
       } LABEL;

/*框架结构定义 (类型值为 4) */
typedef struct _frame{
	int x1,y1;              /* 起始座标                      */
	int x2,y2;              /* 结束座标                      */
	int type;               /* 类型值                        */
	char text[MaxTextLen];  /* 正文文本                      */
	int textcolor;          /* 文字的颜色                    */
	int font;               /* 正文字体                      */
	int bkcolor;            /* 背景颜色                      */
	int alignment;          /* 文本排列方示(0:左 1:中 2:右)  */
	int enable;             /* 是否允许激活                  */
       }FRAME;

/* 输入框结构定义 (类型值为 5) */
typedef struct _inputbox{
	int x1,y1;              /* 起始座标                           */
	int maxchar;            /* 窗口所含最大字符数                 */
	int password;           /* 是否用密码输入                     */
	int maxl;               /* 输入字符串的最大长度               */
	int board;              /* 边框类型(0:无 1:有)                */
	int boardcolor;         /* 边框颜色(0-15)                     */
	int textfont;           /* 正文字体(0:16点阵宋体 1:16点阵楷体)*/
	int textcolor;          /* 正文字体颜色(0-15)                 */
	int textbkcolor;        /* 正文字体背景颜色(0-15)             */
	int inputboxbkcolor;    /* 背景色(0-15)                       */
	int  sels;              /* 选中的字符起始位置                 */
	int  seln;              /* 选中的字符数                       */
	int  enable;            /* 是否允许激活(0:是 1:否)            */
	int  index;             /* 返回值                             */
	int  hotkey;            /* 热键                               */
	char text[MaxInputTextLen];       /*内容                      */
	char seltext[MaxInputTextLen];    /*所选内容                  */
	int  point;             /* (保留)                             */
	int  startline;         /* (保留)                             */
       } INPUTBOX;

/* 单选钮结构定义 (类型值为 6) */
typedef struct _option{
	int x1,y1;              /* 起始坐标                       */
	char text[MaxTextLen];  /* 提示正文                       */
	int textcolor;          /* 正文颜色                       */
	int enable;             /* 是否允许激活(0:是 1:否)        */
	int hotkey;             /* 热键                           */
	int font;               /* 正文字体                       */
	int bkcolor;            /* 环境背景色                     */
	int YN;                 /* 当前是否被选中                 */
	int type;               /* 表现形式 (为 0 则为按钮式)     */
	char bmpname1[MaxPath]; /* 图形文件名 (表现形式为 0 时)   */
	int index;
	int piclongx;
	int piclongy;
       }OPTION;

/* 多选钮结构定义 (类型值为 7) */
typedef struct boy_check{
	 int x1,y1;             /* 起始坐标                      */
	 char text[MaxTextLen]; /* 提示正文                      */
	 int textcolor;         /* 正文颜色                      */
	 int enable;            /* 当前是否被激活                */
	 int hotkey;            /* 热键                          */
	 int font;              /* 正文字体                      */
	 int bkcolor;           /* 环境背景色                    */
	 int YN;                /* 当前是否被选中                */
	 int type;              /* 表现形式 (为 0 则为按钮式)    */
	 char filename[MaxPath];/* 图形文件名 (表现形式为 0 时)  */
	 int index;
	}CHECK;

/* 图标结构定义 (类型值为 8) */
typedef struct _icon{
	int x1,y1;              /* 起始坐标    */
	int index;              /* 返回值      */
	char name[MaxPath];     /* 图标文件名  */
       }ICON;

/* 图形结构定义 (类型值为 9) */
typedef struct _pic{
	int x1,y1;              /* 起始坐标    */
	char name[MaxPath];     /* 图形文件名  */
       }PICTURE;

/* 三维效果结构 (类型值为 10) */
typedef struct bar3d{
	int x1,y1;              /* 起始坐标    */
	int x2,y2;              /* 结束始坐标  */
	int hight,space;        /* 高度与距离  */
	int type;               /* 表现形式    */
	} BAR3D;

 /*加减器结构定义 (类型值为 11) */
 typedef struct _adddec{
	 int x,y;               /* 创建加减器的横纵坐标 */
	 int v;                 /* 当前值               */
	 int max;               /* 最大值               */
	 int min;               /* 最小值               */
	 int bkcolor;           /* 环境背景色           */
	 int index;             /* 返回值               */
	 int enable;            /* 是否充许激活         */
	}ADDDEC;

/* 列表框结构定义 (类型值为 12) */
typedef struct {
	int x1,y1;              /* 起始坐标                           */
	int x2,y2;              /* (保留)                             */
	int len,line;           /* 列表框中所显示字符串的长度, 与行数 */
	int to;                 /* 当前的光条所处位置                 */
	int top,botton;         /* (保留)                             */
	int enable;             /* 是否允许激活                       */
	int textcolor;          /* 文字色彩                           */
	int bkcolor;            /* 背景色彩                           */
	int index;              /* 返回值                             */
	int sl,tl;              /* 列表项数量及每项长度               */
	char *text;             /* 列表字符串数组                     */
       }LISTED;

/* 组合框结构定义 (类型值为 13) */
typedef struct {
	int x1,y1;              /* 组合框的横纵坐标                */
	int x2,y2;              /* (保留)                          */
	int len;                /* 组合框中所允许显示字符串的长度  */
	int line;               /* 组合框下拉行数                  */
	int to;                 /* 当前的光条所处位置              */
	int top,botton;         /* (保留)                          */
	int enable;             /* 是否允许激活                    */
	int type;               /* 是否为下拉                      */
	int input;              /* 是否允许输入定义                */
	int textcolor;          /* 文字色彩                        */
	int bkcolor;            /* 背景色彩                        */
	int sl,tl;              /* 列表项数量及每项长度            */
	int index;              /* 返回值                          */
	int index2;             /* (保留)                          */
	char name[MaxTextLen];  /* 正文内容                        */
	char *text;             /* 列表字符串数组指针              */
       }COMBO;

/* 图形线结构定义 (类型值为 14) */
typedef struct _line{
	int x1,y1;              /* 起始坐标   */
	int x2,y2;              /* 结束坐标   */
	int color;              /* 颜色       */
	int type;               /* 表现形式   */
       }LINE;

/* 驱动器列表框结构定义 (类型值为 15) */
typedef struct {
	int x1,y1;              /* 起始坐标                       */
	int x2,y2;              /* (保留)                         */
	int len,line;           /* 驱动器列表框中所显示字符串行数 */
	int to;                 /* 当前的光条所处位置             */
	int top,botton;         /* (保留)                         */
	int enable;             /* 是否允许激活                   */
	int textcolor;          /* 文字色彩                       */
	int bkcolor;            /* 背景色彩                       */
	int index;              /* 返回值                         */
	char drive[3];          /* 驱动器名称                     */
       }DRIVELIST;

/* 文件列表框结构定义 (类型值为 16)  */
typedef struct {
	int x1,y1;              /* 起始坐标                               */
	int x2,y2;              /* (保留)                                 */
	int len,line;           /* 文件列表框中所显示字符串的长度, 与行数 */
	int to;                 /* 当前的光条所处位置                     */
	int top,botton;         /* (保留)                                 */
	int enable;             /* 是否允许激活                           */
	int textcolor;          /* 文字色彩                               */
	int bkcolor;            /* 背景色彩                               */
	int index;              /* 返回值                                 */
	int sl,tl;              /* 文件名缓冲区数组下标                   */
	char path[MaxPath];     /* 文件路径名                             */
	char filetype[MaxTextLen];  /*文件类型名                          */
	char *filename;         /* 文件名缓冲区数组指针,长度为 sl*tl 个字符*/
       }FILELIST;

/* 目录列表框结构定义 (类型值为 17) */
typedef struct {
	int x1,y1;              /* 目录列表框的横纵坐标                   */
	int x2,y2;              /* (保留)                                 */
	int len,line;           /* 目录列表框中所显示字符串的长度, 与行数 */
	int to;                 /* 当前的光条所处位置                     */
	int top,botton;         /* (保留)                                 */
	int enable;             /* 是否允许激活                           */
	int textcolor;          /* 文字色彩                               */
	int bkcolor;            /* 背景色彩                               */
	int index;              /* 返回值                                 */
	char path[MaxPath];     /* 目录路径名                             */
       } DIRLIST;

/* 窗口菜单结构定义 (类型值为 18) */
typedef struct _menu{
	char name[MaxTextLen]; /* 菜单名称          */
	int hotkey;            /* 激活菜单热键      */
	int pd;                /* 当前是否允许激活  */
	int type;              /* 菜单的层次        */
	int font;              /* 菜单字体          */
	int index;             /* 出口参数          */
	int x,y;               /* (保留)            */
        int active;            /* (保留)            */
       }MENU;

/* 窗口结构定义 */
typedef struct _window{
	int x1,y1;             /* 窗口定义的左上角坐标 */
	int x2,y2;             /* 窗口定义的右下角坐标 */
	char text[MaxTextLen]; /* 窗口标题正文字符汉字 */
	int winbkcolor;        /* 窗口背景色           */
	int bkcolor;           /* 窗口标题背景色       */
	int mouse;             /* 窗口中鼠标的形状     */
	int font;              /* 窗口16点阵正文字体   */
	int enable;            /* 窗口是否被激活       */
	int wintype;           /* 窗口边际类型         */
	int textcolor;         /* 窗口标题字符颜色     */
	int texttab;           /* 标题字距             */
	int wincolor;          /* 标题边框色           */
	int menusl;            /* 窗口菜单数量         */
        int menubkcolor;       /* 窗口菜单栏背景色     */
        int menutextbkcolor;   /* 窗口菜单条颜色       */
        int menutextcolor;     /* 窗菜单条文字色       */
        int menubktextcolor;   /* 窗口菜单文字前景色   */
        int menudisablecolor;  /* 窗口菜单非激活文字色 */
        int menuframecolor;    /* 窗口菜单边框色       */
        int menushadow;        /* 窗口菜单阴影(0:无 1:有)*/
       long bkpic;             /* (保留)               */

	KEY3D *key;            /* (保留)               */
	SCROLL *scl;           /* (保留)               */
	LABEL *lab;            /* (保留)               */
	FRAME *frm;            /* (保留)               */
	INPUTBOX *inp;         /* (保留)               */
	OPTION *opti;          /* (保留)               */
	CHECK *chk;            /* (保留)               */
	ICON *icn;             /* (保留)               */
	PICTURE *pic;          /* (保留)               */
	BAR3D *b3d;            /* (保留)               */
	ADDDEC *ad;            /* (保留)               */
	LISTED *lst;           /* (保留)               */
	COMBO *cmb;            /* (保留)               */
	LINE *line;            /* (保留)               */
	DRIVELIST *drv;        /* (保留)               */
	DIRLIST *dir;          /* (保留)               */
	FILELIST *fil;         /* (保留)               */
	MENU *menu;            /* (保留)               */
      }WINDOWS;

/**********************************************************************/
/* 注:凡是注明(保留)的项均为系统内部使用, 用户不需要对其进行操作.     */
/**********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/***************************函数声明***********************************/

/* 1. 三维按键 */
  void CREATE_BOY_KEY3D(KEY3D *);
  int  BOY_KEY3D_TEST(KEY3D *,TEST *);
  int  BOY_KEY3D_TESTm(KEY3D *keys,TEST *test);
  void BOY_KEY3D_DISABLE(KEY3D *);
  void BOY_KEY3D_ENABLE(KEY3D *);

/* 2. 滚动条 */
  void CREATE_BOY_SCROLL(SCROLL *);
  int  BOY_SCROLL_TEST(SCROLL *scrolls, TEST *keys);
  int  BOY_SCROLL_TESTm(SCROLL *scrolls, TEST *keys);
  void BOY_SCROLL_DISABLE(SCROLL *);
  void BOY_SCROLL_ENABLE(SCROLL *);
  void REDRAW_BOY_SCROLL(SCROLL *scl,int newv);

/* 3. 标签 */
  void CREATE_BOY_LABEL(LABEL *);
  int  BOY_LABEL_TEST(LABEL *l, TEST *keys);

/* 4. 框架 */
  void CREATE_BOY_FRAME(FRAME *);

/* 5. 输入框 */
  void CREATE_BOY_INPUTBOX(INPUTBOX *,int type);
  void BOY_INPUTBOX_ENABLE(INPUTBOX *);
  void BOY_INPUTBOX_DISABLE(INPUTBOX *);
  int  BOY_INPUTBOX_TEST(INPUTBOX *in, TEST *keys);
  int  BOY_INPUTBOX_TESTm(INPUTBOX *in, TEST *keys);

/* 6. 单选钮 */
  void CREATE_BOY_OPTION(OPTION *);
  int  BOY_OPTION_TEST(WINDOWS *ws,OPTION *opti,TYPE *tp,TEST *test,int total);
  int  BOY_OPTION_TESTm(WINDOWS *ws,OPTION *opti,TYPE *tp,TEST *test,int total);
  void BOY_OPTION_ENABLE(OPTION *opti);
  void BOY_OPTION_DISABLE(OPTION *opti);
  int  FRAME_OPTION(FRAME *f,OPTION *o); /*包容处理 */
  void BOY_OPTION_CLEAN (OPTION *opti); /*清除当前单选的置位*/
  void BOY_OPTION_DRAW (OPTION *opti);  /*清除当前单选的置位*/
  void BOY_OPTION_CLEANHELP(OPTION *opti);

/* 7. 多选钮 */
  void CREATE_BOY_CHECK(CHECK *);
  int  BOY_CHECK_TEST(CHECK *check,TEST *test);
  int  BOY_CHECK_TESTm(CHECK *check,TEST *test);
  void BOY_CHECK_ENABLE(CHECK *);
  void BOY_CHECK_DISABLE(CHECK *);
  void BOY_CHECK_DRAW(CHECK *check);
  void BOY_CHECK_CLEAN(CHECK *check);

/* 8. 图标 */
  void CREATE_BOY_ICON(ICON *icn);
  int  BOY_ICON_TEST(ICON *icn,TEST *test);

/* 9. 图形 */
  void CREATE_BOY_PICTURE(PICTURE *pic);

/* 10.三维效果结构 */
  void CREATE_BOY_BAR3D(BAR3D *);

/* 11.加减器 */
  void CREATE_BOY_ADDDEC(ADDDEC *);
  int  BOY_ADDDEC_TEST(ADDDEC *,TEST *);
  void BOY_ADDDEC_ENABLE(ADDDEC *);
  void BOY_ADDDEC_DISABLE(ADDDEC *);
  void ins_adddec(ADDDEC *);

/* 12.列表框 */
  void CREATE_BOY_LISTED(LISTED *);
  int  BOY_LISTED_TEST(LISTED *,TEST *);
  void BOY_LISTED_DISABLE(LISTED *lst);
  void BOY_LISTED_ENABLE(LISTED *lst);

/* 13.组合框 */
  void CREATE_BOY_COMBO(COMBO *);
   int BOY_COMBO_TEST(COMBO *, TEST *);
   int BOY_COMBO_TESTm(COMBO *, TEST *);
  void BOY_COMBO_DISABLE(COMBO *);
  void BOY_COMBO_ENABLE(COMBO *);

/* 14.图形线 */
  void CREATE_BOY_LINE(LINE *ln);

/* 15.驱动器列表框 */
  void CREATE_BOY_DIRLIST(DIRLIST *);
   int BOY_DIRLIST_TEST(DIRLIST *, TEST *);
  void BOY_DIRLIST_ENABLE(DIRLIST *);
  void BOY_DIRLIST_DISABLE(DIRLIST *);

/* 16.文件列表框 */
  void CREATE_BOY_FILELIST(FILELIST *flst);
   int BOY_FILELIST_TEST(FILELIST *,TEST *);
  void BOY_FILELIST_DISABLE(FILELIST *flst);
  void BOY_FILELIST_ENABLE(FILELIST *flst);

/* 17.目录列表框 */
  void CREATE_BOY_DRIVELIST(DRIVELIST *);
   int BOY_DRIVELIST_TEST(DRIVELIST *, TEST *);
   int BOY_DRIVELIST_TESTm(DRIVELIST *, TEST *);
  void BOY_DRIVELIST_ENABLE(DRIVELIST *);
  void BOY_DRIVELIST_DISABLE(DRIVELIST *);

/* 18.窗口菜单 */
  void CREATE_BOY_MENU(MENU *menus,WINDOWS *wins);
  int  BOY_MENU_TEST(MENU *menus,WINDOWS *wins,TEST *test);
  void CLOSE_BOY_MENU(MENU *menus,WINDOWS *wins);
  void BOY_MENU_ENABLE(MENU *menus,WINDOWS *wins);
  void BOY_MENU_DISABLE(MENU *menus,WINDOWS *wins);

/* 19.窗口 */
  void CREATE_BOY_WINDOWS(WINDOWS *);
  void CREATE_WINDOWS_ALL(WINDOWS *wnd,TYPE *type,int total, int tab);
  int  BOY_WINDOWS_TEST (WINDOWS *wins, TEST *test, int total, int tab, TYPE *type);
  int  BOY_ALL_TEST(WINDOWS *w, TEST *keys, int total, int *tab, TYPE *type);
  void REDRAW_WINDOWS_ALL(WINDOWS *wnd,TYPE *type,int total, int tab, int dx, int dy);
  void CLOSE_BOY_WINDOWS(WINDOWS *);
  void BOY_WINDOWS_DISABLE(WINDOWS *wins);
  void BOY_WINDOWS_ENABLE(WINDOWS *wins);
  void RestoreWindows(WINDOWS *wnd,TYPE *type,int total,int tab);
  void GetWindowsMax(WINDOWS *wnd,TYPE *type,int total,int tab);


/* 20.汉字的显示及汉字输入法 */
  void BOY_OUT_TEXTXY(int x, int y, char *str);
  void BOY_OUT_TEXT(char *str);
  void BOY_OUT_CHARXY(int x, int y, char ch);
  void BOY_OUT_CHAR(char ch);
  void BOY_OUT_HZXY(int x, int y, char *str);
  void BOY_OUT_HZ(char *str);
  void BOY_SETHZ_XY(int x, int y);
  void BOY_GETHZ_XY(int *x, int *y);
  void BOY_SETHZ_FONT(int font);
   int BOY_GETHZ_FONT(void);
  void BOY_SETHZ_COLOR(int color);
   int BOY_GETHZ_COLOR(void);

  void CREATE_BOY_CHINESE(void);
  void CLOSE_BOY_CHINESE(void);
   int BOY_CHINESE_TEST(TEST *keys);
  char BOY_HZ_GET(void);
   int BOY_CODE_GET(void);

/* 21.图形处理 */
  long BOY_GET_IMAGE(int x1, int y1, int x2, int y2);
   int BOY_PUT_IMAGE(int x, int y, long n, int op, int type);
   int BOY_GET_IMAGEF(int x1, int y1, int x2, int y2,char *fn);
   int BOY_PUT_IMAGEF(int x, int y, char *fn, int op);
   int BOY_IMAGE_SIZE(char *fn,int *x, int *y);
   int BOY_DRAW_PIC(int x1, int y1,char *fn);
   int BOY_DRAW_ICN(int x1, int y1,char *fn);
  void BOY_DEL_IMAGEBUF(long n);
  void BOY_DEL_IMAGEBUF_ALL(void);

/* 22.鼠标 */
   int BOY_SET_MOUSE(void);
  void BOY_MOUSE_VIEW(void);
  void BOY_MOUSE_HIDE(void);
  void BOY_MOUSE_MOVE(int x,int y);
  void BOY_MOUSE_GET(int *x,int *y);
  void BOY_MOUSE_DGET(int *x,int *y);
   int BOY_MOUSE_INBOX(int x1,int y1, int x2, int y2);
   int BOY_MOUSE_BUTTON(void);
  void BOY_MOUSE_TYPE(int type);
  void BOY_MOUSE_GETALL(int *x, int *y, int *button);

/* 系统 */
   int BOY_SETUP_ALL(void);
  void BOY_CLOSE_ALL(void);
  void BOY_GET_TEST(TEST *BOY_TEST);
   int BOY_DESKTOP(int type, char *fn);
//   int MessageBox(char *name, char *text, int win);
   int CreateWarningWindows(char *name,char *text,int type);

int puthz16(int x,int y,int color,char p[256],int space,int font);
int puthz24(int x,int y,int z,int color,char *p,int PD);
void puthz163d(int x,int y,int g,char text[256],int type,int cl);
int puthz24_2(int x,int y,int z,int color,char *p,int PD);
int puthz24_small(int small,char name1[256],int x,int y,int z,int color,char *p,int PD);
int puthz24_2_small(int small,char name1[256],int x,int y,int z,int color,char *p,int PD);

#ifdef __cplusplus
}
#endif

#endif  /*__BOY_WIN_H */
