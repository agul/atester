object Form1: TForm1
  Left = 366
  Top = 155
  Width = 440
  Height = 563
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'ATester'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000FFFF
    FFFFFFFFFFFFFC1FC007FC1FC007FC1FC007FC1FC007FC1FFF87FC1FFF87FC1F
    FF87FC1FFF87FC1FFF87FC1FFF87FC1FFF87FC1FFF87FC1FC007FC1FC007FC1F
    C007FC1FC007FC1FC1FFFC1FC1FFFC1FC1FFFC1FC1FFFC1FC1FFFC1FC1FFFC1F
    C1FFFC1FC1FFC001C007C001C007C001C007C001C007FFFFFFFFFFFFFFFF}
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object path: TLabel
    Left = 464
    Top = 336
    Width = 15
    Height = 13
    Caption = 'C:\'
    Visible = False
  end
  object Label9: TLabel
    Left = 104
    Top = 508
    Width = 170
    Height = 13
    Caption = #169' '#1040#1075#1091#1083#1077#1085#1082#1086' '#1040#1083#1077#1082#1089#1072#1085#1076#1088' 2010'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object chkr: TLabel
    Left = 136
    Top = 496
    Width = 21
    Height = 13
    Caption = 'chkr'
    Visible = False
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 0
    Width = 417
    Height = 493
    Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1090#1077#1089#1090#1086#1074
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 40
      Width = 88
      Height = 13
      Caption = #1042#1093#1086#1076#1085#1099#1077' '#1076#1072#1085#1085#1099#1077':'
    end
    object Label2: TLabel
      Left = 213
      Top = 40
      Width = 96
      Height = 13
      Caption = #1042#1099#1093#1086#1076#1085#1099#1077' '#1076#1072#1085#1085#1099#1077':'
    end
    object Label4: TLabel
      Left = 8
      Top = 312
      Width = 83
      Height = 13
      Caption = #1051#1080#1084#1080#1090' '#1074#1088#1077#1084#1077#1085#1080':'
    end
    object Label6: TLabel
      Left = 140
      Top = 312
      Width = 41
      Height = 13
      Caption = #1089#1077#1082#1091#1085#1076#1072
    end
    object Label8: TLabel
      Left = 224
      Top = 285
      Width = 54
      Height = 13
      Cursor = crHandPoint
      Caption = #1063#1090#1086' '#1101#1090#1086'?'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMenuHighlight
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      OnClick = Label8Click
      OnMouseMove = Label8MouseMove
      OnMouseLeave = Label8MouseLeave
    end
    object Label10: TLabel
      Left = 8
      Top = 336
      Width = 109
      Height = 13
      Caption = #1048#1084#1103' '#1074#1093#1086#1076#1085#1086#1075#1086' '#1092#1072#1081#1083#1072':'
    end
    object Label11: TLabel
      Left = 216
      Top = 336
      Width = 117
      Height = 13
      Caption = #1048#1084#1103' '#1074#1099#1093#1086#1076#1085#1086#1075#1086' '#1092#1072#1081#1083#1072':'
    end
    object Label14: TLabel
      Left = 352
      Top = 269
      Width = 58
      Height = 13
      Cursor = crHandPoint
      Hint = #1054#1073#1085#1086#1074#1080#1090#1100' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1090#1077#1089#1090#1086#1074
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMenuHighlight
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = Label14Click
      OnMouseEnter = Label14MouseEnter
      OnMouseLeave = Label14MouseLeave
    end
    object Label15: TLabel
      Left = 319
      Top = 253
      Width = 90
      Height = 13
      Cursor = crHandPoint
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1090#1077#1089#1090#1099
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMenuHighlight
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      OnClick = Label15Click
      OnMouseEnter = Label15MouseEnter
      OnMouseLeave = Label15MouseLeave
    end
    object Label18: TLabel
      Left = 204
      Top = 312
      Width = 76
      Height = 13
      Caption = #1051#1080#1084#1080#1090' '#1087#1072#1084#1103#1090#1080':'
    end
    object Label19: TLabel
      Left = 336
      Top = 312
      Width = 16
      Height = 13
      Caption = 'MB'
    end
    object Label20: TLabel
      Left = 192
      Top = 444
      Width = 85
      Height = 13
      Caption = #1060#1072#1081#1083' '#1085#1077' '#1074#1099#1073#1088#1072#1085
      Enabled = False
    end
    object Button1: TButton
      Left = 136
      Top = 462
      Width = 153
      Height = 25
      Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1100' '#1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1077
      Enabled = False
      TabOrder = 0
      OnClick = Button1Click
    end
    object Memo1: TMemo
      Left = 8
      Top = 56
      Width = 195
      Height = 185
      ScrollBars = ssBoth
      TabOrder = 1
    end
    object Memo2: TMemo
      Left = 213
      Top = 56
      Width = 195
      Height = 185
      ScrollBars = ssBoth
      TabOrder = 2
    end
    object Button2: TButton
      Left = 164
      Top = 248
      Width = 89
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1090#1077#1089#1090
      TabOrder = 3
      OnClick = Button2Click
    end
    object SpinEdit1: TSpinEdit
      Left = 96
      Top = 308
      Width = 41
      Height = 22
      MaxValue = 60
      MinValue = 1
      TabOrder = 4
      Value = 1
      OnChange = SpinEdit1Change
    end
    object RadioButton1: TRadioButton
      Left = 8
      Top = 285
      Width = 161
      Height = 17
      Cursor = crHandPoint
      Caption = #1042#1074#1077#1089#1090#1080' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1090#1077#1089#1090#1086#1074':'
      TabOrder = 5
      OnClick = RadioButton1Click
    end
    object SpinEdit2: TSpinEdit
      Left = 168
      Top = 281
      Width = 49
      Height = 22
      Enabled = False
      MaxValue = 1000
      MinValue = 0
      TabOrder = 6
      Value = 0
    end
    object RadioButton2: TRadioButton
      Left = 8
      Top = 16
      Width = 113
      Height = 17
      Cursor = crHandPoint
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1090#1077#1089#1090#1099':'
      Checked = True
      TabOrder = 7
      TabStop = True
      OnClick = RadioButton2Click
    end
    object Edit1: TEdit
      Left = 8
      Top = 352
      Width = 190
      Height = 21
      TabOrder = 8
      Text = 'input.txt'
    end
    object Edit2: TEdit
      Left = 216
      Top = 352
      Width = 190
      Height = 21
      TabOrder = 9
      Text = 'output.txt'
    end
    object CheckBox10: TCheckBox
      Left = 8
      Top = 383
      Width = 249
      Height = 17
      Cursor = crHandPoint
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1092#1072#1081#1083#1099' '#1090#1077#1089#1090#1086#1074' '#1087#1086#1089#1083#1077' '#1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1103
      TabOrder = 10
    end
    object CheckBox3: TCheckBox
      Left = 8
      Top = 404
      Width = 289
      Height = 17
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1086#1090#1095#1077#1090' '#1086' '#1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1080' '#1074' '#1092#1086#1088#1084#1072#1090#1077' HTML'
      TabOrder = 11
      OnClick = CheckBox3Click
    end
    object CheckBox4: TCheckBox
      Left = 280
      Top = 404
      Width = 121
      Height = 17
      Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1072#1090#1100' '#1086#1090#1095#1077#1090
      Enabled = False
      TabOrder = 12
    end
    object CheckBox5: TCheckBox
      Left = 8
      Top = 424
      Width = 161
      Height = 17
      Caption = #1047#1072#1087#1091#1089#1082' '#1074' '#1092#1086#1085#1086#1074#1086#1084' '#1088#1077#1078#1080#1084#1077
      Checked = True
      State = cbChecked
      TabOrder = 13
    end
    object SpinEdit3: TSpinEdit
      Left = 284
      Top = 308
      Width = 49
      Height = 22
      MaxValue = 1024
      MinValue = 1
      TabOrder = 14
      Value = 256
    end
    object CheckBox6: TCheckBox
      Left = 8
      Top = 442
      Width = 177
      Height = 17
      Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1074#1085#1077#1096#1085#1080#1081' '#1095#1077#1082#1077#1088
      TabOrder = 15
      OnClick = CheckBox6Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 0
    Width = 417
    Height = 493
    Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1099' '#1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1103
    TabOrder = 1
    Visible = False
    object Label3: TLabel
      Left = 170
      Top = 16
      Width = 63
      Height = 13
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1099':'
      Visible = False
    end
    object Label5: TLabel
      Left = 8
      Top = 34
      Width = 3
      Height = 13
      Visible = False
    end
    object Label7: TLabel
      Left = 54
      Top = 200
      Width = 301
      Height = 24
      Caption = #1055#1086#1076#1075#1086#1090#1086#1074#1082#1072' '#1082' '#1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1102'...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label12: TLabel
      Left = 6
      Top = 240
      Width = 240
      Height = 16
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090' '#1087#1088#1077#1076#1099#1076#1091#1097#1077#1075#1086' '#1090#1077#1089#1090#1072':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      Visible = False
    end
    object Label13: TLabel
      Left = 246
      Top = 240
      Width = 39
      Height = 16
      Caption = 'undef'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Visible = False
    end
    object Label16: TLabel
      Left = 6
      Top = 258
      Width = 317
      Height = 16
      Caption = #1042#1088#1077#1084#1103' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1103' '#1085#1072' '#1087#1088#1077#1076#1099#1076#1091#1097#1077#1084' '#1090#1077#1089#1090#1077':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      Visible = False
    end
    object Label17: TLabel
      Left = 322
      Top = 258
      Width = 39
      Height = 16
      Caption = 'undef'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Visible = False
    end
    object Button3: TButton
      Left = 144
      Top = 460
      Width = 121
      Height = 25
      Caption = #1058#1077#1089#1090#1080#1088#1086#1074#1072#1090#1100' '#1079#1072#1085#1086#1074#1086
      Enabled = False
      TabOrder = 0
      OnClick = Button3Click
    end
    object Memo7: TMemo
      Left = 208
      Top = 500
      Width = 185
      Height = 89
      Lines.Strings = (
        'Memo7')
      ScrollBars = ssBoth
      TabOrder = 1
      Visible = False
    end
  end
  object Memo4: TMemo
    Left = 184
    Top = 536
    Width = 185
    Height = 89
    Lines.Strings = (
      'Memo4')
    ScrollBars = ssBoth
    TabOrder = 2
    Visible = False
  end
  object Button4: TButton
    Left = 8
    Top = 500
    Width = 75
    Height = 25
    Hint = #1053#1072#1078#1084#1080#1090#1077', '#1095#1090#1086#1073#1099' '#1087#1086#1083#1091#1095#1080#1090#1100' '#1082#1088#1072#1090#1082#1091#1102' '#1089#1087#1088#1072#1074#1082#1091
    Caption = #1055#1086#1084#1086#1097#1100
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    OnClick = Button4Click
  end
  object Memo5: TMemo
    Left = 96
    Top = 536
    Width = 185
    Height = 89
    Lines.Strings = (
      'Memo5')
    ScrollBars = ssBoth
    TabOrder = 4
    Visible = False
  end
  object Button5: TButton
    Left = 288
    Top = 500
    Width = 139
    Height = 25
    Caption = #1060#1086#1088#1084#1072#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1090#1077#1089#1090#1086#1074
    TabOrder = 5
    OnClick = Button5Click
  end
  object ListBox1: TListBox
    Left = 8
    Top = 584
    Width = 177
    Height = 153
    ItemHeight = 13
    TabOrder = 6
    Visible = False
  end
  object CheckBox1: TCheckBox
    Left = 240
    Top = 600
    Width = 97
    Height = 17
    Caption = 'CheckBox1'
    Checked = True
    State = cbChecked
    TabOrder = 7
    Visible = False
  end
  object CheckBox2: TCheckBox
    Left = 240
    Top = 616
    Width = 97
    Height = 17
    Caption = 'CheckBox2'
    Checked = True
    State = cbChecked
    TabOrder = 8
    Visible = False
  end
  object Memo3: TMemo
    Left = 216
    Top = 536
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
    TabOrder = 9
    Visible = False
  end
  object report: TMemo
    Left = 56
    Top = 544
    Width = 185
    Height = 89
    ScrollBars = ssBoth
    TabOrder = 10
    Visible = False
  end
  object Memo6: TMemo
    Left = 192
    Top = 536
    Width = 185
    Height = 89
    Lines.Strings = (
      'Memo6')
    ScrollBars = ssBoth
    TabOrder = 11
    Visible = False
  end
  object stderr: TMemo
    Left = 88
    Top = 532
    Width = 185
    Height = 89
    ScrollBars = ssBoth
    TabOrder = 12
    Visible = False
  end
  object od1: TOpenDialog
    Filter = #1048#1089#1087#1086#1083#1085#1103#1077#1084#1099#1077' '#1092#1072#1081#1083#1099' (*.exe)|*.exe'
    Title = #1042#1099#1073#1088#1072#1090#1100' '#1087#1088#1086#1075#1088#1072#1084#1084#1091' '#1076#1083#1103' '#1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1103'...'
    Left = 24
    Top = 528
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer1Timer
    Left = 56
    Top = 520
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer2Timer
    Left = 400
    Top = 496
  end
  object od2: TOpenDialog
    Filter = #1048#1089#1087#1086#1083#1085#1103#1077#1084#1099#1077' '#1092#1072#1081#1083#1099' (*.exe)|*.exe'
    Left = 264
    Top = 496
  end
  object IdHTTP1: TIdHTTP
    MaxLineAction = maException
    ReadTimeout = 0
    AllowCookies = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = 0
    Request.ContentRangeStart = 0
    Request.ContentType = 'text/html'
    Request.Accept = 'text/html, */*'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    HTTPOptions = [hoForceEncodeParams]
    Left = 216
    Top = 504
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 1
    OnTimer = Timer3Timer
    Left = 96
    Top = 512
  end
end
