#include <cpx51.h>
#include <stdarg.h>
#define MODEL 10
/*==============*/
/*  系统宏定义  */
/*==============*/
#define DELAY_SCALE 115 /*1000/(12/FREQ)*/
#define TIMEBASE    50     /*  定时中断时间,单位ms */
#define T0_INIT     19457   /*0xffff-(TIMEBASE*1000)/(12/FREQ)  */
#define WAITTIME 3
#define COMP_ZERO   20

/*------------------------------*/
/*  keyboard value table        */
/*------------------------------*/
#define NO  0xf
#define OK  1
#define ESC 2
#define INC 3
#define DEC 4

/*------------------------------*/
/*      设置变量范围定义        */
/*------------------------------*/
#define DELAY_CHANGE_MAX 360
#define DELAY_CHANGE_MIN 6
#define BT_MIN_MAX      480
#define BT_MIN_MIN      420
#define BT_MAX_MIN      560
#define BT_MAX_MAX      720
#define BT_RELOAD_MIN   420
#define BT_RELOAD_MAX   600
#define DELAY_DIS_MAX   250
#define DELAY_DIS_MIN   1
#define COMP_TEMP_MAX   50
#define COMP_TEMP_MIN   0

/*----------------------*/
/*      变量缺省值定义  */
/*----------------------*/
#define DELAY_CHANGE_DEFAULT_VALUE      60
#define COMP_TEMP_DEFAULT_VALUE         0
#define BT_MIN_DEFAULT_VALUE            448
#define BT_MAX_DEFAULT_VALUE            640
#define BT_RELOAD_DEFAULT_VALUE         512
#define DELAY_DISCONNECT_DEFAULT_VALUE  200

/*------------------------------*/
/*      EPROM存储序列定义       */
/*------------------------------*/
#define COMP_TEMP       5
#define DELAY_CHANGE    6
#define BT_MIN          7
#define BT_RELOAD       8
#define BT_MAX          9
#define DELAY_DISCONNECT 10
#define LOCAL           11
#define AUTO_UPLOAD     15
#define UP_HOUR         16
#define UP_MIN          17
#define PHONE           18
#define SYSTEM_FLAG     40
#define CLIP            41
#define DATA_INDEX      57
#define DATA            58

/*----------------------*/
/*      光标设置        */
/*----------------------*/
#define ON      1
#define OFF     0

/*----------------------*/
/*      EPROM操作代码   */
/*----------------------*/
#define EWEN    0x01
#define EWDS    0
#define ERAL    0x0300
#define ERASE   0x0200

#define BT_V            0
#define SR_V            6
#define GRID_V          7
#define TEMP_BT         8
#define GRID_I          14
#define BT_I            15
#define SR_I           0x10

#define ALARM_HI        0x1
#define ALARM_LO        0x2
#define LOAD_DISABLE    0x4

#define LAMP		0x20
#define bank           0x20
#define LOAD            0X40

/*MODEM CODE*/
#define CONNECT         '1'
#define NO_CARRIER      '3'
#define NowData         10
#define OVER            '5'
#define HistoryData     72
#define SetData         73
#define SendSetData     74



/*  DS12887 BIT     */
sbit dcs=P3^4;
sbit das=P3^5;
#define drw P36
sbit dds=P2^4;

    sbit port_en=P2^3;
    sbit wdg=P2^7;

    sbit RS=P2^4;
    #define rw P36
    sbit e=P2^5;
    sbit lamp=P2^6;

  sbit Do=P1^4;
  sbit di=P1^5;
  sbit clk=P1^6;
  sbit cs=P1^7;


    sbit sk=P2^1;
    sbit dout=P2^2;
    sbit cs0=P2^0;

/*======================*/
/*      函数预说明      */
/*======================*/
lcd_init(void);
aprintf(char *format,...);
delay(unsigned int times);
set_eprom(unsigned char command);
unsigned int eprom(unsigned char address);
unsigned char wait_key();
write_eprom(unsigned char address,unsigned int Data);
sendstr(unsigned char *Data);
setuploop();
char hour();
char min();
char sec();

/*==============*/
/*  系统初始化  */
/*==============*/
init()
{
    unsigned char i;
    P0=0;
    P37=0;
    lcd_init();
    /*  系统状态判别    */
    aprintf("\a   Solar Inverter");
    IE=0x82;
    SCON=0x70;
    TMOD=0x21;
    TH1=0xfd;
    PCON=0;

}

