//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBView.h	类CFBView的执行文件

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
#include "FBView.h"
//####################################################################
CFBView::CFBView()
{
	m_nBkMode		= 0;
	m_hBkBmpDC		= NULL;
	m_hBkBrush		= NULL;
}

CFBView::~CFBView()
{
	if(m_hBkBmpDC)
		DeleteDC(m_hBkBmpDC);
	if(m_hBkBrush)
		DeleteObject(m_hBkBrush);
}
//####################################################################
LRESULT CFBView::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = 0;

	switch(msg)
	{
	case WM_ERASEBKGND:
		if(!DrawBackground((HDC)wParam))
			lResult = CFBWnd::WindowProc(msg,wParam,lParam);
		else
			lResult = 1;
		break;
	case WM_PAINT:
		lResult = CFBWnd::WindowProc(msg,wParam,lParam);
		OnDraw(GetDC(m_hWnd));
		break;
	default:
		lResult = CFBWnd::WindowProc(msg,wParam,lParam);
		break;
	}

	return lResult;
}
//####################################################################
BOOL CFBView::Create(CFBWnd* pParent,UINT uID,UINT style)
{
	if(!pParent)return FALSE;

	style |= WS_CHILD|WS_VISIBLE;

	return CFBWnd::Create(CLS_FBSTDWNDCLASS,
						  NULL,
						  pParent->GetInstance(),
						  pParent,
						  style,
						  WS_EX_CLIENTEDGE,
						  (HMENU)uID);
}
//####################################################################
BOOL CFBView::DrawBackground(HDC hDC)
{
	if(m_hBkBmpDC && (m_nBkMode == 2))
	{
		RECT rc;
		GetClientRect(m_hWnd,&rc);
		TileBitmap(hDC,&rc,m_hBkBmpDC,m_cxBkBmp,m_cyBkBmp);
		return TRUE;
	}
	else if(m_hBkBrush && (m_nBkMode == 1))
	{
		RECT rc;
		GetClientRect(m_hWnd,&rc);
		FillRect(hDC,&rc,m_hBkBrush);
		return TRUE;
	}
	else
		return FALSE;
}
//####################################################################
void CFBView::OnDraw(HDC hDC)
{
}
//####################################################################
void CFBView::SetBkColor(COLORREF clr)
{
	m_hBkBrush = CreateSolidBrush(clr);
	if(m_hBkBrush)
		m_nBkMode = 1;
}
//####################################################################
void CFBView::SetBkImage(HBITMAP hBmp)
{
	if(!hBmp)return;

	if(m_hBkBmpDC)
	{
		DeleteDC(m_hBkBmpDC);
		m_hBkBmpDC = NULL;
	}

	BITMAP bmp;
	GetObject(hBmp,sizeof(BITMAP),&bmp);
	m_cxBkBmp = bmp.bmWidth;
	m_cyBkBmp = bmp.bmHeight;

	m_hBkBmpDC = CreateCompatibleDC(GetDC(m_hWnd));
	SelectObject(m_hBkBmpDC,hBmp);
	DeleteObject(hBmp);

	m_nBkMode = 2;
}
//####################################################################
void CFBView::SetBkImage(LPTSTR pszFilename)
{
	HBITMAP hBmp = (HBITMAP)LoadImage(NULL,pszFilename,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	SetBkImage(hBmp);
}

