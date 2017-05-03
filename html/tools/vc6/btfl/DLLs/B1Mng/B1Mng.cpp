// B1Mng.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "B1Mng.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CB1MngApp

BEGIN_MESSAGE_MAP(CB1MngApp, CWinApp)
	//{{AFX_MSG_MAP(CB1MngApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CB1MngApp construction

CB1MngApp::CB1MngApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
extern "C" BLSTATUS __stdcall OnBlApi(HWND h,UINT m, WPARAM w, LPARAM l)
{	
	BLSTATUS	r = BL_STATUS_NOT_SUPPORT_INTERFACE; 	  
	static CMyLib	o(h);
	r =o.plBlApi(h,m,w,l);  
	return r;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CB1MngApp object

CB1MngApp theApp;
