//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBTabCtrl.cpp  类CFBTabCtrl的执行文件

	版权：Firebird Software Workroom

	声明：本源程序的版权受《中华人民共和国著作权法》以及其
		  它相关法律和条约的保护。任何有机会得到本源程序的
		  个人和机构，未经作者明确授权，不得将本源程序用于
		  任何商业目的(直接的或间接的)。对于非商业目的的使
		  用 (包括复制、传播、编译和修改)， 原则上没有特别
		  的限制条款，但请在相关文档中说明其来源，并尊重原
		  作者的署名权。

	编写：秦传安(chings)	1999.12 - 2000.5

	联络：Tel：(0792)6323086	E_mail：chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include "fclstd.h"
#include "FBCtrls.h"

//###################################################################
//	class CFBTabCtrl
//	活页控件
//###################################################################

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFBTabCtrl::CFBTabCtrl()
{
	m_pActiveView	= NULL;
	m_uStyle		= 0;
}

CFBTabCtrl::~CFBTabCtrl()
{
	RemoveAll();
}
//////////////////////////////////////////////////////////////////////
BOOL CFBTabCtrl::Create(CFBWnd* pParent,UINT nID,UINT style)
{
	InitCommonControls();

	style |= WS_CHILD | WS_VISIBLE| WS_CLIPCHILDREN | WS_CLIPSIBLINGS |
				TCS_BUTTONS | TCS_FIXEDWIDTH | TCS_FORCELABELLEFT |
				CCS_NODIVIDER | CCS_NORESIZE;

	m_uStyle = style;

	if(!CFBWnd::Create(WC_TABCONTROL,
						NULL,
						pParent->GetInstance(),
						pParent,
						style,
						NULL,
						(HMENU)nID))
		return FALSE;

	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(m_hWnd,WM_SETFONT,(WPARAM)hFont,FALSE);
	SendMessage(m_hWnd,TCM_SETITEMSIZE,0,MAKELPARAM(60,16));
	
	return TRUE;
}
///////////////////////////////////////////////////////////////////////
//窗口过程
LRESULT CFBTabCtrl::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = 0;

	switch(msg)
	{
	case WM_SIZE:
		OnSize();
		break;
	case WM_ERASEBKGND:
		if(GetItemCount() > 0)
		{
			RECT rc;
			GetChildRect(&rc);
			ExcludeClipRect((HDC)wParam,rc.left,rc.top,rc.right,rc.bottom);
		}
		lResult = CFBWnd::WindowProc(msg,wParam,lParam);
		break;
	case WM_NOTIFY:
		{
			LPNMHDR pNMHDR = (LPNMHDR)lParam;
			if(pNMHDR->code == TCN_SELCHANGE)
			{
				SetActiveView(GetCurSel());
				SendMessage(m_pOwner->m_hWnd,FBWM_NOTIFY,MAKEWPARAM(GetWndID(),FB_TABN_SELCHANGED),0);
			}
		}
		break;
	default:
		lResult = CFBWnd::WindowProc(msg,wParam,lParam);
		break;
	}

	return lResult;
}
///////////////////////////////////////////////////////////////////////////////////
int CFBTabCtrl::AddView(CFBWnd *pChild,LPSTR pszCaption,BOOL bEnableImg)
{
	if(!pChild)return -1;

	int index = GetItemCount();

	TCITEM tci;
	tci.mask = TCIF_TEXT|TCIF_PARAM;
	if(bEnableImg)
		tci.mask |= TCIF_IMAGE;
	tci.pszText = pszCaption;
	tci.cchTextMax = 32;
	if(bEnableImg)
		tci.iImage = index;
	tci.lParam = (LPARAM)pChild;

	if(SendMessage(m_hWnd,TCM_INSERTITEM,(WPARAM)index,(LPARAM)&tci) == -1)
		return -1;
	
	SetParent(pChild->m_hWnd,m_hWnd);
	return index;
}
///////////////////////////////////////////////////////////////////////////////////
void CFBTabCtrl::SetActiveView(int nIndex)
{
	if(nIndex == -1)
		return;

	CFBWnd* pWnd = GetAt(nIndex);
	if(pWnd)
	{
		if(pWnd == m_pActiveView)
			return;

		if(m_pActiveView)
			ShowWindow(m_pActiveView->m_hWnd,SW_HIDE);

		ShowWindow(pWnd->m_hWnd,SW_SHOW);
		m_pActiveView = pWnd;
		OnSize();
	}
	SetCurSel(nIndex);
}
///////////////////////////////////////////////////////////////////////////////////
void CFBTabCtrl::GetChildRect(LPRECT prc)
{
	GetClientRect(m_hWnd,prc);

	prc->bottom -= 3;
	prc->left += 3;
	prc->right -= 3;

	if(m_uStyle & CCS_TOP)
		prc->top += 21;
	else if(m_uStyle & CCS_BOTTOM)
		prc->bottom -= 21;
}
///////////////////////////////////////////////////////////////////////////////////
void CFBTabCtrl::OnSize()
{
 	if(!m_pActiveView)return;

	RECT rc;
	GetChildRect(&rc);
	SetWindowPos(m_pActiveView->m_hWnd,NULL,rc.left,rc.top,
				rc.right - rc.left,rc.bottom - rc.top,
				SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOCOPYBITS);
}
///////////////////////////////////////////////////////////////////////////////////
CFBWnd* CFBTabCtrl::GetAt(int index)
{
	TCITEM tci;
	memset(&tci,0,sizeof(TCITEM));
	tci.mask = TCIF_PARAM;
	if(!GetItem(index,&tci))
		return NULL;

	return (CFBWnd*)tci.lParam;
}
///////////////////////////////////////////////////////////////////////////////////
void CFBTabCtrl::Remove(int index)
{
	CFBWnd *pWnd = GetAt(index);
	if(pWnd)
		delete pWnd;
	else
		return;

	int n = GetItemCount();

	SendMessage(m_hWnd,TCM_DELETEITEM,(WPARAM)index,0);

	if(n == 1)
	{
		m_pActiveView = NULL;
		return;
	}

	if(index == n-1)//如果删除的是最后一页，置前页为当前页
		SetActiveView(index-1);
	else//否则， 置后页为当前页。
		SetActiveView(index);
}
///////////////////////////////////////////////////////////////////////////////////
void CFBTabCtrl::RemoveAll()
{
	int count = GetItemCount();
	if(count == 0)return;

	CFBWnd *pWnd;

	for(int i=0;i<count;i++)
	{
		pWnd = GetAt(i);
		if(pWnd)
			delete pWnd;
	}

	m_pActiveView = NULL;

	SendMessage(m_hWnd,TCM_DELETEALLITEMS,0,0);
}
///////////////////////////////////////////////////////////////////////////////////
void CFBTabCtrl::SetCaption(int index,LPTSTR szCaption)
{
	if(index<0 || index>=GetItemCount())
		return;

	TCITEM tci;
	tci.mask = TCIF_TEXT;
	tci.pszText = szCaption;
	tci.cchTextMax = lstrlen(szCaption);

	TabCtrl_SetItem(m_hWnd,index,&tci);
}
///////////////////////////////////////////////////////////////////////////////////
void CFBTabCtrl::GetCaption(int index,LPTSTR szCaption,int cbSize)
{
	if(index<0 || index>=GetItemCount())
		return;

	TCITEM tci;
	tci.mask = TCIF_TEXT;
	tci.pszText = szCaption;
	tci.cchTextMax = cbSize;

	GetItem(index,&tci);
}
