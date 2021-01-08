/*==================================*/
/*  太阳能同步逆变器系统控制程序    */
/*  TBI.C                           */
/*  1997.12.1                       */
/*==================================*/

/*==============*/
/*  包含头文件  */
/*==============*/
#include <mice.h>
#include <stdarg.h>
#include <string.h>

/*==============*/
/*  设置结构    */
/*==============*/
typedef struct{
    char type;              /*  型式标志                */
                            /*  0=数值                  */
                            /*  1=字符串选项            */
                            /*  2=时钟                  */
                            /*  3=日期                  */
    char title[32];         /*  提示信息字符串        */
    int max,min;            /*  最大最小值                  */
    char **option;          /*  字符串选项的显示指针        */
    unsigned int *value;
    unsigned int *value1;
    unsigned int *value2;
}setup_index;               /*  设置所需要的信息结构        */
#define CLOCK 2
#define DATE    3

/*==============*/
/*  系统宏定义  */
/*==============*/
#define MODEL 10            /*机器代码  */
#define DELAY_SCALE 115     /*  延时子程序系数  */
#define WAITTIME 3*60       /*  不按键等待时间  */
#define COMP_ZERO   20
#define FLASH_TIME  100     /*  闪烁时间    */
#define INPUT_DELAY 25      /*  设置连加等待时间    */
#define TIMEBASE    50     /*  定时中断时间,单位ms */
#define T0_INIT     19457   /*0xffff-(TIMEBASE*1000)/(12/FREQ)  */

/*------------------------------*/
/*  keyboard value table        */
/*------------------------------*/
#define NO  0
#define OK  0xe
#define ESC 0xd
#define INC 0xb
#define DEC 7

/*------------------------------*/
/*      设置变量范围定义        */
/*------------------------------*/
#define BT_MIN_MAX      960
#define BT_MIN_MIN      840
#define BT_MAX_MIN      1120
#define BT_MAX_MAX      1440

/*----------------------*/
/*      变量缺省值定义  */
/*----------------------*/
#define DELAY_CHANGE_VALUE      2
#define BT_MIN_DEFAULT_VALUE    896
#define BT_MAX_DEFAULT_VALUE    1280
#define BT_RELOAD_VALUE         1024
#define DELAY_DISCONNECT_VALUE  2
#define FLOAT_MAX_VALUE         960
#define FLOAT_MIN_VALUE         940
#define BOOST_BELOW_VALUE       992
#define taper                   1120
#define bm                      1200
#define comp_temp               0
/*------------------------------*/
/*      EPROM存储序列定义       */
/*------------------------------*/
#define EHOUR           0
#define SHOUR           1
#define SMIN            2
#define EMIN            3
#define MODE            4
#define GRID_MAX        5
#define GRID_MIN        6
#define BT_MIN          7
#define BT_MAX          8
#define LOCAL           9
#define AUTO_UPLOAD     10
#define UP_HOUR         11
#define UP_MIN          12
#define PHONE           13
#define SYSTEM_FLAG     40
#define CLIP            41
#define DATA_INDEX      57
#define DATA            58

/*----------------------*/
/*      EPROM操作代码   */
/*----------------------*/
#define EWEN    0x01
#define EWDS    0
#define ERAL    0x0300
#define ERASE   0x0200

#define CONNECT 1
#define NO_CARRIER  3
#define NowData 51
#define HistoryData 52
#define SetData     53
#define SendSetData 54

/*==================*/
/*  A/D输入通道号   */
/*==================*/
#define BT_V            0
#define SR_V0           1
#define SR_V1           2
#define SR_V2           3
#define SR_V3           4
#define SR_V4           5
#define SR_V5           6
#define GRID_V          7
#define TEMP_BT         8
#define INV_V           9
#define INV_C           10
#define LOAD_I          14
#define BT_I            15
#define SR_I0           0x10
#define SR_I1           0x11
#define SR_I2           0x12
#define SR_I3           0x13
#define SR_I4           0x14
#define SR_I5           0x15

#define SOLAR   1
/*==============*/
/*  输出口定义  */
/*==============*/
union{
struct{
    unsigned char adport:4;
    unsigned char led:1;
}pa;
char pao;
}paa;

union{
struct{
    char solorsw:6;
    char loadsw:1;
    char high:1;
}pb;
char pbo;
}pbb;

union{
struct{
    char low:1;
    char shrot:1;
    char work:1;
}pc;
char pco;
}pcc;

