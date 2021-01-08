 # include "jrtz.h"

extern TYPE  DialogType[15];
extern KEY3D DialogKey3d[5] ;
extern LABEL DialogLabel[5] ;
extern INPUTBOX DialogInputbox[3] ;
extern ICON DialogIcon[1] ;
extern PICTURE DialogPicture[1] ;
extern WINDOWS DialogWindows ;
extern int  DialogTotal;
extern  int  DialogTab;
extern  int  CS_Dialog ;
extern char DialogPath[MaxPath];
extern  char DLGPATH[MaxPath];
extern char BOY_FILE_NAME[MaxPath];

extern char DLL_openname[MaxPath];
extern TEST DLL_test;
extern char COM;
extern int station_sum;

void waitsend(void)
{
	char result[20],FLAG=1,PHONE[12];
	int i,CASE,*p;
	_Now now;
        _Set set;
	struct date date;
	struct time time;
	char savefile[13];
	FILE *fp;
	extern int current_station;
	extern _station *station;

	strset(DLL_openname,'\0');
	strcpy(DLL_openname,DLGPATH);
	strcat(DLL_openname,"\\warning1.Dlg");

	ReadDialogWindows(DLL_openname);
	strcpy(DialogLabel[0].text,"�غ�״̬,��Esc���˳�...");
	SetDialogPath(DLGPATH);
	Com_Init(COM,4,8,1,3);
	Send_String("\rat&fv0e0s0=1\r");
	delay(1000);
	Recvice_String(result);
	CreateDialogWindows();

	while(1){
		if(kbhit()){
			if(getch()==ESC){
				CloseDialogWindows();
				return;
			}
		}
		if(recvice_r()){
			Recvice_String(result);
			i=atoi(result);
			switch(i){
/*				case 0:{
					CreateWarningWindows("��ʾ","�绰���벻��ȷ!",0);
					break;
				}*/
				case 2:{
					break;
				}
				case 3:{
					break;
				}
				case 6:{
					break;
				}
				case 7:{
					break;
				}
				default:{
					break;
				}
				case 1:
				case 5:
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
				case 18:
				case 24:
				case 28:{
					while(FLAG){
						sender(SetData);
						ReceviceData((char *)&set,sizeof(set));
						CASE=0;
						p=(int *)&set;
						for(i=0;i<sizeof(set)/2-1;i++)CASE+=p[i];
						if(CASE==p[sizeof(set)/2-1])FLAG=0;
					}
					FLAG=1;
					while(FLAG){
						sender(NowData);
						ReceviceData((char *)&now,sizeof(now));
						CASE=0;
						p=(int *)&now;
						for(i=0;i<sizeof(now)/2-1;i++)CASE+=p[i];
						if(CASE==p[sizeof(now)/2-1])FLAG=0;
					}
					//for(i=0;i<20;i++)result[i]=0;
					//itoa(set.Sit_Number,result,10);
					for(i=0;i<station_sum;i++){
						//if(strcmp(station[i].NO,result)==0)current_station=i;
						if(set.Sit_Number==atoi(station[i].NO))current_station=i;
					}
					getdate(&date);
					gettime(&time);
					for(i=0;i<13;i++)savefile[i]='\0';
					strncpy(savefile,"W",1);
					strncat(savefile,station[current_station].NO,3);
					savefile[4]=date.da_mon/10+'0';
					savefile[5]=date.da_mon%10+'0';
					savefile[6]=date.da_day/10+'0';
					savefile[7]=date.da_day%10+'0';
					strcat(savefile,".TXT");
					if((fp=fopen(savefile,"wt"))==NULL){
						CreateErrorWindows("δ�ܽ����ļ�!");
						break;
					}
					fprintf(fp,"	��ǰ״̬��¼\n");
					fprintf(fp,"\nվ��:%s	�绰����:%s	˵��:%s\n",station[current_station].NO,station[current_station].phone,station[current_station].comment);
					fprintf(fp,"��¼ʱ��:%d��%d��%d�� 	%dʱ%d��\n",date.da_year,date.da_mon,date.da_day,time.ti_hour,time.ti_min);
					fprintf(fp,"���ص�ѹ = %.1f V\n",(float)now.Battery_Voltage/10);
					fprintf(fp,"���س����� = %.1f A\n",(float)now.Battery_Current/10);
					fprintf(fp,"���ص�ѹ = %.1f V\n",(float)now.Load_Voltage/10);
					fprintf(fp,"���ص��� = %.1f A\n",(float)now.Load_Current/10);
					fprintf(fp,"�����¶� = %d ���϶�\n",now.Battery_Temp);
					fprintf(fp,"�����¶� = %d ���϶�\n",now.In_Temp);
					fprintf(fp,"���״̬ = %d \n",now.WorkState);
					fprintf(fp,"ʱ�� = %-2d:%-2d\n",now.Hour,now.Min);
					for(i=0;i<6;i++)fprintf(fp,"̫���ܵ�ص� %d ���ѹ = %.1f V		���� = %.1f A\n",i+1,(float)now.Solar_Voltage[i]/10,(float)now.Solar_Current[i]/10);
					fprintf(fp,"�����ۼƳ����� = %d AH\n",now.Charge_Ah);
					fprintf(fp,"�����ۼƷŵ���� = %d AH\n",now.Discharge_Ah);
					fprintf(fp,"����������ߵ�ѹ = %.1f V\n",(float)now.Max_Battery_Voltage/10);
					fprintf(fp,"����������͵�ѹ = %.1f V\n",(float)now.Min_Battery_Voltage/10);
					fprintf(fp,"\n	����״̬��¼\n");
					fprintf(fp,"\nվ��:%s	�绰����:%s	˵��:%s\n",station[current_station].NO,station[current_station].phone,station[current_station].comment);
					fprintf(fp,"��¼ʱ��:%d��%d��%d�� 	%dʱ%d��\n",date.da_year,date.da_mon,date.da_day,time.ti_hour,time.ti_min);
					fprintf(fp,"\n����		ԭ�趨ֵ		���趨ֵ\n\n");
					fprintf(fp,"ǿ������ѹ	%.1fV			%.1fV\n\n",(float)set.Boost/10,(float)set.Boost/10);
					fprintf(fp,"ǿ��ݼ���ѹ	%.1fV			%.1fV\n\n",(float)set.Taper/10,(float)set.Taper/10);
					fprintf(fp,"�����ѹ����	%.1fV			%.1fV\n\n",(float)set.Float_Max/10,(float)set.Float_Max/10);
					fprintf(fp,"�����ѹ����	%.1fV			%.1fV\n\n",(float)set.Float_Min/10,(float)set.Float_Min/10);
					fprintf(fp,"����ǿ���ѹ	%.1fV			%.1fV\n\n",(float)set.Boost_Below/10,(float)set.Boost_Below/10);
					fprintf(fp,"�¶Ȳ�����ѹ	%dmV			%dmV\n\n",set.Comp_Temp,set.Comp_Temp);
					fprintf(fp,"״̬ת����ʱ	%dS			%dS\n\n",set.Delay_Change,set.Delay_Change);
					fprintf(fp,"�澯��ѹ����	%.1fV			%.1fV\n\n",(float)set.Alarm_Voltage_High/10,(float)set.Alarm_Voltage_High/10);
					fprintf(fp,"�澯��ѹ����	%.1fV			%.1fV\n\n",(float)set.Alarm_Voltage_Low/10,(float)set.Alarm_Voltage_Low/10);
					fprintf(fp,"���������ӵ�ѹ	%.1fV			%.1fV\n\n",(float)set.Voltage_Reload/10,(float)set.Voltage_Reload/10);
					fprintf(fp,"�Ͽ�����ǰ��ʱ	%dS			%dS\n\n",set.Delay_Disconnect,set.Delay_Disconnect);
					fprintf(fp,"���������	%d			%d\n\n",set.Sit_Number,set.Sit_Number);
					fprintf(fp,"��ǰʱ��	%d:%d			%d:%d\n\n",set.Hour,set.Min,set.Hour,set.Min);
					fprintf(fp,"�����ʾ�¶�	%d��			%d��\n\n",set.Temp_Lcd,set.Temp_Lcd);
					fprintf(fp,"��ʱ�Զ�����	%s			%s\n\n",set.Auto_Upload?"Yes":"No",set.Auto_Upload?"Yes":"No");
					fprintf(fp,"�Զ�����ʱ��	%d:%d			%d:%d\n\n",set.UpHour,set.UpMin,set.UpHour,set.UpMin);
					for(i=0;i<12;i++)PHONE[i]=set.Phone[i];
					fprintf(fp,"���ص绰����	%s			",PHONE);
					for(i=0;i<12;i++)PHONE[i]=set.Phone[i];
					fprintf(fp,"%s\n\n",PHONE);
					//fprintf(fp,"���ص绰����	%s			%s\n\n",set.Phone,set.Phone);
					fprintf(fp,"**********	�ļ�����    **********");
					fclose(fp);
					delay(1000);
					Send_String("+++");
					delay(2000);
					Send_String("ath0\r");
				}
			}
		}
	}
}