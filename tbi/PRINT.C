#define POD8751
#include<mice.h>
#include <stdarg.h>
#include <string.h>

    sbit RS=0xd8;
    sbit rw=0xd9;
    sbit e=0xda;
    sbit stb=0xd8;
    sbit ack=0xd9;
    sbit usy=0xdb;
    sbit nopaper=0xdc;


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
                if(format_flag=='o' && div_val==1){
                     aputchar('0');
                }
            do{
                if(format_flag=='o' && div_val==1){
                     aputchar('.');
                }
                 aputchar (u_val / div_val+48);
                u_val %= div_val;
                div_val /= base;
            }
            while (div_val);
        }
        cc++;
    }
}

out_char(char cc)
{
       if(nopaper)printf("\bno paper!");
       while(nopaper);
       while(usy);
       P0=cc;
       stb=0;
       stb=1;
}
print (char *format,...)
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
            out_char(format_flag);
        }
        switch (format_flag = *format++){
            case 'c':
                format_flag = va_arg(ap,int);
            default:
                out_char (format_flag);
            continue;
            case 's':
                ptr = va_arg(ap,char *);
            while (format_flag = *ptr++){
                 out_char (format_flag);
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
                     out_char('0');
                }
            do{
                if(format_flag=='o' && div_val==1){
                     out_char('.');
                }
                else out_char (u_val / div_val+48);
                u_val %= div_val;
                div_val /= base;
            }
            while (div_val);
        }
        cc++;
    }
}

main()
{
    lcd_init();
    while(1)
        print("1234abc世界真奇妙\n\r");
}