/*==================*/
/*  系统变量定义    */
/*==================*/
idata struct{
    unsigned int bt_v;        /*蓄电池电压  */
    unsigned int solar_v[6];
    unsigned int grid_v;    /*电网电压电流  */
    int Battery_Temp;         /*蓄电池温度  */
    unsigned int inv_v;
    unsigned inv_c;    /* 逆变器电压电流  */
    unsigned int solar_c;     /*太阳电池电流    */
    unsigned int bt_c;        /*蓄电池电流  */
    unsigned int Solar_Current[6];

    unsigned int bt_v_max;  /*  蓄电池最高电压  */
    unsigned int bt_v_min;  /*  蓄电池最低电压  */
    unsigned long charge_ah;    /*  充电安时    */
    unsigned long discharge_ah; /*  放电安时    */
    unsigned char hour,min;
    unsigned char solar_state;   /*  充电当前及下一状态  */
    unsigned char load;                  /*  输出状态    */
    unsigned char year,mon,day;
    unsigned int CheckSum;
}now;
idata    unsigned char ad_ch;        /*  A/D通道号   */
    bit up_load;
    code unsigned int v[7]={0,taper,(taper*4+bm)/5,(taper*3+bm*2)/5,(taper*2+bm*3)/5,
                       (taper+bm*4)/5,bm};  /*  充电参数值  */
    idata unsigned int  bt_min;   /*  低压告警值  */
    idata unsigned int  bt_max;   /*  高压告警值  */
    idata unsigned int  grid_max; /*  电网高压告警值  */
    idata unsigned int  grid_min; /*  电网低压告警值  */

    idata unsigned char char_point=10; /*  设置变量指针    */
    idata unsigned int time;     /*  系统计时    */

    idata unsigned int ad_result; /*  A/D结果 */
    idata unsigned char please;   /*  AD请求  */

    code unsigned char clip[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; /*  AD校正系数  */


    bit intflag;    /*  中断标志    */

    idata unsigned int sec,shour,smin,ehour,emin;

    idata int mode;
    code char *pmode[]={"OFF","ON"};
    code setup_index prompt[10]={
        {0,"\aBATTERY HIGH AL-\nARM IN %oV",BT_MAX_MAX,BT_MAX_MIN,NULL,&bt_max,NULL,NULL},
        {0,"\aBATTERY LOW  AL-\nARM IN %oV",BT_MIN_MAX,BT_MIN_MIN,NULL,&bt_min,NULL,NULL},
        {0,"\aGRID HIGH ALARM\n IN %oV",2500,2000,NULL,&grid_max,NULL,NULL},
        {0,"\aGRID LOW  ALARM\n IN %oV",2000,1500,NULL,&grid_min,NULL,NULL},
        {3,"\aCURRENT DATE:\n %d-%d-%d",0,0,NULL,&now.mon,(unsigned int *)&now.day,(unsigned int*)&now.year},
        {2,"\aCURRENT TIME:\n %d:%d:%d",0,0,NULL,(int)&now.hour,(int)&now.min,(int)&sec},
        {1,"\aAUTO WORK BY\nTIME:%s",1,0,pmode,(int)&mode,NULL,NULL},
        {2,"\aSTART TIME:\n %d:%d",0,0,NULL,(int)&shour,(int)&smin,NULL},
        {2,"\aEND TIME:\n %d:%d",0,0,NULL,(int)&ehour,(int)&emin,NULL},
        {0,"\aVIEW HISTORY",0,0,NULL,NULL,NULL,NULL}
    };

    idata char bufin,bufout,buf[10];
    idata unsigned char up_hour,up_min;
/*==================*/
/*  输入输出口定义  */
/*==================*/

/*  DS12887 BIT     */
#ifdef POD8751
    sbit dcs=0Xdc;
    sbit das=0xdb;
    sbit drw=0xd9;
    sbit dds=0xd8;

    sbit wdg=0xcc;
    sbit paen=0xdd;
    sbit pben=0xde;
    sbit pcen=0xdf;
    sbit outen=0XCE;

    sbit RS=0xd8;
    sbit rw=0xd9;
    sbit e=0xda;

    sbit Do=P1^4;
    sbit di=P1^5;
    sbit clk=P1^6;
    sbit cs=P1^7;

    sbit sk=0xcf;
    sbit dout=0xcd;
    sbit cs0=0xca;
#endif
#ifndef POD8751
    sbit dcs=0Xa4;
    sbit das=0xa3;
    sbit drw=0xa1;
    sbit dds=0xa0;

    sbit wdg=0xb4;
    sbit paen=0xa5;
    sbit pben=0xa6;
    sbit pcen=0xa7;
    sbit outen=0Xb6;

    sbit RS=0xa0;
    sbit rw=0xa1;
    sbit e=0xa2;

    sbit Do=P1^4;
    sbit di=P1^5;
    sbit clk=P1^6;
    sbit cs=P1^7;

    sbit sk=0xb7;
    sbit dout=0xb5;
    sbit cs0=0xb2;
#endif
/*======================*/
/*      函数预说明      */
/*======================*/
lcd_init(void);
printf(char *format,...);
delay(unsigned int times);
set_eprom(unsigned char command);
unsigned int eprom(unsigned char address);
unsigned char wait_key();
write_eprom(unsigned char address,unsigned int Data);
setuploop();
char dsr(char ads);
dsw(char ads,char db);

/*==============*/
/*  系统初始化  */
/*==============*/
init()
{
    unsigned char i;
    P0=paa.pao=pbb.pbo=pcc.pco=paen=pben=pcen=e=outen=0;
    paa.pa.led=1;
    P0=paa.pao;
    paen=1;
    paen=0;
    now.bt_v_min=1024;
    /*  LCD显示器初始化 */
    lcd_init();
    /*  系统状态判别    */
    printf("\a Solar Inverter\nVer:1.00 98-1");
    delay(1000);
    IE=0x86;
    SCON=0x70;
    TMOD=0x21;
    TH1=0xfd;
    PCON=0;
    IT1=1;
    TR0=ES=TR1=EA=1;

    if(eprom(SYSTEM_FLAG)!=MODEL){
        printf("\aSETUP ERROR!\nLoad Default.");
        wait_key();
        set_eprom(EWEN);
        write_eprom(BT_MIN,BT_MIN_DEFAULT_VALUE);
        write_eprom(BT_MAX,BT_MAX_DEFAULT_VALUE);
        for(i=DATA_INDEX;i<DATA+4*32;i++)write_eprom(i,0);
        for(i=PHONE;i<PHONE+12;i++)write_eprom(i,'*');
        write_eprom(SYSTEM_FLAG,MODEL);
        set_eprom(EWDS);
    }
    bt_max=eprom(BT_MAX);
    bt_min=eprom(BT_MIN);
    grid_max=eprom(GRID_MAX);
    grid_min=eprom(GRID_MIN);
    ehour=eprom(EHOUR);
    emin=eprom(EMIN);
    shour=eprom(SHOUR);
    smin=eprom(SMIN);
    mode=eprom(MODE)?1:0;
}



/*AD转换子程序*/
int ad(unsigned char ch)
{
    idata union{
        unsigned char i;
        unsigned long l;
    }a;
    idata unsigned int result;
    paa.pa.adport=ch;
    P0=paa.pao;
    paen=1;
    paen=0;
    for(a.i=0;a.i<255;a.i++);
    sk=0;
    dout=1;
    result=0;
    cs0=0;
    while(!dout);
    sk=1;
    sk=0;
    sk=1;
    result|=dout;
    sk=0;
    for(a.i=0;a.i<11;a.i++){
        sk=1;
        result=(result<<1)|dout;
        sk=0;
    }
/*    a.l=128+clip[ch];
    a.l=result*a.l;
    result=a.l/1024;*/
    sk=dout=cs0=1;
    return result;
}
                
                
/*AD转换子程序*/                
ad_get(unsigned char ch)
{
    switch(ch){
        case TEMP_BT:return (ad(ch)*4-2732-COMP_ZERO)/10;
        case BT_V:return (ad(ch)+(comp_temp*48*now.Battery_Temp)/100);
        case LOAD_I:return ad(ch)/2;
        case SR_I0:pbb.pb.solorsw=1;ch=BT_I;break;
        case SR_I1:pbb.pb.solorsw=2;ch=BT_I;break;
        case SR_I2:pbb.pb.solorsw=4;ch=BT_I;break;
        case SR_I3:pbb.pb.solorsw=8;ch=BT_I;break;
        case SR_I4:pbb.pb.solorsw=0x10;ch=BT_I;break;
        case SR_I5:pbb.pb.solorsw=0x20;ch=BT_I;break;
    }
    P0=pbb.pbo;
    pben=1;
    pben=0;
    return ad(ch);
}

int1() interrupt 2
{
    dsr(0xc);
    now.year=dsr(9);
    now.mon=dsr(8);
    now.day=dsr(7);
    now.hour=dsr(4);
    now.min=dsr(2);
    sec=dsr(0);
    intflag=1;
}

timer0() interrupt 1
{
    code char control[14]={0,0x3f,0x1f,0xf,0x7,0x3,1,0,1,3,7,0xf,0x1f,0x3f};
    unsigned char tmp;
    static char ms,delay_c,delay_dis,next_state;
    unsigned int *adres=&now;
    /*定时器初值设置*/
    TH0=T0_INIT/256;
    TL0=T0_INIT%256;
    wdg=~wdg;
    tmp=P0;
    P0=0xff;
    /*A/D循环采样*/
    adres[ad_ch]=ad_get(ad_ch>10?ad_ch+3:ad_ch);

    ad_ch>=13?ad_ch=0:ad_ch++;

    if(please!=0xff){
        ad_result=ad_get(please);
        please=0xff;
    }
    /*50mS加一*/
    if((ms++)==(1000/TIMEBASE-1)){
        /*看门狗复位*/
        /*1秒*/
        ms=0;
        time++;
        if(mode){
            if(pcc.pc.work){
                if(now.hour==ehour&&now.min==emin)pcc.pc.work=0;
            }
            else{
                if(now.hour==shour&&now.min==smin)pcc.pc.work=1;
            }
        }

        if(pcc.pc.work){
            if(!now.load&&now.inv_v>=now.grid_v&&now.grid_v>grid_min&&now.grid_v<grid_max)pbb.pb.loadsw=1;
            else pbb.pb.loadsw=0;
        }
        if(now.solar_state<7){
            /*强充状态,1-6*/
            if(now.bt_v<v[now.solar_state-1]){
                if(next_state==now.solar_state-1){
                    if(delay_c==0)now.solar_state-=1;
                }
                else{
                    next_state=now.solar_state-1;
                    delay_c=DELAY_CHANGE_VALUE;
                }
            }
            else {
                if(now.bt_v>=v[now.solar_state]){
                    if(next_state==now.solar_state+1){
                        if(delay_c==0)now.solar_state+=1;
                    }
                    else{
                        next_state=now.solar_state+1;
                        delay_c=DELAY_CHANGE_VALUE;
                    }
                }
                else next_state=0;
            }
        }
        else{
            /*浮充状态,7-13*/
            if(now.bt_v<(now.solar_state==13?BOOST_BELOW_VALUE:FLOAT_MIN_VALUE)){
                if(next_state==now.solar_state+1){
                    if(delay_c==0)now.solar_state=now.solar_state==13?1:now.solar_state+1;
                }
                else{
                    next_state=now.solar_state+1;
                    delay_c=DELAY_CHANGE_VALUE;
                }
            }
            else {
                if(now.bt_v>FLOAT_MAX_VALUE && now.solar_state!=7){
                    if(next_state==now.solar_state-1){
                        if(delay_c==0)now.solar_state-=1;
                    }
                    else{
                        next_state=now.solar_state-1;
                        delay_c=DELAY_CHANGE_VALUE;
                    }
                }
                else next_state=0;
            }
        }

        /*最高,最低电压,充电,放电安时记录*/
        if(now.bt_v>now.bt_v_max)now.bt_v_max=now.bt_v;
        if(now.bt_v<now.bt_v_min)now.bt_v_min=now.bt_v;
        now.charge_ah+=now.bt_c;
        now.discharge_ah+=now.inv_c*now.grid_v;

        /*负载控制,load=0,负载正常供电*/
        if(!now.load){
            if(now.bt_v>bt_max){
                /*过压告警*/
                if(delay_dis==0){
                    pbb.pb.high=1;
                    now.load=1;
                }
            }
            else{
                if(now.bt_v<bt_min){
                    /*欠压告警*/
                    if(delay_dis==0){
                        pcc.pc.low=1;
                        now.load=2;
                    }
                }
                else{
                    delay_dis=DELAY_DISCONNECT_VALUE;
                }
            }
        }
        else{
            if(now.load==1){
                /*过压告警恢复*/
                if(now.bt_v<bt_max-40){
                    pbb.pb.high=0;
                    now.load=0;
                }
            }
            else{
                /*欠压告警恢复*/
                if(now.bt_v>BT_RELOAD_VALUE){
                    pcc.pc.low=0;
                    now.load=0;
                }
            }
        }
        delay_c--;
        delay_dis--;
    }
    pbb.pb.solorsw=control[now.solar_state];
    P0=paa.pao;
    paen=1;
    paen=0;
    P0=pbb.pbo;
    pben=1;
    pben=0;
    P0=pcc.pco;
    pcen=1;
    pcen=0;
    P0=tmp;
}

unsigned int get_result(unsigned char a)
{
    please=a;
    while(please!=0xff);
    return ad_result;
}

DELAY()
{
    clk=1;
    clk=0;
}
  
/*----------------------*/
/*  EPROM设置及擦除程序 */
/*  command=00H,EWDS  */
/*  command=01H,EWEN  */
/*----------------------*/
set_eprom(unsigned char command)
{
    unsigned char k;
    cs=clk=di=0;
    Do=1;
    cs=1;
    while(!Do);
    di=1;
    DELAY();
    if(command==0){
            di=0;
            DELAY();
            DELAY();
        }
        else{
            di=0;
            DELAY();
            DELAY();
            command=0xc0;
        }
    for(k=0;k<8;k++){
        di=command>>7;
        DELAY();
        command<<=1;
    }
    cs=0;
}

/*--------------------------*/
/*  EPROM写入程序           */
/*  address<256,写单个数据  */
/*--------------------------*/
write_eprom(unsigned char address,unsigned int Data)
{
    unsigned char k;
    cs=clk=di=0;
    Do=1;
    cs=1;
    while(!Do);
    di=1;
    DELAY();
    di=0;
    DELAY();
            di=1;
    DELAY();
    for(k=0;k<8;k++){
        di=address>>7;
        DELAY();
        address<<=1;
    }
    for(k=0;k<16;k++){
        di=Data>>15;
        DELAY();
        Data<<=1;
    }
    cs=0;
}

/*------------------*/
/*  EPROM读出程序   */
/*------------------*/
unsigned int eprom(unsigned char address)
{
    unsigned char k,i;
    idata unsigned int result;
    for(i=0;i<10;i++){
        cs=clk=di=0;
        Do=1;
        cs=1;
        while(!Do);
        cs=0;
        cs=1;
        di=1;
        DELAY();
        DELAY();
        di=0;
        DELAY();
        for(k=0;k<8;k++){
            di=address>>7;
            DELAY();
            address<<=1;
        }
        if(Do==0)goto GOOD;
    }
    return 0;
GOOD:
    for(k=0;k<16;k++){
        result<<=1;
        DELAY();
        result=result|Do;
    }
    cs=0;
    return result;
}

/*----------------------*/
/*  液晶显示驱动程序    */
/*  型号:   MDLS-16265B */
/*----------------------*/
/*----------------------*/
/*  液晶显示器判忙程序  */
/*----------------------*/

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
printf (char *format,...)
{
    idata unsigned char format_flag,*ptr,cc=0;                               /*格式标志*/
    idata unsigned int div_val, u_val, base;
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
                if(cc==char_point)aputchar(' ');
                else aputchar (format_flag);
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
                if(format_flag=='o' && div_val==1){
                    if(cc==char_point)aputchar(' ');
                    else aputchar('0');
                }
            do{
                if(format_flag=='o' && div_val==1){
                    if(cc==char_point)aputchar(' ');
                    else aputchar('.');
                }
                if(cc==char_point)aputchar(' ');
                else aputchar (u_val / div_val+48);
                u_val %= div_val;
                div_val /= base;
            }
            while (div_val);
        }
        cc++;
    }
}

