{$APPTYPE CONSOLE}
uses SysUtils;
var a,b:integer;
begin
assign(input,'input.txt');
reset(input);
readln(a,b);
if a=1 then begin 
        assign(output,'output.txt');
        rewrite(output);
        sleep(2000);
end else
if a=2 then begin
        assign(output,'output.txt');
        rewrite(output);
        writeln(a-b);
end else
if a=3 then begin
        assign(output,'output.tx');
        rewrite(output);
        writeln(a+b);
end else
if a=5 then begin
        close(input);
        //assign(input,'inpu.txt');
        //reset(input);
        RunError(117);
end else begin
        assign(output,'output.txt');
        rewrite(output);
        writeln(a+b);
end;
end.
