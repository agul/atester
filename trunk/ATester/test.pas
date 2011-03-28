unit test;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Memo1: TMemo;
    Memo2: TMemo;
    Edit1: TEdit;
    procedure Button1Click(Sender: TObject);
    procedure Edit1KeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}
function mask(a,b:integer):string;
var s:string; i:integer;
begin
s:=inttostr(a);
if length(s)<b then for i:=1 to b-length(s) do s:='0'+s;
mask:=s;
end;
procedure TForm1.Button1Click(Sender: TObject);
var i,j:integer;  f:textfile; a,b:integer;
begin
randomize;
for i:=1 to strtoint(edit1.text) do begin
  j:=FileCreate('tests/'+mask(i,1)+'.in');
  fileclose(j);
  assignfile(f,'tests/'+mask(i,1)+'.in');
  rewrite(f);
  a:=random(10000);
  b:=random(10000);
  writeln(f,a,' ',b);
  closefile(f);
  j:=FileCreate('tests/'+mask(i,1)+'.out');
  fileclose(j);
  assignfile(f,'tests/'+mask(i,1)+'.out');
  rewrite(f);
  writeln(f,a+b);
  closefile(f);
end;
end;

procedure TForm1.Edit1KeyPress(Sender: TObject; var Key: Char);
begin
if key=#13 then button1.click;
end;

end.