unsigned char busy()
{
    unsigned char ac;
    P0=0xff;
    RS=0;
    rw=1;
    EA=0;
    e=1;
    ac=P0;
    e=0;
    EA=1;
    return ac>>7;
}

lcd_opr(unsigned char ch)
{
    while(busy());
    RS=rw=0;
    P0=ch;
    e=1;
    e=0;
}

/*--------------------------*/
/*  液晶显示器初始化程序    */
/*--------------------------*/
lcd_init(void)
{
    /*  工作方式设置,8位数据接口,两行显示,5X7点阵   */
    lcd_opr(0x38);
    /*  输入方式选择,AC自动加1,画面不动 */
    lcd_opr(6);
    /*  显示开关控制,开显示,关光标,禁止闪烁 */
    lcd_opr(12);
    lcd_opr(1);
}


/*------------------------------*/
/*  单字符显示,供printf()调用   */
/*------------------------------*/
unsigned int aputchar(unsigned char c)
{
    while(busy());
    RS=rw=0;
/*    if(c!='\n'){
        if(c!='\b'){
            if(c!='\a'){
                RS=1;
                P0=c;
            }
            else P0=1;
        }
        else P0=2;
    }
    else P0=0xc0;*/
    switch(c){
        case '\n':P0=0xc0;break;
        case '\b':P0=2;break;
        case '\a':P0=1;break;
        default:RS=1;P0=c;
    }
    e=1;
    e=0;
}

/*------------------*/
/*  格式化输出命令  */
/*------------------*/
aprintf (char *format,...)
{
    unsigned char format_flag,*ptr;                               /*格式标志*/
    unsigned int div_val, u_val, base;
    va_list ap;
    va_start(ap,format);
    for (;;){
        while ((format_flag = *format++) != '%'){      /* Until '%' or '\0' */
            if (!format_flag){
                return (1);
            }
            aputchar (format_flag);
        }
        switch (format_flag = *format++){
            case 'c':
                format_flag = va_arg(ap,int);
            default:
                aputchar (format_flag);
            continue;
            case 's':
                ptr = va_arg(ap,char *);
            while (format_flag = *ptr++){
                aputchar (format_flag);
            }
            continue;
            case 'o':
            case 'd':
                base = 10;
                div_val = 10000;
            u_val = va_arg(ap,int);
                while (div_val > 1 && div_val > u_val){
                    div_val /= 10;
                }
                if(format_flag=='o' && div_val==1)aputchar('0');
            do{
                if(format_flag=='o' && div_val==1)aputchar('.');
                aputchar (u_val / div_val+48);
                u_val %= div_val;
                div_val /= base;
            }
            while (div_val);
        }
    }
}

delay(unsigned int time)
{
    unsigned char j;
    for(;time>0;time--)for(j=0;j<DELAY_SCALE;j++);
}

unsigned char keyhit()
{
    return P1&0x0f;
}

unsigned char key()
{
    unsigned char j,k;
    j=P1&0x0f;
    delay(20);
    if(j==(P1&0xf))return j;
    return 0;
}


main()
{
    unsigned char farme;
    init();
    goto start;
    while(1){
        if(key()!=NO){
start:        
            lcd_init();
            lamp=1;
            while(1){
                switch(key()){
                    case OK:
                    case INC:farme++;break;
                    case DEC:farme--;break;
                }
                switch(farme){
                    case 0:aprintf("\b\n%d:%d:%d",hour(),min(),sec());break;
                    case 1:aprintf("\bSOLAR:");break;
                    case 2:aprintf("\bBATTERY");
                    case 3:aprintf("\bGRID");
                    case 4:aprintf("\bINVERTE");
            }
            lcd_opr(8);
            lamp=0;
        }
    }
}
}

char hour()
{
    char i;
    das=1;
    dds=1;
    drw=1;
    dcs=0;
    P0=4;
    das=0;
    P0=0xff;
    dds=0;
    i=P0;
    dds=1;
    dcs=1;
    das=1;
    return i;
}

char min()
{
    char i;
    das=1;
    dds=1;
    drw=1;
    dcs=0;
    P0=2;
    das=0;
    P0=0xff;
    dds=0;
    i=P0;
    dds=1;
    dcs=1;
    das=1;
    return i;
}

char sec()
{
    char i;
    das=1;
    dds=1;
    drw=1;
    dcs=0;
    P0=0;
    das=0;
    P0=0xff;
    dds=0;
    i=P0;
    dds=1;
    dcs=1;
    das=1;
    return i;
}

