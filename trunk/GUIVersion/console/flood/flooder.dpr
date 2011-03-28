{$APPTYPE CONSOLE}
uses  Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls,
      Buttons, ExtCtrls, Spin;

var i,a,b,k:longint; s:string; t:textfile;
begin
randomize;
for i:=1 to 10 do begin
  s:=extractfilepath(Application.ExeName)+'tests\inp'+inttostr(i)+'.txt';
  k:=filecreate(s);
  fileclose(k);
  a:=random(1000);
  b:=random(1000);
  assignfile(t,s);
  rewrite(t);
  writeln(t,a,' ',b);
  close(t);
  s:=extractfilepath(Application.ExeName)+'tests\ans'+inttostr(i)+'.txt';
  assignfile(t,s);
  rewrite(t);
  writeln(t,a+b);
  close(t);
end;
end.
 