//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBCommDlg.cpp

	版权：Firebird Software Workroom 保留

	声明：本源程序的版权受《中华人民共和国著作权法》以及其
		  它相关法律和条约的保护。任何有机会得到本源程序的
		  个人和机构，未经作者明确授权，不得将本源程序用于
		  任何商业目的(直接的或间接的)。对于非商业目的的使
		  用 (包括复制、传播、编译和修改)， 原则上没有特别
		  的限制条款，但请在相关文档中说明其来源，并尊重原
		  作者的署名权。

	编写：秦传安(chings)	2000.5

	联络：Tel：(0792)6323086	E_mail：chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include "fclstd.h"
#include <cderr.h>
#include "FBCommDlg.h"
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		class CFileDlg

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
CFileDlg::CFileDlg()
{
	memset(&m_OpenData,0,sizeof(OPENFILENAME));

	m_OpenData.lStructSize = sizeof(OPENFILENAME);
	m_OpenData.lpfnHook = FileDlgProc;
	m_OpenData.Flags = OFN_EXPLORER|OFN_ENABLEHOOK;
	m_OpenData.lpstrFile = new char[MAX_PATH];
	m_OpenData.lpstrFile[0] = '\0';
	m_OpenData.nMaxFile = MAX_PATH;
	m_OpenData.lpstrFileTitle = new char[_MAX_FNAME];
	m_OpenData.nMaxFileTitle = _MAX_FNAME;
	m_OpenData.lCustData = (DWORD)this;
}

CFileDlg::~CFileDlg()
{
	if(m_OpenData.lpstrFile)
		delete [] m_OpenData.lpstrFile;
	if(m_OpenData.lpstrFileTitle)
		delete [] m_OpenData.lpstrFileTitle;
}
//#####################################################################
UINT APIENTRY CFileDlg::FileDlgProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_INITDIALOG)
	{
		LPOPENFILENAME pofn = (LPOPENFILENAME)lParam;
		CFileDlg* pDlg = (CFileDlg*)pofn->lCustData;

		if(!pDlg)return 0;

		pDlg->m_hWnd = hdlg;
		m_pWndList->Add(pDlg);

		CenterWindow(GetParent(hdlg));
		return pDlg->WindowProc(msg,wParam,lParam);
	}

	CFileDlg* pDlg = (CFileDlg*)CFBWnd::FromHandle(hdlg);
	if(pDlg == NULL)
		return 0;
	else
		return pDlg->WindowProc(msg,wParam,lParam);
}
//#####################################################################
BOOL CFileDlg::Create(CFBWnd		*pOwner,
					  LPTSTR		szFilter,
					  BOOL			bOpen,
					  DWORD			Flags,
					  LPTSTR		szTemplate)
{
	m_bFlag = bOpen;
	m_pOwner = pOwner;
	if(pOwner)
		m_OpenData.hwndOwner = pOwner->m_hWnd;

	m_OpenData.Flags |= Flags;
	m_OpenData.lpstrFilter = szFilter;

	if(szTemplate)
	{
		m_OpenData.Flags |= OFN_ENABLETEMPLATE;
		m_OpenData.lpTemplateName = szTemplate;
		if(pOwner)
			m_OpenData.hInstance = pOwner->GetInstance();
		else
			m_OpenData.hInstance = GetModuleHandle(NULL);
	}

	return TRUE;
}
//#####################################################################
int CFileDlg::DoModal()
{
	BOOL bRet;

	if(m_bFlag)
		bRet = GetOpenFileName(&m_OpenData);
	else
		bRet = GetSaveFileName(&m_OpenData);

	if(bRet)
		return IDOK;

	return IDCANCEL;
}


/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		class CColorDlg

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
CColorDlg::CColorDlg()
{
	memset(&m_ccl,0,sizeof(CHOOSECOLOR));
	m_ccl.lStructSize = sizeof(CHOOSECOLOR);
	m_ccl.lpCustColors = new COLORREF[16];
	m_ccl.lpfnHook = ColorDlgProc;
	m_ccl.Flags = CC_RGBINIT|CC_ENABLEHOOK;
	m_ccl.lCustData = (LPARAM)this;
}

