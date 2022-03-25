//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TestView.h"
#include <string>
#include<map>
#include <vector>
#include<algorithm>


USING_CENTERS();

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTestViewer *TestViewer;
//---------------------------------------------------------------------------
__fastcall TTestViewer::TTestViewer(TComponent* Owner)
    : TFrame(Owner)
{
	SettingStringgrid();
	ChooseCatalog();
	m_nNowPage = 1;
	m_nPageStart = 0;
	m_nPageEnd = 0;
	m_nPageNumber = 0;
	pageupButton->Enabled = true;
	pagedownButton->Enabled = true;
    isUpButton=false;
	isDownButton=false;
	pageNumberLabel->Caption = "1";
	CatalogComboBox->ItemIndex = 0;
	ChooseStock();
    m_nOrder=1;
}
//---------------------------------------------------------------------------

void TTestViewer::GetInterface(Interface Inf, void*& pInf)

{
    switch ( Inf)
    {
        case IID_WINCONTROL: pInf = (void*) dynamic_cast<TWinControl*>( this);break;
        case IID_QUOTE: pInf = (void*) dynamic_cast<IQuote*>(this);break;
        default : pInf = NULL;
    }
}

void TTestViewer::Execute( unsigned int unMsg, int nParam1, int nParam2)
{
}

void TTestViewer::AddExtend( ICommand* pCommand)
{
}
		
int TTestViewer::GetID()
{
    return 9000;
}

AnsiString TTestViewer::GetName()
{
    return "Test";
}
	
CHotKeys* TTestViewer::GetHotKeys()
{
    return NULL;
}
	
void TTestViewer::SetHotKeys( const CHotKeys& Keys)
{
}

void TTestViewer::SetStock( const CStock& Stock)
{
}
	
void TTestViewer::SetPageNo( short sPageNo)
{
    m_sPage = sPageNo+1;  // m_sPage 要在 .h檔宣告(short)
}

short TTestViewer::GetPageNo()
{
    return m_sPage;
}
	
void TTestViewer::SetStockGraphic( const vector<int>& Graphics)
{
}
	
void TTestViewer::QuoteUpdated( int nSubject, int nParam1, int nParam2)
{
//內容請參考報價練習的說明
    switch( nSubject)
    {
        case 0x10:
            PostMessage( Handle, WM_USER+0x10, nParam1, nParam2); //   不等待執行緒處理訊息就返回。
            break;
        case 0x30:
            PostMessage( Handle, WM_USER+0x30, nParam1, nParam2);
            break;
        case 0x31:
            PostMessage( Handle, WM_USER+0x31, nParam1, nParam2);
            break;                              //Msg.WParam 市場代碼    Msg.LParam 市場類別
        case RESET:
            PostMessage( Handle, WM_USER+RESET, nParam1, nParam2);
            break;
    }
}

void __fastcall TTestViewer::On0x10(TMessage &Msg)              //0x10通知商品下載完成
{

      //市場代號 跟商品代號 告訴你是哪個商品要更新
	ChooseCatalog();
    m_nNowPage = 1;
    m_nPageStart = 0;
    m_nPageEnd = 0;
    m_nPageNumber = 0;
    pageupButton->Enabled = true;
    pagedownButton->Enabled = true;
    pageNumberLabel->Caption = "1";
    CatalogComboBox->ItemIndex = 0;
    ChooseStock();
}
void __fastcall TTestViewer::On0x30(TMessage &Msg)                //0x30通知商品清盤
{

	int vPageStockSize = m_vPageStock.size();
    map< const CStock*, double>::iterator it;
    for (int i = 0;i<vPageStockSize;i++)      //Msg.WParam 市場代碼    Msg.LParam 市場類別  1-15
    {
    //Msg.WParam     Msg.LParam
    	const  CStock* myStock1 = g_pQuoteWarehouse->GetStock(Msg.WParam,Msg.LParam);
    	if(stockStringGrid->Cells[1][i+1] == myStock1->GetStockNo())
        {

        
            SetDealPrice( i, myStock1);
            break;

        }
    }

}
void __fastcall TTestViewer::On0x31(TMessage &Msg)       // 通知商品即時報價
{

	int vPageStockSize = m_vPageStock.size();
    map< const CStock*, double>::iterator it;
    for (int i = 0;i<vPageStockSize;i++)      //Msg.WParam 市場代碼    Msg.LParam 市場類別  1-15
    {
    //Msg.WParam     Msg.LParam
    	const  CStock* myStock1 = g_pQuoteWarehouse->GetStock(Msg.WParam,Msg.LParam);

        if(stockStringGrid->Cells[1][i+1] == myStock1->GetStockNo())
        {

        	SetDealPrice( i, myStock1);

        	break;
        }
    }

}


void __fastcall TTestViewer::OnRESET(TMessage &Msg)      //OnReset清盤
{
           //清盤

    multimap_Stocks.clear();
    m_vPageStock.clear();
    ClearStock();

}

void TTestViewer::ClearMap()
{


   multimap_Stocks.clear();
   m_vPageStock.clear();


}

