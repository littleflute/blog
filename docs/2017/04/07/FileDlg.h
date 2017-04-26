//Download by http://www.NewXing.com
// FileDlg.h: interface for the CFileDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEDLG_H__0C33BD20_BD5A_11D3_B431_8B2F70591D97__INCLUDED_)
#define AFX_FILEDLG_H__0C33BD20_BD5A_11D3_B431_8B2F70591D97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <commdlg.h>

#define OFM_GETBITMAP		WM_USER+510
//////////////////////////////////////////////////////////////////////////////////
class CFileDlg  
{
public:
	CFileDlg();
	void SetTemplate(HINSTANCE hInst,HWND hOwner,UINT nTemplateID,BOOL bHook);
	virtual ~CFileDlg();

	OPENFILENAME ofn;
	char szFile[MAX_PATH];

	BOOL DoModal(BOOL);
	LPSTR GetFilePath();

protected:
	static char name[64];
	static HDC hBmpDC;
	static HWND hMainWnd;
	static LONG picWidth;
	static LONG picHeight;
	static RECT rcPic;
	static UINT APIENTRY OFNHookProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam);
};

#endif // !defined(AFX_FILEDLG_H__0C33BD20_BD5A_11D3_B431_8B2F70591D97__INCLUDED_)
