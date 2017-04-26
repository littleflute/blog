//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	�ļ���CapForm.h	��CCapForm��ִ���ļ�

	��Ȩ��Firebird Software Workroom ����

	��������Դ����İ�Ȩ�ܡ��л����񹲺͹�����Ȩ�����Լ���
		  ����ط��ɺ���Լ�ı������κ��л���õ���Դ�����
		  ���˺ͻ�����δ��������ȷ��Ȩ�����ý���Դ��������
		  �κ���ҵĿ��(ֱ�ӵĻ��ӵ�)�����ڷ���ҵĿ�ĵ�ʹ
		  �� (�������ơ�������������޸�)�� ԭ����û���ر�
		  �������������������ĵ���˵������Դ��������ԭ
		  ���ߵ�����Ȩ��

	��д���ش���(chings)	2000.5

	���磺Tel��(0792)6323086	E_mail��chings@163.net
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