void TTestViewer::SetDealPrice(int i,const CStock* myStock1 )     //顯示報價
{


	stockStringGrid->Cells[0][i+1] = AnsiString("");    //K
    stockStringGrid->Cells[1][i+1] = myStock1->GetStockNo();    //代號
    stockStringGrid->Cells[2][i+1] = myStock1->GetStockName();  //名稱
    String strAmp = "";
    string strPlus = "+";
    double dAmp;
    double dHigh_low=myStock1->GetHigh()-myStock1->GetLow();

    if(dHigh_low>0&&myStock1->GetYDay()>0)
    {
    	dAmp = 100*(myStock1->GetHigh()-myStock1->GetLow())/ myStock1->GetYDay();

    }else
    {
     	dAmp=0.00;
    }
	String strAmpresult=FloatToStrF(dAmp, ffFixed,7,myStock1->GetDecimal()) ;  //振幅    (當日最高-最低) / 前一交易日收盤價
    string strAmpresult1 = strAmpresult.c_str();
    strAmp = strPlus.data()+AnsiString((strAmpresult1.substr(0)).data()) ;
    stockStringGrid->Cells[3][i+1] = strAmp ;  //振幅Amplitude



    AnsiString anBuy= FloatToStrF( myStock1->GetBuy(), ffFixed, 7, myStock1->GetDecimal()) ;
    if (atof(anBuy.c_str()) == -7777.00)
    {
          anBuy= "市價";
    }

    stockStringGrid->Cells[4][i+1] = anBuy;         //買進
    stockStringGrid->Cells[5][i+1] = FloatToStrF(myStock1->GetSell(), ffFixed,7,myStock1->GetDecimal()) ;        //賣出
    stockStringGrid->Cells[6][i+1] = FloatToStrF(myStock1->GetDeal(), ffFixed,7,myStock1->GetDecimal()) ;;      //成交價
    stockStringGrid->Cells[7][i+1] = AnsiString( myStock1->GetTickQty()).c_str();    //單量
    stockStringGrid->Cells[8][i+1] = AnsiString( myStock1->GetTotalQty()).c_str(); //成交量
    double dUpDown= GetUpDown( myStock1->GetDeal(), myStock1->GetYDay());
    String strUpDown = "";
    string strUp = "▲";
    string strDown = "▼";
    String strUPresult = FloatToStrF(dUpDown, ffFixed,7,myStock1->GetDecimal());
    string strUPresult1 = strUPresult.c_str();
    if(dUpDown >= 0)
    {

       strUpDown = strUp.data()+AnsiString((strUPresult1.substr(0)).data()) ;


    }else if(dUpDown < 0)
    {

    	strUpDown = strDown.data()+AnsiString((strUPresult1.substr(1)).data()) ;

    }
    stockStringGrid->Cells[9][i+1] = strUpDown;       //漲跌
    double dLimit = GetLimit( myStock1->GetDeal(), myStock1->GetYDay());
    AnsiString strLimit = FloatToStrF( dLimit, ffFixed,7, myStock1->GetDecimal());
    if(dLimit<0)
    {
    	string strLimit1 = strLimit.c_str();
    	strLimit = AnsiString(( strLimit1.substr(1)).data()) ;

    }

    stockStringGrid->Cells[10][i+1] = strLimit;   //幅度
    stockStringGrid->Cells[11][i+1] = FloatToStrF( myStock1->GetYDay(), ffFixed,7, myStock1->GetDecimal());  //昨收價
    AnsiString anOpen = FloatToStrF( myStock1->GetOpen(), ffFixed,7, myStock1->GetDecimal()) ;
    stockStringGrid->Cells[12][i+1] = anOpen ;   // 開盤價
    stockStringGrid->Cells[13][i+1] = FloatToStrF( myStock1->GetHigh(), ffFixed,7, myStock1->GetDecimal()) ;   // 最高價
    stockStringGrid->Cells[14][i+1] = FloatToStrF( myStock1->GetLow(), ffFixed,7, myStock1->GetDecimal()) ;   // 最低價
    stockStringGrid->Cells[15][i+1] = FloatToStrF( myStock1->GetUp(), ffFixed,7, myStock1->GetDecimal()) ;   // 漲停價
    stockStringGrid->Cells[16][i+1] = FloatToStrF( myStock1->GetDown(), ffFixed,7, myStock1->GetDecimal()) ;   // 跌停價


}
void __fastcall TTestViewer::AfterConstruction( )
{

	g_pQuoteWarehouse->AttachDispatcher( this, 0x10);   //0x10通知商品下載完成
    g_pQuoteWarehouse->AttachDispatcher( this, 0x30);   //0x30通知商品清盤
    g_pQuoteWarehouse->AttachDispatcher( this, 0x31);   //0x31通知商品即時報價
    g_pQuoteWarehouse->AttachDispatcher( this, RESET);  //清盤


}