delay(unsigned int time)
{
    unsigned char j;
    for(;time>0;time--)for(j=0;j<DELAY_SCALE;j++);
}

unsigned char kbhit()
{
    if((P1&0x0f)==0xf)return 0;else return 1;
}

unsigned char getch()
{
    unsigned char j,k;
    j=P1&0x0f;
    if(j==0xf)return 0;
    delay(20);
    if(j==(P1&0xf)){
        time=0;
        return j;
    }
    return 0;
}

unsigned char wait_key()
{
    unsigned char k;
    while(getch()!=NO&&time<WAITTIME);
    while((k=getch())==NO && time<WAITTIME);
	return k;
}	
	
char dsr(char ads)
{
    das=1;
    dds=1;
    drw=1;
    dcs=0;
    P0=ads;
    das=0;
    P0=0xff;
    dds=0;
    ads=P0;
    dds=1;
    dcs=1;
    das=1;
    return ads;
}

dsw(char ads,char db)
{
    das=1;
    dds=1;
    drw=1;
    dcs=1;
    P0=ads;
    dcs=0;
    das=0;
    P0=db;
    drw=0;
    drw=1;
    dcs=1;
    das=1;
    P0=0xff;
}

setup(setup_index x)
{
    idata unsigned char flash=0,key_time;     /*flash:闪烁时间计时,key_time:按键时间计时*/
    idata char last_key;       /*last_key:记忆上次键值,char_point:时钟日期设置指针*/
    idata int p[3],max,min,i;
    bit flag,ff;
    flag=1;
    p[0]=*x.value;
    p[1]=*x.value1;
    p[2]=*x.value2;
    if(x.type<2){
        max=x.max;
        min=x.min;
    }
    else{
        if(x.type==CLOCK){
            max=23;
            min=0;
        }
        else{
            max=12;
            min=0;
        }
    }
/*    printf(x.title,p[0],p[1],p[2]);*/
    while(kbhit());
    char_point=0;
    while(1){
        if(flag){
            if(ff){
                i=char_point;
                char_point=3;
                switch(x.type){
                    case 0:printf(x.title,p[0]);break;
                    case 1:printf(x.title,x.option[p[0]]);break;
                    case 2:printf(x.title,p[0],p[1]);break;
                    case 3:printf(x.title,p[0],p[1],p[2]);break;
                }
                flag=0;
                ff=0;
                char_point=i;
                delay(50);
            }
            else{
                switch(x.type){
                    case 0:printf(x.title,p[0]);break;
                    case 1:printf(x.title,x.option[0]);break;
                    case 2:printf(x.title,p[0],p[1]);break;
                    case 3:printf(x.title,p[0],p[1],p[2]);break;
                }
                flag=0;
                ff=1;
                delay(50);
            }
        }
        delay(10);
        if(time>WAITTIME)return;
        if(kbhit()){
            switch(getch()){
                case ESC:char_point=10;return 0;
                case OK:{
                    char_point=10;
                    *x.value=p[0];
                    *x.value1=p[1];
                    *x.value2=p[2];
                    return 1;
                }
                case INC:{
                    flag=ff=1;
                    if(last_key!=INC){
                        p[char_point]>=max?p[char_point]=min:p[char_point]++;
                        last_key=INC;
                        key_time=0;
                    }
                    else{
                        if(key_time>INPUT_DELAY){
                            p[char_point]>=max?p[char_point]=min:p[char_point]++;
                        }
                        else key_time++;
                    }
                    flash=0;
                    break;
                }
                case DEC:{
                    flag=ff=1;
                    if(x.type==CLOCK){
                        if(char_point==1){
                            char_point=0;
                            max=23;
                        }
                        else{
                            char_point=1;
                            max=59;
                        }
                        break;
                    }
                    if(x.type==DATE){
                        if(char_point>=2)char_point=0;else char_point++;
                        if(char_point==0)max=12;
                        else{
                            if(char_point==1)max=31;
                            else max=99;
                        }
                        break;
                    }
                    if(last_key!=DEC){
                        p[char_point]<=min?p[char_point]=max:p[char_point]--;
                        last_key=DEC;
                        key_time=0;
                    }
                    else{
                        if(key_time>INPUT_DELAY){
                            p[char_point]<=min?p[char_point]=max:p[char_point]--;
                        }
                        else key_time++;
                    }
                    flash=0;
                    break;
                }
                default:last_key=ESC;key_time=0;
            }
        }
        else{
            last_key=ESC;key_time=0;
        }
        if(flash>FLASH_TIME){flash=0;flag=1;}
        else flash++;
    }
}

