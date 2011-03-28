object Form1: TForm1
  Left = 256
  Top = 206
  BorderStyle = bsNone
  Caption = 'Form1'
  ClientHeight = 381
  ClientWidth = 716
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object path: TLabel
    Left = 192
    Top = 32
    Width = 21
    Height = 13
    Caption = 'path'
  end
  object label5: TLabel
    Left = 224
    Top = 32
    Width = 3
    Height = 13
  end
  object Button1: TButton
    Left = 256
    Top = 0
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Memo3: TMemo
    Left = 0
    Top = 185
    Width = 185
    Height = 89
    Lines.Strings = (
      
        '<html xmlns:v="urn:schemas-microsoft-com:vml" xmlns:o="urn:schem' +
        'as-microsoft-com:office:office" xmlns:w="urn:schemas-microsoft-c' +
        'om:office:word" xmlns:m="http://schemas.microsoft.com/office/200' +
        '4/12/omml" xmlns="http://www.w3.org/TR/REC-html40"><head id="ctl' +
        '00_Head1"><title>'#1054#1090#1095#1077#1090' '#1086' '#1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1080'</title><style>.first {bord' +
        'er: solid #999999 1.0pt;mso-border-alt:solid #999999 .75pt;backg' +
        'round:white;padding:4.2pt 4.2pt 4.2pt 4.2pt;} .second {font-size' +
        ':9.5pt;font-family:Segoe UI,sans-serif;mso-fareast-font-family:T' +
        'imes New Roman;color:dimgray} .ok{font-size:9.5pt;font-family:Se' +
        'goe UI, sans-serif;mso-fareast-font-family: Times New Roman;colo' +
        'r:green} .bad{font-size:9.5pt;font-family:Segoe UI, sans-serif;m' +
        'so-fareast-font-family: Times New Roman;color:red} .third {font-' +
        'size:9.5pt;font-family:Segoe UI,sans-serif;mso-fareast-font-fami' +
        'ly:Times New Roman;color:dimgray} '
      
        '.forth {border:solid #999999 1.0pt;mso-border-alt:solid #999999 ' +
        '.75pt; background:#E8EEF4; padding:5.0pt 4.2pt 5.0pt 4.2pt}</sty' +
        'le></head><body bgcolor="#B6B7BC" link="#034AF3" vlink="#034AF3"' +
        ' style="tab-interval:35.4pt"><div class="Section1"><div style="m' +
        'argin-left:6.7pt;margin-top:10.05pt;margin-right:6.7pt;margin-bo' +
        'ttom: 6.7pt" id="main"><table class="MsoNormalTable" border="1" ' +
        'cellpadding="0" width="98%" style="width:98.78%;mso-cellspacing:' +
        '1.5pt;margin-left:4.9pt;border:solid #999999 1.5pt; mso-yfti-tbl' +
        'look:1184"><thead><tr style="mso-yfti-irow:0;mso-yfti-firstrow:y' +
        'es"><td colspan="16" style="border:none;background:#E8EEF4;paddi' +
        'ng:5.0pt 4.2pt 5.0pt 4.2pt"><p class="MsoNormal" align="center" ' +
        'style="text-align:center"><span style="font-size:12.0pt;font-fam' +
        'ily:&quot;Segoe UI&quot;,&quot;sans-serif&quot;;mso-fareast-font' +
        '-family: &quot;Times New Roman&quot;;color:dimgray">'#1042#1088#1077#1084#1103': <b>'
      '%time%'
      '</b>&nbsp;&nbsp;&nbsp;'#1060#1072#1081#1083': <b>'
      '%filename%'
      '</b>&nbsp;&nbsp;&nbsp;'#1051#1080#1084#1080#1090' '#1074#1088#1077#1084#1077#1085#1080': <b>'
      '%time_limit%'
      '</b>&nbsp;&nbsp;&nbsp;'#1051#1080#1084#1080#1090' '#1087#1072#1084#1103#1090#1080': <b>'
      '%memory_limit%'
      '</b>&nbsp;&nbsp;&nbsp;School Result: <b>'
      '%School_result%'
      '</b>&nbsp;&nbsp;&nbsp;ACM Result: <b>'
      '%acm_result%'
      
        '</b></span><span class="third"><o:p></o:p></span></p></td></tr><' +
        'tr style="mso-yfti-irow:1"><td class="forth" style="width:10%"><' +
        'p class="MsoNormal" align="center" ><b><span class="third">'#8470'<o:p' +
        '></o:p></span></b></p></td><td class="forth" style="width:20%"><' +
        'p class="MsoNormal" align="center"><b><span class="third">'#1042#1088#1077#1084#1103' ' +
        #1074#1099#1087#1086#1083#1085#1077#1085#1080#1103'</span></b></p></td><td style="width:20%" class="forth' +
        '"><p class="MsoNormal" align="center" ><b><span class="third"><a' +
        'bbr>'#1042#1093#1086#1076#1085#1099#1077' '#1076#1072#1085#1085#1099#1077'</abbr><o:p></o:p></span></b></p></td><td styl' +
        'e="width:20%" class="forth"><p class="MsoNormal" align="center">' +
        '<b><span class="third"><abbr>'#1042#1099#1093#1086#1076#1085#1099#1077' '#1076#1072#1085#1085#1099#1077'</abbr><o:p></o:p></' +
        'span></b></p></td><td style="width:20%" class="forth"><p class="' +
        'MsoNormal" align="center"><b><span class="third"><abbr>'#1054#1090#1074#1077#1090' '#1087#1088#1086 +
        #1075#1088#1072#1084#1084#1099'</abbr><o:p></o:p></span></b></p></td><td style="width:10%' +
        '" class="forth"><p class="MsoNormal" align="center"><b><span cla' +
        'ss="third"><abbr>'#1057#1090#1072#1090#1091#1089'</abbr><o:p></o:p></span></b></p></td></t' +
        'r></thead><tbody>'
      ''
      '</tbody></table></div></div></body></html>')
    ScrollBars = ssBoth
    TabOrder = 1
    Visible = False
  end
  object stderr: TMemo
    Left = 0
    Top = 1
    Width = 185
    Height = 89
    ScrollBars = ssBoth
    TabOrder = 2
    Visible = False
  end
  object report: TMemo
    Left = 0
    Top = 97
    Width = 185
    Height = 89
    ScrollBars = ssBoth
    TabOrder = 3
    Visible = False
  end
  object Memo5: TMemo
    Left = 0
    Top = 276
    Width = 185
    Height = 89
    ScrollBars = ssBoth
    TabOrder = 4
    Visible = False
  end
  object Memo4: TMemo
    Left = 192
    Top = 52
    Width = 185
    Height = 89
    ScrollBars = ssBoth
    TabOrder = 5
    Visible = False
  end
  object Memo7: TMemo
    Left = 192
    Top = 140
    Width = 185
    Height = 89
    ScrollBars = ssBoth
    TabOrder = 6
    Visible = False
  end
  object Memo6: TMemo
    Left = 192
    Top = 228
    Width = 185
    Height = 89
    ScrollBars = ssBoth
    TabOrder = 7
    Visible = False
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer2Timer
    Left = 224
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer1Timer
    Left = 192
  end
end