void __fastcall  TTestViewer::ChooseCatalog()
{

	const map<char, CMarket*> myMarket = g_pQuoteWarehouse->GetMarkets();  //取得國內市場
	map<char, CMarket*>::const_iterator pMarket = myMarket.begin();


    for (int i = 0;i<5;i++)
    {

    	m_cMarketNo = pMarket->first;        //市場代碼
        const CATALOG& myCatalogs = g_pQuoteWarehouse->GetCatalogs(m_cMarketNo);        //取得市場下類別
        map<short, CFormat06>::const_iterator Catalog_iter;
        for(Catalog_iter = myCatalogs.begin();Catalog_iter!= myCatalogs.end();Catalog_iter++)
        {

             short  sTypeNo = Catalog_iter->first;   //類別代碼
             const CFormat06& myCF06 = g_pQuoteWarehouse->Get06( m_cMarketNo,sTypeNo);
             CatalogComboBox->Items->AddObject(IntToStr(sTypeNo)+ " " + myCF06.GetTypeName() ,(TObject*)&myCF06);

         }

         pMarket++;
    }

}
void TTestViewer::ClearStock()
{

	for(int i = 1;i<stockStringGrid->RowCount;i++)
	{

	    stockStringGrid->Rows[i]->Clear();

    }

    stockStringGrid->Invalidate(); //重繪

}

void TTestViewer::ChoseAmp(){    //選擇振幅
	const CFormat06 *myCF061 = (CFormat06*)CatalogComboBox->Items->Objects[CatalogComboBox->ItemIndex];  //取combobox 類別
    const set<short>& myStock = myCF061->GetStocks();       //取得<商品索引>
    set<short>::iterator pSortStock = myStock.begin();
    m_nStockSize = myStock.size();


    CBasket mapSortBasket;

    if(m_nNowPage==1)
    {
   		multimap_Stocks.clear();

        for (int nCount = 0; nCount<m_nStockSize;nCount++)
        {
        	mapSortBasket.AddItem( myCF061->GetMarketNo(), *pSortStock);
            pSortStock++;
        }
        PuttingSortBasket( mapSortBasket);


    }


}

void TTestViewer::ChooseStock()
{
    m_vPageStock.clear();
	ClearStock();
    const CFormat06 *myCF061 = (CFormat06*)CatalogComboBox->Items->Objects[CatalogComboBox->ItemIndex];  //取combobox 類別
    const set<short>& myStock = myCF061->GetStocks();       //取得<商品索引>
    set<short>::iterator pStock = myStock.begin();
    set<short>::iterator pSortStock = myStock.begin();
    m_nStockSize = myStock.size();

    m_nPageNumber = m_nStockSize/15;
    int nPageRemainder = 0;     //剩餘頁數
    nPageRemainder = m_nStockSize%15;
                                                             //沒餘數
    if(nPageRemainder != 0)
    {   	                                      //有餘數狀況
    	m_nPageNumber += 1;

    }
    SettingPageButton();

    int row = 0;
    CBasket Basket;

    for(int count = 0; count< m_nStockSize;count++)
    {

    	if( count >= m_nPageStart&&row< 15)
        {
        	const CStock *  myStock1 = g_pQuoteWarehouse->GetStock( myCF061->GetMarketNo(), *pStock);
            SetDealPrice( row, myStock1);
            Basket.AddItem( myCF061->GetMarketNo(), *pStock);
            m_vPageStock.push_back( myStock1);
            row++;

        }

        if(row>=15)
        {
            break;

        }
        pStock++;

    }
    g_pQuoteCenter->RequestStocks( m_sPage, 15, Basket);

}
void TTestViewer::PuttingSortBasket(const CBasket& Basket)
{
	map<AnsiString,PriceInfo> Info = m_HttpRequestCenter.GetPriceInfo( Basket);
    map<AnsiString,PriceInfo>::iterator pInfo = Info.begin() ;                          //info[qhDeal] = strValue;
    AnsiString anStockNo;
    double dQhHigh;
    double dQhLow;
    double dQhYDay;
    double dAmp;
    for(int nCount = 0; nCount<m_nStockSize;nCount++)
    {

		map<int,AnsiString>::iterator pPriceInfo ;
        int nCountInfo=0;
        for (pPriceInfo = (*pInfo).second.begin(); pPriceInfo != (*pInfo).second.end(); ++pPriceInfo)
        {

        	if(nCountInfo == 5)           //High
            {
            	dQhHigh =  atof (((*pPriceInfo).second).c_str());

            }else if(nCountInfo == 6)           //low
            {
            	dQhLow =  atof (((*pPriceInfo).second).c_str());


            }else if(nCountInfo == 10)               //YDay
            {
             	dQhYDay =  atof (((*pPriceInfo).second).c_str());

            }
            anStockNo = ((*pInfo).first);
        	nCountInfo++;
        }
        dAmp = 100*(dQhHigh - dQhLow)/dQhYDay;
        AnsiString strAmpresult = FloatToStrF(dAmp, ffFixed,7,2) ;
        multimap_Stocks.insert(pair<double, AnsiString>(atof(strAmpresult.c_str()),anStockNo));
    	pInfo++;
    }

}