view()
{
    unsigned char k,address;
    idata unsigned int i;
    i=k=0;
    for(;;){
        if(time>WAITTIME)return;
        address=((i+eprom(DATA_INDEX))%32)*4+DATA;
        printf("\aD%d %oBV~%oV\nCHR %d  DIS %d",i,eprom(address),eprom(address+1),eprom(address+2),eprom(address+3));
        switch(wait_key()){
            case INC:i=(i+1)%32;break;
            case DEC:if(i==0)i=31;else i--;break;
            default:lcd_opr(1);return 0;
        }
     }
}

setuploop()
{
    char k,i;
    i=0;
    while(1){
        if(prompt[i].type==1)printf(prompt[i].title,prompt[i].option[*prompt[i].value]);else
        printf(prompt[i].title,*prompt[i].value,*prompt[i].value1,*prompt[i].value2);
        k=wait_key();
        if(time>WAITTIME)return;
        switch (k){
            case ESC:return;
            case OK:{
                if(i==9){view();break;};
                set_eprom(EWEN);
                if(setup(prompt[i])){
                    switch(i){
                        case 0:write_eprom(BT_MAX,*prompt[i].value);break;
                        case 1:write_eprom(BT_MIN,*prompt[i].value);break;
                        case 2:write_eprom(GRID_MAX,*prompt[i].value);break;
                        case 3:write_eprom(GRID_MIN,*prompt[i].value);break;
                        case 4:dsw(8,*prompt[i].value);dsw(7,*prompt[i].value1);dsw(9,*prompt[i].value2);break;
                        case 5:dsw(4,*prompt[i].value);dsw(2,*prompt[i].value1);dsw(0,*prompt[i].value2);break;
                        case 6:write_eprom(MODE,*prompt[i].value);break;
                        case 7:write_eprom(SHOUR,*prompt[i].value);write_eprom(SMIN,*prompt[i].value1);break;
                        case 8:write_eprom(EHOUR,*prompt[i].value);write_eprom(EMIN,*prompt[i].value1);break;
                    }
                set_eprom(EWDS);
                }
                break;
            }
            case INC:i++;if(i>9)i=0;break;
            case DEC:if(i>0)i--;else i=9;break;
        }
    }
}

