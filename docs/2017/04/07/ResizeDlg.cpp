//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���ResizeDlg.cpp		��CResizeDlg��ִ���ļ�

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
#include "ScreenCap.h"
#include "resource.h"
#include "MainWnd.h"
#include "ResizeDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResizeDlg::CResizeDlg()
{
	m_pImg = NULL;
	m_hBmpTemp = NULL;
}

CResizeDlg::~CResizeDlg()
{

}
//####################################################################
LRESULT CResizeDlg::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_HSCROLL)
	{
		HWND hwnd = GetDlgItem(m_hWnd,IDC_SLIDER1);
		if(hwnd == (HWND)lParam && m_pImg)
		{
			if((LOWORD(wParam) == TB_ENDTRACK) ||
				(LOWORD(wParam) == TB_THUMBPOSITION))
				OnHScroll(HIWORD(wParam));
		}
		return 0;
	}
	else if(msg == WM_DESTROY && m_pImg)
	{
		LPIMAGE_INFO pii = m_pImg->GetImageInfo();
		memcpy(pii,&img,sizeof(IMAGE_INFO));
	}

	return CModalDlg::WindowProc(msg,wParam,lParam);
}
//####################################################################
void CResizeDlg::OnInitDialog()
{
	if(!m_pImg)
	{
		CMainWnd* pFrame = (CMainWnd*)GetApp()->m_pMainWnd;
		if(pFrame)
			m_pImg = pFrame->GetCurrentImage();

		if(!m_pImg)
			EndDialog(m_hWnd,IDCANCEL);
	}

	LPIMAGE_INFO pii = m_pImg->GetImageInfo();
	memcpy(&img,pii,sizeof(IMAGE_INFO));
	memset(pii,0,sizeof(IMAGE_INFO));

	cx = img.cx;
	cy = img.cy;
	scale = 100;

	HWND hwnd = GetDlgItem(m_hWnd,IDC_SLIDER1);
	if(hwnd)
		SendMessage(hwnd,TBM_SETRANGE,(WPARAM)TRUE,MAKELPARAM(0,200));

	RECT rc,rcOwner;
	GetWindowRect(m_hWnd,&rc);
	GetWindowRect(m_pOwner->m_hWnd,&rcOwner);
	int x = rcOwner.right - (rc.right - rc.left);
	int y = rcOwner.bottom - (rc.bottom - rc.top);

	SetWindowPos(m_hWnd,NULL,x,y,0,0,SWP_NOZORDER|SWP_NOSIZE);

	UpdateControl();
}
//####################################################################
void CResizeDlg::UpdateControl()
{
	if(!m_hWnd)return;

	char str[16];
	HWND hwnd = GetDlgItem(m_hWnd,IDC_EDIT_SCALE);
	if(hwnd)
	{
		ltoa(scale,str,10);
		SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)str);
	}

	hwnd = GetDlgItem(m_hWnd,IDC_EDIT_WIDTH);
	if(hwnd)
	{
		ltoa(cx,str,10);
		SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)str);
	}

	hwnd = GetDlgItem(m_hWnd,IDC_EDIT_HEIGHT);
	if(hwnd)
	{
		ltoa(cy,str,10);
		SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)str);
	}

	hwnd = GetDlgItem(m_hWnd,IDC_SLIDER1);
	if(hwnd)
		SendMessage(hwnd,TBM_SETPOS,(WPARAM)TRUE,(LPARAM)scale);
}
//####################################################################
void CResizeDlg::OnHScroll(int nNewPos)
{
	HDC hdc = NULL, hBmpDC = NULL,hImgDC = NULL;
	HBITMAP hbmp = NULL;
	int pos;

	HWND hwnd = GetDlgItem(m_hWnd,IDC_SLIDER1);
	if(hwnd)
		pos = SendMessage(hwnd,TBM_GETPOS,0,0);

	if(pos == scale)
		return;

	scale = pos;
	cx = (int)(img.cx*scale)/100;
	cy = (int)(img.cy*scale)/100;
	UpdateControl();

	hImgDC = GetDC(m_pImg->m_hWnd);
	hdc = CreateCompatibleDC(hImgDC);
	if(!hdc)return;

	SelectObject(hdc,img.hBmp);

	hBmpDC = CreateCompatibleDC(hImgDC);
	if(!hBmpDC)
		goto Done;

	hbmp = CreateCompatibleBitmap(hdc,cx,cy);
	if(!hbmp)
		goto Done;

	SelectObject(hBmpDC,hbmp);
	StretchBlt(hBmpDC,0,0,cx,cy,hdc,0,0,img.cx,img.cy,SRCCOPY);

	if(m_hBmpTemp)
		DeleteObject(m_hBmpTemp);

	m_hBmpTemp = hbmp;
	m_pImg->LoadFromHandle(hbmp);
	m_pImg->Invalidate();

Done:
	if(hdc)
		DeleteDC(hdc);
	if(hBmpDC)
		DeleteDC(hBmpDC);
	if(hImgDC)
		ReleaseDC(m_hWnd,hImgDC);
}