void TTestViewer::SettingPageButton()
{

    if(m_nNowPage<m_nPageNumber)            //現在頁數小於總頁數
    {

        m_nPageStart = (m_nNowPage-1)*15;

        if(m_nNowPage == 1)
        {
            pageupButton->Enabled = false;
            pagedownButton->Enabled = true;
        }else
        {
            pagedownButton->Enabled = true;
            pageupButton->Enabled = true;
        }


    }else if(m_nNowPage == m_nPageNumber)            //現在頁數等於總頁數
    {

    	m_nPageStart = (m_nNowPage-1)*15;

        if(m_nNowPage == 1)
        {
            pageupButton->Enabled = false;
            pagedownButton->Enabled = false;
        } else
        {
        	pageupButton->Enabled = true;
            pagedownButton->Enabled = false;
        }

    }

}
void TTestViewer::SettingStringgrid()
{

	stockStringGrid->Cells[0][0] = "K" ;
	stockStringGrid->Cells[1][0] = "代號" ;
    stockStringGrid->Cells[2][0] = "名稱" ;
    stockStringGrid->Cells[3][0] = "振幅" ;
    stockStringGrid->Cells[4][0] = "買進" ;
    stockStringGrid->Cells[5][0] = "賣出";
    stockStringGrid->Cells[6][0] = "成交價";
    stockStringGrid->Cells[7][0] = "單量";
    stockStringGrid->Cells[8][0] = "成交量";
    stockStringGrid->Cells[9][0] = "漲跌";
    stockStringGrid->Cells[10][0] = "幅度";
    stockStringGrid->Cells[11][0] = "昨收價";
    stockStringGrid->Cells[12][0] = "開盤價";
    stockStringGrid->Cells[13][0] = "最高價";
    stockStringGrid->Cells[14][0] = "最低價";
    stockStringGrid->Cells[15][0] = "漲停價";
    stockStringGrid->Cells[16][0] = "跌停價";
}
void __fastcall TTestViewer::stockStringGridDrawCell(TObject *Sender,
      int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	TStringGrid* pGrid = dynamic_cast<TStringGrid*>(Sender);
    int vPageStockSize = m_vPageStock.size();
    if(State.Contains(gdFixed))
    {
    	pGrid->Canvas->Font->Color = clWindow ;
        pGrid->Canvas->Brush->Color = clGrayText;
        pGrid->Canvas->FillRect(Rect);
    }else
    {
    	pGrid->Canvas->Brush->Color = clWindowText;
        pGrid->Canvas->Font->Color = clWindow ;

        if(ARow < vPageStockSize||vPageStockSize != 0)
        {

        	if(ACol)
            {

            	switch(ACol)
                {
                	case 1: //代號
                    {
                    	pGrid->Canvas->Font->Color = TColor(RGB(255, 215, 0));

                        break;
                    }
                    case 2:  //名稱
                    	pGrid->Canvas->Font->Color = clAqua;//TColor(RGB(0, 199, 255)); //藍色

                        break;
                    case 3: //振幅
                        pGrid->Canvas->Font->Color = TColor(RGB(255, 0, 0)); //紅色
                         break;
                    case 4: //買進
                    case 5: //賣出
                    case 6://成交價
                    case 13://最高
                    case 14://最低
                    {

                    	pGrid->Canvas->Font->Style = TFontStyles()<< fsBold;
                        if(atof(pGrid->Cells[ACol][ARow].c_str()) != 0)
                        {

                        	if(atof (pGrid->Cells[ACol][ARow].c_str())<atof (pGrid->Cells[11][ARow].c_str())) //跌
                            {

                            	if(atof (pGrid->Cells[ACol][ARow].c_str()) == atof (pGrid->Cells[15][ARow].c_str()))
                                {

                                	pGrid->Canvas->Brush->Color = TColor(RGB(0, 255, 0)); //綠色
                                    pGrid->Canvas->Brush->Style = bsSolid;
                                    pGrid->Canvas->Font->Color = clWindowText ; //黑色


                                }else
                                {
                                	pGrid->Canvas->Font->Color = TColor(RGB(0, 255, 0));

                                }

                            }else if(atof(pGrid->Cells[ACol][ARow].c_str())>atof(pGrid->Cells[11][ARow].c_str()))
                            {

                            	if(atof (pGrid->Cells[ACol][ARow].c_str()) == atof (pGrid->Cells[15][ARow].c_str()))
                                {
                                	pGrid->Canvas->Brush->Color = clRed;      //紅色
                                    pGrid->Canvas->Brush->Style = bsSolid;
                                    pGrid->Canvas->Font->Color = clWindow ; //白色


                                }else
                                {
                                	pGrid->Canvas->Font->Color =TColor(RGB(255, 0, 0));

                                }

                            }else
                            {
                            	pGrid->Canvas->Font->Color =clWindow ;

                            }


                        }else
                        {

                        	if (AnsiCompareStr(pGrid->Cells[ACol][ARow], "市價") == 0)
                            {

                            	pGrid->Canvas->Font->Color =clWindow ; //白色

                            }else
                            {

                            	pGrid->Canvas->Font->Color =  clWindowText ; //黑色

                            }

                        }

                    	break;

                    }
                    case 7:  //單量
                    {
                    	pGrid->Canvas->Font->Style = TFontStyles()<< fsBold;
                        if(atof(pGrid->Cells[7][ARow].c_str())!=0)
                        {

                        	if(atof(pGrid->Cells[6][ARow].c_str())>=atof(pGrid->Cells[5][ARow].c_str()))     //成交價>=賣出
                            {

                            	pGrid->Canvas->Font->Color =TColor(RGB(255, 0, 0)) ;


                            }else if (atof(pGrid->Cells[6][ARow].c_str())<=atof(pGrid->Cells[4][ARow].c_str()))    //成交價<=買進
                            {

                            	pGrid->Canvas->Font->Color =TColor(RGB(0, 255, 0)) ;

                            }else if ((atof(pGrid->Cells[6][ARow].c_str())<atof(pGrid->Cells[5][ARow].c_str()))&&(atof(pGrid->Cells[6][ARow].c_str())>atof(pGrid->Cells[4][ARow].c_str())))
                            {

                            	pGrid->Canvas->Font->Color =TColor(RGB(255, 0, 0)) ;                        //買進 <成交價 <賣出

                            }

                        }else
                        {

                        	pGrid->Canvas->Font->Color =  clWindowText ; //黑色


                        }
                        break;

                    }
                    case 8://成交量
                    {
                    	pGrid->Canvas->Font->Style = TFontStyles()<< fsBold;
                        if(atof(pGrid->Cells[8][ARow].c_str())!=0)
                        {

                        	pGrid->Canvas->Font->Color =TColor(RGB(255, 215, 0)) ; //黃色
                        }else
                        {

                        	pGrid->Canvas->Font->Color =  clWindowText ; //黑色

                        }
                        break;
                    }
                    case 9://漲跌
                    case 10://幅度
                    {

                        if(pGrid->Cells[9][ARow]=="")
                        {

                            break;
                        }
                        pGrid->Canvas->Font->Style = TFontStyles()<< fsBold;
                        string strUpDownZero="";
                        string strUpDown1="";
                        strUpDown1=(pGrid->Cells[9][ARow]).c_str();
                        strUpDownZero=strUpDown1.substr(2);


                        if(atof(strUpDownZero.c_str())!=0)
                        {

                            string strUpDown="";
                            strUpDown=(pGrid->Cells[9][ARow]).c_str();
                            strUpDown= strUpDown.substr(0,2);
                            string strUp="▲";
                            string strDown="▼";
                            int nAns=strncmp(strUpDown.c_str(), strDown.c_str(),2);

                            if(nAns==0)    //跌
                            {

                                pGrid->Canvas->Font->Color =TColor(RGB(0, 255, 0)) ;

                            }else
                            {

                                pGrid->Canvas->Font->Color =TColor(RGB(255, 0, 0)) ;

                            }

                        }else
                        {

                        	pGrid->Canvas->Font->Color =clWindowText ; //黑色

                        }
                        break;
                    }

                    case 11: //昨收價
                    {
                    	pGrid->Canvas->Font->Style = TFontStyles()<< fsBold;
                        if(atof(pGrid->Cells[11][ARow].c_str())!=0)
                        {

                        	pGrid->Canvas->Font->Color =clWindow; //白色

                        }else
                        {

                        	pGrid->Canvas->Font->Color =clWindowText ; //黑色

                        }

                    	break;
                    }

                    case 12: //開盤價
                    {
                    	pGrid->Canvas->Font->Style = TFontStyles()<< fsBold;
                        if(atof(pGrid->Cells[12][ARow].c_str())!=0)
                        {

                        	pGrid->Canvas->Font->Color = TColor(RGB(255, 215, 0)) ; //黃色

                        }else if(atof(pGrid->Cells[12][ARow].c_str())==0)
                        {

                        	pGrid->Canvas->Font->Color = clWindowText ; //黑色

                        }else if(pGrid->Cells[12][ARow] == "-9999.99"){

                            pGrid->Canvas->Font->Color = clWindowText ; //黑色

                        }
                        break;
                    }
                    case 15:     //漲停價
                    {
                    	pGrid->Canvas->Font->Style = TFontStyles()<< fsBold;
                        if(atof(pGrid->Cells[15][ARow].c_str())!=0)
                        {
                        	pGrid->Canvas->Brush->Color=clRed;      //紅色
                            pGrid->Canvas->Brush->Style=bsSolid;
                            pGrid->Canvas->Font->Color =clWindow ; //白色

                        }
                        break;
                    }
                    case 16:   // 跌停價
                    {
                    	pGrid->Canvas->Font->Style = TFontStyles()<< fsBold;
                        if(atof(pGrid->Cells[16][ARow].c_str())!=0)
                        {
                        	pGrid->Canvas->Brush->Color=TColor(RGB(0, 255, 0)); //綠色
                        	pGrid->Canvas->Brush->Style=bsSolid;
                        	pGrid->Canvas->Font->Color =clWindowText ; //黑色
                        }

                    	break;
                    }

                }

            }

        }

        pGrid->Canvas->FillRect( Rect);
	}
//--------------------------------------------------------------------------- k棒
    if(ACol==0&&ARow!=0)
    {
    	if(ARow < vPageStockSize+1&&vPageStockSize!=0)
        {
        	double dOpen=  atof((stockStringGrid->Cells[12][ARow]).c_str());
            double dClose= atof((stockStringGrid->Cells[6][ARow]).c_str());   //成交價代替
            double dHigh= atof((stockStringGrid->Cells[13][ARow]).c_str());
            double dLow=  atof((stockStringGrid->Cells[14][ARow]).c_str());
            int nCellWidth= (Rect.right-1)-(Rect.left+1);
            int nCellHeight=(Rect.bottom-1)-(Rect.top+1);


            if(dOpen!=0&&dClose!=0&&dHigh!=0&&dLow!=0)
            {


            	if(dOpen<dClose)  // 收盤價>開盤價 //紅棒        //跳高漲停、實體紅k、帶下影線之紅K 、帶上下影線之紅K、帶上影之紅K
                {

                	pGrid->Canvas->Pen->Color=clRed;
                  	pGrid->Canvas->MoveTo(Rect.left+nCellWidth/2,Rect.top+1);
                  	pGrid->Canvas->LineTo(Rect.left+nCellWidth/2,Rect.top+nCellHeight);
                  	pGrid->Canvas->MoveTo(Rect.left+nCellWidth/2,Rect.top+1);
                  	double nHighClose=dHigh- dClose;                                        //  (x1,y1)
                  	double nOpenLow=dOpen-dLow;             //Rect(x1,y1,x2,y2)                   .-------
                  	double nHighLow=dHigh-dLow;                                              //   |      |
                  	double dproportion=nCellHeight/nHighLow;                                 //  |      |
                                                                                           //   -------.
                  	int nx1=Rect.left+1;                                                                  // (x2,y2)

                  	int ny1=(Rect.top+1)+(int)(nHighClose*dproportion);
                  	int nx2=nx1+nCellWidth;
                  	int ny2=(Rect.Bottom-1)-(int)(nOpenLow*dproportion);
                  	pGrid->Canvas->Brush->Color=clRed;
                  	pGrid->Canvas->Brush->Style=bsSolid;
                  	pGrid->Canvas->Rectangle(nx1,ny1,nx2,ny2);



                	}else if (dOpen>dClose)        // 收盤價<開盤價//黑棒     //帶下影之黑K、帶上下影線之黑K、帶上影線之黑K、實體黑K
                	{
                   		pGrid->Canvas->Pen->Color=TColor(RGB(0, 255, 0));
                   		pGrid->Canvas->MoveTo(Rect.left+nCellWidth/2,Rect.top+1);
                   		pGrid->Canvas->LineTo(Rect.left+nCellWidth/2,Rect.top+nCellHeight);
                   		pGrid->Canvas->MoveTo(Rect.left+nCellWidth/2,Rect.top+1);
                   		double nCloseLow=dClose-dLow;                                        //  (x1,y1)
                       	double nHighOpen=dHigh-dOpen;             //Rect(x1,y1,x2,y2)                  .-------
                       	double nHighLow=dHigh-dLow;                                              //   |      |
                       	double dproportion=nCellHeight/nHighLow;                                 //  |      |                                                                                           //   -------.
                       	int nx1=Rect.left+1;                                                     //   -------. // (x2,y2)                                                                                                       // (x2,y2)
                       	int ny1=(Rect.top+1)+(int)(nHighOpen*dproportion);
                       	int nx2=nx1+nCellWidth;
                       	int ny2=(Rect.Bottom-1)-(int)(nCloseLow*dproportion);
                       	pGrid->Canvas->Brush->Color=TColor(RGB(0, 255, 0));
                       	pGrid->Canvas->Brush->Style=bsSolid;
                       	pGrid->Canvas->Rectangle(nx1,ny1,nx2,ny2);
                	}else           // 收盤價=開盤價           //帶下影平盤線、十字平盤線、帶上影之平盤線、
                	{
                   		double nHighOpen=dHigh-dOpen;             //Rect(x1,y1,x2,y2)
                   		double nHighLow=dHigh-dLow;

                    	if(dClose==dOpen)
                    	{


                        	if(dHigh==dOpen&&dLow!=dOpen)      // 帶下影平盤線
                        	{
                                pGrid->Canvas->Pen->Color=TColor(RGB(212, 212, 212));
                                pGrid->Canvas->MoveTo((Rect.left+1),(Rect.top+1));
                                pGrid->Canvas->LineTo((Rect.left+1)+nCellWidth,(Rect.top+1));
                                pGrid->Canvas->Pen->Color=TColor(RGB(212, 212, 212));
                                pGrid->Canvas->MoveTo((Rect.left+1)+nCellWidth/2,(Rect.top+1));  //nCellHeight/2
                                pGrid->Canvas->LineTo((Rect.left+1)+nCellWidth/2,(Rect.top+1)+nCellHeight);



                            }else if(dLow==dOpen&&dHigh!=dClose)             //帶上影之平盤線
                            {
                                pGrid->Canvas->Pen->Color=TColor(RGB(212, 212, 212));
                                pGrid->Canvas->MoveTo((Rect.left+1),(Rect.Bottom-1));
                                pGrid->Canvas->LineTo((Rect.left+1)+nCellWidth,(Rect.Bottom-1));
                                pGrid->Canvas->Pen->Color=TColor(RGB(212, 212, 212));
                                pGrid->Canvas->MoveTo((Rect.left+1)+nCellWidth/2,(Rect.Bottom-1));
                                pGrid->Canvas->LineTo((Rect.left+1)+nCellWidth/2,(Rect.top+1)); //

                            }else if(dHigh==dLow&&dHigh==dOpen)         //成交價=開盤價=最高價=最低價
                            {

                                pGrid->Canvas->Pen->Color=TColor(RGB(212, 212, 212));
                                pGrid->Canvas->MoveTo((Rect.left+1),(Rect.top+1)+nCellHeight/2);
                                pGrid->Canvas->LineTo((Rect.left+1)+nCellWidth,(Rect.top+1)+nCellHeight/2);

                            }else      //  十字平盤線
                            {
                                pGrid->Canvas->Pen->Color=TColor(RGB(212, 212, 212));
                                pGrid->Canvas->MoveTo((Rect.left+1)+nCellWidth/2,(Rect.top+1));
                                pGrid->Canvas->LineTo((Rect.left+1)+nCellWidth/2,(Rect.top+1)+nCellHeight);
                                pGrid->Canvas->Pen->Color=TColor(RGB(212, 212, 212));
                                pGrid->Canvas->MoveTo((Rect.left+1),(Rect.top+1)+(nCellHeight*nHighOpen/nHighLow));
                                pGrid->Canvas->LineTo((Rect.left+1)+nCellWidth,(Rect.top+1)+(nCellHeight*nHighOpen/nHighLow));
                            }
                    	}
                	}

            }else
            {

            	pGrid->Canvas->Pen->Color=TColor(RGB(212, 212, 212));
            	pGrid->Canvas->MoveTo((Rect.left+1),(Rect.top+1)+nCellHeight/2);
            	pGrid->Canvas->LineTo((Rect.left+1)+nCellWidth,(Rect.top+1)+nCellHeight/2);

            }

        }
    }


    String cellText="";
    cellText = stockStringGrid->Cells[ACol][ARow];
    pGrid->Canvas->TextOut(Rect.Left+2 , Rect.Top+2 , cellText);
    pGrid->DefaultDrawing= false;
}
//---------------------------------------------------------------------------



