{$APPTYPE CONSOLE}
uses SysUtils;
var test,outp,log:textfile; a,b:longint;
begin
assignfile(test,'test.out');
assignfile(outp,'output.txt');
assignfile(log,'check.log');
reset(test);
reset(outp);
rewrite(log);
readln(test,a);
readln(outp,b);
if a=b then writeln(log,'ok') else writeln(log,'wa');
closefile(test);
closefile(outp);
closefile(log);
end.
 