CColorDlg::~CColorDlg()
{
	if(m_ccl.lpCustColors)
		delete [] m_ccl.lpCustColors;
}
//#####################################################################
UINT APIENTRY CColorDlg::ColorDlgProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_INITDIALOG)
	{
		LPCHOOSECOLOR pccl = (LPCHOOSECOLOR)lParam;
		CColorDlg* pDlg = (CColorDlg*)pccl->lCustData;

		if(!pDlg)return 0;

		pDlg->m_hWnd = hdlg;
		m_pWndList->Add(pDlg);

		CenterWindow(hdlg);
		return pDlg->WindowProc(msg,wParam,lParam);
	}

	CColorDlg* pDlg = (CColorDlg*)CFBWnd::FromHandle(hdlg);
	if(pDlg == NULL)
		return 0;
	else
		return pDlg->WindowProc(msg,wParam,lParam);
}
//#####################################################################
BOOL CColorDlg::Create(CFBWnd* pOwner,
					   COLORREF rgbInit,
					   DWORD Flags,
				       LPTSTR szTemplate)
{
	m_pOwner = pOwner;
	if(pOwner)
		m_ccl.hwndOwner = pOwner->m_hWnd;

	m_ccl.Flags |= Flags;
	m_ccl.rgbResult = rgbInit;

	if(szTemplate)
	{
		m_ccl.lpTemplateName = szTemplate;
		m_ccl.Flags |= CC_ENABLETEMPLATE;
		if(pOwner)
			m_ccl.hInstance = (HWND)pOwner->GetInstance();
		else
			m_ccl.hInstance = (HWND)GetModuleHandle(NULL);
	}

	return TRUE;
}
//#####################################################################
int CColorDlg::DoModal()
{
	if(ChooseColor(&m_ccl))
		return IDOK;

	return IDCANCEL;
}

/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		class CPrintDlg

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
CPrintDlg::CPrintDlg()
{
	memset(&m_ptd,0,sizeof(PRINTDLG));

	m_ptd.lStructSize = sizeof(PRINTDLG);
	m_ptd.lCustData = (DWORD)this;
	m_ptd.Flags = PD_ENABLEPRINTHOOK | PD_PAGENUMS;
	m_ptd.lpfnPrintHook = PrintDlgProc;
	m_ptd.nFromPage = 1;
	m_ptd.nToPage = 1;
	m_ptd.nMinPage = 1;
	m_ptd.nMaxPage = 1;
}

CPrintDlg::~CPrintDlg()
{
}
//#####################################################################
UINT APIENTRY CPrintDlg::PrintDlgProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_INITDIALOG)
	{
		LPPRINTDLG ppd = (LPPRINTDLG)lParam;
		CPrintDlg* pDlg = (CPrintDlg*)ppd->lCustData;

		if(!pDlg)return 0;

		pDlg->m_hWnd = hdlg;
		m_pWndList->Add(pDlg);

		CenterWindow(hdlg);
		return pDlg->WindowProc(msg,wParam,lParam);
	}

	CPrintDlg* pDlg = (CPrintDlg*)CFBWnd::FromHandle(hdlg);
	if(pDlg == NULL)
		return 0;
	else
		return pDlg->WindowProc(msg,wParam,lParam);
}
//#####################################################################
BOOL CPrintDlg::Create(CFBWnd* pOwner,DWORD Flags,LPTSTR szTemplate)
{
	m_pOwner = pOwner;
	if(pOwner)
		m_ptd.hwndOwner = pOwner->m_hWnd;

	m_ptd.Flags |= Flags;

	if(szTemplate)
	{
		m_ptd.lpPrintTemplateName = szTemplate;
		m_ptd.Flags |= CC_ENABLETEMPLATE;
		if(pOwner)
			m_ptd.hInstance = pOwner->GetInstance();
		else
			m_ptd.hInstance = GetModuleHandle(NULL);
	}

	return TRUE;
}
//#####################################################################
int CPrintDlg::DoModal()
{
	if(PrintDlg(&m_ptd))
		return IDOK;

	if(CommDlgExtendedError() == PDERR_NODEVICES)
		MessageBox(NULL,"系统没有找到任何打印机，请检查打印机是否正确安装。","错误",MB_OK|MB_ICONWARNING);
	return IDCANCEL;
}
