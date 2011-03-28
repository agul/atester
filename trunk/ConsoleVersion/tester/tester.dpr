program tester;
{$APPTYPE CONSOLE}
uses  Windows, SysUtils, Forms, Controls, StdCtrls, ExtCtrls,
      Unit1 in 'Unit1.pas' {Form1};

{$R *.res}

const config='tester.xml';
      options=1;
      opt:array[1..options] of string=('config_help');

var count,TL,ML:longint;
    filename,input,output,checker:string;
    report,success:boolean;
    option:array[0..255] of string;

procedure print_file_not_found(filename:string);
begin
writeln('File "',filename,'" was not found. Testing stopped.');
end;

function count_files:longint;
var i:longint;
begin
i:=1;
while fileexists(extractfilepath(application.ExeName)+'tests\'+inttostr(i)+'.in') and fileexists(extractfilepath(application.ExeName)+'tests\'+inttostr(i)+'.out') do inc(i);
result:=i;
end;

procedure get_options;
var i:longint;
begin
for i:=1 to options do
  option[i]:=paramstr(i);
end;

procedure check_options;
var i,j,k:longint;
begin
for i:=1 to options do begin
  k:=0;
  for j:=1 to options do
    if (option[i]=opt[j]) or (option[i]='') then begin
      inc(k);
      break;
    end;
  if k=0 then success:=false;
end;
end;

procedure print_bad_option;
begin
writeln('Unknown option!');
end;

procedure print_usage_config(s:string);
begin
if s='BAD' then writeln('Incorrect configuration file!');
writeln('Configuration file usage:');
writeln('<KEY>VALUE</KEY>');
writeln;
writeln('Available keys:');
writeln('PROGRAM - Filename of program to test');
writeln('COUNT - Number of tests to format');
writeln('TIMELIMIT - Timelimit');
writeln('MEMORYLIMIT - Memorylimit');
writeln('CHECKER - Checker filename');
writeln('REPORT - 1 (if need for generating report), 0 (if not need for generating report)');
writeln('INPUT - Input filename');
writeln('OUTPUT - Output filename');
end;

procedure parse;
var cfg:textfile; lines,k,i,k1:longint; t,cur:string;
begin
assignfile(cfg,config);
reset(cfg);
count:=0;
filename:='';
input:='';
output:='';
checker:='';
report:=false;
TL:=2;
ML:=256;
lines:=0;
while not eof(cfg) do begin
  readln(cfg,t);
  cur:=uppercase(t);
  if t<>'' then begin
    inc(lines);
    if (pos('<COUNT>',cur)=1) and (pos('</COUNT>',cur)=length(t)+1-length('</COUNT>')) then begin
      delete(t,length(t)+1-length('</COUNT>'),length('</COUNT>'));
      delete(t,1,length('<COUNT>'));
      Val(t,count,k);
      if k<>0 then success:=false;
    end else
    if (pos('<PROGRAM>',cur)=1) and (pos('</PROGRAM>',cur)=length(t)+1-length('</PROGRAM>')) then begin
      delete(t,length(t)+1-length('</PROGRAM>'),length('</PROGRAM>'));
      delete(t,1,length('<PROGRAM>'));
      filename:=t;
    end else
    if (pos('<TIMELIMIT>',cur)=1) and (pos('</TIMELIMIT>',cur)=length(t)+1-length('</TIMELIMIT>')) then begin
      delete(t,length(t)+1-length('</TIMELIMIT>'),length('</TIMELIMIT>'));
      delete(t,1,length('<TIMELIMIT>'));
      Val(t,TL,k);
      if k<>0 then success:=false;
    end else
    if (pos('<MEMORYLIMIT>',cur)=1) and (pos('</MEMORYLIMIT>',cur)=length(t)+1-length('</MEMORYLIMIT>')) then begin
      delete(t,length(t)+1-length('</MEMORYLIMIT>'),length('</MEMORYLIMIT>'));
      delete(t,1,length('<MEMORYLIMIT>'));
      Val(t,ML,k);
      if k<>0 then success:=false;
    end else
    if (pos('<CHECKER>',cur)=1) and (pos('</CHECKER>',cur)=length(t)+1-length('</CHECKER>')) then begin
      delete(t,length(t)+1-length('</CHECKER>'),length('</CHECKER>'));
      delete(t,1,length('<CHECKER>'));
      checker:=t;
    end else
    if (pos('<REPORT>',cur)=1) and (pos('</REPORT>',cur)=length(t)+1-length('</REPORT>')) then begin
      delete(t,length(t)+1-length('</REPORT>'),length('</REPORT>'));
      delete(t,1,length('<REPORT>'));
      Val(t,i,k);
      if (k=0) and (i=0) then report:=false else
      if (k=0) and (i=1) then report:=true else success:=false;
    end else
    if (pos('<INPUT>',cur)=1) and (pos('</INPUT>',cur)=length(t)+1-length('</INPUT>')) then begin
      delete(t,length(t)+1-length('</INPUT>'),length('</INPUT>'));
      delete(t,1,length('<INPUT>'));
      input:=t;
    end else
    if (pos('<OUTPUT>',cur)=1) and (pos('</OUTPUT>',cur)=length(t)+1-length('</OUTPUT>')) then begin
      delete(t,length(t)+1-length('</OUTPUT>'),length('</OUTPUT>'));
      delete(t,1,length('<OUTPUT>'));
      output:=t;
    end else success:=false;
  end;
end;
closefile(cfg);
if  (lines<>8) or (input='') or (output='') or (input=CheckerName) or (output=CheckerName) or
    (input=output) or (input=ProgramName) or (output=ProgramName) or (TL<1) or (TL>60) or
    (ML<1) or (ML>1024) or (count_files<count) or ((checker<>'') and (fileexists(checker)=false)) then success:=false;
if (pos('.in',input)=length(input)-2) then begin
  val(copy(input,1,length(input)-3),k1,k);
  if k=0 then begin
    if (k1<=count) and (fileexists(extractfilepath(application.exename)+'tests\'+input)) then success:=false;
  end;
end;
if (pos('.in',output)=length(output)-2) then begin
  val(copy(output,1,length(output)-3),k1,k);
  if k=0 then begin
    if (k1<=count) and (fileexists(extractfilepath(application.exename)+'tests\'+output)) then success:=false;
  end;
end;
if (pos('.out',input)=length(input)-3) then begin
  val(copy(input,1,length(input)-4),k1,k);
  if k=0 then begin
    if (k1<=count) and (fileexists(extractfilepath(application.exename)+'tests\'+input)) then success:=false;
  end;
end; 
if (pos('.out',output)=length(output)-3) then begin
  val(copy(output,1,length(output)-4),k1,k);
  if k=0 then begin
    if (k1<=count) and (fileexists(extractfilepath(application.exename)+'tests\'+output)) then success:=false;
  end;
end;
end;

procedure print_usage;
begin
writeln('1. Before testing you should put files with tests to the directory "tests\", which should be located in the same directory as tester.');
writeln('2. Then you should make configuration file (for further information call formatter with "config_help" option).');
end;

procedure print_config_not_found;
begin
writeln('Configuration file "',config,'" was not found!');
end;

begin
Application.Initialize;
Application.CreateForm(TForm1, Form1);
success:=true;
get_options;
check_options;
if (option[1]='config_help') and success then print_usage_config('HELP') else
if success then begin
  if DirectoryExists(extractfilepath(Application.ExeName)+'tests\') then begin
    if fileexists(config) then begin
      parse;
      if success then begin
        if fileexists(filename) then begin
          form1.testing(filename,count,TL,ML,checker,report,input,output);
          Application.ShowMainForm:=false;
          application.Run;    
        end else print_file_not_found(filename);
      end else print_usage_config('BAD');
    end else print_config_not_found;
  end else print_usage;
end else print_bad_option;
end.