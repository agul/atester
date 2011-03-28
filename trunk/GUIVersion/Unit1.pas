unit Unit1;

interface

uses Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
     Dialogs, StdCtrls, ExtCtrls, FileCtrl, shellapi, Spin, XPMan, psAPI,
  IdBaseComponent, IdComponent, IdTCPConnection, IdTCPClient, IdHTTP, wininet;
const new_v='http://atester.googlecode.com/svn/';
      version='3.1';
      release_date='28.03.2011';
type
  TForm1 = class(TForm)
    od1: TOpenDialog;
    GroupBox1: TGroupBox;
    Button1: TButton;
    Memo1: TMemo;
    Label1: TLabel;
    Memo2: TMemo;
    Label2: TLabel;
    Button2: TButton;
    Timer1: TTimer;
    GroupBox2: TGroupBox;
    Button3: TButton;
    Label3: TLabel;
    Label5: TLabel;
    Label7: TLabel;
    Label4: TLabel;
    SpinEdit1: TSpinEdit;
    Label6: TLabel;
    Memo4: TMemo;
    Button4: TButton;
    RadioButton1: TRadioButton;
    SpinEdit2: TSpinEdit;
    RadioButton2: TRadioButton;
    Label8: TLabel;
    Memo5: TMemo;
    path: TLabel;
    Button5: TButton;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Edit1: TEdit;
    Edit2: TEdit;
    CheckBox10: TCheckBox;
    Label12: TLabel;
    Label13: TLabel;
    ListBox1: TListBox;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    Label14: TLabel;
    Label15: TLabel;
    Timer2: TTimer;
    Label16: TLabel;
    Label17: TLabel;
    CheckBox3: TCheckBox;
    Memo3: TMemo;
    report: TMemo;
    Memo6: TMemo;
    CheckBox4: TCheckBox;
    stderr: TMemo;
    CheckBox5: TCheckBox;
    Label18: TLabel;
    SpinEdit3: TSpinEdit;
    Label19: TLabel;
    CheckBox6: TCheckBox;
    Label20: TLabel;
    od2: TOpenDialog;
    chkr: TLabel;
    Memo7: TMemo;
    IdHTTP1: TIdHTTP;
    Timer3: TTimer;
    procedure Button1Click(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Timer1Timer(Sender: TObject);
    procedure SpinEdit1Change(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure RadioButton1Click(Sender: TObject);
    procedure RadioButton2Click(Sender: TObject);
    procedure Label8MouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
    procedure Label8MouseLeave(Sender: TObject);
    procedure Label8Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure kill;
    procedure check;
    function check_abc:boolean;
    procedure count_files;
    procedure FormCreate(Sender: TObject);
    procedure Label14MouseEnter(Sender: TObject);
    procedure Label14MouseLeave(Sender: TObject);
    procedure Label14Click(Sender: TObject);
    procedure Label15MouseEnter(Sender: TObject);
    procedure Label15MouseLeave(Sender: TObject);
    procedure Label15Click(Sender: TObject);
    procedure Timer2Timer(Sender: TObject);
    procedure CheckBox3Click(Sender: TObject);
    procedure test(t:integer);
    procedure CheckBox6Click(Sender: TObject);
    procedure kill_checker;
    function checker_is_active:boolean;
    procedure Timer3Timer(Sender: TObject);
  private

  public

end;

var
  Form1: TForm1;
  f,g:text;
  numb,error,wid,acm_test,acm_type:integer;
  get,rep,new_version:string;
  time:int64;
  not_found,first:boolean;
  sa: TSECURITYATTRIBUTES;
  si: TSTARTUPINFO;
  pi: TPROCESSINFORMATION;
  hPipeOutputRead: THANDLE;
  hPipeOutputWrite: THANDLE;
  hPipeErrorsRead: THANDLE;
  hPipeErrorsWrite: THANDLE;
  Res, bTest: Boolean;
  env: array[0..100] of Char;
  szBuffer: array[0..256] of Char;
  dwNumberOfBytesRead: DWORD;
  Stream: TMemoryStream;
  OutP, ErrorP: TStringList;

implementation

uses unit2, unit3,unit4,unit5,unit6,unit7;

{$R *.dfm}
procedure tform1.count_files;
var i:integer;
begin
i:=1;
spinedit2.MinValue:=0;
spinedit2.MaxValue:=0;
while (fileexists(extractfilepath(application.ExeName)+'tests\'+inttostr(i)+'.in')=true) and (fileexists(extractfilepath(application.ExeName)+'tests\'+inttostr(i)+'.out')=true) do inc(i);
spinedit2.Value:=i-1;
if spinedit2.Value>0 then begin
  button1.Enabled:=true;
  spinedit2.MinValue:=1;
  spinedit2.MaxValue:=spinedit2.Value;
end else begin
  button1.Enabled:=false;
  spinedit2.MaxValue:=1;
end;
end;

procedure KillProgram(ClassName: PChar; WindowTitle: PChar);
const PROCESS_TERMINATE = $0001;
var ProcessHandle:THandle; ProcessID:Integer; TheWindow:HWND;
begin
TheWindow:=FindWindow(Classname, WindowTitle);
GetWindowThreadProcessID(TheWindow, @ProcessID);
ProcessHandle:=OpenProcess(PROCESS_TERMINATE, FALSE, ProcessId);
TerminateProcess(ProcessHandle,4);
end;

procedure tform1.kill;
begin
Killprogram(nil,pchar(extractfilepath(application.exename)+'tests\current.exe'));
Sleep(100);
end;

procedure tform1.kill_checker;
begin
Killprogram(nil,pchar(extractfilepath(application.exename)+'tests\checker.exe'));
Sleep(100);
end;

function  GetMemUsage(PID:Integer):Integer;
var hProc:THandle; pps:TPROCESSMEMORYCOUNTERS;
begin
hProc:=OpenProcess(PROCESS_VM_READ or PROCESS_QUERY_INFORMATION, False, PID);
if hProc<>0 then begin
  FillChar(pps,Sizeof(pps),0);
  pps.cb:=Sizeof(pps);
  GetProcessMemoryInfo(hProc,@pps,Sizeof(pps));
  Result:=pps.WorkingSetSize;
  CloseHandle(hProc);
end else Result:=0;
end;

function tform1.checker_is_active:boolean;
var  Wnd:hWnd; windowtitle:pchar;
begin
windowtitle:=pchar(extractfilepath(application.exename)+'tests\checker.exe');
wnd:=FindWindow(nil, WindowTitle);
if wnd<>0 then checker_is_active:=true else checker_is_active:=false;
end;

function tform1.check_abc:boolean;
var  Wnd : hWnd; err:byte; windowtitle:pchar; procid:longint;
begin
err:=0;
windowtitle:=pchar(extractfilepath(application.exename)+'tests\current.exe');
wnd:=FindWindow(nil, WindowTitle);
if wnd<>0 then begin
  err:=1;
  GetWindowThreadProcessId(wnd, @ProcId);
  if ((getmemusage(procid)-1) div (1024*1024)+1)>spinedit3.Value then begin
    error:=5;
    timer2.Enabled:=false;
    timer1.Enabled:=false;
    timer1.Interval:=1;
    timer1.Enabled:=true;
  end;
end;
if err=0 then check_abc:=true else check_abc:=false;
end;

procedure tform1.check;
var  Wnd : hWnd;  windowtitle:pchar;
begin
windowtitle:=pchar(extractfilepath(application.exename)+'tests\current.exe');
wnd:=FindWindow(nil, WindowTitle);
if wnd<>0 then begin
  if error=0 then error:=3;
  kill;
end;
end;

procedure ExecConsoleApp(CommandLine: AnsiString; Output: TStringList; Errors: TStringList);
begin
sa.nLength:=sizeof(sa);
sa.bInheritHandle:=true;
sa.lpSecurityDescriptor:=nil;
CreatePipe(hPipeOutputRead,hPipeOutputWrite,@sa,0);
CreatePipe(hPipeErrorsRead,hPipeErrorsWrite,@sa,0);
ZeroMemory(@env,SizeOf(env));
ZeroMemory(@si,SizeOf(si));
ZeroMemory(@pi,SizeOf(pi));
si.cb:=SizeOf(si);
si.dwFlags:=(STARTF_USESHOWWINDOW) or (STARTF_USESTDHANDLES);
if form1.checkbox5.checked then si.wShowWindow:=SW_HIDE else si.wShowWindow:=SW_SHOW;
si.hStdInput:=0;
si.hStdOutput:=hPipeOutputWrite;
si.hStdError:=hPipeErrorsWrite;
Res:=CreateProcess(nil,pchar(CommandLine),nil,nil,true,(CREATE_NEW_CONSOLE) or (NORMAL_PRIORITY_CLASS),@env,nil,si,pi);
if not(Res) then begin
  CloseHandle(hPipeOutputRead);
  CloseHandle(hPipeOutputWrite);
  CloseHandle(hPipeErrorsRead);
  CloseHandle(hPipeErrorsWrite);
  Exit;
end;
CloseHandle(hPipeOutputWrite);
CloseHandle(hPipeErrorsWrite);
end;

procedure tform1.test(t:integer);
var k:integer; s:string; f,g:textfile;
begin
s:=extractfilepath(application.exename)+'tests\'+inttostr(t);
if (fileexists(s+'.in')=true) and (fileexists(s+'.out')=true) then begin
  if first=false then form1.label7.caption:='���� ������������... ���� #'+inttostr(t) else begin
    form1.label7.caption:='���������� � ������������...';
    first:=false;
  end;
  k:=filecreate(extractfilepath(application.exename)+'tests\'+form1.edit1.text);
  fileclose(k);
  s:=extractfilepath(application.exename)+'tests\'+inttostr(t)+'.in';
  assignfile(f,s);
  reset(f);
  assignfile(g,extractfilepath(application.exename)+'tests\'+form1.edit1.text);
  rewrite(g);
  while not eof(f) do begin
    readln(f,s);
    writeln(g,s);
  end;
  closefile(f);
  closefile(g);
  chdir(extractfilepath(application.exename)+'tests\');
  OutP := TStringList.Create;
  ErrorP := TstringList.Create;
  stderr.lines.clear;
  not_found:=false;
  error:=0;
  ExecConsoleApp('current.exe',OutP,ErrorP);
end else begin
  s:='���� ����� #'+inttostr(t)+' �� ������. ������������ �����������.';
  not_found:=true;
  numb:=99999;
  error:=1;
  Application.MessageBox(pchar(s),'������',mb_iconerror);
end;
end;

procedure TForm1.Label8MouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);begin
label8.font.style:=[fsBold,fsUnderline];
end;

procedure TForm1.Label8MouseLeave(Sender: TObject);
begin
label8.font.style:=[fsBold];
end;

procedure TForm1.Button1Click(Sender: TObject);
var s,st,r,e1,e2,chk:string; i,k,k1:integer; opStruc:TSHFileOpStruct; frombuf,tobuf:array[0..128] of Char; er:byte;
begin
e1:=edit1.text;
e2:=edit2.Text;
er:=0;
s:=ExtractFilePath(application.exename)+'tests\';
if (pos('.in',e1)=length(e1)-2) then begin
  val(copy(e1,1,length(e1)-3),k1,k);
  if k=0 then begin
    if (k1<=spinedit2.MaxValue) and (fileexists(extractfilepath(application.exename)+'tests\'+e1)) then inc(er);
  end;
end;
if (pos('.in',e2)=length(e2)-2) then begin
  val(copy(e2,1,length(e2)-3),k1,k);
  if k=0 then begin
    if (k1<=spinedit2.MaxValue) and (fileexists(extractfilepath(application.exename)+'tests\'+e2)) then inc(er);
  end;
end;
if (pos('.out',e1)=length(e1)-3) then begin
  val(copy(e1,1,length(e1)-4),k1,k);
  if k=0 then begin
    if (k1<=spinedit2.MaxValue) and (fileexists(extractfilepath(application.exename)+'tests\'+e1)) then inc(er);
  end;
end; 
if (pos('.out',e2)=length(e2)-3) then begin
  val(copy(e2,1,length(e2)-4),k1,k);
  if k=0 then begin
    if (k1<=spinedit2.MaxValue) and (fileexists(extractfilepath(application.exename)+'tests\'+e2)) then inc(er);
  end;
end;
if (er<>0) or (e1='checker.exe') or (e2='checker.exe') or (e1='current.exe') or (e2='current.exe') or (e1=e2) then begin
  s:='�������� ��� ��������/��������� �����!';
  Application.MessageBox(pchar(s),'������',mb_iconerror);
end else begin
wid:=0;
error:=0;
if od1.Execute then begin
  label5.caption:='';
  label7.Caption:='���������� � ������������...';
  GroupBox2.Visible:=true;
  GroupBox1.Visible:=false;
  form1.Repaint;
  if fileexists(ExtractFilePath(Application.ExeName)+'tests\current.exe') then deletefile(ExtractFilePath(Application.ExeName)+'tests\current.exe');
  if fileexists(ExtractFilePath(Application.ExeName)+'tests\checker.exe') then deletefile(ExtractFilePath(Application.ExeName)+'tests\checker.exe');
  if fileexists(ExtractFilePath(Application.ExeName)+'tests\'+edit1.text) then deletefile(ExtractFilePath(Application.ExeName)+'tests\'+edit1.Text);
  if fileexists(ExtractFilePath(Application.ExeName)+'tests\'+edit2.text) then deletefile(ExtractFilePath(Application.ExeName)+'tests\'+edit2.text);
  error:=0;
  st:=path.caption;
  s:=ExtractFilePath(Application.ExeName)+'tests\current.exe';
  rep:=extractfilepath(application.ExeName)+'reports\report';
  r:=datetostr(now);
  while pos('.',r)<>0 do delete(r,pos('.',r),1);
  rep:=rep+'_'+r;
  r:=timetostr(now);
  while pos(':',r)<>0 do delete(r,pos(':',r),1);
  rep:=rep+'_'+r+'.html';
  i:=filecreate(rep);
  fileclose(I);
  if checkbox3.Checked=true then begin
    acm_type:=0;
    acm_test:=0;
    deletefile(rep);
    i:=filecreate(rep);
    fileclose(i);
    report.lines:=memo3.lines;
    report.Lines.Strings[4]:=od1.FileName;
    report.lines.strings[2]:=timetostr(now);
    report.Lines.Strings[6]:=inttostr(spinedit1.Value)+' s';
    report.Lines.Strings[8]:=inttostr(spinedit3.Value)+' MB';
  end;
    FillChar(frombuf, Sizeof(frombuf), 0);
    FillChar(tobuf, Sizeof(tobuf), 0);
    StrPCopy(frombuf, od1.FileName);
    StrPCopy(tobuf, s);
    with OpStruc do begin
      Wnd:=Handle;
      wFunc:=FO_COPY;
      pFrom:=@frombuf;
      pTo:=@tobuf;
      fFlags:=FOF_NOCONFIRMATION or FOF_RENAMEONCOLLISION;
      fAnyOperationsAborted:=False;
      hNameMappings:=nil;
      lpszProgressTitle:=nil;
    end;
    ShFileOperation(OpStruc);
  if checkbox6.checked then begin
    chk:=ExtractFilePath(Application.ExeName)+'tests\checker.exe';
    FillChar(frombuf, Sizeof(frombuf), 0);
    FillChar(tobuf, Sizeof(tobuf), 0);
    StrPCopy(frombuf, chkr.caption);
    StrPCopy(tobuf, chk);
    with OpStruc do begin
      Wnd:=Handle;
      wFunc:=FO_COPY;
      pFrom:=@frombuf;
      pTo:=@tobuf;
      fFlags:=FOF_NOCONFIRMATION or FOF_RENAMEONCOLLISION;
      fAnyOperationsAborted:=False;
      hNameMappings:=nil;
      lpszProgressTitle:=nil;
    end;
    ShFileOperation(OpStruc);
  end;
  chdir(st);
  timer1.Interval:=SpinEdit1.Value*1000;
  time:=0;
  first:=true;
  test(1);
  sleep(timer1.Interval);
  check;
  timer1.Enabled:=true;
  test(1);
  if not_found=false then begin
    timer2.Enabled:=true;
    button5.enabled:=false;
    numb:=1;
  end;
end;
end;
end;

procedure TForm1.FormActivate(Sender: TObject);
var s:string;
begin
count_files;
GetDir(0,s);
s:=s+'\';
if DirectoryExists(extractfilepath(application.exename)+'tests\')=false then createdir(extractfilepath(application.exename)+'tests\');
if DirectoryExists(extractfilepath(application.exename)+'reports\')=false then createdir(extractfilepath(application.exename)+'reports\');
path.caption:=s;
end;

procedure TForm1.Button2Click(Sender: TObject);
var i,j:integer; s:string;
begin
if (memo1.lines.count=0) or (memo2.Lines.count=0) then Application.MessageBox('�������� ������ �������/�������� ������!','������',mb_iconstop) else begin
i:=1;
while (fileexists(extractfilepath(application.ExeName)+'tests\'+inttostr(i)+'.in')=true) and (fileexists(extractfilepath(application.ExeName)+'tests\'+inttostr(i)+'.out')=true) do inc(i);
s:=extractfilepath(application.exename)+'tests\'+inttostr(i)+'.in';
deletefile(s);
j:=filecreate(s);
fileclose(j);
memo1.Lines.SaveToFile(s);
s:=extractfilepath(application.exename)+'tests\'+inttostr(i)+'.out';
deletefile(s);
i:=filecreate(s);
fileclose(i);
memo2.Lines.SaveToFile(s);
memo1.Lines.Clear;
memo2.Lines.Clear;
button1.Enabled:=true;
memo1.SetFocus;
count_files;
end;
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
if timer1.Enabled=true then begin
  Application.MessageBox('� ������ ������ ��� ������������ ���������. ����� ����������.','������',MB_iconstop);
  action:=caNone;
end else
if (Application.MessageBox('����� �� ATester?','����� �� ���������',MB_YESNOCANCEL+mb_iconquestion)=idyes) then begin
end else
action:=canone;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
label check_existence;
var s,st,file_text,error_str:string; er,i,count,j,k,tim,got,show:integer; report_add:ansistring; F,g:textfile;
begin
timer1.Enabled:=false;
timer2.Enabled:=false;
file_text:='';
er:=0;
if error<>5 then error:=0;
st:=path.caption;
chdir(st);
check;
got:=0;
if (error=3) and (time<500) and (timer1.Interval=1) then error:=0;
if not_found=false then begin
Stream := TMemoryStream.Create;
try
  while true do begin
    bTest := ReadFile(hPipeOutputRead, szBuffer, 256, dwNumberOfBytesRead, nil);
    if not bTest then break;
    Stream.Write(szBuffer, dwNumberOfBytesRead);
  end;
  stream.Position := 0;
  Outp.LoadFromStream(Stream);
finally
  Stream.Free;
end;
Stream := TMemoryStream.Create;
try
  while true do begin
    bTest := ReadFile(hPipeErrorsRead, szBuffer, 256, dwNumberOfBytesRead, nil);
    if not bTest then break;
    Stream.Write(szBuffer, dwNumberOfBytesRead);
  end;
  Stream.Position := 0;
  Errorp.LoadFromStream(Stream);
finally
  Stream.Free;
end;
WaitForSingleObject(pi.hProcess, INFINITE);
CloseHandle(pi.hProcess);
CloseHandle(hPipeOutputRead);
CloseHandle(hPipeErrorsRead);
stderr.lines.assign(outp);
OutP.Free;
ErrorP.Free;
check_existence: begin
if fileexists(extractfilepath(application.exename)+'tests\'+edit2.text)=true then begin
  memo4.lines.LoadFromFile(extractfilepath(application.exename)+'tests\'+edit2.text);
  if error=3 then er:=3 else
  if error=5 then er:=5 else begin
  s:=extractfilepath(application.exename)+'tests\'+inttostr(numb)+'.out';
  memo5.Lines.loadfromfile(s);
  if memo5.Lines.count<>memo4.Lines.count then er:=1 else begin
  assignfile(f,s);
  reset(f);
  assignfile(g,extractfilepath(application.exename)+'tests\'+edit2.text);
  reset(g);
  while (not eof(f)) and (er=0) do begin
    readln(g,s);
    readln(f,st);
    if s<>st then inc(er);
  end;
  closefile(f);
  closefile(g);
  end;
  end;
end else er:=2;
end;
if (er=2) and (got=0) then begin
  sleep(50);
  if fileexists(extractfilepath(application.exename)+'tests\'+edit2.text) then begin
    er:=0;
    inc(got);
    goto check_existence;
  end;
end;
if stderr.lines.count>0 then begin
  if (pos('Runtime error ',stderr.lines.Strings[0])=1) and (pos(' at ',stderr.lines.Strings[0])<>0) then begin
    er:=4;
    error_str:=stderr.lines.Strings[0];
  end;
end;
if (er<2) and (checkbox6.checked) then begin
try
  if (not(fileexists(extractfilepath(application.ExeName)+'tests\checker.exe'))) or (not(fileexists(extractfilepath(application.ExeName)+'tests\'+inttostr(numb)+'.in'))) or (not(fileexists(extractfilepath(application.ExeName)+'tests\'+inttostr(numb)+'.out')))  then er:=5 else begin
    memo7.Lines.LoadFromFile(extractfilepath(application.ExeName)+'tests\'+edit2.text);
    if not(fileexists(extractfilepath(application.ExeName)+'tests\output.txt')) then begin
      k:=filecreate(extractfilepath(application.ExeName)+'tests\output.txt');
      fileclose(k);
    end;
    if not(fileexists(extractfilepath(application.ExeName)+'tests\test.in')) then begin
      k:=filecreate(extractfilepath(application.ExeName)+'tests\test.in');
      fileclose(k);
    end;
    if not(fileexists(extractfilepath(application.ExeName)+'tests\test.out')) then begin
      k:=filecreate(extractfilepath(application.ExeName)+'tests\test.out');
      fileclose(k);
    end;
    if not(fileexists(extractfilepath(application.ExeName)+'tests\check.log')) then begin
      k:=filecreate(extractfilepath(application.ExeName)+'tests\check.log');
      fileclose(k);
    end;
    memo7.Lines.SaveToFile(extractfilepath(application.ExeName)+'tests\output.txt');
    memo7.Lines.LoadFromFile(extractfilepath(application.ExeName)+'tests\'+inttostr(numb)+'.in');
    memo7.Lines.SaveToFile(extractfilepath(application.ExeName)+'tests\test.in');
    memo7.Lines.LoadFromFile(extractfilepath(application.ExeName)+'tests\'+inttostr(numb)+'.out');
    memo7.Lines.SaveToFile(extractfilepath(application.ExeName)+'tests\test.out');
    tim:=0;
    chdir(extractfilepath(application.exename)+'tests\');
    if checkbox5.Checked then show:=SW_HIDE else show:=sw_show;
    ShellExecute(random(1000), 'open', 'checker.exe', nil,nil,show);
    sleep(100);
    while (checker_is_active) and (tim<100) do begin
      sleep(100);
      inc(tim);
    end;
    if (tim>=100) then begin
      kill_checker;
      er:=6;
    end else
    if fileexists(extractfilepath(application.exename)+'tests\check.log')=false then er:=6 else begin
      memo7.Lines.LoadFromFile(extractfilepath(application.ExeName)+'tests\check.log');
      if UpperCase(memo7.lines.strings[0])='OK' then er:=0 else
      if UpperCase(memo7.lines.strings[0])='WA' then er:=1 else er:=6;
    end;
    if fileexists(extractfilepath(application.exename)+'tests\check.log') then DeleteFile(extractfilepath(application.exename)+'tests\check.log');
  end;
except
  er:=6;
end;
end;
if er=1 then begin
  label5.caption:=label5.caption+' '+'W';
  label13.Caption:='Wrong Answer';
  if acm_type=0 then begin
    acm_type:=1;
    acm_test:=numb;
  end;
end else
if er=2 then begin
  label5.caption:=label5.caption+' '+'O';
  label13.Caption:='No Output File';
  if acm_type=0 then begin
    acm_type:=2;
    acm_test:=numb;
  end;
end else
if er=3 then begin
  label5.caption:=label5.caption+' '+'T';
  label13.Caption:='Time Limit Excedeed';
  if acm_type=0 then begin
    acm_type:=3;
    acm_test:=numb;
  end;
end else
if er=4 then begin
  label5.caption:=label5.caption+' '+'R';
  label13.Caption:='Runtime Error';
  if acm_type=0 then begin
    acm_type:=4;
    acm_test:=numb;
  end;
end else
if er=5 then begin
  label5.caption:=label5.caption+' '+'M';
  label13.Caption:='Memory Limit Excedeed';
  if acm_type=0 then begin
    acm_type:=5;
    acm_test:=numb;
  end;
  error:=0;
end else
if er=6 then begin
  label5.caption:=label5.caption+' '+'C';
  label13.Caption:='Checker Error';
end;
if er=0 then begin
  label5.caption:=label5.caption+' '+'A';
  label13.Caption:='Accepted';
end;
label12.Visible:=true;
label13.Visible:=true;
if (er<>3) and (er<>4) and (er<>5) then begin
  if time=0 then time:=100;
  label17.Caption:=inttostr(time)+' ms';
end else label17.Caption:='0 ms';
if time>=spinedit1.Value*1000 then time:=-1;
label16.Visible:=true;
label17.Visible:=true;
if checkbox3.Checked=true then begin
  report_add:='<tr style="mso-yfti-irow:2"><td class="first"><p class="MsoNormal" align="center"><span class="second">'+inttostr(numb)+'<o:p></o:p></span></p></td><td class="first"><p class="MsoNormal" align="center"><span class="second">';
  if (er<>3) and (er<>5) then report_add:=report_add+inttostr(time)+' ms' else report_add:=report_add+'Killed';
  report_add:=report_add+'<o:p></o:p></span></p></td><td class="first"><p class="MsoNormal" align="center"><span class="second">';
  memo6.lines.loadfromfile(extractfilepath(application.exename)+'tests\'+inttostr(numb)+'.in');
  file_text:='';
  for i:=0 to memo6.lines.count-1 do file_text:=file_text+memo6.lines.strings[i]+'<br>';
  report_add:=report_add+file_text+'<o:p></o:p></span></p></td><td class="first"><p class="MsoNormal" align="center"><span class="second">';
  memo6.lines.loadfromfile(extractfilepath(application.exename)+'tests\'+inttostr(numb)+'.out');
  file_text:='';
  for i:=0 to memo6.lines.count-1 do file_text:=file_text+memo6.lines.strings[i]+'<br>';
  report_add:=report_add+file_text+'<o:p></o:p></span></p></td><td class="first"><p class="MsoNormal" align="center"><span class="second">';
  file_text:='';
  if (fileexists(extractfilepath(application.exename)+'tests\'+edit2.text)) and (er<>2) and (er<>3) then begin
    memo6.lines.loadfromfile(extractfilepath(application.exename)+'tests\'+edit2.text);
    for i:=0 to memo6.lines.count-1 do file_text:=file_text+memo6.lines.strings[i]+'<br>';
  end;
  if error_str<>'' then begin
    j:=1;
    while not(error_str[j] in ['0'..'9']) do inc(j);
    while error_str[j]<>' ' do inc(j);
    delete(error_str,j,length(error_str)-j+1);
  end;
  report_add:=report_add+file_text+'<o:p></o:p></span></p></td><td class="first"><p class="MsoNormal" align="center">';
  if label5.caption[length(label5.Caption)]='A' then file_text:='<span class="ok">OK' else
  if label5.caption[length(label5.Caption)]='W' then file_text:='<span class="bad">Wrong Answer' else
  if label5.caption[length(label5.Caption)]='T' then file_text:='<span class="bad">Time Limit Excedeed' else
  if label5.caption[length(label5.Caption)]='O' then file_text:='<span class="bad">No Output File' else
  if label5.caption[length(label5.Caption)]='C' then file_text:='<span class="bad">Checker Error' else
  if label5.caption[length(label5.Caption)]='M' then file_text:='<span class="bad">Memory Limit Excedeed' else
  if label5.caption[length(label5.caption)]='R' then file_text:='<span class="bad">'+error_str;
  report_add:=report_add+file_text+'<o:p></o:p></span></p></td></tr>';
  report.lines.Insert(report.lines.count-2,report_add);
end;
if canvas.TextWidth(label5.Caption)-wid*390>=390 then begin
  label5.Caption:=label5.Caption+#13;
  inc(wid);
end;
deletefile(extractfilepath(application.exename)+'tests\'+edit1.text);
deletefile(extractfilepath(application.exename)+'tests\'+edit2.text);
s:=extractfilepath(application.exename)+'tests\'+inttostr(numb)+'.in';
if CheckBox10.checked=true then deletefile(s);
s:=extractfilepath(application.exename)+'tests\'+inttostr(numb)+'.out';
if CheckBox10.checked=true then deletefile(s);
inc(numb);
end;
if (numb>spinedit2.Value) and (spinedit2.Value<>0) then  begin
  DeleteFile(extractfilepath(application.exename)+'tests\current.exe');
  if fileexists(extractfilepath(application.exename)+'tests\checker.exe') then DeleteFile(extractfilepath(application.exename)+'tests\checker.exe');
  if fileexists(extractfilepath(application.exename)+'tests\test.in') then DeleteFile(extractfilepath(application.exename)+'tests\test.in');
  if fileexists(extractfilepath(application.exename)+'tests\test.out') then DeleteFile(extractfilepath(application.exename)+'tests\test.out');
  if fileexists(extractfilepath(application.exename)+'tests\output.txt') then DeleteFile(extractfilepath(application.exename)+'tests\output.txt');
  label7.visible:=false;
  label3.Visible:=true;
  if error=1 then begin
    s:=label5.caption;
    delete(s,length(s),1);
    label5.Caption:=s;
  end;
  count:=0;
  for i:=1 to length(label5.caption) do if label5.caption[i]='A' then inc(count);
  label5.caption:=label5.Caption+' = '+inttostr(count);
  if checkbox3.Checked=true then begin
    report.Lines.Strings[10]:=inttostr(count);
    if (not_found=true) and (length(label5.caption)=4) then file_text:='Tests has not been found!' else
    if acm_type=0 then file_text:='Accepted!' else
    if acm_type=1 then file_text:='Wrong Answer (Test #'+inttostr(acm_test)+')' else
    if acm_type=2 then file_text:='No Output File (Test #'+inttostr(acm_test)+')' else
    if acm_type=3 then file_text:='Time Limit Excedeed (Test #'+inttostr(acm_test)+')' else
    if acm_type=4 then file_text:='Runtime Error (Test #'+inttostr(acm_test)+')' else
    if acm_type=5 then file_text:='Memory Limit Excedeed (Test #'+inttostr(acm_test)+')';
    report.lines.Strings[12]:=file_text;
    if checkbox6.Checked then report.Lines.Insert(9,'</b>&nbsp;&nbsp;&nbsp;Checker: <b>'+chkr.Caption);
    report.Lines.SaveToFile(rep);
  end;
  if checkbox3.checked then shellexecute(application.handle,'open',pChar(rep),NIL,NIL,SW_SHOWNORMAL);
  if checkbox4.checked then shellexecute(application.handle,'print',pchar(rep),nil,nil,SW_SHOWNORMAL);
  label5.Visible:=true;
  button3.Enabled:=true;
  label12.Visible:=false;
  label13.Visible:=false;
  label16.Visible:=false;
  label17.Visible:=false;
end else begin
  timer1.Interval:=spinedit1.Value*1000;
  time:=0;
  test(numb);
  timer1.enabled:=true;
  sleep(100);
  timer2.Enabled:=true;
end;
end;

procedure TForm1.SpinEdit1Change(Sender: TObject);
var n:integer;
begin
n:=SpinEdit1.Value;
if (n mod 10=1) and (n<>11) then label6.caption:='�������' else
if ((n mod 10=2) or (n mod 10=3) or (n mod 10=4)) and (n<>12) and (n<>13) and (n<>14) then label6.caption:='�������' else
label6.Caption:='������'
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
memo1.Lines.clear;
memo2.Lines.clear;
count_files;
checkbox6.Checked:=false;
od2.FileName:='';
chkr.Caption:='';
label20.Caption:='���� �� ������';
if spinedit2.value=0 then button1.Enabled:=false;
button3.Enabled:=false;
SpinEdit1.Value:=1;
timer1.Enabled:=false;
label5.Caption:='';
GroupBox1.Visible:=true;
GroupBox2.Visible:=false;
label7.Visible:=true;
label3.Visible:=false;
label5.Visible:=false;
RadioButton2.Checked:=true;
RadioButton1.Checked:=false;
memo1.Enabled:=true;
memo2.Enabled:=true;
button2.Enabled:=true;
label1.Enabled:=true;
label2.Enabled:=true;
label8.Enabled:=false;
spinedit2.Enabled:=false;
button5.enabled:=true;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
hlp.Show;
end;

procedure TForm1.FormResize(Sender: TObject);
begin
form1.Width:=440;
form1.Height:=563;
end;

procedure TForm1.RadioButton1Click(Sender: TObject);
begin
if RadioButton1.Checked=true then begin
  spinedit2.Enabled:=true;
  button1.Enabled:=true;
  label8.Enabled:=true;
  memo1.Enabled:=false;
  memo2.Enabled:=false;
  label1.Enabled:=false;
  label2.Enabled:=false;
  button2.Enabled:=false;
  if spinedit2.value=0 then button1.Enabled:=false;
end;
end;

procedure TForm1.RadioButton2Click(Sender: TObject);
begin
if RadioButton2.Checked=true then begin
  spinedit2.Enabled:=false;
  label8.Enabled:=false;
  memo1.Enabled:=true;
  memo2.Enabled:=true;
  label1.Enabled:=true;
  label2.Enabled:=true;
  button2.Enabled:=true;
  if spinedit2.value=0 then button1.Enabled:=false;
end;
end;

procedure TForm1.Label8Click(Sender: TObject);
begin
hlp1.show;
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
fmt.show;
end;

procedure TForm1.FormCreate(Sender: TObject);
var s,new:string;
begin
count_files;
if fileexists(extractfilepath(Application.ExeName)+'updater.exe') then deletefile(extractfilepath(Application.ExeName)+'updater.exe');
if fileexists(extractfilepath(Application.ExeName)+'updater.bat') then deletefile(extractfilepath(Application.ExeName)+'updater.bat');
if fileexists(extractfilepath(Application.ExeName)+'new.exe') then deletefile(extractfilepath(Application.ExeName)+'new.exe');
new_version:=version;
try
  new:=new_v+'version.txt';
  new_version:=IdHTTP1.Get(new);
  if new_version>version then begin
    timer3.enabled:=true;
  end;
except
end;
end;

procedure TForm1.Label14MouseEnter(Sender: TObject);
begin
label14.font.style:=[fsBold,fsUnderline];
end;

procedure TForm1.Label14MouseLeave(Sender: TObject);
begin
label14.font.style:=[fsBold];
end;

procedure TForm1.Label14Click(Sender: TObject);
begin
count_files;
end;

procedure TForm1.Label15MouseEnter(Sender: TObject);
begin
label15.font.style:=[fsBold,fsUnderline];
end;

procedure TForm1.Label15MouseLeave(Sender: TObject);
begin
label15.font.style:=[fsBold];
end;

procedure TForm1.Label15Click(Sender: TObject);
var i:integer; s:string; t:tcursor;
begin
count_files;
if application.MessageBox('�� �������, ��� ������ ������� ��� �����?','�������� ������', MB_ICONQUESTION+MB_YESNOCANCEL)=mryes then begin
t:=cursor;
cursor:=crHourGlass;
form1.Repaint;
for i:=1 to spinedit2.value do begin
  s:=extractfilepath(application.exename)+'tests\'+inttostr(i)+'.in';
  DeleteFile(s);
  s:=extractfilepath(application.exename)+'tests\'+inttostr(i)+'.out';
  DeleteFile(s);
end;
count_files;
cursor:=t;
end;
end;

procedure TForm1.Timer2Timer(Sender: TObject);
begin
inc(time,timer2.Interval);
if check_abc then begin
  timer2.Enabled:=false;
  timer1.Enabled:=false;
  timer1.Interval:=1;
  timer1.Enabled:=true;
end;
end;

procedure TForm1.CheckBox3Click(Sender: TObject);
begin
if checkbox3.Checked then checkbox4.Enabled:=true else begin
  checkbox4.Enabled:=false;
  checkbox4.Checked:=false;
end;
end;

procedure TForm1.CheckBox6Click(Sender: TObject);
begin
od2.FileName:='';
chkr.Caption:='';
label20.Caption:='���� �� ������';
if checkbox6.Checked then begin
  if od2.Execute then begin
    if od2.FileName<>'' then begin
      label20.caption:=MinimizeName(od2.FileName,form1.Canvas,217);
      chkr.caption:=od2.FileName;
    end else checkbox6.Checked:=false;
  end else checkbox6.Checked:=false;
end;
end;

procedure TForm1.Timer3Timer(Sender: TObject);
begin
timer3.Enabled:=false;
upd.label3.Caption:=version;
upd.Label5.Caption:=new_version;
upd.Show;
end;

end.