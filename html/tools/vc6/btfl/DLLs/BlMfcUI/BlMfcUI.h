// BlMfcUI.h : main header file for the BLMFCUI DLL
//

#if !defined(AFX_BLMFCUI_H__50320FE4_98EA_473F_861A_2C1B4226C6C2__INCLUDED_)
#define AFX_BLMFCUI_H__50320FE4_98EA_473F_861A_2C1B4226C6C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBlMfcUIApp
// See BlMfcUI.cpp for the implementation of this class
//

class CBlMfcUIApp : public CWinApp
{
public:
	CBlMfcUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlMfcUIApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CBlMfcUIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLMFCUI_H__50320FE4_98EA_473F_861A_2C1B4226C6C2__INCLUDED_)