/****************************/
/*  单片机串口通讯基本程序  */
/*  无硬件握手信号          */
/*  中断接收、查询发送      */
/****************************/


/*------------------*/
/*  单字符发送      */
/*------------------*/
send(unsigned char Data)
{
	while(TI);
    SBUF=Data;
    delay(10);
}

/*------------------------------*/
/*  发送一个字符串，直到字符为0 */
/*------------------------------*/
sendstr(unsigned char *Data)
{
    while(*Data!=0){
    	send(*Data);
        Data++;
    }
}

/*--------------------------*/
/*  调制解调器初始化        */
/*  设置为无回显、数字回应  */
/*--------------------------*/

/*--------------------------*/
/*  串行通讯中断程序        */
/*  接收中断将字符          */
/*  发送中断清除发送标志    */
/*--------------------------*/
serial() interrupt 4 using 2
{
    if(RI){
        buf[bufin]=SBUF;
        bufin>=(sizeof(buf)-1)?bufin=0:bufin++;
        RI=0;
    }
    TI=0;
}

unsigned char recviced()
{
    unsigned char i;
    if(bufin!=bufout){
        for(i=bufout;i!=bufin;){
            if(buf[i]==13)return 1;
            i>=(sizeof(buf)-1)?i=0:i++;
        }
    }
    return 0;
}

