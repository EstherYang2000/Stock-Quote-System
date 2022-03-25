//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused
#pragma link "SK2004v2.lib"
		
#include "TestView.h"
#include "DllMain.h"
#include "Macro.h"

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
    return 1;
}
//---------------------------------------------------------------------------

DEFINE_CENTERS()

ICommand* __stdcall GetInstance( TWinControl* pParent, TCenters* Centers, bool bMDI)
{
    try
    {
    
        g_pQuoteWarehouse = Centers->GetQuoteWarehouse();  // 取得QuoteWarehouse的實體
        g_pQuoteCenter = Centers->GetQuoteCenter();
        g_pConfigCenter= Centers->GetConfigCenter();         //
        TTestViewer* pFrame = new TTestViewer(pParent);
        pFrame->Align = alClient;
        pFrame->Parent = pParent;
        return pFrame;

    }
    catch( Exception& e)
    {
        return NULL;
    }
}

void __stdcall FreeInstance()
{
}
		
int __stdcall GetID()
{
    return 9000; // 該DLL的ID編號
}
		
char* __stdcall GetCaption()
{
    return "Test"; // 該DLL的名稱
}
		
char* __stdcall GetDllVersion()
{
    return "2.07.01";
}                   

TCapability __stdcall GetCapability()
{
    return abComponent | abQuote;
    //abComponent 表示可出現在組合視窗選項中
    //abQuote            表示此項目有報價功能
}
                