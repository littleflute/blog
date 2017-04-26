//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBCtrls.cpp

	��Ȩ��Firebird Software Workroom

	��������Դ����İ�Ȩ�ܡ��л����񹲺͹�����Ȩ�����Լ���
		  ����ط��ɺ���Լ�ı������κ��л���õ���Դ�����
		  ���˺ͻ�����δ��������ȷ��Ȩ�����ý���Դ��������
		  �κ���ҵĿ��(ֱ�ӵĻ��ӵ�)�����ڷ���ҵĿ�ĵ�ʹ
		  �� (�������ơ�������������޸�)�� ԭ����û���ر�
		  �������������������ĵ���˵������Դ��������ԭ
		  ���ߵ�����Ȩ��

	��д���ش���(chings)	1999.12 - 2000.4

	���磺Tel��(0792)6323086	E_mail��chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include "fclstd.h"
#include "FBCtrls.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//######################################################################
//	class CFBToolBar
//	������
//###################################################################
#define RT_TOOLBAR  MAKEINTRESOURCE(241)

struct TOOLBAR_DATA
{
	WORD wVersion;
	WORD wWidth;
	WORD wHeight;
	WORD wItemCount;

	WORD* items()
		{ return (WORD*)(this+1); }
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFBToolBar::CFBToolBar()
{
	m_nHotItem = -1;
}

CFBToolBar::~CFBToolBar()
{
}
//////////////////////////////////////////////////////////////////////////////
//��������
BOOL CFBToolBar::Create(CFBWnd* pParent,UINT nStyle,UINT nID)
{
	if(!pParent)return FALSE;

	InitCommonControls();

	nStyle |= WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS |
			  TBSTYLE_BUTTON | TBSTYLE_TOOLTIPS|TBSTYLE_FLAT|TBSTYLE_AUTOSIZE|TBSTYLE_TRANSPARENT|
			  CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;

	BOOL bRet  = CFBWnd::Create(TOOLBARCLASSNAME,
						NULL,
						pParent->GetInstance(),
						pParent,
						nStyle,
						NULL);

	if(bRet)
	{
		UINT style = GetClassLong(m_hWnd,GCL_STYLE);
		style |= CS_PARENTDC;
		SetClassLong(m_hWnd,GCL_STYLE,style);
	}

	return bRet;
}
////////////////////////////////////////////////////////////////////////
BOOL CFBToolBar::OnCreate()
{
    SendMessage(m_hWnd,TB_BUTTONSTRUCTSIZE,(WPARAM) sizeof(TBBUTTON),0); 
	return TRUE;
}
////////////////////////////////////////////////////////////////////////
//���ڹ���
LRESULT CFBToolBar::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = 1;

	switch(msg)
	{
	case WM_COMMAND:
		if(m_pOwner)
			SendMessage(m_pOwner->m_hWnd,msg,wParam,lParam);
		lResult = 0;//WM_COMMAND ��Ϣ���뷵�� 0.
		break;
	case WM_NOTIFY:
		OnNotify((LPNMHDR)lParam,lResult);
		break;
	default:
		lResult = CFBWnd::WindowProc(msg,wParam,lParam);
		break;
	}

