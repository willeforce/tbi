 # include "jrtz.h"

extern char Connect;
 void Control(void)
 {
   extern int current_station;
   extern _station *station;
   _Set set,newset;
   char PHONE[13];
   FILE *fp;
   struct date date;
   struct time time;
   char savefile[13];
   char WORK=0;
   int *p;
   int FLAG = 0;
   int CASE,i,j;
   static int  BOY_TOTAL = 51;
   static TEST BOY_TEST;
   static int  BOY_TAB = 50;

   static TYPE BOY_TYPE[51] = {
				 {99,0},{4,0},{3,0},{3,1},{3,2},
				 {3,3},{3,4},{3,5},{3,6},{5,0},
                                 {3,7},{5,1},{3,8},{5,2},{3,9},
				 {5,3},{3,10},{5,4},{5,5},{5,6},
				 {3,11},{3,12},{3,13},{4,1},{3,14},
                                 {3,15},{3,16},{3,17},{5,7},{5,8},
				 {5,9},{5,10},{3,18},{3,19},{3,20},
                                 {3,21},{4,2},{7,0},{3,22},{5,11},
				 {3,23},{5,12},{3,24},{3,25},{3,26},
                                 {5,13},{5,14},{5,15},{1,0},{1,1},
                                 {1,2},
				};


    static KEY3D BOY_KEY3D[3] = {
				   {505,200,565,230,"",0,0,1,0,2,"存盘",0,0,15,0,1},
				   {505,250,565,280,"",0,0,1,0,2,"更改",0,0,15,0,2},
				   {505,300,565,330,"",0,0,1,0,2,"返回",27,0,15,0,3},
                                  };
    static LABEL BOY_LABEL[27] = {
				    {77,154,197,174,0,0,0,0,0,0,7,0,0,1,"强充最大电压",0,""},
					{77,179,197,199,0,0,0,0,0,0,7,0,0,1,"强充递减电压",0,""},
				    {77,204,197,224,0,0,0,0,0,0,7,0,0,1,"浮充电压上限",0,""},
				    {77,229,197,249,0,0,0,0,0,0,7,0,0,1,"浮充电压下限",0,""},
				    {77,254,197,274,0,0,0,0,0,0,7,0,0,1,"返回强充电压",0,""},
				    {77,279,197,299,0,0,0,0,0,0,7,0,0,1,"温度补偿电压",0,""},
				    {77,304,197,324,0,0,0,0,0,0,7,0,0,1,"状态转换延时",0,""},
				    {237,154,267,174,0,0,0,0,0,0,7,0,0,1,"V",0,""},
				    {237,179,257,199,0,0,0,0,0,0,7,0,0,1,"V",0,""},
				    {237,204,257,224,0,0,0,0,0,0,7,0,0,1,"V",0,""},
					{237,229,257,249,0,0,0,0,0,0,7,0,0,1,"V",0,""},
				    {237,254,257,274,0,0,0,0,0,0,7,0,0,1,"V",0,""},
				    {237,279,267,299,0,0,0,0,0,0,7,0,0,1,"mV",0,""},
				    {237,304,257,324,0,0,0,0,0,0,7,0,0,1,"S",0,""},
				    {307,154,427,174,0,0,0,0,0,0,7,0,0,1,"告警电压上限",0,""},
				    {307,179,427,199,0,0,0,0,0,0,7,0,0,1,"告警电压下限",0,""},
				    {307,204,407,224,0,0,0,0,0,0,7,0,0,1,"重连接电压",0,""},
				    {307,229,407,249,0,0,0,0,0,0,7,0,0,1,"断开前延时",0,""},
				    {462,154,477,174,0,0,0,0,0,0,7,0,0,1,"V",0,""},
					{462,179,477,199,0,0,0,0,0,0,7,0,0,1,"V",0,""},
				    {462,204,477,224,0,0,0,0,0,0,7,0,0,1,"V",0,""},
				    {462,229,477,249,0,0,0,0,0,0,7,0,0,1,"S",0,""},
				    {307,344,427,364,0,0,0,0,0,0,7,0,0,1,"上载电话号码",0,""},
				    {307,320,377,339,0,0,0,0,0,0,7,0,0,1,"上载时间",0,""},
				    {80,340,180,360,0,0,0,0,0,0,7,0,0,1,"控制器编号",0,""},
				    {80,365,160,385,0,0,0,0,0,0,7,0,0,1,"当前时间",0,""},
				    {80,390,200,410,0,0,0,0,0,0,7,0,0,1,"最低显示温度",0,""},
				   };
	static FRAME BOY_FRAME[3] = {
				  {67,134,277,334,2,"充电设置",0,0,7,0,1},
				  {297,134,487,264,2,"负载设置",0,0,7,0,1},
				  {297,269,487,400,2,"通讯设置",0,0,7,0,1},
                                 };
    static INPUTBOX BOY_INPUTBOX[16] = {
					{182,154,6,0,6,2,0,0,0,15,15,0,4,1,0,0,"0","",6,4},
					{182,179,6,0,4,2,0,0,0,15,15,0,4,1,0,0,"1","",4,0},
					{182,204,6,0,4,2,0,0,0,15,15,0,4,1,0,0,"2","",4,0},
					{182,229,6,0,4,2,0,0,0,15,15,0,4,1,0,0,"3","",4,0},
					{182,254,6,0,4,2,0,0,0,15,15,0,4,1,0,0,"4","",4,0},
					{182,279,6,0,2,2,0,0,0,15,15,0,2,1,0,0,"5","",2,0},
					{182,304,6,0,3,2,0,0,0,15,15,0,3,1,0,0,"6","",3,0},
					{407,154,6,0,4,2,0,0,0,15,15,0,4,1,0,0,"7","",4,0},
					{407,179,6,0,4,2,0,0,0,15,15,0,4,1,0,0,"8","",4,0},
					{407,204,6,0,4,2,0,0,0,15,15,0,4,1,0,0,"9","",4,0},
					{407,229,6,0,3,2,0,0,0,15,15,0,3,1,0,0,"10","",3,0},
					{380,320,6,0,5,2,0,0,0,15,15,0,5,1,0,0,"00:00","",5,3},
					{317,369,13,0,12,2,0,0,0,15,15,0,12,1,0,0,"037166153415","",12,5},
					{180,340,6,0,3,2,0,0,0,15,15,0,3,1,0,0,"13","",3,0},
					{180,365,6,0,5,2,0,0,0,15,15,0,0,1,0,0,"00:00","",0,0},
					{180,390,6,0,2,2,0,0,0,15,15,0,2,1,0,0,"15","",2,0},
					};
    static CHECK BOY_CHECK[1] = {
				    {307,294,"自动定时上载",0,1,0,0,7,0,1,"",0},
				  };
    static WINDOWS BOY_WINDOWS = { 37,84,577,434,"控制器设置",7,1,0,0,1,3,15,0,0,0,15,1,15,0,7,0,0};

    for(i=0;i<16;i++)BOY_INPUTBOX[i].enable=0;
    BOY_CHECK[0].enable=0;
    strcpy(BOY_KEY3D[1].text,"更改");

    if(current_station==-1){
	strcpy(BOY_WINDOWS.text,"控制器设置:未连接");
    }
    else{
	strcpy(BOY_WINDOWS.text,"控制器设置:");
	strncat(BOY_WINDOWS.text,(char *)&station[current_station],sizeof(*station));
    }

    p=(int *)&set;
    FLAG=Connect;
    while(FLAG){
		sender(SetData);
		ReceviceData((char *)&set,sizeof(set));
		CASE=0;
		for(i=0;i<sizeof(set)/2-1;i++)CASE+=p[i];
		if(CASE==p[sizeof(set)/2-1])FLAG=0;
	}
	strcpy(BOY_INPUTBOX[0].text,hex(set.Boost,1,""));
	strcpy(BOY_INPUTBOX[1].text,hex(set.Taper,1,""));
	strcpy(BOY_INPUTBOX[2].text,hex(set.Float_Max,1,""));
	strcpy(BOY_INPUTBOX[3].text,hex(set.Float_Min,1,""));
	strcpy(BOY_INPUTBOX[4].text,hex(set.Boost_Below,1,""));
	strcpy(BOY_INPUTBOX[5].text,hex(set.Comp_Temp,0,""));
	strcpy(BOY_INPUTBOX[6].text,hex(set.Delay_Change,0,""));
	strcpy(BOY_INPUTBOX[7].text,hex(set.Alarm_Voltage_Low,1,""));
	strcpy(BOY_INPUTBOX[8].text,hex(set.Alarm_Voltage_High,1,""));
	strcpy(BOY_INPUTBOX[9].text,hex(set.Voltage_Reload,1,""));
	strcpy(BOY_INPUTBOX[10].text,hex(set.Delay_Disconnect,0,""));
	strcpy(BOY_INPUTBOX[14].text,hex(set.Hour,0,":"));
	strcat(BOY_INPUTBOX[14].text,hex(set.Min,0,""));
	for(i=0;i<12;i++)PHONE[i]=set.Phone[i];
	strcpy(BOY_INPUTBOX[12].text,PHONE);
	strcpy(BOY_INPUTBOX[13].text,hex(set.Sit_Number,0,""));
	strcpy(BOY_INPUTBOX[11].text,hex(set.UpHour,0,":"));
	strcat(BOY_INPUTBOX[11].text,hex(set.UpMin,0,""));
	strcpy(BOY_INPUTBOX[15].text,hex(set.Temp_Lcd,0,""));
	if(set.Auto_Upload)BOY_CHECK[0].YN=1;
		else BOY_CHECK[0].YN=0;

	BOY_WINDOWS.key = BOY_KEY3D;
	BOY_WINDOWS.lab = BOY_LABEL;
	BOY_WINDOWS.frm = BOY_FRAME;
	BOY_WINDOWS.inp = BOY_INPUTBOX;
	BOY_WINDOWS.chk = BOY_CHECK;

	CREATE_WINDOWS_ALL(&BOY_WINDOWS,&BOY_TYPE[0],BOY_TOTAL,BOY_TAB);

	FLAG=0;
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
		strncpy(savefile,"S",1);
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
		fprintf(fp,"	设置状态记录\n");
		fprintf(fp,"\n站点:%s	电话号码:%s	说明:%s\n",station[current_station].NO,station[current_station].phone,station[current_station].comment);
		fprintf(fp,"记录时间:%d年%d月%d日 	%d时%d分\n",date.da_year,date.da_mon,date.da_day,time.ti_hour,time.ti_min);
		fprintf(fp,"\n参数		原设定值		现设定值\n\n");
		fprintf(fp,"强充最大电压	%.1fV			%.1fV\n\n",(float)set.Boost/10,(float)newset.Boost/10);
		fprintf(fp,"强充递减电压	%.1fV			%.1fV\n\n",(float)set.Taper/10,(float)newset.Taper/10);
		fprintf(fp,"浮充电压上限	%.1fV			%.1fV\n\n",(float)set.Float_Max/10,(float)newset.Float_Max/10);
		fprintf(fp,"浮充电压下限	%.1fV			%.1fV\n\n",(float)set.Float_Min/10,(float)newset.Float_Min/10);
		fprintf(fp,"返回强充电压	%.1fV			%.1fV\n\n",(float)set.Boost_Below/10,(float)newset.Boost_Below/10);
		fprintf(fp,"温度补偿电压	%dmV			%dmV\n\n",set.Comp_Temp,newset.Comp_Temp);
		fprintf(fp,"状态转换延时	%dS			%dS\n\n",set.Delay_Change,newset.Delay_Change);
		fprintf(fp,"告警电压上限	%.1fV			%.1fV\n\n",(float)set.Alarm_Voltage_High/10,(float)newset.Alarm_Voltage_High/10);
		fprintf(fp,"告警电压下限	%.1fV			%.1fV\n\n",(float)set.Alarm_Voltage_Low/10,(float)newset.Alarm_Voltage_Low/10);
		fprintf(fp,"负载重连接电压	%.1fV			%.1fV\n\n",(float)set.Voltage_Reload/10,(float)newset.Voltage_Reload/10);
		fprintf(fp,"断开负载前延时	%dS			%dS\n\n",set.Delay_Disconnect,newset.Delay_Disconnect);
		fprintf(fp,"控制器编号	%d			%d\n\n",set.Sit_Number,newset.Sit_Number);
		fprintf(fp,"当前时间	%d:%d			%d:%d\n\n",set.Hour,set.Min,newset.Hour,newset.Min);
		fprintf(fp,"最低显示温度	%d℃			%d℃\n\n",set.Temp_Lcd,newset.Temp_Lcd);
		fprintf(fp,"定时自动上载	%s			%s\n\n",set.Auto_Upload?"Yes":"No",newset.Auto_Upload?"Yes":"No");
		fprintf(fp,"自动上载时间	%d:%d			%d:%d\n\n",set.UpHour,set.UpMin,newset.UpHour,newset.UpMin);
		for(i=0;i<12;i++)PHONE[i]=set.Phone[i];
		fprintf(fp,"上载电话号码	%s			",PHONE);
		for(i=0;i<12;i++)PHONE[i]=newset.Phone[i];
		fprintf(fp,"%s\n\n",PHONE);
		fprintf(fp,"********************文件结束******************");

		fclose(fp);
	 break;
	 }
	 case 2:{
		if(!WORK){
			for(i=0;i<16;i++)BOY_INPUTBOX[i].enable=1;
			BOY_CHECK[0].enable=1;
			BOY_CHECK[0].textcolor=0;
			strcpy(BOY_KEY3D[1].text,"发送");
			CLOSE_BOY_WINDOWS(&BOY_WINDOWS);

			CREATE_WINDOWS_ALL(&BOY_WINDOWS,&BOY_TYPE[0],BOY_TOTAL,BOY_TAB);
			WORK=1;

			break;
		}
		else{
			newset.Boost=(int)(atof(BOY_INPUTBOX[0].text)*10);
			newset.Taper=(int)(atof(BOY_INPUTBOX[1].text)*10);
			newset.Float_Max=(int)(atof(BOY_INPUTBOX[2].text)*10);
			newset.Float_Min=(int)(atof(BOY_INPUTBOX[3].text)*10);
			newset.Boost_Below=(int)(atof(BOY_INPUTBOX[4].text)*10);
			newset.Comp_Temp=(atoi(BOY_INPUTBOX[5].text));
			newset.Delay_Change=(atoi(BOY_INPUTBOX[6].text));
			newset.Alarm_Voltage_Low=(int)(atof(BOY_INPUTBOX[7].text)*10);
			newset.Alarm_Voltage_High=(int)(atof(BOY_INPUTBOX[8].text)*10);
			newset.Voltage_Reload=(int)(atof(BOY_INPUTBOX[9].text)*10);
			newset.Delay_Disconnect=(atoi(BOY_INPUTBOX[10].text));
			newset.Hour=atoi(BOY_INPUTBOX[14].text);
			for(i=0;i<4;i++){
				if(BOY_INPUTBOX[14].text[i]==':')break;
			}
			newset.Min=atoi(&BOY_INPUTBOX[14].text[i+1]);
			strcpy(PHONE,BOY_INPUTBOX[12].text);
			for(i=0;i<12;i++)newset.Phone[i]=PHONE[i];
			newset.Sit_Number=atoi(BOY_INPUTBOX[13].text);
			newset.UpHour=atoi(BOY_INPUTBOX[11].text);
			for(i=0;i<4;i++){
				if(BOY_INPUTBOX[11].text[i]==':')break;
			}
			newset.UpMin=atoi(&BOY_INPUTBOX[11].text[i+1]);
			newset.Temp_Lcd=atoi(BOY_INPUTBOX[15].text);
			newset.Auto_Upload=BOY_CHECK[0].YN?1:0;
			if((BOOST_MIN>newset.Boost)||(newset.Boost>BOOST_MAX)){
				CreateErrorWindows("最大强充电压设置错误!");
				break;
			}
			if((TAPER_MIN>newset.Taper)||(newset.Taper>TAPER_MAX)){
				CreateErrorWindows("最大递减电压设置错误!");
				break;
			}
			if((FLOAT_MIN>newset.Float_Max)||(newset.Float_Max>FLOAT_MAX)){
				CreateErrorWindows("浮充电压上限设置错误!");
				break;
			}
			if((FLOAT_MIN>newset.Float_Min)||(newset.Float_Min>FLOAT_MAX)){
				CreateErrorWindows("浮充电压下限设置错误!");
				break;
			}
			if((BOOST_BELOW_MIN>newset.Boost_Below)||(newset.Boost_Below>BOOST_BELOW_MAX)){
				CreateErrorWindows("返回强充电压设置错误!");
				break;
			}

			newset.CheckSum=0;
			p=(int *)&newset;
			for(i=0;i<(sizeof(newset)/2-1);i++)newset.CheckSum+=p[i];
			sender(SendSetData);
//			SendData((char *)&newset,sizeof(newset));
			if(Connect)
			while(1){
				while((i=getb())==-1);
				if(i==30)break;
					sender(p[i]/256);
					delay(500);
					sender(p[i]%256);
					delay(500);
					sender(p[i]/256);
					delay(500);
					sender(p[i]%256);
					delay(500);
//				printf("i=%d",i);
				}

			CreateWarningWindows("","设置发送完毕!",0);
			break;
		}
	 }
	 case 3:
	 case WindowsClose:FLAG=1;break;
	}
	  }
	 CLOSE_BOY_WINDOWS(&BOY_WINDOWS);
  }