unsigned int getb()
{
    unsigned char i;
    if(bufout!=bufin){
        i=buf[bufout];
        bufout>=(sizeof(buf)-1)?bufout=0:bufout++;
        return i;
    }
    else return 0xffff;
}

unsigned char getcode()
{
    unsigned int b1=0xffff,b2=0xffff;
    while((b1=getb())!=0xffff){
	if(b1==13)return b2;
	if((b2=getb())==13)return b1;
    }
}

unsigned char dial()
{
    unsigned char i,phone[13];
    for(i=0;i<13;i++)phone[i]=eprom(PHONE+i);
    bufin=bufout=0;
    sendstr("ATDP");
    sendstr(phone);
    send('\r');
    for(i=0;i<120;i++){
	delay(500);
	if(recviced())break;
    }
    if(getcode()==CONNECT)return 1;
    else return 0;
}

sendw(unsigned int a)
{
    union{
    unsigned int a;
    unsigned char c[2];
    }d;
    d.a=a;
    send(d.c[1]);
    send(d.c[0]);
}

unsigned int getw(){
    union{
    unsigned int a;
    unsigned char b[2];
    }c;
    unsigned int i;
    while((i=getb())==0xffff);
    c.b[0]=i;
    while((i=getb())==0xffff);
    c.b[1]=i;
    return c.a;
}

