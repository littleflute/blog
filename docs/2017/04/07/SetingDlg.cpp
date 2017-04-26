//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：SetingDlg.h 类CSetingDlg的执行文件

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
#include "resource.h"
#include "ScreenCap.h"
#include "FBCommDlg.h"
#include <shlobj.h>
#include "SetingDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSetingDlg::CSetingDlg()
{
}

CSetingDlg::~CSetingDlg()
{
	if(m_pas)
		delete m_pas;
}
//////////////////////////////////////////////////////////////////////
LRESULT CSetingDlg::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lRet = 0;

	if(msg == WM_PAINT)
	{
		lRet = CModalDlg::WindowProc(msg,wParam,lParam);

		if(m_pas == NULL)
			return lRet;

		DrawColorRect();

		return lRet;
	}
	else if(msg == WM_LBUTTONDBLCLK)
	{
		lRet = CModalDlg::WindowProc(msg,wParam,lParam);

		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		OnLButtonDblclk(pt);

		return lRet;
	}
	else if(msg == WM_DRAWITEM)
	{
		HWND hwnd = GetDlgItem(m_hWnd,IDC_SELDIR);
		if((UINT) wParam == IDC_SELDIR ||
			(UINT) wParam == IDC_SELBKFILE)
		{
			LPDRAWITEMSTRUCT pds = (LPDRAWITEMSTRUCT)lParam;

			COLORREF clr1 = GetSysColor(COLOR_3DSHADOW);
			COLORREF clr2 = GetSysColor(COLOR_3DHILIGHT);
			UINT state = pds->itemState;
			state &= BST_CHECKED;
			if(state & ODS_SELECTED)
				Draw3DRect(pds->hDC,&pds->rcItem,clr1,clr2,1);
			else
				Draw3DRect(pds->hDC,&pds->rcItem,clr2,clr1,1);

			HICON hico = LoadIcon(GetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON2));
			DrawIconEx(pds->hDC,pds->rcItem.left+1,pds->rcItem.top+1,hico,
					16,16,0,NULL,DI_NORMAL);

			return 0;
		}
	}

	return CModalDlg::WindowProc(msg,wParam,lParam);
}
//////////////////////////////////////////////////////////////////////
void CSetingDlg::OnInitDialog()
{
	HWND hwnd;
	CMainWnd* pFrame = (CMainWnd*)GetApp()->m_pMainWnd;
	m_pas = new APP_SETINGS;

	if(!pFrame || !m_pas)
		EndDialog(m_hWnd,IDCANCEL);

	memcpy(m_pas,pFrame->GetSetings(),sizeof(APP_SETINGS));

	if(m_pas->nStartMode == 0)
		CheckRadioButton(m_hWnd,IDC_GENERAL,IDC_TRAYICON,IDC_GENERAL);
	else
		CheckRadioButton(m_hWnd,IDC_GENERAL,IDC_TRAYICON,IDC_TRAYICON);

	if(m_pas->nToolBarBackMod == 0)
		CheckRadioButton(m_hWnd,IDC_TBK_NON,IDC_TBK_BITMAP,IDC_TBK_NON);
	else if(m_pas->nToolBarBackMod == 1)
		CheckRadioButton(m_hWnd,IDC_TBK_NON,IDC_TBK_BITMAP,IDC_TBK_GRAD);
	else
		CheckRadioButton(m_hWnd,IDC_TBK_NON,IDC_TBK_BITMAP,IDC_TBK_BITMAP);

	if(m_pas->nDefaultFmt == 0)
		CheckRadioButton(m_hWnd,IDC_RADIO_BMP,IDC_RADIO_GIF,IDC_RADIO_BMP);
	else if(m_pas->nDefaultFmt == 1)
		CheckRadioButton(m_hWnd,IDC_RADIO_BMP,IDC_RADIO_GIF,IDC_RADIO_JPG);
	else
		CheckRadioButton(m_hWnd,IDC_RADIO_BMP,IDC_RADIO_GIF,IDC_RADIO_GIF);
	if(GetApp()->GetVersion() == 0)//如果是演示版
	{
		hwnd = GetDlgItem(m_hWnd,IDC_RADIO_BMP);
		EnableWindow(hwnd,FALSE);
		hwnd = GetDlgItem(m_hWnd,IDC_RADIO_JPG);
		EnableWindow(hwnd,FALSE);
		hwnd = GetDlgItem(m_hWnd,IDC_RADIO_GIF);
		EnableWindow(hwnd,FALSE);
	}

	if(m_pas->bAutoShowWnd == FALSE)
		CheckDlgButton(m_hWnd,IDC_CHECK_AUTOSHOW,BST_CHECKED);

	UINT mod = 0;
	if(m_pas->uHotkeyMod & MOD_ALT)
	{
		CheckDlgButton(m_hWnd,IDC_CHECK_ALT,BST_CHECKED);
		mod |= HOTKEYF_ALT;
	}
	if(m_pas->uHotkeyMod & MOD_SHIFT)
	{
		CheckDlgButton(m_hWnd,IDC_CHECK_SHIFT,BST_CHECKED);
		mod |= HOTKEYF_SHIFT;
	}
	if(m_pas->uHotkeyMod & MOD_CONTROL)
	{
		CheckDlgButton(m_hWnd,IDC_CHECK_CTRL,BST_CHECKED);
		mod |= HOTKEYF_CONTROL;
	}

	hwnd = GetDlgItem(m_hWnd,IDC_HOTKEY1);
	SendMessage(hwnd,HKM_SETHOTKEY,MAKEWORD(m_pas->chKey,mod),0);
	SendMessage(hwnd,HKM_SETRULES,HKCOMB_NONE,MAKELPARAM(mod,0));

	hwnd = GetDlgItem(m_hWnd,IDC_EDIT_DEFDIR);
	SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)pFrame->m_strDefDir);
	lstrcpy(m_strDefDir,pFrame->m_strDefDir);

	hwnd = GetDlgItem(m_hWnd,IDC_EDIT_BKFILE);
	SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)pFrame->m_strBackFile);
	if(m_pas->nToolBarBackMod != 2)
		EnableWindow(hwnd,FALSE);
	lstrcpy(m_strBackFile,pFrame->m_strBackFile);

	char str[4];
	if(m_pas->nGradStyle > 3)
		m_pas->nGradStyle = 3;
	ltoa(m_pas->nGradStyle,str,10);
	hwnd = GetDlgItem(m_hWnd,IDC_EDIT_STYLE);
	SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)str);
	if(m_pas->nToolBarBackMod != 1)
		EnableWindow(hwnd,FALSE);
	if(m_pas->nToolBarBackMod != 2)
	{
		hwnd =  GetDlgItem(m_hWnd,IDC_SELBKFILE);
		EnableWindow(hwnd,FALSE);
	}

	POINT pt;
	hwnd = GetDlgItem(m_hWnd,IDC_STATIC1);
	GetWindowRect(hwnd,&rc1);
	pt.x = rc1.right;
	pt.y = rc1.top;
	ScreenToClient(m_hWnd,&pt);
	rc1.left = pt.x;
	rc1.right = rc1.left + rc1.bottom - rc1.top;
	rc1.top = pt.y;
	rc1.bottom = rc1.top + rc1.right - rc1.left;

	hwnd = GetDlgItem(m_hWnd,IDC_STATIC2);
	GetWindowRect(hwnd,&rc2);
	pt.x = rc2.right;
	pt.y = rc2.top;
	ScreenToClient(m_hWnd,&pt);
	rc2.left = pt.x;
	rc2.right = rc2.left + rc2.bottom - rc2.top;
	rc2.top = pt.y;
	rc2.bottom = rc2.top + rc2.right - rc2.left;

	hwnd = GetDlgItem(m_hWnd,IDC_STATIC3);
	GetWindowRect(hwnd,&rc3);
	pt.x = rc3.right;
	pt.y = rc3.top;
	ScreenToClient(m_hWnd,&pt);
	rc3.left = pt.x;
	rc3.right = rc3.left + rc3.bottom - rc3.top;
	rc3.top = pt.y;
	rc3.bottom = rc3.top + rc3.right - rc3.left;

	CenterWindow(m_hWnd);
}
//////////////////////////////////////////////////////////////////////
void CSetingDlg::DrawColorRect()
{
	HDC hdc = GetDC(m_hWnd);

	if(m_pas->nToolBarBackMod == 1)
	{
		FillSolidRect(hdc,&rc1,m_pas->clrGradLo);
		FillSolidRect(hdc,&rc2,m_pas->clrGradHi);
	}
	else
	{
		COLORREF clr = GetSysColor(COLOR_BTNFACE);
		FillSolidRect(hdc,&rc1,clr);
		FillSolidRect(hdc,&rc2,clr);
	}
	FillSolidRect(hdc,&rc3,m_pas->clrViewBack);

	COLORREF clr1 = GetSysColor(COLOR_3DSHADOW);
	COLORREF clr2 = GetSysColor(COLOR_3DHILIGHT);

	Draw3DRect(hdc,&rc1,clr1,clr2,1);
	Draw3DRect(hdc,&rc2,clr1,clr2,1);
	Draw3DRect(hdc,&rc3,clr1,clr2,1);

	ReleaseDC(m_hWnd,hdc);
}
//////////////////////////////////////////////////////////////////////
void CSetingDlg::OnLButtonDblclk(POINT& pt)
{
	int flag = 0;
	COLORREF clr;

	if(PtInRect(&rc1,pt))
	{
		flag = 1;
		clr = m_pas->clrGradLo;
	}
	else if(PtInRect(&rc2,pt))
	{
		flag = 2;
		clr = m_pas->clrGradHi;
	}
	else if(PtInRect(&rc3,pt))
	{
		flag = 3;
		clr = m_pas->clrViewBack;
	}

	if(flag == 0)
		return;
	if((m_pas->nToolBarBackMod != 1) && (flag != 3))
		return;

	CColorDlg dlg;
	dlg.Create(this,clr);

	if(dlg.DoModal() != IDOK)
		return;

	if(flag == 1)
		m_pas->clrGradLo = dlg.GetSelColor();
	else if(flag == 2)
		m_pas->clrGradHi = dlg.GetSelColor();
	else if(flag == 3)
		m_pas->clrViewBack = dlg.GetSelColor();

	DrawColorRect();
}
//////////////////////////////////////////////////////////////////////
void CSetingDlg::OnCommand(UINT uCmdID,UINT code)
{
	switch(uCmdID)
	{
	case IDC_SELDIR:
		OnSelDir();
		break;
	case IDC_SELBKFILE:
		OnSelBkFile();
		break;
	case IDOK:
		OnOk();
		break;
	default:
		break;
	}

	if(code == BN_CLICKED)
		OnBtnClicked(uCmdID);
}
//////////////////////////////////////////////////////////////////////
void CSetingDlg::OnSelDir()
{
    BROWSEINFO bi;
    LPITEMIDLIST pidlDesktop;
    LPITEMIDLIST pidlBrowse;

    if(SHGetSpecialFolderLocation(m_hWnd, CSIDL_DRIVES, &pidlDesktop)!=NOERROR)
        return;

    bi.hwndOwner = m_hWnd;
    bi.pidlRoot = pidlDesktop;
    bi.pszDisplayName = m_strDefDir;

    bi.lpszTitle = "请选择文件夹：";
    bi.ulFlags = BIF_RETURNONLYFSDIRS;
    bi.lpfn = NULL;
    bi.lParam = 0;

    pidlBrowse = SHBrowseForFolder(&bi);

    if (pidlBrowse != NULL)
    {
        SHGetPathFromIDList(pidlBrowse, m_strDefDir);
		HWND hwnd = GetDlgItem(m_hWnd,IDC_EDIT_DEFDIR);
		SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)m_strDefDir);
    }
}
//////////////////////////////////////////////////////////////////////
void CSetingDlg::OnBtnClicked(UINT uID)
{
	HWND hwnd;

	switch(uID)
	{
	case IDC_GENERAL:
		m_pas->nStartMode = 0;
		break;
	case IDC_TRAYICON:
		m_pas->nStartMode = 1;
		break;
	case IDC_TBK_NON:
		m_pas->nToolBarBackMod = 0;
		CheckRadioButton(m_hWnd,IDC_TBK_NON,IDC_TBK_BITMAP,uID);
		hwnd = GetDlgItem(m_hWnd,IDC_EDIT_STYLE);
		EnableWindow(hwnd,FALSE);
		hwnd = GetDlgItem(m_hWnd,IDC_EDIT_BKFILE);
		EnableWindow(hwnd,FALSE);
		hwnd = GetDlgItem(m_hWnd,IDC_SELBKFILE);
		EnableWindow(hwnd,FALSE);
		DrawColorRect();
		break;
	case IDC_TBK_GRAD:
		m_pas->nToolBarBackMod = 1;
		CheckRadioButton(m_hWnd,IDC_TBK_NON,IDC_TBK_BITMAP,uID);
		hwnd = GetDlgItem(m_hWnd,IDC_EDIT_STYLE);
		EnableWindow(hwnd,TRUE);
		hwnd = GetDlgItem(m_hWnd,IDC_EDIT_BKFILE);
		EnableWindow(hwnd,FALSE);
		hwnd = GetDlgItem(m_hWnd,IDC_SELBKFILE);
		EnableWindow(hwnd,FALSE);
		DrawColorRect();
		break;
	case IDC_TBK_BITMAP:
		m_pas->nToolBarBackMod = 2;
		CheckRadioButton(m_hWnd,IDC_TBK_NON,IDC_TBK_BITMAP,uID);
		hwnd = GetDlgItem(m_hWnd,IDC_EDIT_STYLE);
		EnableWindow(hwnd,FALSE);
		hwnd = GetDlgItem(m_hWnd,IDC_EDIT_BKFILE);
		EnableWindow(hwnd,TRUE);
		hwnd = GetDlgItem(m_hWnd,IDC_SELBKFILE);
		EnableWindow(hwnd,TRUE);
		DrawColorRect();
		break;
	case IDC_RADIO_BMP:
		m_pas->nDefaultFmt = 0;
		CheckRadioButton(m_hWnd,IDC_RADIO_BMP,IDC_RADIO_GIF,uID);
		break;
	case IDC_RADIO_JPG:
		m_pas->nDefaultFmt = 1;
		CheckRadioButton(m_hWnd,IDC_RADIO_BMP,IDC_RADIO_GIF,uID);
		break;
	case IDC_RADIO_GIF:
		m_pas->nDefaultFmt = 2;
		CheckRadioButton(m_hWnd,IDC_RADIO_BMP,IDC_RADIO_GIF,uID);
		break;
	case IDC_CHECK_ALT:
	case IDC_CHECK_SHIFT:
	case IDC_CHECK_CTRL:
		{
			UINT mod = 0;
			hwnd = GetDlgItem(m_hWnd,IDC_CHECK_ALT);
			if(SendMessage(hwnd,BM_GETSTATE,0,0) & BST_CHECKED)
				mod |= HOTKEYF_ALT;
			hwnd = GetDlgItem(m_hWnd,IDC_CHECK_SHIFT);
			if(SendMessage(hwnd,BM_GETSTATE,0,0) & BST_CHECKED)
				mod |= HOTKEYF_SHIFT;
			hwnd = GetDlgItem(m_hWnd,IDC_CHECK_CTRL);
			if(SendMessage(hwnd,BM_GETSTATE,0,0) & BST_CHECKED)
				mod |= HOTKEYF_CONTROL;

			hwnd = GetDlgItem(m_hWnd,IDC_HOTKEY1);
			BYTE key = LOBYTE(SendMessage(hwnd,HKM_GETHOTKEY,0,0));
			SendMessage(hwnd,HKM_SETHOTKEY,MAKEWORD(key,mod),0);
			SendMessage(hwnd,HKM_SETRULES,HKCOMB_NONE,MAKELPARAM(mod,0));
		}
		break;
	case IDC_CHECK_AUTOSHOW:
		hwnd = GetDlgItem(m_hWnd,IDC_CHECK_AUTOSHOW);
		if(SendMessage(hwnd,BM_GETSTATE,0,0) & BST_CHECKED)
			m_pas->bAutoShowWnd = FALSE;
		else
			m_pas->bAutoShowWnd = TRUE;
		break;
	}
}
//////////////////////////////////////////////////////////////////////
void CSetingDlg::OnOk()
{
	HWND hwnd;

	if(m_pas->nToolBarBackMod == 1)
	{
		char str[2];
		hwnd = GetDlgItem(m_hWnd,IDC_EDIT_STYLE);
		SendMessage(hwnd,WM_GETTEXT,2,(LPARAM)str);
		if((str[0] > 0x33) || (str[0] < 0x30))
			str[0] = 0x33;

		str[0] -= 0x30;
		m_pas->nGradStyle = (int)str[0];
	}

	hwnd = GetDlgItem(m_hWnd,IDC_HOTKEY1);
	WORD hotkey = (WORD)SendMessage(hwnd,HKM_GETHOTKEY,0,0);
	m_pas->chKey = LOBYTE(hotkey);
	BYTE mod = HIBYTE(hotkey);
	m_pas->uHotkeyMod = 0;
	if(mod & HOTKEYF_ALT)
		m_pas->uHotkeyMod |= MOD_ALT;
	if(mod & HOTKEYF_SHIFT)
		m_pas->uHotkeyMod |= MOD_SHIFT;
	if(mod & HOTKEYF_CONTROL)
		m_pas->uHotkeyMod |= MOD_CONTROL;
}
//////////////////////////////////////////////////////////////////////
void CSetingDlg::OnSelBkFile()
{
	CFileDlg dlg;
	dlg.Create(this,"位图文件\0*.bmp\0",TRUE);
	if(dlg.DoModal() == IDOK)
	{
		lstrcpy(m_strBackFile,dlg.GetFileFullPath());
		HWND hwnd = GetDlgItem(m_hWnd,IDC_EDIT_BKFILE);
		SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)m_strBackFile);
	}
}