void __fastcall TTestViewer::CatalogComboBoxChange(TObject *Sender)
{
    multimap_Stocks.erase(multimap_Stocks.begin(), multimap_Stocks.end());
    //mp_SortStocks.erase(mp_SortStocks.begin(), mp_SortStocks.end());
    isUpButton=false;
	isDownButton=false;
	m_nNowPage=1;
    m_nPageStart=0;
    m_nPageEnd=0;
    m_nPageNumber=0;
    pageupButton->Enabled=true;
    pagedownButton->Enabled=true;
    ChooseStock();
    pageNumberLabel->Caption="1";
    stockStringGrid->Cells[3][0] = "振幅" ;
    m_nOrder=1;
}
//---------------------------------------------------------------------------





void __fastcall TTestViewer::pageupButtonClick(TObject *Sender)         //上一頁
{

    if(m_nNowPage!=0)
    {
    	m_nNowPage--;
        if(isUpButton)
        {

        	Asc();
        }
        else if(isDownButton)
        {

        	Desc();

        }else
        {
        	ChooseStock();

        }

        pageNumberLabel->Caption=IntToStr(m_nNowPage);

    }

}
//---------------------------------------------------------------------------

void __fastcall TTestViewer::pagedownButtonClick(TObject *Sender)            //下一頁
{

    if(m_nNowPage!=0&&m_nNowPage<=m_nPageNumber)
    {
    	m_nNowPage++;

        if(isUpButton)
        {

        	Asc();
        }
        else if(isDownButton)
        {

        	Desc();

        }else
        {
        	ChooseStock();

        }
        pageNumberLabel->Caption=IntToStr(m_nNowPage);

    }

}
//---------------------------------------------------------------------------


