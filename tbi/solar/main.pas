unit Main;

interface

uses
  SysUtils, Windows, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, Buttons, ExtCtrls, Menus, ComCtrls, ToolWin,
  DBTables, ComDrv32, OleCtrls, graphsv3, Grids, TeEngine, TeeFunci,
  Series, TeeProcs, Chart, Mask;

type
  TMainForm = class(TForm)
    StatusLine: TStatusBar;
    MainMenu: TMainMenu;
    FileMenu: TMenuItem;
    opensite: TMenuItem;
    save: TMenuItem;
    N1: TMenuItem;
    FilePrintItem: TMenuItem;
    FilePrintSetupItem: TMenuItem;
    N4: TMenuItem;
    FileExitItem: TMenuItem;
    EditMenu: TMenuItem;
    modemsetup: TMenuItem;
    HelpMenu: TMenuItem;
    HelpContentsItem: TMenuItem;
    N3: TMenuItem;
    HelpAboutItem: TMenuItem;
    hangup: TMenuItem;
    ToolBar1: TToolBar;
    SpeedButton1: TSpeedButton;
    CommPortDriver1: TCommPortDriver;
    display: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    TabSheet3: TTabSheet;
    SaveDialog1: TSaveDialog;
    PrintDialog1: TPrintDialog;
    PrinterSetupDialog1: TPrinterSetupDialog;
    SpeedButton2: TSpeedButton;
    SpeedButton3: TSpeedButton;
    SpeedButton4: TSpeedButton;
    StringGrid1: TStringGrid;
    StringGrid2: TStringGrid;
    Chart1: TChart;
    Series2: TLineSeries;
    Series3: TLineSeries;
    Series4: TLineSeries;
    TeeFunction1: TAddTeeFunction;
    TeeFunction2: TAddTeeFunction;
    TeeFunction3: TAddTeeFunction;
    TeeFunction4: TAddTeeFunction;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Series1: TLineSeries;
    procedure FormCreate(Sender: TObject);
    procedure ShowHint(Sender: TObject);
    procedure FileExit(Sender: TObject);
    procedure open(Sender: TObject);
    procedure EditCutItemClick(Sender: TObject);
    procedure HelpAboutItemClick(Sender: TObject);
    procedure modemsetupClick(Sender: TObject);
    procedure FilePrintSetupItemClick(Sender: TObject);
    procedure FilePrintItemClick(Sender: TObject);
    procedure applycommsettings;
    procedure CommPortDriver1ReceivePacket(Sender: TObject;
      Packet: Pointer; DataSize: Integer);
    procedure Button1Click(Sender: TObject);
  end;

var
  MainForm: TMainForm;
  ddelay,sended:boolean;
implementation

uses SiteUnit, about,setupunit;

{$R *.DFM}

procedure TMainForm.FormCreate(Sender: TObject);
begin
  sended:=false;
  Application.OnHint := ShowHint;
  assignfile(setupfile,'modem.cfg');
  reset(setupfile);
  read(setupfile,setupstate);
  closefile(setupfile);
end;

procedure TMainForm.ShowHint(Sender: TObject);
begin
  StatusLine.SimpleText := Application.Hint;
end;


procedure TMainForm.FileExit(Sender: TObject);
begin
  Close;
end;



procedure TMainForm.open(Sender: TObject);
begin
  {showsitebox(application);}
  siteform:=tsiteform.create(application);
  siteform.show;
  siteform.update;
end;

procedure TMainForm.EditCutItemClick(Sender: TObject);
begin
  {showsitebox(application);}
  siteform:=tsiteform.create(application);
  siteform.show;
  siteform.update;
end;


procedure TMainForm.HelpAboutItemClick(Sender: TObject);
begin
  showaboutbox(application);
end;

procedure TMainForm.modemsetupClick(Sender: TObject);
begin
  showsetupbox(application);
end;

procedure TMainForm.FilePrintSetupItemClick(Sender: TObject);
begin
  printersetupdialog1.Execute;
end;

procedure TMainForm.FilePrintItemClick(Sender: TObject);
begin
  printdialog1.Execute;
end;

procedure tmainform.applycommsettings;
begin
  commportdriver1.comport:=tcomportnumber(ord(setupstate.com));
  commportdriver1.comportspeed:=tcomportbaudrate(ord(setupstate.baud));
  commportdriver1.comportdatabits:=db8bits;
  commportdriver1.comportparity:=ptnone;
  commportdriver1.comporthwhandshaking:=hhnonertson;
  commportdriver1.comportswhandshaking:=shnone;
end;

procedure delay(dd:integer);
var i:integer;
begin
  for i:=1 to dd do
    ;
end;

procedure TMainForm.CommPortDriver1ReceivePacket(Sender: TObject;
  Packet: Pointer; DataSize: Integer);
  type tresult=array[1..680] of byte;
  var p:^tresult;
    i:smallint;
    num:integer;
    id:char;
    f:system.textfile;
    ss:string;
    ah:double;
