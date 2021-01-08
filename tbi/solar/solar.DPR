program solar;

uses
  Forms,
  main in 'main.pas' {MainForm},
  CoverUnit in 'CoverUnit.pas' {CoverForm},
  about in 'about.pas' {AboutBox},
  SiteUnit in 'SiteUnit.pas' {siteform},
  new in 'new.pas' {OKBottomDlg},
  ComDrv32 in 'ComDrv32.pas',
  setupunit in 'setupunit.pas' {setup};


{$R *.RES}

begin
  CoverForm:=TCoverForm.Create(Application);
  CoverForm.Show;
  CoverForm.Update;
  CoverForm.Hide;
  CoverForm.free;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