	return lResult;
}
///////////////////////////////////////////////////////////////////////////////
BOOL CFBToolBar::LoadToolBar(UINT nID)
{
	if(!m_hWnd)return FALSE;

	HRSRC hRsrc = ::FindResource(GetInstance(), MAKEINTRESOURCE(nID), RT_TOOLBAR);
	if (hRsrc == NULL)
		return FALSE;

	HGLOBAL hGlobal = LoadResource(GetInstance(), hRsrc);
	if (hGlobal == NULL)
		return FALSE;

	TOOLBAR_DATA* pData = (TOOLBAR_DATA*)LockResource(hGlobal);
	if (pData == NULL)
		return FALSE;

	BOOL bResult;
	TBBUTTON tbb;
	memset(&tbb,0,sizeof(TBBUTTON));
	tbb.iString = -1;
	int iImage = 0;

	for (int i = 0; i < pData->wItemCount; i++)
	{
		tbb.fsState = TBSTATE_ENABLED;
		tbb.idCommand = pData->items()[i];
		if(tbb.idCommand == 0)
		{
			tbb.fsStyle = TBSTYLE_SEP;
			tbb.iBitmap = -1;
		}
		else
		{
			tbb.fsStyle = TBSTYLE_BUTTON;
			tbb.iBitmap = iImage++;
		}

		bResult = AddButtons(1,&tbb);

		if(!bResult)return FALSE;
	}

	if(bResult)
	{
		TBADDBITMAP tbab;

		tbab.hInst = GetInstance();
		tbab.nID = nID;
		SendMessage(m_hWnd,TB_ADDBITMAP,(WPARAM)pData->wItemCount,(LPARAM)&tbab);
	}

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return bResult;
}
////////////////////////////////////////////////////////////////////////////
void CFBToolBar::OnToolTip(LPTOOLTIPTEXT ptt)
{
	ptt->hinst = GetInstance();

	if(LoadString(GetInstance(),ptt->hdr.idFrom,m_pText,80) == 0)
		return;

	char* pchr = strchr(m_pText,'\n');

	if(pchr)
		pchr[0] = '\0';
	ptt->lpszText = m_pText;

	SendMessage(m_pOwner->m_hWnd,FBWM_NOTIFY,MAKEWPARAM(GetWndID(),FB_TTN_SHOWING),(LPARAM)(pchr+1));
}
/////////////////////////////////////////////////////////////////////
void CFBToolBar::OnNotify(LPNMHDR pNMHDR,LRESULT& lResult)
{
	lResult = 1;
	switch(pNMHDR->code)
	{
	case TTN_NEEDTEXT:
		if(GetHotItem() != m_nHotItem)
			OnToolTip((LPTOOLTIPTEXT)pNMHDR);
		break;
	case TTN_POP:
		SendMessage(m_pOwner->m_hWnd,FBWM_NOTIFY,MAKEWPARAM(GetWndID(),FB_TTN_HIDEN),0);
		break;
	case TBN_DROPDOWN:
		{
			LPNMTOOLBAR pnmtb = (LPNMTOOLBAR)pNMHDR;

			TBBUTTONINFOA tbi;
			tbi.cbSize = sizeof(tbi);
			tbi.dwMask = TBIF_COMMAND |TBIF_LPARAM;
			tbi.idCommand = pnmtb->iItem;

			int nIndex = SendMessage(m_hWnd,TB_COMMANDTOINDEX,(WPARAM)tbi.idCommand,0);

			SendMessage(m_hWnd,TB_GETBUTTONINFO,tbi.idCommand,(LPARAM)&tbi);
			HMENU hMenu = (HMENU)tbi.lParam;
			if(hMenu)
			{
				RECT rc;
				GetButtonRect(nIndex,&rc);
				ClientToScreen(m_hWnd,&rc);
				TrackPopupMenuEx(hMenu,
						TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,
						rc.left,rc.bottom,m_pOwner->m_hWnd,NULL);
			}

			lResult = TBDDRET_DEFAULT;
		}
		break;
	case TBN_HOTITEMCHANGE:
		{
			LPNMTBHOTITEM phot = (LPNMTBHOTITEM)pNMHDR;
			if(phot->dwFlags & HICF_LEAVING)
				m_nHotItem = -1;
			else
				m_nHotItem = phot->idNew;
		}
		break;
	default:
		break;
	}
}
/////////////////////////////////////////////////////////////////////////
void CFBToolBar::CheckedButton(UINT uID,BOOL bCheck)
{
	UINT state = SendMessage(m_hWnd,TB_GETSTATE,uID,0);
	if(bCheck)
		state |= TBSTATE_CHECKED;
	else
		state &= ~TBSTATE_CHECKED;
	SendMessage(m_hWnd,TB_SETSTATE,uID,MAKELPARAM(state,0));
}
/////////////////////////////////////////////////////////////////////////////
void CFBToolBar::SetDropDowmBtn(UINT nID,HMENU hMenu)
{
	UINT style = SendMessage(m_hWnd,TB_GETEXTENDEDSTYLE,0,0);
	style |= TBSTYLE_EX_DRAWDDARROWS;
	SendMessage(m_hWnd,TB_SETEXTENDEDSTYLE,0,style);

	TBBUTTONINFOA tbi;
	tbi.cbSize = sizeof(tbi);
	tbi.dwMask = TBIF_STYLE|TBIF_LPARAM;
	tbi.idCommand = nID;

	SendMessage(m_hWnd,TB_GETBUTTONINFO,nID,(LPARAM)&tbi);

	tbi.fsStyle |= TBSTYLE_DROPDOWN;
	tbi.lParam = (LPARAM)hMenu;
	SendMessage(m_hWnd,TB_SETBUTTONINFO,nID,(LPARAM)&tbi);
}