begin
  messagebeep(0);
  mainform.stringgrid1.Cells[0,0]:='参数名称';
  mainform.StringGrid1.Cells[1,0]:='数值';
  mainform.stringgrid1.Cells[3,0]:='参数名称';
  mainform.StringGrid1.Cells[4,0]:='数值';
  p:=packet;
  assignfile(f,'current.dat');
  reset(f);
  i:=1;
  while not seekeof(f) do
    begin
      readln(f,id,num,ss);
      {num:=strtoint(snum);}
      mainform.StringGrid1.cells[0,i]:=ss;
      case id of
      '0':
      mainform.StringGrid1.cells[1,i]:=floattostr((p[num+1]*256+p[num])/10);
      '1':
      mainform.StringGrid1.Cells[1,i]:=inttostr(p[num]);
      '2':
      begin
      ah:=16777216/36000*p[num+3];
      ah:=ah+p[num+2]*65536/36000+p[num+1]*256/36000+p[num]/36000;
      mainform.StringGrid1.Cells[1,i]:=floattostr(ah);
      end;
      end;
      inc(i);
    end;
  closefile(f);
  mainform.StringGrid2.Cells[0,0]:='倒数天数';
  mainform.StringGrid2.cells[1,0]:='最高电压';
  mainform.StringGrid2.cells[2,0]:='最低电压';
  mainform.StringGrid2.Cells[3,0]:='充电电量';
  mainform.StringGrid2.cells[4,0]:='放电电量';
  mainform.Series1.Clear;
  mainform.Series2.Clear;
  mainform.Series3.Clear;
  mainform.Series4.Clear;
  for i:=0 to 31 do
  begin
    mainform.StringGrid2.Cells[0,i+1]:=inttostr(i);
    mainform.StringGrid2.cells[1,i+1]:=floattostr((p[169+i*8]+p[170+i*8]*256)/10);
    mainform.Series1.Add((p[169+i*8]+p[170+i*8]*256)/10,'',clteecolor);
    mainform.StringGrid2.Cells[2,i+1]:=floattostr((p[171+i*8]+p[172+i*8]*256)/10);
    mainform.Series2.Add((p[171+i*8]+p[172+i*8]*256)/10,'',clteecolor);
    mainform.StringGrid2.cells[3,i+1]:=inttostr(p[173+i*8]+p[174+i*8]*256);
    mainform.Series3.Add(p[173+i*8]+p[174+i*8]*256,'',clteecolor);
    mainform.StringGrid2.cells[4,i+1]:=inttostr(p[175+i*8]+p[176+i*8]*256);
    mainform.Series4.Add(p[175+i*8]+p[176+i*8]*256,'',clteecolor);
  end;
  if p[61]=0 then mainform.CheckBox1.Checked:=false
    else mainform.CheckBox1.Checked:=true;
  if p[73]=0 then mainform.CheckBox2.checked:=false
    else mainform.CheckBox2.Checked:=true;
  mainform.MaskEdit1.editmask:='';
  mainform.MaskEdit2.editmask:='';
  mainform.MaskEdit3.editmask:='';
  mainform.MaskEdit4.editmask:='';
  mainform.MaskEdit5.editmask:='';
  mainform.maskedit4.Text:=inttostr(p[57])+':'+inttostr(p[59]);
  mainform.MaskEdit3.Text:=inttostr(p[53])+':'+inttostr(p[55]);
  mainform.MaskEdit6.text:=floattostr((p[69]+p[70]*256)/10);
  mainform.MaskEdit7.text:=floattostr((p[67]+p[68]*256)/10);
  mainform.MaskEdit8.Text:=floattostr((p[63]+p[64]*256)/10);
  mainform.MaskEdit9.Text:=floattostr((p[65]+p[66]*256)/10);
  mainform.MaskEdit10.Text:=inttostr(p[72]);
  mainform.MaskEdit5.Text:=inttostr(p[76])+':'+inttostr(p[78]);
  mainform.MaskEdit11.text:='';
  for i:=1 to 12  do
  mainform.MaskEdit11.Text:=mainform.maskedit11.text+chr(p[77+i*2]);
  mainform.MaskEdit1.Text:=inttostr(p[560])+'-'+inttostr(p[561])+'-'+inttostr(p[562]);
  mainform.MaskEdit2.Text:=inttostr(p[557])+':'+inttostr(p[555]);
end;

procedure sendint(i:string;j:integer);
  var a:integer;
begin
  a:=round(strtofloat(i)*10);
  with mainform.commportdriver1 do
  begin
    sendbyte(54);
    sendbyte(j);
    sendbyte(a div 256);
    sendbyte(a mod 256);
  end;
  delay(10);
end;

procedure senddate(i:string);
var day,mon,year:integer;
    s1,s2,s:string;
