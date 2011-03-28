program Project1;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  Unit2 in 'Unit2.pas' {hlp},
  Unit3 in 'Unit3.pas' {hlp1},
  Unit4 in 'Unit4.pas' {fmt},
  Unit5 in 'Unit5.pas' {fmth},
  Unit6 in 'Unit6.pas' {upd},
  Unit7 in 'Unit7.pas' {splash};

{$R *.res}

begin
  Application.Initialize;
    splash:=Tsplash.Create(Application);
    splash.Show;
    splash.Update;
  Application.CreateForm(TForm1, Form1); 
  Application.CreateForm(Tupd, upd);
  Application.CreateForm(Thlp, hlp);
  Application.CreateForm(Thlp1, hlp1);
  Application.CreateForm(Tfmt, fmt);
  Application.CreateForm(Tfmth, fmth);
    splash.close;
    splash.Free;
  Application.Title := 'ATester';
  Application.Run;
end.
