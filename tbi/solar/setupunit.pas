unit setupunit;

interface

uses
  SysUtils, Windows, Messages, Classes, Graphics, Controls,
  StdCtrls, ExtCtrls, Forms, ComCtrls,ComDrv32;

type
  Tsetup = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    CheckBox1: TCheckBox;
    ComboBox1: TComboBox;
    ComboBox2: TComboBox;
    Label1: TLabel;
    Label2: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  end;

  Tsetupstate = Record
    com:integer;
    baud:integer;
    upload:Boolean;
  end;

  Tsetupfile = File of Tsetupstate;

var
  setupstate:Tsetupstate;
  setupfile:tsetupfile;
  setup: Tsetup;

procedure showsetupbox(sender:tobject);

implementation

{$R *.DFM}
procedure showsetupbox(Sender: TObject);
begin
  with tsetup.create(application) do
    try
      showmodal;
    finally
      free;
  end;
end;

procedure Tsetup.Button1Click(Sender: TObject);
begin
  setupstate.com:=combobox1.itemindex;
  setupstate.baud:=combobox2.itemindex;
  setupstate.upload:=checkbox1.checked;
  assignfile(setupfile,'modem.cfg');
  rewrite(setupfile);
  write(setupfile,setupstate);
  closefile(setupfile);
end;

procedure Tsetup.FormCreate(Sender: TObject);
begin
  combobox1.ItemIndex:=setupstate.com;
  combobox2.ItemIndex:=setupstate.baud;
  checkbox1.Checked:=setupstate.upload;
end;

end.