talk()
{
    unsigned char flag=1,i;
    unsigned int *p,a,b;
    for(i=0;i<6;i++)now.Solar_Current[i]=get_result(SR_I0+i);
    while(flag){
	now.CheckSum=0;
	switch(getb()){
		case NowData:{
			#ifdef DEBUG_TERM
			aprintf("\bsendnow");
			#endif
            p=(unsigned int *)&now;
			for(a=0;a<sizeof(now)/2;a++){
				b=p[a];
				now.CheckSum+=b;
				sendw(b);
			}
			#ifdef DEBUG_TERM
			aprintf ("\nchecksum:%d",now.CheckSum);
			#endif
			break;
		}
		case HistoryData:{
			#ifdef DEBUG_TERM
			aprintf("\bsethis");
			#endif
			for(a=DATA_INDEX;a<DATA+4*32;a++){
				b=eprom(a);
				now.CheckSum+=b;
				sendw(b);
			}
			sendw(now.CheckSum);
			#ifdef DEBUG_TERM
			aprintf ("\nchecksum:%d",now.CheckSum);
			#endif
			break;
		}
		case SetData:{
			#ifdef DEBUG_TERM
			aprintf("\bsetSET");
			#endif
			for(a=0;a<30;a++){
				b=eprom(a);
				now.CheckSum+=b;
				sendw(b);
			}
			sendw(now.CheckSum);
			#ifdef DEBUG_TERM
			aprintf ("\nchecksum:%d",now.CheckSum);
			#endif
			break;
		}
		case SendSetData:{
			set_eprom(EWEN);
			for(a=0;a<30;){
				send(a);
				b=getw();
				if(getw()==b){
					write_eprom(a,b);
					#ifdef DEBUG_TERM
					aprintf("\nnow:%d",a);
					#endif
					a++;
				}
			}
			set_eprom(EWDS);
			send(30);
			#ifdef DEBUG_TERM
			aprintf("\bok");
			#endif
			break;
		}
		case NO_CARRIER:flag=0;
	}
    }
}

