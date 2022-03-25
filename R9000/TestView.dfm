object TestViewer: TTestViewer
  Left = 0
  Top = 0
  Width = 1673
  Height = 836
  TabOrder = 0
  object pageNumberLabel: TLabel
    Left = 448
    Top = 528
    Width = 14
    Height = 32
    Caption = '1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object stockStringGrid: TStringGrid
    Left = 8
    Top = 16
    Width = 1625
    Height = 497
    ColCount = 17
    FixedCols = 0
    RowCount = 16
    TabOrder = 0
    OnDrawCell = stockStringGridDrawCell
    OnMouseDown = stockStringGridMouseDown
    ColWidths = (
      16
      83
      177
      77
      95
      83
      114
      89
      93
      93
      88
      98
      103
      99
      90
      105
      106)
  end
  object CatalogComboBox: TComboBox
    Left = 48
    Top = 528
    Width = 281
    Height = 19
    Style = csOwnerDrawFixed
    ItemHeight = 13
    TabOrder = 1
    OnChange = CatalogComboBoxChange
  end
  object pagedownButton: TButton
    Left = 480
    Top = 528
    Width = 49
    Height = 33
    Caption = #8594
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -53
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = pagedownButtonClick
  end
  object pageupButton: TButton
    Left = 376
    Top = 528
    Width = 49
    Height = 33
    Caption = #8592
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -53
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = pageupButtonClick
  end
end
