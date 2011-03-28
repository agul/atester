unit Unit6;

interface
uses windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
     Dialogs, StdCtrls, ExtCtrls, FileCtrl, shellapi, Spin, XPMan, psAPI,
  IdBaseComponent, IdComponent, IdTCPConnection, IdTCPClient, IdHTTP,
  ComCtrls;
  
type
  Tupd = class(TForm)
    IdHTTP1: TIdHTTP;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Button1: TButton;
    panel1: TPanel;
    Timer1: TTimer;
    Panel2: TPanel;
    ProgressBar1: TProgressBar;
    Label6: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  upd: Tupd;

implementation
uses unit1;
{$R *.dfm}

procedure getfile(url,filename:string);
var FileStream : TFileStream; http:tidhttp; s:string;
begin
HTTP:=TIdHTTP.Create(nil);
s:=filename;
deletefile(s);
FileStream:=TFileStream.Create(s, fmCreate);
try
  HTTP.Get(url, FileStream);
except
  Application.MessageBox('�� ����� �������� ��������� ������. ��������� �������.', '������', MB_ICONERROR);
end;
HTTP.Free;
FileStream.Free;
end;

procedure Tupd.FormCreate(Sender: TObject);
begin
Position:=poScreenCenter;
label3.caption:=version;
end;

procedure Tupd.Button1Click(Sender: TObject);
var new, localfilename:string;
begin
panel1.Visible:=false;
panel2.Visible:=true;
sleep(100);
upd.Repaint;
ProgressBar1.Position:=15;
try
    new:=new_v+'atester.v'+label5.Caption+'.exe';
    LocalFileName:=extractfilepath(application.exename)+'new.exe';
    timer1.Enabled:=true;
    progressbar1.Position:=25;
    Getfile(new, LocalFileName);
    progressbar1.Position:=40;
    sleep(100);
    progressbar1.Position:=65;
    new:=new_v+'updater.exe';
    LocalFileName:=extractfilepath(application.exename)+'updater.exe';
    Getfile(new, LocalFileName);
    timer1.Enabled:=false;
    progressbar1.Position:=85;
    sleep(100);
    progressbar1.Position:=100;
    if (fileexists(extractfilepath(application.exename)+'new.exe')) and (fileexists(extractfilepath(application.exename)+'updater.exe')) then begin
      winexec('updater.exe',sw_show);
      Application.Terminate;
    end;
except

end;
panel2.Visible:=false;
panel1.Visible:=true;
end;

procedure Tupd.Timer1Timer(Sender: TObject);
begin
if progressbar1.Position<100 then ProgressBar1.Position:=ProgressBar1.Position+5;
upd.Repaint;
end;

end.
