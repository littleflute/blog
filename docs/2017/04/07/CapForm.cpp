//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	文件：CapForm.h	类CCapForm的执行文件

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
#include "CapForm.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCapForm::CCapForm()
{
	m_hScreenDC = NULL;
	m_hCursor = NULL;
	m_nCapFlag = 0;
	m_bDown = FALSE;
}

CCapForm::~CCapForm()
{
	
}

//////////////////////////////////////////////////////////////////////
void CCapForm::OnInitDialog()
{
	HDC hdc = GetDC(NULL);

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	m_hScreenDC = CreateCompatibleDC(hdc);
	HBITMAP hBmp = CreateCompatibleBitmap(hdc,cx,cy);
	SelectObject(m_hScreenDC,hBmp);

	BitBlt(m_hScreenDC,0,0,cx,cy,hdc,0,0,SRCCOPY);
	ReleaseDC(NULL,hdc);

	SetWindowPos(m_hWnd,NULL,0,0,cx,cy,
				SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOCOPYBITS);

/*
	WINDOWPLACEMENT wpl;
	memset(&wpl,0,sizeof(WINDOWPLACEMENT));
	wpl.length = sizeof(WINDOWPLACEMENT);
	wpl.rcNormalPosition.left = 0;
	wpl.rcNormalPosition.top = 0;
	wpl.rcNormalPosition.right = cx;
	wpl.rcNormalPosition.bottom = cy;
	wpl.showCmd = SW_SHOWNORMAL;
	SetWindowPlacement(m_hWnd,&wpl);*/
}
//////////////////////////////////////////////////////////////////////
LRESULT CCapForm::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = 0;
	
	switch(msg)
	{
	case WM_ERASEBKGND:
		lResult = 1;
		break;
	case WM_PAINT:
		{
			HDC hDC = GetDC(m_hWnd);
			int cx = GetSystemMetrics(SM_CXSCREEN);
			int cy = GetSystemMetrics(SM_CYSCREEN);
			BitBlt(hDC,0,0,cx,cy,m_hScreenDC,0,0,SRCCOPY);
			ReleaseDC(m_hWnd,hDC);
		}
		break;
	case WM_LBUTTONDOWN:
		m_ptBegin.x = m_ptEnd.x = LOWORD(lParam);
		m_ptBegin.y = m_ptEnd.y = HIWORD(lParam);
		if(m_nCapFlag = 2)
		{
			m_bDown = TRUE;
			m_rcSel.left = m_rcSel.right = m_ptBegin.x;
			m_rcSel.top = m_rcSel.bottom = m_ptBegin.y;
		}
		break;
	case WM_LBUTTONUP:
		EndDialog(m_hWnd,IDOK);
		break;
	case WM_MOUSEMOVE:
		if(m_nCapFlag = 2 && m_bDown)
		{
			HDC hdc = GetDC(m_hWnd);

			DrawFocusRect(hdc,&m_rcSel);

			m_ptEnd.x = LOWORD(lParam);
			m_ptEnd.y = HIWORD(lParam);
			m_rcSel.left = min(m_ptBegin.x,m_ptEnd.x);
			m_rcSel.top = min(m_ptBegin.y,m_ptEnd.y);
			m_rcSel.right = max(m_ptBegin.x,m_ptEnd.x);
			m_rcSel.bottom = max(m_ptBegin.y,m_ptEnd.y);

			DrawFocusRect(hdc,&m_rcSel);
			ReleaseDC(m_hWnd,hdc);
		}
		break;
	case WM_SETCURSOR:
		SetCursor(m_hCursor);
		lResult = 1;
		break;
	default:
		lResult = CModalDlg::WindowProc(msg,wParam,lParam);
		break;
	}

	return lResult;	
}