main()
{
    unsigned char farme,i;
    bit flag;
    code char *state[]={"INVERTER CLOSED.","INVERTER STARTED."};
    init();
    now.solar_state=1;
    dsw(0xa,0x2f);
    dsw(0xb,0x16);

    farme=time=0;
    flag=1;
    goto start;
    while(1){
        if(getch()!=NO){
start:        
            lcd_init();
            paa.pa.led=1;
            while(time<WAITTIME){
                switch(getch()){
                    case OK:flag=1;farme=0;break;
                    case INC:flag=1;farme++;if(farme==10)farme=0;break;
                    case DEC:flag=1;if(farme==0)farme=9;else farme--;break;
                    case ESC:setuploop();flag=1;break;
                    case OK&INC:{
                        if(pcc.pc.work){
                            pcc.pc.work=0;
                            printf("\aINVERTER CLOSED.");
                        }
                        else{
                            pcc.pc.work=1;
                            printf("\aINVERTER STARTED.");
                        }
                        while(kbhit());
                    }
                }
                if(flag){
                    switch(farme){
                        case 0:printf("\a%s\n%d:%d:%d %d-%d-%d",state[pcc.pc.work],(int)now.hour,(int)now.min,(int)sec,now.mon,now.day,now.year);break;
                        case 1:printf("\aBATTERY:%oV\n%oA STATE:%d",now.bt_v,now.bt_c,(int)now.solar_state);break;
                        case 2:printf("\aGRID:%oV",now.grid_v);break;
                        case 3:printf("\aINVERTE:%oV\n%oA",now.inv_v,now.inv_c);break;
                        case 4:printf("\aSOLAR1:%oV\n%oA",now.solar_v[0],get_result(0x10));break;
                        case 5:printf("\aSOLAR2:%oV\n%oA",now.solar_v[1],get_result(0x11));break;
                        case 6:printf("\aSOLAR3:%oV\n%oA",now.solar_v[2],get_result(0x12));break;
                        case 7:printf("\aSOLAR4:%oV\n%oA",now.solar_v[3],get_result(0x13));break;
                        case 8:printf("\aSOLAR5:%oV\n%oA",now.solar_v[4],get_result(0x14));break;
                        case 9:printf("\aSOLAR6:%oV\n%oA",now.solar_v[5],get_result(0x15));break;
                    }
                    flag=0;
                    while(kbhit());
                }
                if(intflag){
                    intflag=0;
                    flag=1;
                }
                if(now.hour==0&&now.min==0&&sec==0){
                    i=eprom(DATA_INDEX);
                    i=i*4+DATA;
                    write_eprom(i,now.bt_v_max);
                    write_eprom(i+1,now.bt_v_min);
                    write_eprom(i+2,now.charge_ah/3600);
                    write_eprom(i+3,now.discharge_ah/3600);
                    write_eprom(DATA_INDEX,i==31?0:i++);
                    now.bt_v_max=0;
                    now.bt_v_min=1024;
                    now.charge_ah=now.discharge_ah=0;
                    delay(1000);
                }
            }
            lcd_opr(8);
            paa.pa.led=0;
        }
        if(up_load && now.hour==up_hour && now.min>=up_min){
            if(dial()==1){
                talk();
                up_load=0;
            }
        }
        if(recviced()){
            if(getcode()==CONNECT){
                talk();
            }
        }
        if(now.hour==0&&now.min==0&&sec==0){
            i=eprom(DATA_INDEX);
            i=i*4+DATA;
            write_eprom(i,now.bt_v_max);
            write_eprom(i+1,now.bt_v_min);
            write_eprom(i+2,now.charge_ah/3600);
            write_eprom(i+3,now.discharge_ah/3600);
            write_eprom(DATA_INDEX,i==31?0:i++);
            now.bt_v_max=0;
            now.bt_v_min=1024;
            now.charge_ah=now.discharge_ah=0;
            delay(1000);
        }
    }
}

