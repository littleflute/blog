//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBDialog.h

	版权：Firebird Software Workroom 保留

	声明：本源程序的版权受《中华人民共和国著作权法》以及其
		  它相关法律和条约的保护。任何有机会得到本源程序的
		  个人和机构，未经作者明确授权，不得将本源程序用于
		  任何商业目的(直接的或间接的)。对于非商业目的的使
		  用 (包括复制、传播、编译和修改)， 原则上没有特别
		  的限制条款，但请在相关文档中说明其来源，并尊重原
		  作者的署名权。

	编写：秦传安(chings)	2000.4

	联络：Tel：(0792)6323086	E_mail：chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include "fclstd.h"
#include "FBDialog.h"
//////////////////////////////////////////////////////////////////////
BOOL CALLBACK FBDlgProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_INITDIALOG)
	{
		CModalDlg* pDlg = (CModalDlg*)lParam;
		if(!pDlg)return 0;

		pDlg->m_hWnd = hdlg;
		CFBWnd::m_pWndList->Add(pDlg);

		return pDlg->WindowProc(msg,wParam,lParam);
	}

	CModalDlg* pDlg = (CModalDlg*)CFBWnd::FromHandle(hdlg);
	if(pDlg == NULL)
		return 0;
	else
		return pDlg->WindowProc(msg,wParam,lParam);
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModalDlg::CModalDlg()
{
	m_pszTemplate = NULL;
}

CModalDlg::~CModalDlg()
{

}
//////////////////////////////////////////////////////////////////////
BOOL CModalDlg::Create(CFBWnd* pParent,UINT idTemplate)
{
	m_pOwner = pParent;

	m_pszTemplate = MAKEINTRESOURCE(idTemplate);

	return TRUE;
}
//////////////////////////////////////////////////////////////////////
int CModalDlg::DoModal()
{
	HINSTANCE hInst;

	if(m_pOwner)
		hInst = m_pOwner->GetInstance();
	else
		hInst = GetModuleHandle(NULL);

	return DialogBoxParam(hInst,m_pszTemplate,
		m_pOwner? m_pOwner->m_hWnd : NULL,
		(DLGPROC)FBDlgProc,(LPARAM)this);
}
//////////////////////////////////////////////////////////////////////
LRESULT CModalDlg::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lRet = 0;

	if(msg == WM_INITDIALOG)
	{
		OnInitDialog();
		lRet = 1;
	}
	else if(msg == WM_COMMAND)
	{
		OnCommand(LOWORD(wParam),HIWORD(wParam));
		if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			EndDialog(m_hWnd,LOWORD(wParam));
	}
	else if(msg == WM_NOTIFY)
		OnNotify((LPNMHDR)lParam,lRet);

	return lRet;
}