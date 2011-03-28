unit Unit4;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls, 
  Buttons, ExtCtrls, Spin;

type
  Tfmt = class(TForm)
    Panel1: TPanel;
    Panel2: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    OKBtn: TButton;
    cancel: TButton;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    Edit6: TEdit;
    Button1: TButton;
    Button2: TButton;
    SpinEdit1: TSpinEdit;
    SpinEdit3: TSpinEdit;
    Edit7: TEdit;
    Edit8: TEdit;
    procedure cancelClick(Sender: TObject);
    procedure OKBtnClick(Sender: TObject);
    procedure Label1MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label1MouseLeave(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Label1Click(Sender: TObject);
    procedure Edit8Change(Sender: TObject);
    procedure Edit7Change(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fmt: Tfmt;

implementation
uses unit1, unit5;
{$R *.dfm}

procedure Tfmt.cancelClick(Sender: TObject);
begin
fmt.close;
end;
function mask(a,b:integer):string;
var s:string; i:integer;
begin
s:=inttostr(a);
if length(s)<b then for i:=1 to b-length(s) do s:='0'+s;
mask:=s;
end;
procedure Tfmt.OKBtnClick(Sender: TObject);
begin
fmt.close;
end;

procedure Tfmt.Label1MouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
label1.Font.Style:=[fsBold,fsUnderline];
end;

procedure Tfmt.Label1MouseLeave(Sender: TObject);
begin
label1.Font.Style:=[fsBold];
end;

procedure Tfmt.Button1Click(Sender: TObject);
var s,st:string; i:integer; a:boolean;
begin
  s:=extractfilepath(application.exename)+'tests\'+edit1.text+mask(1,length(edit7.Text))+edit2.text+'.'+edit3.text;
  if FileExists(s)=false then begin
    Application.MessageBox('Файл не найден! Проверьте правильность ввода данных','Ошибка',MB_iconstop);
  end else begin
    panel2.Visible:=false;
    panel1.Visible:=true;
    fmt.Repaint;
    i:=0;
    repeat
      inc(i);
      s:=extractfilepath(application.exename)+'tests\'+edit1.Text+mask(i,length(edit7.Text))+edit2.Text+'.'+edit3.Text;
      if FileExists(s)=false then begin
        Application.MessageBox('Файл не найден! Форматирование прервано.','Ошибка',MB_iconstop);
        i:=spinedit1.Value;
      end else begin
        st:=extractfilepath(application.exename)+'tests\'+inttostr(i)+'.in';
        a:=RenameFile(s,st);
      end;
    until i>=spinedit1.Value;
    panel1.Visible:=false;
    panel2.Visible:=true;
    fmt.Repaint;
    edit1.Text:='';
    edit2.Text:='';
    edit3.Text:='';
    edit7.Text:='*';
    spinedit1.value:=1;
 end;
end;

procedure Tfmt.Button2Click(Sender: TObject);
var s,st:string; i:integer; a:boolean;
begin
  s:=extractfilepath(application.exename)+'tests\'+edit4.text+mask(1,length(edit8.Text))+edit5.text+'.'+edit6.text;
  if FileExists(s)=false then begin
    Application.MessageBox('Файл не найден! Проверьте правильность ввода данных','Ошибка',MB_iconstop);
  end else begin 
    panel2.Visible:=false;
    panel1.Visible:=true;
    fmt.Repaint;
    i:=0;
    repeat
      inc(i);
      s:=extractfilepath(application.exename)+'tests\'+edit4.Text+mask(i,length(edit8.Text))+edit5.Text+'.'+edit6.Text;
      if FileExists(s)=false then begin
        Application.MessageBox('Файл не найден! Форматирование прервано.','Ошибка',MB_iconstop);
        i:=spinedit3.Value;
      end else begin
        st:=extractfilepath(application.exename)+'tests\'+inttostr(i)+'.out';
        a:=RenameFile(s,st);
      end;
    until i>=spinedit3.Value;
    panel1.Visible:=false;
    panel2.Visible:=true;
    fmt.Repaint;
    edit4.Text:='';
    edit5.Text:='';
    edit6.Text:='';
    edit8.text:='*';
    spinedit3.value:=1;
end;
end;

procedure Tfmt.Label1Click(Sender: TObject);
begin
fmth.Show;
end;
procedure Tfmt.Edit8Change(Sender: TObject);
begin
if length(edit8.Text)=0 then begin
  application.MessageBox('Маска числа не может быть нулевой!','Ошибка',mb_iconerror);
  edit8.Text:='*';
end;
end;

procedure Tfmt.Edit7Change(Sender: TObject);
begin
if length(edit7.Text)=0 then begin
  application.MessageBox('Маска числа не может быть нулевой!','Ошибка',mb_iconerror);
  edit7.Text:='*';
end;
end;

end.
