// # include <dos.h>
// # include <stdio.h>
// # include <string.h>
 # include "jrtz.h"
extern char Connect;
 void Now(void)
 {
   char savefile[13],i;
   FILE *fp;
   int *p;
   char tmp[1];
   struct date date;
   struct time time;
   extern int current_station;
   _Now now;
   extern _station *station;
   int FLAG = 0;
   int CASE;
   static int  BOY_TOTAL = 51;
   static TEST BOY_TEST;
   static int  BOY_TAB = 50;

   static TYPE BOY_TYPE[51] = {
				 {99,0},{3,0},{3,1},{3,2},{3,3},
				 {3,4},{3,5},{3,6},{3,7},{3,8},
				 {3,9},{3,10},{3,11},{3,12},{3,13},
				 {3,14},{3,15},{3,16},{3,17},{3,18},
				 {3,19},{3,20},{3,21},{3,22},{3,23},
				 {3,24},{3,25},{3,26},{3,27},{3,28},
				 {3,29},{3,30},{3,31},{3,32},{3,33},
				 {3,34},{3,35},{3,36},{3,37},{3,38},
				 {3,39},{3,40},{3,41},{3,42},{3,43},
				 {3,44},{3,45},{3,46},{3,47},{1,0},
				 {1,1},
				};


    static KEY3D BOY_KEY3D[2] = {
				   {350,380,410,410,"",0,0,1,0,2,"存盘",0,0,15,0,1},
				   {450,380,510,410,"",0,0,1,0,2,"返回",27,0,15,0,2},
				  };
    static LABEL BOY_LABEL[48] = {
				    {100,120,240,140,0,0,0,0,0,0,7,0,0,1,"当前蓄电池电压",0,""},
				    {100,150,240,170,0,0,0,0,0,0,7,0,0,1,"当前蓄电池电流",0,""},
				    {100,180,180,200,0,0,0,0,0,0,7,0,0,1,"负载电压",0,""},
				    {100,210,180,230,0,0,0,0,0,0,7,0,0,1,"负载电流",0,""},
				    {100,240,220,260,0,0,0,0,0,0,7,0,0,1,"当日最高电压",0,""},
				    {100,270,220,290,0,0,0,0,0,0,7,0,0,1,"当日最低电压",0,""},
				    {100,300,220,320,0,0,0,0,0,0,7,0,0,1,"当日充电安时",0,""},
				    {100,330,220,350,0,0,0,0,0,0,7,0,0,1,"当日放电安时",0,""},
				    {100,360,240,380,0,0,0,0,0,0,7,0,0,1,"当前蓄电池温度",0,""},
				    {100,390,220,410,0,0,0,0,0,0,7,0,0,1,"当前环境温度",0,""},
				    {300,120,380,140,0,0,0,0,0,0,7,0,0,1,"当前时间",0,""},
				    {300,150,420,170,0,0,0,0,0,0,7,0,0,1,"当前充电状态",0,""},
				    {300,180,400,200,0,0,0,0,0,0,7,0,0,1,"第一组电压",0,""},
				    {450,180,490,200,0,0,0,0,0,0,7,0,0,1,"电流",0,""},
				    {300,210,400,230,0,0,0,0,0,0,7,0,0,1,"第二组电压",0,""},
				    {450,210,490,230,0,0,0,0,0,0,7,0,0,1,"电流",0,""},
				    {300,240,400,260,0,0,0,0,0,0,7,0,0,1,"第三组电压",0,""},
				    {450,240,490,260,0,0,0,0,0,0,7,0,0,1,"电流",0,""},
				    {300,270,400,290,0,0,0,0,0,0,7,0,0,1,"第四组电压",0,""},
				    {450,270,490,290,0,0,0,0,0,0,7,0,0,1,"电流",0,""},
				    {300,300,400,320,0,0,0,0,0,0,7,0,0,1,"第五组电压",0,""},
				    {450,300,490,320,0,0,0,0,0,0,7,0,0,1,"电流",0,""},
				    {300,330,400,350,0,0,0,0,0,0,7,0,0,1,"第六组电压",0,""},
				    {450,330,490,350,0,0,0,0,0,0,7,0,0,1,"电流",0,""},
				    {220,120,270,140,0,1,0,0,0,0,15,0,0,1,"99.9V",0,""},
				    {220,150,270,170,0,1,0,0,0,0,15,0,0,1,"99.9V",0,""},
				    {220,180,270,200,0,1,0,0,0,0,15,0,0,1,"99.9v",0,""},
				    {220,210,270,230,0,1,0,0,0,0,15,0,0,1,"99.9A",0,""},
				    {220,240,270,260,0,1,0,0,0,0,15,0,0,1,"99.9V",0,""},
				    {220,270,270,290,0,1,0,0,0,0,15,0,0,1,"99.9V",0,""},
				    {220,300,280,320,0,1,0,0,0,0,15,0,0,1,"1200AH",0,""},
				    {220,330,280,350,0,1,0,0,0,0,15,0,0,1,"1200AH",0,""},
				    {220,360,260,380,0,1,0,0,0,0,15,0,0,1,"70C",0,""},
				    {220,390,260,410,0,1,0,0,0,0,15,0,0,1,"70C",0,""},
				    {460,120,510,140,0,1,0,0,0,0,15,0,0,1,"23:11",0,""},
				    {460,150,480,170,0,1,0,0,0,0,15,0,0,1,"13",0,""},
				    {390,180,440,200,0,1,0,0,0,0,15,0,0,1,"99.9V",0,""},
				    {490,180,540,200,0,1,0,0,0,0,15,0,0,1,"99.9A",0,""},
				    {390,210,440,230,0,1,0,0,0,0,15,0,0,1,"99.9V",0,""},
				    {490,210,540,230,0,1,0,0,0,0,15,0,0,1,"99.9A",0,""},
				    {390,240,440,260,0,1,0,0,0,0,15,0,0,1,"99.9V",0,""},
				    {490,240,540,260,0,1,0,0,0,0,15,0,0,1,"99.9A",0,""},
				    {390,270,440,290,0,1,0,0,0,0,15,0,0,1,"99.9V",0,""},
				    {490,270,540,290,0,1,0,0,0,0,15,0,0,1,"99.9A",0,""},
				    {390,300,440,320,0,1,0,0,0,0,15,0,0,1,"99.9V",0,""},
				    {490,300,540,320,0,1,0,0,0,0,15,0,0,1,"99.9A",0,""},
				    {390,330,440,350,0,1,0,0,0,0,15,0,0,1,"99.9V",0,""},
				    {490,330,540,350,0,1,0,0,0,0,15,0,0,1,"99.9A",0,""},
				   };
    static WINDOWS BOY_WINDOWS = { 50,60,590,430,"当前状态:",7,1,0,0,1,3,15,0,0,0,15,1,15,0,7,0,0};

    if(current_station==-1){
	strcpy(BOY_WINDOWS.text,"当前状态:未连接");
    }
    else{
	strcpy(BOY_WINDOWS.text,"当前状态:");
	strncat(BOY_WINDOWS.text,(char *)&station[current_station],sizeof(*station));
    }

    BOY_WINDOWS.key = BOY_KEY3D;
    BOY_WINDOWS.lab = BOY_LABEL;

    p=(int *)&now;
    FLAG=Connect;
    while(FLAG){
		sender(NowData);
		ReceviceData((char *)&now,sizeof(now));
		CASE=0;
		for(i=0;i<sizeof(now)/2-1;i++)CASE+=p[i];
		if(CASE==p[sizeof(now)/2-1])FLAG=0;
	}
	strcpy(BOY_LABEL[24].text,hex(now.Battery_Voltage,1,"V"));
	strcpy(BOY_LABEL[25].text,hex(now.Battery_Current,1,"A"));
	strcpy(BOY_LABEL[26].text,hex(now.Load_Voltage,1,"V"));
	strcpy(BOY_LABEL[27].text,hex(now.Load_Current,1,"A"));
	strcpy(BOY_LABEL[28].text,hex(now.Max_Battery_Voltage,1,"V"));
	strcpy(BOY_LABEL[29].text,hex(now.Min_Battery_Voltage,1,"V"));
	strcpy(BOY_LABEL[30].text,hex(now.Charge_Ah,0,"AH"));
	strcpy(BOY_LABEL[31].text,hex(now.Discharge_Ah,0,"AH"));
	strcpy(BOY_LABEL[32].text,hex(now.Battery_Temp,0,"℃"));
	strcpy(BOY_LABEL[33].text,hex(now.In_Temp,0,"℃"));
	strcpy(BOY_LABEL[34].text,hex(CASE=now.Hour,0,":"));
	strcat(BOY_LABEL[34].text,hex(CASE=now.Min,0,""));
	strcpy(BOY_LABEL[35].text,hex(CASE=now.WorkState,0,""));
	strcpy(BOY_LABEL[36].text,hex(now.Solar_Voltage[0],1,"V"));
	strcpy(BOY_LABEL[37].text,hex(now.Solar_Current[0],1,"A"));
	strcpy(BOY_LABEL[38].text,hex(now.Solar_Voltage[1],1,"V"));
	strcpy(BOY_LABEL[39].text,hex(now.Solar_Current[1],1,"A"));
	strcpy(BOY_LABEL[40].text,hex(now.Solar_Voltage[2],1,"V"));
	strcpy(BOY_LABEL[41].text,hex(now.Solar_Current[2],1,"A"));
	strcpy(BOY_LABEL[42].text,hex(now.Solar_Voltage[3],1,"V"));
	strcpy(BOY_LABEL[43].text,hex(now.Solar_Current[3],1,"A"));
	strcpy(BOY_LABEL[44].text,hex(now.Solar_Voltage[4],1,"V"));
	strcpy(BOY_LABEL[45].text,hex(now.Solar_Current[4],1,"A"));
	strcpy(BOY_LABEL[46].text,hex(now.Solar_Voltage[5],1,"V"));
	strcpy(BOY_LABEL[47].text,hex(now.Solar_Current[5],1,"A"));

	FLAG=0;
	CREATE_WINDOWS_ALL(&BOY_WINDOWS,&BOY_TYPE[0],BOY_TOTAL,BOY_TAB);


	while(!FLAG)
	 {
	   BOY_GET_TEST(&BOY_TEST);
	   CASE=BOY_ALL_TEST(&BOY_WINDOWS,&BOY_TEST,BOY_TOTAL,&BOY_TAB,BOY_TYPE);
	   switch(CASE)
	   {
	 case 1:{
		getdate(&date);
		gettime(&time);
		for(i=0;i<13;i++)savefile[i]='\0';
		strncpy(savefile,"C",1);
		strncat(savefile,station[current_station].NO,3);
		savefile[4]=date.da_mon/10+'0';
		savefile[5]=date.da_mon%10+'0';
		savefile[6]=date.da_day/10+'0';
		savefile[7]=date.da_day%10+'0';
		strcat(savefile,".TXT");
		if((fp=fopen(savefile,"wt"))==NULL){
			CreateErrorWindows("未能建立文件!");
			break;
		}
		fprintf(fp,"	当前状态记录\n");
		fprintf(fp,"\n站点:%s	电话号码:%s	说明:%s\n",station[current_station].NO,station[current_station].phone,station[current_station].comment);
		fprintf(fp,"记录时间:%d年%d月%d日 	%d时%d分\n",date.da_year,date.da_mon,date.da_day,time.ti_hour,time.ti_min);
		fprintf(fp,"蓄电池电压 = %.1f V\n",(float)now.Battery_Voltage/10);
		fprintf(fp,"蓄电池充电电流 = %.1f A\n",(float)now.Battery_Current/10);
		fprintf(fp,"负载电压 = %.1f V\n",(float)now.Load_Voltage/10);
		fprintf(fp,"负载电流 = %.1f A\n",(float)now.Load_Current/10);
		fprintf(fp,"蓄电池温度 = %d 摄氏度\n",now.Battery_Temp);
		fprintf(fp,"环境温度 = %d 摄氏度\n",now.In_Temp);
		fprintf(fp,"充电状态 = %d \n",now.WorkState);
		fprintf(fp,"时间 = %-2d:%-2d\n",now.Hour,now.Min);
		for(i=0;i<6;i++)fprintf(fp,"太阳能电池第 %d 组电压 = %.1f V		电流 = %.1f A\n",i+1,(float)now.Solar_Voltage[i]/10,(float)now.Solar_Current[i]/10);
		fprintf(fp,"当日累计充电电量 = %d AH\n",now.Charge_Ah);
		fprintf(fp,"当日累计放电电量 = %d AH\n",now.Discharge_Ah);
		fprintf(fp,"当日蓄电池最高电压 = %.1f V\n",(float)now.Max_Battery_Voltage/10);
		fprintf(fp,"当日蓄电池最低电压 = %.1f V\n",(float)now.Min_Battery_Voltage/10);
		fprintf(fp,"**********	文件结束    **********");
		fclose(fp);
		CreateWarningWindows("提示","存储完成.",0);
		break;
	 }
	 case 2:
	 case WindowsClose:FLAG=1;break;
	}
      }
     CLOSE_BOY_WINDOWS(&BOY_WINDOWS);
  }