double TTestViewer:: GetUpDown(AnsiString strDeal, AnsiString strYDay)
{

     double dUpDown=0.0;
     if(atof(strDeal.c_str())!=0&&atof(strYDay.c_str())!=0)
     {
     	dUpDown= (atof(strDeal.c_str())-atof(strYDay.c_str()));   //成交價-昨收價

     }else
     {
     	dUpDown=0.0;

     }
     return dUpDown;

}

double TTestViewer:: GetLimit(AnsiString strDeal, AnsiString strYDay)
{

    double dLimit=0;

    if(atof(strDeal.c_str())!=0&&atof(strYDay.c_str())!=0)
    {
    	double dUpDown= (atof(strDeal.c_str())-atof(strYDay.c_str()));
        dLimit=dUpDown/atof(strYDay.c_str())/0.01;

   }else
   {
   		dLimit=0.0;
   }

	return dLimit;
}



//---------------------------------------------------------------------------


void TTestViewer::Desc()       //大到小
{


	const CFormat06 *myCF061 = (CFormat06*)CatalogComboBox->Items->Objects[CatalogComboBox->ItemIndex];  //取combobox 類別
    const set<short>& myStock = myCF061->GetStocks();       //取得<商品索引>
    set<short>::iterator pSortStock = myStock.begin();
    m_nStockSize = myStock.size();

    int multimap_SKSize= multimap_Stocks.size();

    int nPageRemainder = 0;     //剩餘頁數
    nPageRemainder = m_nStockSize%15;
    m_nPageNumber = multimap_SKSize/15;
    ClearStock();
    if(nPageRemainder != 0)
    {
    	                                         //有餘數狀況
    	m_nPageNumber += 1;

    }
    SettingPageButton();
    int nSize=0;
    int row = 0;
    CBasket Basket;
    multimap<double, AnsiString>::reverse_iterator pKey1  ;                         //<振幅,代號>
    for(pKey1= multimap_Stocks.rbegin();pKey1!=multimap_Stocks.rend(); ++pKey1)    //小到大MAP順序
    {

    	if( nSize >= m_nPageStart&&row< 15)
    	{
        	const CStock* myStock1 = g_pQuoteWarehouse->GetStockByNo( myCF061->GetMarketNo(), ((*pKey1).second));

            Basket.AddItem( myStock1->GetMarketNo(), myStock1->GetStockidx());
            SetDealPrice( row, myStock1);
            row++;

        }
        if(row>=15)
        {
        	break;

        }

        nSize++;

    }
    g_pQuoteCenter->RequestStocks( m_sPage, 15, Basket);


}

