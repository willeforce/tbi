 # include <stdlib.h>
 # include <stdio.h>
 # include <dos.h>
 # include <string.h>
 # include <bios.h>
 # include <alloc.h>
 # include <conio.h>
 # include <ctype.h>
// # include <graphics.h>

 # include "d:\tbi\pc\boywin.h"
 # include "d:\tbi\pc\key.h"
 # include "d:\tbi\pc\dialog.h"

#define cfgfilehead "JRTZ CONFIG FILE\n"

#define NowData         10
#define HistoryData     72
#define SetData         73

#define SendSetData     74

typedef struct {
	char NO[4];
	char comment[21];
	char phone[13];
}_station;


typedef struct {
	int Battery_Voltage;
	int Solar_Voltage[6];
	int Load_Voltage;
	int Battery_Temp;
	int In_Temp;
//	int nc1;
//	int nc2;
//	int door;
//        int yan;
	int Load_Current;
	int Battery_Current;
	int Solar_Current[6];
	int Max_Battery_Voltage;
	int Min_Battery_Voltage;
	unsigned long Charge_Ah;
	unsigned long Discharge_Ah;
	char Min;
	char Hour;
	char load;
	char WorkState;
	int CheckSum;
}_Now;

typedef struct{
	int Voltage_Max;
	int Voltage_Min;
	int Charge_Ah;
	int Discharge_Ah;
}_HISTRUCT;

typedef struct {
	int Data_Index;
	_HISTRUCT Data[32];
	int Checksum;
}_History;

typedef struct {
	int Boost;
	int Taper;
	int Float_Max;
	int Float_Min;
	int Boost_Below;
	int Comp_Temp;
	int Delay_Change;
	int Alarm_Voltage_High;
	int Alarm_Voltage_Low;
	int Voltage_Reload;
	int Delay_Disconnect;
	int Sit_Number;
	int Hour;
	int Min;
	int Temp_Lcd;
	int Auto_Upload;
	int UpHour;
	int UpMin;
	int Phone[12];
	int CheckSum;
}_Set;


typedef struct{
	unsigned ClearSendChange:1;
	unsigned CTSChange:1;
	unsigned RingChange:1;
	unsigned CarrierChange:1;
	unsigned CTS:1;
	unsigned DSR:1;
	unsigned Ring:1;
	unsigned DCD:1;

	unsigned Reday:1;
	unsigned OverErr:1;
	unsigned ParErr:1;
	unsigned FarmeErr:1;
	unsigned BreakDet:1;
	unsigned TReg:1;
	unsigned free:1;
	unsigned TimeOut:1;
}_status;

int Com_Init(char com,int baud,int datab,int stopb,int parity);
int getb(void);
unsigned char sender(unsigned char ch);
int recvice_r(void);
void Com_Close(void);
int Recvice(void);
int Recvice_String(char *Phone);
 void Send_String(char *text);
 int CreateErrorWindows(char *text);
int ReceviceData(char *buf,int len);
char *hex(int inter,char base,char *unit);
int SendData(char *buf,int len);
 void CreateDialogWindows(void);
 void  CloseDialogWindows(void);
 void waitsend(void);


/*------------------------------*/
/*      设置变量范围定义        */
/*------------------------------*/

#define BOOST_MAX       680*2
#define BOOST_MIN       540*2
#define TAPER_MAX       680
#define TAPER_MIN       520
#define BANK_MAX        6
#define BANK_MIN        1
#define FLOAT_MAX       600
#define FLOAT_MIN       480
#define BOOST_BELOW_MAX 600
#define BOOST_BELOW_MIN 480
#define COMP_TEMP_MAX   5000
#define COMP_TEMP_MIN   0
#define DELAY_CHANGE_MAX 360
#define DELAY_CHANGE_MIN 6
#define LCD_TEMP_MAX    70
#define LCD_TEMP_MIN    0
#define BT_MIN_MAX      480
#define BT_MIN_MIN      420
#define BT_MAX_MIN      560
#define BT_MAX_MAX      720
#define BT_RELOAD_MIN   420
#define BT_RELOAD_MAX   600
#define DELAY_DIS_MAX   250
#define DELAY_DIS_MIN   1