begin
  {s1:=i[1]+i[2];
  s2:=i[3]+i[4];
  s:=i[5]+i[6];}
  s1:=copy(i,pos('-',i)+1,length(i)-pos('-',i));
  s2:=copy(s1,pos('-',s1)+1,length(s1)-pos('-',s1));
  mon:=length(i);
  for day:=1 to mon do
    if i[day]='-' then break
      else s:=s+i[day];
  day:=strtoint(s);
  with mainform.commportdriver1 do
  begin
    sendbyte(55);
    sendbyte(7);
    sendbyte(day);
    delay(10);
  s:='';
  mon:=length(s1);
  for day:=1 to mon do
    if s1[day]='-' then break
      else s:=s+s1[day];
  mon:=strtoint(s);
    sendbyte(55);
    sendbyte(8);
    sendbyte(mon);
    delay(10);
   year:=strtoint(s2);
    sendbyte(55);
    sendbyte(9);
    sendbyte(year);
    delay(10);
 end;
end;

procedure sendsystime(i:string);
var hour,min:integer;
    s1,s:string;
begin
  {s1:=i[3]+i[4];
  s:=i[1]+i[2];}
  s1:=copy(i,pos(':',i)+1,length(i)-pos(':',i));
  hour:=length(i);
  for min:=1 to hour do
    if i[min]=':' then break
      else s:=s+i[min];
  hour:=strtoint(s);
  min:=strtoint(s1);
  with mainform.CommPortDriver1 do
  begin
    sendbyte(55);
    sendbyte(4);
    sendbyte(hour);
    delay(10);
    sendbyte(55);
    sendbyte(2);
    sendbyte(min);
    delay(10);
  end;
end;

procedure sendtime(i:string;a:integer);
var hour,min:integer;
    s1,s:string;
begin
{  s:=i[1]+i[2];
  s1:=i[3]+i[4];}
  s1:=copy(i,pos(':',i)+1,length(i)-pos(':',i));
  hour:=length(i);
  for min:=1 to hour do
    if i[min]=':' then break
      else s:=s+i[min];
  hour:=strtoint(s);
  min:=strtoint(s1);
  with mainform.CommPortDriver1 do
  begin
    sendbyte(54);
    sendbyte(a);
    sendbyte(0);
    delay(10);
    sendbyte(hour);
    sendbyte(54);
    sendbyte(a+1);
    sendbyte(0);
    sendbyte(min);
    delay(10);
  end;
end;

procedure sendphone(i:string);
var j,k:integer;
begin
  k:=length(i);
  for j:=1 to k do
  begin
  with mainform.CommPortDriver1 do
  begin
    sendbyte(54);
    sendbyte(12+j);
    sendbyte(0);
    sendchar(i[j]);
    delay(10);
    end;
  end;
  for j:=k-1 to 12 do
  begin
  with mainform.CommPortDriver1 do
  begin
    sendbyte(54);
    sendbyte(13+j);
    sendbyte(0);
    sendbyte(0);
    delay(10);
  end;
  end;
end;

procedure sendboolean(b:boolean;a:integer);
begin
  with mainform.CommPortDriver1 do
  begin
    sendbyte(54);
    sendbyte(a);
    sendbyte(0);
    if b then sendbyte(1)
      else sendbyte(0);
  end;
end;

procedure TMainForm.Button1Click(Sender: TObject);
begin
  if not sended then
    begin
  maskedit1.enabled:=true;
  maskedit2.enabled:=true;
  maskedit3.enabled:=true;
  maskedit4.enabled:=true;
  maskedit5.enabled:=true;
  maskedit6.enabled:=true;
  maskedit7.enabled:=true;
  maskedit8.enabled:=true;
  maskedit9.enabled:=true;
  maskedit10.enabled:=true;
  maskedit11.enabled:=true;
  checkbox1.enabled:=true;
  checkbox2.enabled:=true;
  button1.caption:='发送数据';
  sended:=true;
    end
  else
    begin
      sendint(maskedit6.text,8);
      sendint(maskedit7.text,7);
      sendint(maskedit8.text,5);
      sendint(maskedit9.text,6);
      senddate(maskedit1.Text);
      sendsystime(maskedit2.text);
      sendtime(maskedit3.text,0);
      sendtime(maskedit4.text,2);
      sendtime(maskedit5.text,11);
      sendint(maskedit10.Text,9);
      sendphone(maskedit11.Text);
      sendboolean(checkbox1.Enabled,4);
      sendboolean(checkbox2.Enabled,10);
      maskedit1.enabled:=false;
  maskedit2.enabled:=false;
  maskedit3.enabled:=false;
  maskedit4.enabled:=false;
  maskedit5.enabled:=false;
  maskedit6.enabled:=false;
  maskedit7.enabled:=false;
  maskedit8.enabled:=false;
  maskedit9.enabled:=false;
  maskedit10.enabled:=false;
  maskedit11.enabled:=false;
  checkbox1.enabled:=false;
  checkbox2.enabled:=false;
  button1.caption:='更改数据';
  sended:=false;
    end;

end;


end.