//---------------------------------------------------------------------------
void TTestViewer::Asc()     //小到大
{


	const CFormat06 *myCF061 = (CFormat06*)CatalogComboBox->Items->Objects[CatalogComboBox->ItemIndex];  //取combobox 類別
    const set<short>& myStock = myCF061->GetStocks();       //取得<商品索引>
    set<short>::iterator pSortStock = myStock.begin();
    m_nStockSize = myStock.size();

    int multimap_SKSize= multimap_Stocks.size();

    int nPageRemainder = 0;     //剩餘頁數
    nPageRemainder = m_nStockSize%15;
    m_nPageNumber = multimap_SKSize/15;
    ClearStock();
    if(nPageRemainder != 0)
    {   	                                      //有餘數狀況
    	m_nPageNumber += 1;

    }
    SettingPageButton();
    int nSize=0;
    int row = 0;
    CBasket Basket;
    multimap<double, AnsiString>::iterator pKey;                         //<振幅,代號>
    for(pKey= multimap_Stocks.begin();pKey!=multimap_Stocks.end(); ++pKey)    //小到大MAP順序
    {

    	if( nSize >= m_nPageStart&&row< 15)
    	{
        	const CStock* myStock1 = g_pQuoteWarehouse->GetStockByNo( myCF061->GetMarketNo(), ((*pKey).second));

            Basket.AddItem( myStock1->GetMarketNo(), myStock1->GetStockidx());
            SetDealPrice( row, myStock1);
            row++;

        }
        if(row>=15)
        {
        	break;

        }
        nSize++;

    }
    g_pQuoteCenter->RequestStocks( m_sPage, 15, Basket);



}
//---------------------------------------------------------------------------