//###################################################################
//	class CMenuBar
//	�˵���
//###################################################################


#define MB_POPUPMENU		WM_USER+500
//////////////////////////////////////////////////////////////////////
//  ���캯������������
//////////////////////////////////////////////////////////////////////

CMenuBar::CMenuBar()
{
	m_hMenu			= NULL;
}

CMenuBar::~CMenuBar()
{

}
////////////////////////////////////////////////////////////////////////////////
CMenuBar*		pMenuBar	= NULL;
HHOOK			g_hMsgHook	= NULL;
////////////////////////////////////////////////////////////////////////////////
LRESULT CMenuBar::MenuInputFilter(int nCode, WPARAM wParam, LPARAM lParam)
{
	MSG* pMsg = (MSG*)lParam;

	if(!pMenuBar || nCode!=MSGF_MENU)
		return CallNextHookEx(g_hMsgHook,nCode,wParam,lParam);
	if(pMenuBar->OnMenuInput(pMsg))
		return TRUE;
	else
		return CallNextHookEx(g_hMsgHook,nCode,wParam,lParam);
}
////////////////////////////////////////////////////////////////////////////
//	����: LoadMenu
//	����: hMenu		�˵����
//		  hMainWnd	�����ھ��
//		  bRemove	�Ƿ���ȥ���ڵ����˵�
//	˵��: ���˵����ص���������. ����CMenuBar �ǽ����˵����������ϰ�������
//		  �ټ��ص���������, ����Ӧ�ṩ�����ھ���Ա��������ڷ����й���Ϣ����
//		  �����ڸ��ٲ˵�����
////////////////////////////////////////////////////////////////////////////
BOOL CMenuBar::LoadMenu(HMENU hMenu,BOOL bRemove)
{
	if(!m_hWnd || !hMenu)return FALSE;

	TBBUTTON		tbb; 
	int				i,nStr;
	BOOL			bRet;

	memset(&tbb,0,sizeof(TBBUTTON));

	tbb.fsState = TBSTATE_ENABLED;
	tbb.fsStyle = TBSTYLE_BUTTON|TBSTYLE_AUTOSIZE;

	m_nItemCount = GetMenuItemCount(hMenu);//�˵���Ŀ����
	SetImageSize(0,0);//û��ͼ��, ��ͼ��ߴ�Ϊ0.

	for(i=0;i<m_nItemCount;i++)
	{
		GetMenuString(hMenu,i,m_pText,80,MF_BYPOSITION);
		nStr = AddString(m_pText);
		tbb.iBitmap = -1;
		tbb.dwData = NULL;
		tbb.iString = nStr;
		tbb.idCommand = i+1;

		bRet = AddButtons(1,&tbb);

		if(!bRet)return FALSE;
	}

	if(bRemove)
		SetMenu(m_pOwner->m_hWnd,NULL);

	m_hMenu = hMenu;

	return bRet;
}
///////////////////////////////////////////////////////////////////////
//���ڹ���
LRESULT CMenuBar::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = 1;

	if(msg == WM_LBUTTONDOWN)
		OnLButtonDown(wParam,LOWORD(lParam),HIWORD(lParam));
	else if(msg == MB_POPUPMENU)
		OnPopupMenu();
	else
		lResult = CFBToolBar::WindowProc(msg,wParam,lParam);

	return lResult;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	����: OnLButtonDown
