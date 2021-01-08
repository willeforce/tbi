unit new;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls,
  Buttons, ExtCtrls,Db, DBTables;

type
  TOKBottomDlg = class(TForm)
    OKBtn: TButton;
    CancelBtn: TButton;
    Bevel1: TBevel;
    label1: TLabel;
    Edit1: TEdit;
    Label2: TLabel;
    Edit2: TEdit;
    Label3: TLabel;
    Edit3: TEdit;
    procedure CancelBtnClick(Sender: TObject);
    procedure OKBtnClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  OKBottomDlg: TOKBottomDlg;
procedure shownewbox(Sender: TObject);
implementation

uses SiteUnit;
{$R *.DFM}

procedure shownewbox(Sender: TObject);
begin
  with tokbottomdlg.create(application) do
    try
      showmodal;
    finally
      free;
  end;
end;

procedure TOKBottomDlg.CancelBtnClick(Sender: TObject);
begin
  okbottomdlg.Hide;
  {okbottomdlg.Free;}
end;

procedure TOKBottomDlg.OKBtnClick(Sender: TObject);
begin
  {site.Table1.Edit;}
  siteform.table1.appendrecord([OkBottomdlg.edit1.text,okbottomdlg.edit2.text,okbottomdlg.edit3.text]);
  {site.table1.Post;}
  okbottomdlg.hide;
end;



procedure TOKBottomDlg.FormCreate(Sender: TObject);
begin
  siteform.table1.open;
end;

end.
