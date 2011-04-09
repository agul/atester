unit Unit1;

interface

uses  Windows, SysUtils, Variants, ExtCtrls, Classes, Controls, Forms,
      StdCtrls, FileCtrl, shellapi, psAPI;

const CheckerName='checker.exe';
      ProgramName='current.exe';
      CheckerLog='check.log';
      CheckerInput='test.in';
      CheckerOutput='test.out';
      ProgramOutput='output.txt';
      TesterLog='tester.log';

type
  TForm1 = class(TForm)
    Button1: TButton;
    path: TLabel;
    Memo3: TMemo;
    stderr: TMemo;  
    report: TMemo;
    Timer2: TTimer;
    Timer1: TTimer;
    Memo5: TMemo;
    Memo4: TMemo;
    Memo7: TMemo;
    label5: TLabel;
    Memo6: TMemo;
    procedure Button1Click(Sender: TObject);
    procedure testing(pf:string; c,t,m:longint; ch:string; r:boolean; i,o:string);
    procedure FormCreate(Sender: TObject);
    procedure test(t:longint);
    procedure ExecConsoleApp(CommandLine: AnsiString; Output: TStringList);
    procedure check;
    procedure kill;
    procedure kill_checker;
    procedure KillProgram(ClassName: PChar; WindowTitle: PChar);
    procedure Timer1Timer(Sender: TObject);
    function checker_is_active:boolean;
    procedure Timer2Timer(Sender: TObject);
    function GetMemUsage(PID:Integer):Integer;
    function check_abc:boolean;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var Form1: TForm1;
    count,TL,ML:longint;
    filename,input,output,checkerfilename:string;
    reportneed,success,Res, bTest:boolean;
    f,g:text;
    numb,error,wid,acm_test,acm_type:integer;
    get,rep,new_version,stdinput,stdoutput:string;
    time:int64;
    not_found,first,use_stdin,use_stdout:boolean;
    sa: TSECURITYATTRIBUTES;
    si: TSTARTUPINFO;
    pi: TPROCESSINFORMATION;
    hPipeOutputRead,hPipeOutputWrite,hPipeInputRead,hPipeInputWrite: THANDLE;
    env: array[0..100] of Char;
    szBuffer: array[0..256] of Char;
    dwNumberOfBytesRead: DWORD;
    Stream: TMemoryStream;
    OutP: TStringList;
    start,finish:tdatetime;
implementation

{$R *.dfm}

procedure tform1.testing(pf:string; c,t,m:longint; ch:string; r:boolean; i,o:string);
begin
filename:=pf;
count:=c;
TL:=t;
ML:=m;
checkerfilename:=ch;
reportneed:=r;
input:=i;
output:=o;
if input='' then use_stdin:=true else use_stdin:=false;
if output='' then use_stdout:=true else use_stdout:=false;
label5.Caption:='';
writeln('Testing...');
button1click(form1);
end;

