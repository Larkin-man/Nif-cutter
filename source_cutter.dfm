object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize, biMaximize, biHelp]
  Caption = 'Nif cutter'
  ClientHeight = 701
  ClientWidth = 336
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -18
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  DesignSize = (
    336
    701)
  PixelsPerInch = 120
  TextHeight = 25
  object Offset: TLabeledEdit
    Left = 8
    Top = 72
    Width = 201
    Height = 33
    EditLabel.Width = 198
    EditLabel.Height = 25
    EditLabel.Caption = 'Offset of '#39'Num Triangles'#39
    NumbersOnly = True
    TabOrder = 2
    Text = '1353'
  end
  object Open: TButton
    Left = 8
    Top = 8
    Width = 97
    Height = 32
    Caption = 'Open Nif'
    TabOrder = 0
    OnClick = OpenClick
  end
  object SetBtn: TButton
    Left = 215
    Top = 73
    Width = 82
    Height = 32
    Caption = 'Set'
    Enabled = False
    TabOrder = 3
    OnClick = SetBtnClick
  end
  object Base: TValueListEditor
    Left = 8
    Top = 111
    Width = 306
    Height = 58
    DefaultColWidth = 160
    DefaultRowHeight = 26
    DisplayOptions = [doAutoColResize, doKeyColFixed]
    FixedCols = 1
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe UI'
    Font.Style = []
    Options = [goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing]
    ParentFont = False
    ScrollBars = ssNone
    Strings.Strings = (
      'Num Triangles= '
      'Num Triangle Points= ')
    TabOrder = 4
    OnSetEditText = BaseSetEditText
    ColWidths = (
      160
      140)
    RowHeights = (
      26
      26)
  end
  object Dots: TValueListEditor
    Left = 8
    Top = 168
    Width = 257
    Height = 525
    Anchors = [akLeft, akTop, akBottom]
    DefaultColWidth = 40
    DisplayOptions = [doAutoColResize, doKeyColFixed]
    FixedCols = 1
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Segoe UI'
    Font.Style = []
    Options = [goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowMoving, goEditing, goAlwaysShowEditor, goThumbTracking]
    ParentFont = False
    ScrollBars = ssVertical
    Strings.Strings = (
      'Triangles= '
      'Num Triangle Points= ')
    TabOrder = 6
    ColWidths = (
      40
      211)
  end
  object SaveBtn: TButton
    Left = 271
    Top = 656
    Width = 58
    Height = 32
    Anchors = [akLeft, akBottom]
    Caption = 'Save'
    TabOrder = 8
    OnClick = SaveBtnClick
  end
  object Refresh: TBitBtn
    Left = 271
    Top = 175
    Width = 41
    Height = 37
    DoubleBuffered = True
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333444444
      33333333333F8888883F33330000324334222222443333388F3833333388F333
      000032244222222222433338F8833FFFFF338F3300003222222AAAAA22243338
      F333F88888F338F30000322222A33333A2224338F33F8333338F338F00003222
      223333333A224338F33833333338F38F00003222222333333A444338FFFF8F33
      3338888300003AAAAAAA33333333333888888833333333330000333333333333
      333333333333333333FFFFFF000033333333333344444433FFFF333333888888
      00003A444333333A22222438888F333338F3333800003A2243333333A2222438
      F38F333333833338000033A224333334422224338338FFFFF8833338000033A2
      22444442222224338F3388888333FF380000333A2222222222AA243338FF3333
      33FF88F800003333AA222222AA33A3333388FFFFFF8833830000333333AAAAAA
      3333333333338888883333330000333333333333333333333333333333333333
      0000}
    ModalResult = 4
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 7
    OnClick = RefreshClick
  end
  object Help: TBitBtn
    Left = 246
    Top = 8
    Width = 82
    Height = 32
    Anchors = [akTop, akRight]
    DoubleBuffered = True
    Kind = bkHelp
    ParentDoubleBuffered = False
    TabOrder = 1
    OnClick = HelpClick
  end
  object RefreshNum: TBitBtn
    Left = 127
    Top = 112
    Width = 26
    Height = 26
    DoubleBuffered = True
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333444444
      33333333333F8888883F33330000324334222222443333388F3833333388F333
      000032244222222222433338F8833FFFFF338F3300003222222AAAAA22243338
      F333F88888F338F30000322222A33333A2224338F33F8333338F338F00003222
      223333333A224338F33833333338F38F00003222222333333A444338FFFF8F33
      3338888300003AAAAAAA33333333333888888833333333330000333333333333
      333333333333333333FFFFFF000033333333333344444433FFFF333333888888
      00003A444333333A22222438888F333338F3333800003A2243333333A2222438
      F38F333333833338000033A224333334422224338338FFFFF8833338000033A2
      22444442222224338F3388888333FF380000333A2222222222AA243338FF3333
      33FF88F800003333AA222222AA33A3333388FFFFFF8833830000333333AAAAAA
      3333333333338888883333330000333333333333333333333333333333333333
      0000}
    ModalResult = 4
    NumGlyphs = 2
    ParentDoubleBuffered = False
    TabOrder = 5
    Visible = False
    OnClick = RefreshNumClick
  end
  object Memo1: TMemo
    Left = 272
    Top = 240
    Width = 57
    Height = 321
    Lines.Strings = (
      'Memo1')
    TabOrder = 9
    WordWrap = False
  end
  object OpenDialog1: TOpenDialog
    Left = 168
  end
end
