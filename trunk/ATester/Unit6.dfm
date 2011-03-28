object upd: Tupd
  Left = 369
  Top = 252
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1054#1073#1085#1086#1074#1083#1077#1085#1080#1077
  ClientHeight = 128
  ClientWidth = 288
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object panel1: TPanel
    Left = 0
    Top = 0
    Width = 289
    Height = 129
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 260
      Height = 20
      Caption = #1044#1086#1089#1090#1091#1087#1085#1086' '#1086#1073#1085#1086#1074#1083#1077#1085#1080#1077' ATester:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 8
      Top = 40
      Width = 124
      Height = 16
      Caption = #1058#1077#1082#1091#1097#1072#1103' '#1074#1077#1088#1089#1080#1103':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 152
      Top = 40
      Width = 21
      Height = 16
      Caption = '3.0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = 0
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 8
      Top = 60
      Width = 140
      Height = 16
      Caption = #1044#1086#1089#1090#1091#1087#1085#1072#1103' '#1074#1077#1088#1089#1080#1103':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 152
      Top = 60
      Width = 21
      Height = 16
      Caption = '3.1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = 0
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Button1: TButton
      Left = 80
      Top = 88
      Width = 129
      Height = 25
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100' '#1089#1080#1089#1090#1077#1084#1091
      TabOrder = 0
      OnClick = Button1Click
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 289
    Height = 129
    TabOrder = 1
    Visible = False
    object Label6: TLabel
      Left = 12
      Top = 32
      Width = 268
      Height = 16
      Caption = #1042#1099#1087#1086#1083#1103#1077#1090#1089#1103' '#1079#1072#1075#1088#1091#1079#1082#1072' '#1086#1073#1085#1086#1074#1083#1077#1085#1080#1081'...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ProgressBar1: TProgressBar
      Left = 24
      Top = 64
      Width = 241
      Height = 25
      TabOrder = 0
    end
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
    Left = 280
    Top = 200
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 216
    Top = 104
  end
end