void __fastcall TTestViewer::stockStringGridMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

    int x, y;
	stockStringGrid->MouseToCell(X, Y, x, y);
    if(m_nOrder==3){

    	m_nOrder=0;
        isUpButton=false;
		isDownButton=false;

    }

    m_nOrder++;
    if( stockStringGrid->Cells[x][y]=="振幅"||stockStringGrid->Cells[x][y] == "振幅▼"||stockStringGrid->Cells[x][y] == "振幅▲")
    {
        switch(m_nOrder)
        {
            case 1:
                if(m_nStockSize<200)
                {
                    stockStringGrid->Cells[3][0] = "振幅" ;
                    ChooseStock();

                }else
                {
                    ShowMessage("此類別暫不提供振幅排序");
                    

                }
                break;
            case 2:
                isUpButton=false;
                isDownButton=true;
                stockStringGrid->Cells[3][0] = "振幅▼" ;   //由大到小
                if(m_nStockSize<200)
                {
                    ChoseAmp();
                    Desc();

                }else
                {
                    ShowMessage("此類別暫不提供振幅排序");

                }
                break;
            case 3:
                if(m_nStockSize<200)
                {
                    isUpButton=true;
                    isDownButton=false;
                    stockStringGrid->Cells[3][0] = "振幅▲" ;  //有小到大
                    ChoseAmp();
                    Asc();
                }else
                {
                    ShowMessage("此類別暫不提供振幅排序");

                }
                break;


        }
      }
}
//---------------------------------------------------------------------------










