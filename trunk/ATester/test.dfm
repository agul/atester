object Form1: TForm1
  Left = 192
  Top = 114
  Width = 870
  Height = 640
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 168
    Top = 32
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 368
    Top = 0
    Width = 185
    Height = 89
    Lines.Strings = (
      '1 2')
    TabOrder = 1
  end
  object Memo2: TMemo
    Left = 368
    Top = 88
    Width = 185
    Height = 89
    Lines.Strings = (
      '3')
    TabOrder = 2
  end
  object Edit1: TEdit
    Left = 48
    Top = 104
    Width = 121
    Height = 21
    TabOrder = 3
    Text = '10'
    OnKeyPress = Edit1KeyPress
  end
end