void CMenuBar::OnLButtonDown(UINT fwKey,LONG x,LONG y)
{
	m_ptMouse.x = x;
	m_ptMouse.y = y;

	int nTest = SendMessage(m_hWnd,TB_HITTEST,0,(LPARAM)&m_ptMouse);

	if(nTest<0 || nTest>=m_nItemCount)
		return;

	m_nPressed = nTest;
	TrackPopup();
}
//////////////////////////////////////////////////////////////////////////
//���ٵ����Ӳ˵�
/////////////////////////////////////////////////////////////////////////
void CMenuBar::TrackPopup()
{
	HMENU hSubMenu = GetSubMenu(m_hMenu,m_nPressed);//�õ��Ӳ˵����
	if(hSubMenu == NULL)return;

	m_bTrack = TRUE;
	PressButton(m_nPressed,TRUE);//ѹ�°�ť

	//�õ���ť����
	RECT rc;
	GetButtonRect(m_nPressed,&rc);
	ClientToScreen(m_hWnd,&rc);

	TPMPARAMS tpm;
	tpm.cbSize = sizeof(tpm);
	tpm.rcExclude = rc;

	//���ù��Ӻ���
	pMenuBar = this;
	g_hMsgHook = SetWindowsHookEx(WH_MSGFILTER,
			MenuInputFilter, NULL, GetCurrentThreadId());

	//���ٲ˵�����
	TrackPopupMenuEx(hSubMenu,
				TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,
				rc.left,rc.bottom,m_pOwner->m_hWnd,&tpm);

	PressButton(m_nPressed,FALSE);
	UnhookWindowsHookEx(g_hMsgHook);//������Ӻ���

	g_hMsgHook = NULL;
	pMenuBar = NULL;
}
/////////////////////////////////////////////////////////////////////////////////
BOOL CMenuBar::OnMenuInput(MSG* pMsg)
{
	BOOL bResult = FALSE;

	switch(pMsg->message)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(pMsg->lParam);
			pt.y = HIWORD(pMsg->lParam);
			ScreenToClient(m_hWnd,&pt);
			if(m_ptMouse.x == pt.x && m_ptMouse.y == pt.y)
				return TRUE;
		
			m_ptMouse.x = pt.x;
			m_ptMouse.y = pt.y;

			int nTest = SendMessage(m_hWnd,TB_HITTEST,0,(LPARAM)&pt);

			if(nTest>=0 && nTest<m_nItemCount && nTest != m_nPressed)
			{
				PressButton(m_nPressed,FALSE);
				PostMessage(m_pOwner->m_hWnd,WM_CANCELMODE,0,0);
				m_nPressed = nTest;
				PostMessage(m_hWnd,MB_POPUPMENU,0,0);
				bResult = TRUE;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(pMsg->lParam);
			pt.y = HIWORD(pMsg->lParam);
			ScreenToClient(m_hWnd,&pt);
			PostMessage(m_pOwner->m_hWnd,FBWM_NOTIFY,MAKEWPARAM(GetWndID(),FB_TTN_HIDEN),0);

			int nTest = SendMessage(m_hWnd,TB_HITTEST,0,(LPARAM)&pt);

			if(nTest<0)
				m_bTrack = FALSE;
			else if(nTest == m_nPressed)
			{
				m_bTrack = FALSE;
				PostMessage(m_pOwner->m_hWnd,WM_CANCELMODE,0,0);
				bResult = TRUE;
			}
		}
		break;
	case WM_KEYDOWN:
		{
			TCHAR vkey = pMsg->wParam;
			if(vkey == VK_LEFT)
			{
				PressButton(m_nPressed,FALSE);
				m_nPressed --;
				PostMessage(m_pOwner->m_hWnd,WM_CANCELMODE,0,0);
				PostMessage(m_hWnd,MB_POPUPMENU,0,0);
				bResult = TRUE;
			}
			else if(vkey == VK_RIGHT)
			{
				PressButton(m_nPressed,FALSE);
				m_nPressed ++;
				PostMessage(m_pOwner->m_hWnd,WM_CANCELMODE,0,0);
				PostMessage(m_hWnd,MB_POPUPMENU,0,0);
				bResult = TRUE;
			}
			else if (vkey == VK_ESCAPE)
			{
				PostMessage(m_pOwner->m_hWnd,FBWM_NOTIFY,MAKEWPARAM(GetWndID(),FB_TTN_HIDEN),0);
				PostMessage(m_pOwner->m_hWnd,WM_CANCELMODE,0,0);
				m_bTrack = FALSE;
				bResult = TRUE;
			}
		}
		break;
	case WM_MENUSELECT:
		OnMenuSelect(pMsg->wParam,pMsg->lParam);
		break;
	default:
		break;
	}

	return bResult;
}
////////////////////////////////////////////////////////////////////////////
void CMenuBar::OnPopupMenu()
{
	if(m_nPressed<0)
		m_nPressed = m_nItemCount - 1;
	if(m_nPressed>=m_nItemCount)
		m_nPressed = 0;
	TrackPopup();
}
//////////////////////////////////////////////////////////////////////////////
void CMenuBar::OnMenuSelect(WPARAM wParam,LPARAM lParam)
{
	UINT uItem = (UINT) LOWORD(wParam);
	if(!LoadString(GetInstance(),uItem,m_pText,80))
	{
		strcpy(m_pText,"\n����");
	}

	char* pchr = strchr(m_pText,'\n');
	if(pchr >= (m_pText+80))
	{
		strcpy(m_pText,"\n����");
		pchr = m_pText;
	}
	SendMessage(m_pOwner->m_hWnd,FBWM_NOTIFY,MAKEWPARAM(GetWndID(),FB_TTN_SHOWING),(LPARAM)pchr+1);
}
/////////////////////////////////////////////////////////////////////////
void CMenuBar::CheckMenuItem(UINT uID,BOOL bCheck)
{
	UINT flag;
	if(bCheck)
		flag = MF_CHECKED;
	else
		flag = MF_UNCHECKED;
	::CheckMenuItem(m_hMenu,uID,flag);
}
/////////////////////////////////////////////////////////////////////////
BOOL CMenuBar::GetMenuItemCheckState(UINT uID)
{
	MENUITEMINFO miif;
	miif.cbSize = sizeof(miif);
	miif.fMask = MIIM_ID|MIIM_STATE;
	miif.wID =uID;
	GetMenuItemInfo(m_hMenu,uID,FALSE,&miif);

	if(miif.fState&MFS_CHECKED)
		return TRUE;
	else
		return FALSE;
}
//////////////////////////////////////////////////////////////////////
BOOL CMenuBar::EnableMenuItem(UINT uID,BOOL bEnable)
{
	MENUITEMINFO miif;
	miif.cbSize = sizeof(miif);
	miif.fMask = MIIM_ID|MIIM_STATE;
	miif.wID =uID;
	if(bEnable)
		miif.fState = MFS_ENABLED;
	else
		miif.fState = MFS_DISABLED;
	
	return SetMenuItemInfo(m_hMenu,uID,FALSE,&miif);
}

