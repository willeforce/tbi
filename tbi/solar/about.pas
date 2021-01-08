unit about;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls,
  Buttons, ExtCtrls;

type
  TAboutBox = class(TForm)
    OKButton: TButton;
    Image1: TImage;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

  procedure showaboutbox(Sender: TObject);

implementation

{$R *.DFM}

procedure showaboutbox(Sender: TObject);
begin
  with taboutbox.create(application) do
    try
      showmodal;
    finally
      free;
  end;
end;

end.
 
