{$APPTYPE CONSOLE}

uses Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
     Dialogs, StdCtrls, ExtCtrls, FileCtrl, shellapi;

procedure KillProgram(ClassName: PChar; WindowTitle: PChar);
const PROCESS_TERMINATE = $0001;
var ProcessHandle:THandle; ProcessID:Integer; TheWindow:HWND;
begin
TheWindow:=FindWindow(Classname, WindowTitle);
GetWindowThreadProcessID(TheWindow, @ProcessID);
ProcessHandle:=OpenProcess(PROCESS_TERMINATE, FALSE, ProcessId);
TerminateProcess(ProcessHandle,4);
end;

procedure kill;
begin
Killprogram(nil,pchar(extractfilepath(application.exename)+'atester.exe'));
Sleep(100);
end;

begin
kill;
sleep(100);
deletefile(extractfilepath(application.ExeName)+'atester.exe');
renamefile(extractfilepath(application.ExeName)+'new.exe',extractfilepath(application.ExeName)+'atester.exe');
winexec('atester.exe',sw_show);
halt;
end.
 