//////////////////////////////////////////////////////////////////////

//###################################################################
//	class CFBStatusBar
//	״̬��
//###################################################################

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFBStatusBar::CFBStatusBar()
{

}

CFBStatusBar::~CFBStatusBar()
{

}
/////////////////////////////////////////////////////////////////////
CFBStatusBar::Create(CFBWnd* pParent,UINT uID)
{
	if(!pParent)return FALSE;

	InitCommonControls();

	UINT nStyle = WS_VISIBLE|WS_CHILD|WS_CLIPSIBLINGS|
				  CCS_NOPARENTALIGN|CCS_NODIVIDER|CCS_NORESIZE |
				  WS_CLIPCHILDREN|SBARS_SIZEGRIP;

	return CFBWnd::Create(STATUSCLASSNAME,
						NULL,
						pParent->GetInstance(),
						pParent,
						nStyle);
}
////////////////////////////////////////////////////////////////////////////
LRESULT CFBStatusBar::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == FBWM_SETSIZE)
	{
		if(IsShow())
			OnSetSize((LPRECT)lParam);

		return 1;
	}
	else if(msg == WM_LBUTTONUP || msg == WM_LBUTTONDBLCLK)
		return DefWindowProc(m_hWnd,msg,wParam,lParam);
	else
		return CFBWnd::WindowProc(msg,wParam,lParam);

}
////////////////////////////////////////////////////////////////////////////////////////////
void CFBStatusBar::SetText(int nIndex,LPCTSTR strText)
{
	if(nIndex<0 || nIndex>m_nParts)return;

	SendMessage(m_hWnd,SB_SETTEXT,(WPARAM)nIndex,(LPARAM)strText);

}
////////////////////////////////////////////////////////////////////////////////////////////
void CFBStatusBar::SetParts(int nParts,LPINT lpParts)
{
	if(!nParts)return;

	m_nParts = nParts;
	SendMessage(m_hWnd, SB_SETPARTS, (WPARAM) m_nParts,(LPARAM)lpParts);
}
////////////////////////////////////////////////////////////////////////////////////////////
void CFBStatusBar::OnSetSize(LPRECT pRect)
{
	RECT rc;
	CopyRect(&rc,pRect);
	int pParts[32];
	SendMessage(m_hWnd,SB_GETPARTS,(WPARAM)m_nParts,(LPARAM)pParts);
	int space = (int)(pRect->right - pRect->left - pParts[m_nParts-1])/m_nParts;
	int sp = 0;
	for(int i=0;i<m_nParts;i++)
	{
		sp += space;
		pParts[i] += sp;
	}
	SendMessage(m_hWnd, SB_SETPARTS, (WPARAM) m_nParts,(LPARAM)pParts);

	rc.top = rc.bottom - 20;
	SetWindowPos(m_hWnd,NULL,rc.left,rc.top,
				rc.right - rc.left,rc.bottom - rc.top,
				SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOCOPYBITS);
	pRect->bottom -= rc.bottom - rc.top;
}
//////////////////////////////////////////////////////////////////////

