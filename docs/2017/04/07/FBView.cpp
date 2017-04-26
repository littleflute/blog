//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBView.h	��CFBView��ִ���ļ�

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

