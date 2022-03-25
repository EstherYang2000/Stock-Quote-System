//---------------------------------------------------------------------------


#ifndef TestViewH
#define TestViewH


//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "ICommand.h"
#include "IObserver.h"
#include "IQuote.h"
#include "Resources.h"
#include "DllMain.h"
#include "Macro.h"
#include "IQuoteWarehouse.h"
#include "IQuoteCenter.h"
#include <System.hpp>
#include <Grids.hpp>
#include <ActnList.hpp>




class TTestViewer : public TFrame,public ICommand, public IObserver, public IQuote
{
__published:	// IDE-managed Components
    TStringGrid *stockStringGrid;
    TComboBox *CatalogComboBox;
    TButton *pagedownButton;
    TButton *pageupButton;
    TLabel *pageNumberLabel;
    void __fastcall AfterConstruction( );
    void __fastcall On0x10(TMessage &Msg);
    void __fastcall On0x30(TMessage &Msg);
    void __fastcall On0x31(TMessage &Msg);


    void __fastcall OnRESET(TMessage &Msg);
    void __fastcall ChooseCatalog();
    void __fastcall stockStringGridDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall CatalogComboBoxChange(TObject *Sender);
    void __fastcall pageupButtonClick(TObject *Sender);
    void __fastcall pagedownButtonClick(TObject *Sender);
	void __fastcall stockStringGridMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
	
private:	// User declarations

        
        short m_sPage;
        multimap<double, AnsiString>multimap_Stocks;    //商品振幅/股票代號 小到大
        set<short> orderStock;//存股票代碼 拿來找商品
        char m_cMarketNo;
        int m_nStockSize;
        int m_nNowPage;
        int m_nPageStart;
        int m_nPageEnd;
        int m_nPageNumber;
        bool isUpButton;
        bool isDownButton;
        int m_nOrder;
        vector<const CStock*>m_vPageStock;   //看商品數量
        double GetUpDown(AnsiString Deal, AnsiString YDay);
        double GetLimit(AnsiString anUpDown, AnsiString anYDay);
        void SetDealPrice(int norder,const CStock* Stock ) ;
        void ClearMap();
        void ClearStock();
        void SettingPageButton();
		void PuttingSortBasket(const CBasket& Basket);
        void Desc();
        void Asc();
        void ChoseAmp();
        CHttpRequestCenter m_HttpRequestCenter;
        
protected:
            // Derived from Command
            void GetInterface(Interface Inf, void*& pInf);
            void Execute( unsigned int unMsg, int nParam1, int nParam2);
            void AddExtend( ICommand* pCommand);
            int GetID();
            AnsiString GetName();
            CHotKeys* GetHotKeys();
            void SetHotKeys( const CHotKeys& Keys);

            // Derived from Observer
            void QuoteUpdated(int nSubject, int nParam1, int nParam2);

            // Derived from Quote
            void SetStock( const CStock& Stock);
            void SetPageNo( short sPageNo);
            void SetStockGraphic( const vector<int>& Graphics);
            short GetPageNo();
            void  SettingStringgrid();
            void ChooseStock();

     BEGIN_MESSAGE_MAP
			VCL_MESSAGE_HANDLER(  WM_USER+0x10,  TMessage, On0x10)
            VCL_MESSAGE_HANDLER(  WM_USER+0x30,  TMessage, On0x30)
            VCL_MESSAGE_HANDLER(  WM_USER+0x31,  TMessage, On0x31)
            VCL_MESSAGE_HANDLER( WM_USER+RESET, TMessage, OnRESET)




        END_MESSAGE_MAP(TFrame)
public:		// User declarations
    __fastcall TTestViewer(TComponent* Owner);


};
//---------------------------------------------------------------------------
extern PACKAGE TTestViewer *TestViewer;
//---------------------------------------------------------------------------
#endif