function  tform1.GetMemUsage(PID:Integer):Integer;
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
windowtitle:=pchar(extractfilepath(application.exename)+'tests\'+checkername);
wnd:=FindWindow(nil, WindowTitle);
if wnd<>0 then result:=true else result:=false;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
label check_existence;
var s,st,file_text,error_str:string; re:cardinal; er,i,counter,k,tim,got,show:longint; report_add:ansistring; F,g:textfile;
begin
finish:=now;
time:=round((finish-start)*100000000);
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
WaitForSingleObject(pi.hProcess, tl div 1000);
GetExitCodeProcess(pi.hProcess,re);
CloseHandle(pi.hProcess);
CloseHandle(hPipeOutputRead); 
closehandle(hPipeInputRead);
stderr.lines.assign(outp);
OutP.Free;
stdoutput:=stderr.text;
check_existence: begin
if fileexists(extractfilepath(application.exename)+'tests\'+output) or use_stdout then begin
  if not use_stdout then memo4.lines.LoadFromFile(extractfilepath(application.exename)+'tests\'+output) else
    memo4.Lines:=stderr.Lines;
  if error=3 then er:=3 else
  if error=5 then er:=5 else begin
  s:=extractfilepath(application.exename)+'tests\'+inttostr(numb)+'.out';
  memo5.Lines.loadfromfile(s);
  if memo5.Lines.count<>memo4.Lines.count then er:=1 else begin
  assignfile(f,s);
  reset(f);
  if not use_stdout then assignfile(g,extractfilepath(application.exename)+'tests\'+output) else begin
    stderr.Lines.SaveToFile(extractfilepath(application.exename)+'tests\output.txt');
    assignfile(g,extractfilepath(application.exename)+'tests\output.txt');
  end;
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
  if fileexists(extractfilepath(application.exename)+'tests\'+output) then begin
    er:=0;
    inc(got);
    goto check_existence;
  end;
end;
if re<>0 then begin
  error_str:='Runtime error '+inttostr(re);
  er:=4;
end;
if (er<2) and (checkerfilename<>'') then begin
try
  if (not(fileexists(extractfilepath(application.ExeName)+'tests\checker.exe'))) or (not(fileexists(extractfilepath(application.ExeName)+'tests\'+inttostr(numb)+'.in'))) or (not(fileexists(extractfilepath(application.ExeName)+'tests\'+inttostr(numb)+'.out')))  then er:=5 else begin
    if not use_stdout then memo7.Lines.LoadFromFile(extractfilepath(application.ExeName)+'tests\'+output) else memo7.Lines:=stderr.Lines;
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
    show:=SW_HIDE;
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
  if acm_type=0 then begin
    acm_type:=1;
    acm_test:=numb;
  end;
end else
if er=2 then begin
  label5.caption:=label5.caption+' '+'O';
  if acm_type=0 then begin
    acm_type:=2;
    acm_test:=numb;
  end;
end else
if er=3 then begin
  label5.caption:=label5.caption+' '+'T';
  if acm_type=0 then begin
    acm_type:=3;
    acm_test:=numb;
  end;
end else
if er=4 then begin
  label5.caption:=label5.caption+' '+'R';
  if acm_type=0 then begin
    acm_type:=4;
    acm_test:=numb;
  end;
end else
if er=5 then begin
  label5.caption:=label5.caption+' '+'M';
  if acm_type=0 then begin
    acm_type:=5;
    acm_test:=numb;
  end;
  error:=0;
end else
if er=6 then begin
  label5.caption:=label5.caption+' '+'C';
end;
if er=0 then begin
  label5.caption:=label5.caption+' '+'A';
end;
if (er<>3) and (er<>4) and (er<>5) then begin
  if time=0 then time:=100;
end;
if time>=TL*1000 then time:=-1;
if reportneed then begin
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
  if (fileexists(extractfilepath(application.exename)+'tests\'+output) or use_stdout) and (er<>2) and (er<>3) then begin
    if use_stdout then memo6.lines:=stderr.lines else memo6.lines.loadfromfile(extractfilepath(application.exename)+'tests\'+output);
    for i:=0 to memo6.lines.count-1 do file_text:=file_text+memo6.lines.strings[i]+'<br>';
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
if not use_stdin then deletefile(extractfilepath(application.exename)+'tests\'+input);
if not use_stdout then deletefile(extractfilepath(application.exename)+'tests\'+output);
inc(numb);
end;
if (numb>count) and (count<>0) then  begin
  DeleteFile(extractfilepath(application.exename)+'tests\'+programname);
  if fileexists(extractfilepath(application.exename)+'tests\'+checkername) then DeleteFile(extractfilepath(application.exename)+'tests\'+checkername);
  if fileexists(extractfilepath(application.exename)+'tests\'+CheckerInput) then DeleteFile(extractfilepath(application.exename)+'tests\'+CheckerInput);
  if fileexists(extractfilepath(application.exename)+'tests\'+checkeroutput) then DeleteFile(extractfilepath(application.exename)+'tests\'+CheckerOutput);
  if fileexists(extractfilepath(application.exename)+'tests\'+ProgramOutput) then DeleteFile(extractfilepath(application.exename)+'tests\'+ProgramOutput);
  if error=1 then begin
    s:=label5.caption;
    delete(s,length(s),1);
    label5.Caption:=s;
  end;
  counter:=0;
  for i:=1 to length(label5.caption) do if label5.caption[i]='A' then inc(counter);
  label5.caption:=label5.Caption+' = '+inttostr(counter);
  if reportneed then begin
    report.Lines.Strings[10]:=inttostr(counter);
    if (not_found=true) and (length(label5.caption)=4) then file_text:='Tests has not been found!' else
    if acm_type=0 then file_text:='Accepted!' else
    if acm_type=1 then file_text:='Wrong Answer (Test #'+inttostr(acm_test)+')' else
    if acm_type=2 then file_text:='No Output File (Test #'+inttostr(acm_test)+')' else
    if acm_type=3 then file_text:='Time Limit Excedeed (Test #'+inttostr(acm_test)+')' else
    if acm_type=4 then file_text:='Runtime Error (Test #'+inttostr(acm_test)+')' else
    if acm_type=5 then file_text:='Memory Limit Excedeed (Test #'+inttostr(acm_test)+')';
    report.lines.Strings[12]:=file_text;
    if checkerfilename<>'' then report.Lines.Insert(9,'</b>&nbsp;&nbsp;&nbsp;Checker: <b>'+checkerfilename);
    report.Lines.SaveToFile(rep);
  end;
  i:=1;
  s:=label5.Caption;
  while i<=length(s) do
    if s[i] in ['A'..'Z'] then inc(i) else delete(s,i,1);
  assignfile(f,extractfilepath(application.exename)+TesterLog);
  rewrite(f);
  writeln(f,s);
  closefile(f);
  writeln('Testing completed.');
  if reportneed then begin
    writeln('Report:');
    writeln(rep);
  end;
  form1.Close;
end else begin
  timer1.Interval:=TL*1000;
  time:=0;
  test(numb);
  timer1.enabled:=true;
  sleep(100);
  timer2.Enabled:=true;
end;
end;

procedure tform1.ExecConsoleApp(CommandLine: AnsiString; Output: TStringList);
var Buf:array[0..1024] of byte; i:dword;
begin
sa.nLength:=sizeof(sa);
sa.bInheritHandle:=true;
sa.lpSecurityDescriptor:=nil;
CreatePipe(hPipeOutputRead,hPipeOutputWrite,@sa,0);
CreatePipe(hPipeInputRead,hPipeInputWrite,@sa,0);
ZeroMemory(@env,SizeOf(env));
ZeroMemory(@si,SizeOf(si));
ZeroMemory(@pi,SizeOf(pi));
si.cb:=SizeOf(si);
si.dwFlags:=(STARTF_USESHOWWINDOW) or (STARTF_USESTDHANDLES);
si.wShowWindow:=SW_HIDE;
if use_stdin then begin
  StrPCopy(@Buf[0],stdInput+^Z);
  WriteFile(hPipeInputWrite,Buf,Length(stdInput),i,nil);
end;
si.hStdInput:=hPipeInputRead;
si.hStdOutput:=hPipeOutputWrite;
si.hStdError:=hPipeOutputWrite;
CloseHandle(hPipeInputWrite);
Res:=CreateProcess(nil,pchar(CommandLine),nil,nil,true,(CREATE_NEW_CONSOLE) or (NORMAL_PRIORITY_CLASS),@env,nil,si,pi);
start:=now;
if first then begin
  closehandle(hPipeInputRead);
  CloseHandle(hPipeOutputRead);
end;
if not(Res) then begin
  CloseHandle(hPipeOutputRead);
  CloseHandle(hPipeOutputWrite);
  Exit;
end;  
CloseHandle(hPipeOutputWrite);
end;

procedure tform1.test(t:longint);
var k:longint; s:string; f,g:textfile;
begin
s:=extractfilepath(application.exename)+'tests\'+inttostr(t);
if fileexists(s+'.in') and fileexists(s+'.out') then begin
  
  s:=extractfilepath(application.exename)+'tests\'+inttostr(t)+'.in';
  assignfile(f,s); 
  reset(f);
  if not use_stdin then begin
    k:=filecreate(extractfilepath(application.exename)+'tests\'+input);
    fileclose(k);
    assignfile(g,extractfilepath(application.exename)+'tests\'+input);
    rewrite(g);
    while not eof(f) do begin
      readln(f,s);
      writeln(g,s);
    end;
    closefile(g);
  end else begin
    stdinput:='';
    while not eof(f) do begin
      readln(f,s);
      stdinput:=stdinput+s+#10#13;
    end;
  end;
  closefile(f);
  chdir(extractfilepath(application.exename)+'tests\');
  OutP := TStringList.Create;
  stderr.lines.clear;
  not_found:=false;
  error:=0;
  ExecConsoleApp('current.exe',OutP);
end else begin
  writeln('File of test #',t,' was not found. Testing stopped.');
  not_found:=true;
  numb:=99999;
  error:=1;
end;
end;

procedure tform1.KillProgram(ClassName: PChar; WindowTitle: PChar);
const PROCESS_TERMINATE = $0001;
var ProcessHandle:THandle; ProcessID:Integer; TheWindow:HWND;
begin
TheWindow:=FindWindow(Classname, WindowTitle);
GetWindowThreadProcessID(TheWindow, @ProcessID);
ProcessHandle:=OpenProcess(PROCESS_TERMINATE, FALSE, ProcessId);
TerminateProcess(ProcessHandle,4);
end;

function tform1.check_abc:boolean;
var  Wnd : hWnd; err:byte; windowtitle:pchar; procid:longint;
begin
err:=0;
windowtitle:=pchar(extractfilepath(application.exename)+'tests\'+ProgramName);
wnd:=FindWindow(nil, WindowTitle);
if wnd<>0 then begin
  err:=1;
  GetWindowThreadProcessId(wnd, @ProcId);
  if ((getmemusage(procid)-1) div (1024*1024)+1)>ML then begin
    error:=5;
    timer2.Enabled:=false;
    timer1.Enabled:=false;
    timer1.Interval:=1;
    timer1.Enabled:=true;
  end;
end;
if err=0 then result:=true else result:=false;
end;

procedure tform1.kill;
begin
Killprogram(nil,pchar(extractfilepath(application.exename)+'tests\'+programname));
Sleep(100);
end;

procedure tform1.kill_checker;
begin
Killprogram(nil,pchar(extractfilepath(application.exename)+'tests\'+checkername));
Sleep(100);
end;

procedure tform1.check;
var  Wnd:hWnd;  windowtitle:pchar;
begin
windowtitle:=pchar(extractfilepath(application.exename)+'tests\'+programname);
wnd:=FindWindow(nil, WindowTitle);
if wnd<>0 then begin
  if error=0 then error:=3;
  kill;
end;
end;

procedure TForm1.Button1Click(Sender: TObject);
var s,st,r,chk:string; i:integer; opStruc:TSHFileOpStruct; frombuf,tobuf:array[0..128] of Char;
begin
if fileexists(ExtractFilePath(Application.ExeName)+'tests\'+ProgramName) then deletefile(ExtractFilePath(Application.ExeName)+'tests\'+programname);
if fileexists(ExtractFilePath(Application.ExeName)+'tests\'+CheckerName) then deletefile(ExtractFilePath(Application.ExeName)+'tests\'+checkername);
if not use_stdin then
  if fileexists(ExtractFilePath(Application.ExeName)+'tests\'+input) then deletefile(ExtractFilePath(Application.ExeName)+'tests\'+input);
if not use_stdout then
  if fileexists(ExtractFilePath(Application.ExeName)+'tests\'+output) then deletefile(ExtractFilePath(Application.ExeName)+'tests\'+output);
error:=0;
st:=path.caption;
s:=ExtractFilePath(Application.ExeName)+'tests\'+programname;
if reportneed then begin
  rep:=extractfilepath(application.ExeName)+'reports\report';
  r:=datetostr(now);
  while pos('.',r)<>0 do delete(r,pos('.',r),1);
  rep:=rep+'_'+r;
  r:=timetostr(now);
  while pos(':',r)<>0 do delete(r,pos(':',r),1);
  rep:=rep+'_'+r+'.html';
  i:=filecreate(rep);
  fileclose(I);
  acm_type:=0;
  acm_test:=0;
  deletefile(rep);
  i:=filecreate(rep);
  fileclose(i);
  report.lines:=memo3.lines;
  report.Lines.Strings[4]:=filename;
  report.lines.strings[2]:=timetostr(now);
  report.Lines.Strings[6]:=inttostr(TL)+' s';
  report.Lines.Strings[8]:=inttostr(ML)+' MB';
end;
FillChar(frombuf, Sizeof(frombuf), 0);
FillChar(tobuf, Sizeof(tobuf), 0);
StrPCopy(frombuf, filename);
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
if checkerfilename<>'' then begin
  chk:=ExtractFilePath(Application.ExeName)+'tests\'+checkername;
  FillChar(frombuf, Sizeof(frombuf), 0);
  FillChar(tobuf, Sizeof(tobuf), 0);
  StrPCopy(frombuf, checkerfilename);
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
timer1.Interval:=TL*1000;
time:=0;
if not use_stdout then begin
  first:=true;
  test(1);
  sleep(timer1.Interval);
  check;
end;
timer1.Enabled:=true;
test(1);
if not_found=false then begin
  timer2.Enabled:=true;
  numb:=1;
end;
end;

procedure TForm1.FormCreate(Sender: TObject);
var s:string;
begin   
GetDir(0,s);
s:=s+'\';
if DirectoryExists(extractfilepath(application.exename)+'tests\')=false then createdir(extractfilepath(application.exename)+'tests\');
if DirectoryExists(extractfilepath(application.exename)+'reports\')=false then createdir(extractfilepath(application.exename)+'reports\');
path.caption:=s;
form1.Width:=0;
form1.Height:=0;
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

end.
