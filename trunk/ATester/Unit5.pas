unit Unit5;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls, 
  Buttons, ExtCtrls;

type
  Tfmth = class(TForm)
    OKBtn: TButton;
    CancelBtn: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Edit1: TEdit;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Edit2: TEdit;
    Label9: TLabel;
    Edit3: TEdit;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Edit4: TEdit;
    Label16: TLabel;
    Edit5: TEdit;
    Label18: TLabel;
    Edit6: TEdit;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Edit7: TEdit;
    Label25: TLabel;
    Edit8: TEdit;
    Label27: TLabel;
    Edit9: TEdit;
    Label28: TLabel;
    Label29: TLabel;
    Label30: TLabel;
    Label31: TLabel;
    Label35: TLabel;
    Edit10: TEdit;
    Label15: TLabel;
    Label17: TLabel;
    Label24: TLabel;
    Label26: TLabel;
    Label32: TLabel;
    Label33: TLabel;
    Edit12: TEdit;
    Label34: TLabel;
    Label36: TLabel;
    Label37: TLabel;
    Label38: TLabel;
    procedure CancelBtnClick(Sender: TObject);
    procedure OKBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fmth: Tfmth;

implementation

{$R *.dfm}

procedure Tfmth.CancelBtnClick(Sender: TObject);
begin
fmth.Close;
end;

procedure Tfmth.OKBtnClick(Sender: TObject);
begin
fmth.Close;
end;

end.
