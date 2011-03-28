{$APPTYPE CONSOLE}
uses  Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls,
      Buttons, ExtCtrls, Spin;

const config='formatter.xml';
      options=1;
      opt:array[1..options] of string=('config_help');

var count,mask:longint;
    ttype,filename,format,beginning,ending:string;
    success:boolean;
    option:array[0..255] of string;

procedure print_config_not_found;
begin
writeln('Configuration file "',config,'" was not found!');
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

procedure print_usage;
begin
writeln('1. Before formatting you should put files with tests to the directory "tests\", which should be located in the same directory as formatter and tester.');
writeln('2. Then you should make configuration file (for further information call formatter with "config_help" option).');
end;

function get_mask(n,mask:longint):string;
var i:longint;
begin
result:=inttostr(n);
if length(result)<mask then
  for i:=1 to mask-length(result) do result:='0'+result;
end;

procedure print_file_not_found(filename:string);
begin
writeln('File "',filename,'" was not found!');
end;

procedure print_formating_stopped;
begin
writeln('Formatting stopped!');
end;

procedure format_files(n:longint);
var i:longint; filename,test:string;
begin
for i:=1 to n do begin
  filename:=ExtractFilePath(Application.exename)+'tests\'+beginning+get_mask(i,mask)+ending+'.'+format;
  if fileexists(filename) then begin
    test:=ExtractFilePath(Application.exename)+'tests\'+inttostr(i)+'.';
    if ttype='INPUT' then test:=test+'in' else
    if ttype='OUTPUT' then test:=test+'out';
    renamefile(filename,test);
  end else begin
    print_file_not_found(filename);
    print_formating_stopped;
    break;
  end;
end;
if success then
  if count=1 then writeln('1 file has been formatted') else writeln(count,' files have been formatted');
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
writeln('COUNT - Number of tests to format');
writeln('TYPE - INPUT or OUTPUT');
writeln('BEGINNING - First common part in filename (before number)');
writeln('ENDING - Last common part in filename (after number)');
writeln('FORMAT - File extension (without dot, example: "txt", "in")');
writeln('MASK - Mask of number ("01" = 2; "1" = 1)');
end;

procedure get_options;
var i:longint;
begin
for i:=1 to options do
  option[i]:=paramstr(i);
end;

procedure parse;
var cfg:textfile; lines,k:longint; t,cur:string;
begin
assignfile(cfg,config);
reset(cfg);
count:=0;
mask:=0;
filename:='';
format:='';
beginning:='';
ending:='';
ttype:='';
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
    if (pos('<TYPE>',cur)=1) and (pos('</TYPE>',cur)=length(t)+1-length('</TYPE>')) then begin
      delete(t,length(t)+1-length('</TYPE>'),length('</TYPE>'));
      delete(t,1,length('<TYPE>'));
      t:=uppercase(t);
      if (t='INPUT') or (t='OUTPUT') then ttype:=t else success:=false;
    end else
    if (pos('<BEGINNING>',cur)=1) and (pos('</BEGINNING>',cur)=length(t)+1-length('</BEGINNING>')) then begin
      delete(t,length(t)+1-length('</BEGINNING>'),length('</BEGINNING>'));
      delete(t,1,length('<BEGINNING>'));
      beginning:=t;
    end else
    if (pos('<ENDING>',cur)=1) and (pos('</ENDING>',cur)=length(t)+1-length('</ENDING>')) then begin
      delete(t,length(t)+1-length('</ENDING>'),length('</ENDING>'));
      delete(t,1,length('<ENDING>'));
      ending:=t;
    end else
    if (pos('<FORMAT>',cur)=1) and (pos('</FORMAT>',cur)=length(t)+1-length('</FORMAT>')) then begin
      delete(t,length(t)+1-length('</FORMAT>'),length('</FORMAT>'));
      delete(t,1,length('<FORMAT>'));
      format:=t;
    end else
    if (pos('<MASK>',cur)=1) and (pos('</MASK>',cur)=length(t)+1-length('</MASK>')) then begin
      delete(t,length(t)+1-length('</MASK>'),length('</MASK>'));
      delete(t,1,length('<MASK>'));
      val(t,mask,k);
      if k<>0 then success:=false;
    end else success:=false;
  end;
end;
closefile(cfg);
if lines<>6 then success:=false;
end;

begin  
success:=true;
get_options;
check_options;
if (option[1]='config_help') and success then print_usage_config('HELP') else
if success then begin
  if DirectoryExists(extractfilepath(Application.ExeName)+'tests\') then begin
    if fileexists(config) then begin
      parse;
      if success then format_files(count) else print_usage_config('BAD');
    end else print_config_not_found;
  end else print_usage;
end else print_bad_option;
end.
 