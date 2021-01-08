unit SiteUnit;

interface

uses
  SysUtils, Windows, Messages, Classes, Graphics, Controls,
  StdCtrls, Forms, DBCtrls, DB, DBGrids, DBTables, Grids, ExtCtrls,Dialogs;

type
  Tsiteform = class(TForm)
    Table1StringField: TStringField;
    Table1StringField2: TStringField;
    Table1StringField3: TStringField;
    DBGrid1: TDBGrid;
    DataSource1: TDataSource;
    Panel2: TPanel;
    Table1: TTable;
    Panel1: TPanel;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    procedure FormCreate(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  siteform: Tsiteform;
procedure showsitebox(Sender: TObject);
implementation

uses new, main;

{$R *.DFM}
procedure showsitebox(Sender: TObject);
begin
  with tsiteform.create(application) do
    try
      showmodal;
    finally
      free;
  end;
end;

procedure Tsiteform.FormCreate(Sender: TObject);
begin
  Table1.Open;
end;

procedure Tsiteform.Button3Click(Sender: TObject);
begin
  if table1.recordcount>0 then table1.delete;
end;

procedure Tsiteform.Button4Click(Sender: TObject);
begin
  siteform.Hide;
  {siteform.free;}
end;

procedure Tsiteform.Button2Click(Sender: TObject);
begin
  {table1.AppendRecord(['001','1234','abcd']);}
  {shownewbox(application);}
  okbottomdlg:=tokbottomdlg.create(application);
  okbottomdlg.show;
  okbottomdlg.update;
end;

procedure Tsiteform.Button1Click(Sender: TObject);
begin
  mainform.applycommsettings;
  if mainform.commportdriver1.connect then
  begin
    if mainform.commportdriver1.getlinestatus=[] then
      mainform.commportdriver1.checklinestatus:=true;
    mainform.statusline.simpletext:='已连接';
    mainform.CommPortDriver1.SendByte(51);
    {mainform.CommPortDriver1.SendString('AT&V');}
    mainform.CommPortDriver1.PacketSize:=680;
    mainform.CommPortDriver1.PacketTimeout:=6000;
     end
  else
    begin
      {mainform.statusline.simpletext:='未能建立连接.请检查串行口设置,然后重试.';
      messagebeep(0);}
      MessageDlg('串行口未打开.请检查串行口设置,然后重试.',mtError,[mbOK],0);
    end;
  siteform.hide;
end;

end.