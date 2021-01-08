# include <conio.h>
# include <string.h>
# include <bios.h>
# include <dos.h>
# include <stdio.h>

#define RXD 0
#define TXD 0
#define LSB 0
#define MSB 1
#define IER 1
#define IIR 2
#define LCR 3
#define MCR 4
#define LSR 5
#define MSR 6

#define IERV 1
#define OUT2 8
#define ERTS 2
#define EDTR 1
#define EMPTY 0x60
#define READY 0x30

#define ICREG 0x20
#define IMASKREG 0x21
#define EOI 0x20

#define WAITCOUNT 5000
#define BUFLEN 512

#define ALTE 0x12
#define ALTQ 0x10
unsigned PortAddr;
unsigned int baudtable[]={0x180,0xc0,0x60,0x30,0x18,0xc,0x6};
unsigned char paritytable[]={0x8,0x18,0,0x28,0x38};
char COM;
unsigned portf;
unsigned char buffer[BUFLEN];
int bufin=0;
int bufout=0;
void interrupt(*vect_com)();

int Recvice(void);

int getb(void)
{
	if(bufout!=bufin){
		if(++bufout==BUFLEN)bufout=0;
		return(buffer[bufout]);
	}
	else return(0xff);
}


void putb(unsigned char ch)
{
	int temp;
	temp=bufin;
	if(++bufin==BUFLEN)bufin=0;
	if(bufin!=bufout)buffer[bufin]=ch;
	else bufin=temp;
}


void interrupt receiver(void)
{
	sound(1000);
	delay(10);
	nosound();
	putb(inportb(PortAddr+RXD));
	outportb(ICREG,EOI);
}



int Com_Init(char com,int baud,int datab,int stopb,int parity)
{
	unsigned char lcr;
	if((PortAddr=peek(0x40,com*2))==0)return -1;
	portf=(com==0)?4:3;
	disable();
	outportb(PortAddr+LCR,0x80);
	outportb(PortAddr+LSB,baudtable[--baud]&0xff);
	outportb(PortAddr+MSB,baudtable[baud]>>8);

	lcr=paritytable[--parity];
	lcr|=datab-5;
	lcr|=(stopb-1)<<1;
	outportb(PortAddr+LCR,lcr);

	vect_com=getvect(portf+8);
	inportb(PortAddr+RXD);
	inportb(PortAddr+MSR);
	inportb(PortAddr+LSR);
	inportb(PortAddr+IIR);

	outportb(PortAddr+IER,IERV);
	outportb(PortAddr+MCR,OUT2|ERTS|EDTR);
	outportb(IMASKREG,inportb(IMASKREG)&(~(1<<portf)));
	setvect(portf+8,receiver);
	enable();
	return 0;
}

void Com_Close(void)
{
	disable();

	outportb(PortAddr+IER,0);
	outportb(PortAddr+MCR,0);
	outportb(IMASKREG,inportb(IMASKREG)|(1<<portf));
	enable();
	setvect(portf+8,vect_com);
}

unsigned char sender(unsigned char ch)
{
	int wait;
	for(wait=0;wait<WAITCOUNT;wait++)
		if((inportb(PortAddr+MSR)&READY)==READY)break;
	if(wait==WAITCOUNT)return 0;
	while((inportb(PortAddr+LSR)&EMPTY)!=EMPTY);
	outportb(PortAddr+TXD,ch);
	return 1;
}

void main(void)
{
	unsigned char Baud,key;
        char echoflag=0;
	printf("COM:");
	scanf("%d",&COM);
	COM--;
	printf("Baud:");
	scanf("%d",&Baud);
	Com_Init(COM,Baud,8,1,3);
	while(1){
		if(kbhit()){
			key=getch();
			if(!key){
				key=getch();
				if(key==ALTE)echoflag=~echoflag;
				if(key==ALTQ)break;
			}
			else{
				if(echoflag)putch(key);
				if(!sender(key)){
					printf("Time Out!\n");
				}
			}
		}
		key=getb();
		if(key!=0xff)
		putch(key);
	}
	Com_Close();
	printf("\n\nOver.\n");

}
