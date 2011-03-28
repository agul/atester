{$APPTYPE CONSOLE}
uses SysUtils;
var a,b:integer; i:longint;
begin
assign(input,'input.txt');
assign(output,'output.txt');
reset(input);
rewrite(output);
readln(a,b);
writeln(a+b);
close(input);
close(output);
end.
 