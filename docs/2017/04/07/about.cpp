//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	�ļ���about.h	��CAboutDlg��ִ���ļ�

	��Ȩ��Firebird Software Workroom ����

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
#include "resource.h"
#include <shellapi.h>
#include "about.h"

BOOL CAboutDlg::m_bOverHLink = FALSE;
HCURSOR CAboutDlg::m_hLinkCursor = NULL;
WNDPROC CAboutDlg::pfnStaticProc = NULL;
///////////////////////////////////////////////////////////////////////////////////
CAboutDlg::CAboutDlg()
{
}
CAboutDlg::~CAboutDlg()
{
}
///////////////////////////////////////////////////////////////////////////////////
LRESULT CAboutDlg::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_CTLCOLORSTATIC)
	{
		int nRet = 1;
		HWND hStatic = GetDlgItem(m_hWnd,IDC_EMAILTO);
		if(hStatic == (HWND)lParam)
		{
			if(!m_bOverHLink)
				SetTextColor((HDC)wParam,RGB(0,0,238));
			else
				SetTextColor((HDC)wParam,RGB(85,26,139));
			SetBkMode((HDC)wParam,TRANSPARENT);
			nRet = (int)(HBRUSH)GetStockObject(NULL_BRUSH);
		}
		return nRet;
	}
	else
		return CModalDlg::WindowProc(msg,wParam,lParam);
}
///////////////////////////////////////////////////////////////////////////////////
void CAboutDlg::OnInitDialog()
{
	char caption[16];
	SendMessage(m_pOwner->m_hWnd,WM_GETTEXT,16,(LPARAM)caption);
	HWND hwnd = GetDlgItem(m_hWnd,IDC_CAPTION);
	SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)caption);

	char WinPath[MAX_PATH];
	GetWindowsDirectory(WinPath, MAX_PATH);
	lstrcat(WinPath,"\\winhlp32.exe");
	HMODULE hModule = LoadLibrary(WinPath);
	if (hModule) {
		HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
		if (hHandCursor)
			m_hLinkCursor = CopyCursor(hHandCursor);
	}
	FreeLibrary(hModule);

	HWND hStatic = GetDlgItem(m_hWnd,IDC_EMAILTO);
	if(hStatic)
		pfnStaticProc = (WNDPROC)SetWindowLong(hStatic,GWL_WNDPROC,(LONG)StaticProc);

	CenterWindow(m_hWnd);
}
///////////////////////////////////////////////////////////////////////////////////
void CAboutDlg::OnCommand(UINT uCmdID,UINT code)
{
	if((code == STN_CLICKED) && (uCmdID == IDC_EMAILTO))
	{
		char str[MAX_PATH];
		char tmp[MAX_PATH];
		HWND hStatic = GetDlgItem(m_hWnd,IDC_EMAILTO);
		SendMessage(hStatic,WM_GETTEXT,MAX_PATH,(LPARAM)tmp);
		lstrcpy(str,"mailto:");
		lstrcat(str,tmp);
		ShellExecute(NULL,NULL,str,NULL,NULL,SW_SHOWNORMAL);
	}
}
///////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK CAboutDlg::StaticProc (HWND hWnd, UINT msg, UINT wParam, LPARAM lParam)
{
	LRESULT lResult = 0;

	switch(msg)
	{
	case WM_SETCURSOR:
		SetCursor(m_hLinkCursor);
		break;
	case WM_MOUSEMOVE:
		{
			RECT rc;
			POINT pt;
			GetClientRect(hWnd,&rc);
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			if(!PtInRect(&rc,pt))
			{
				m_bOverHLink = FALSE;
				ReleaseCapture();
				RedrawWindow(hWnd,NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW);
			}
			else
			{
				m_bOverHLink = TRUE;
				SetCapture(hWnd);
				RedrawWindow(hWnd,NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW);
			}
		}
		break;
	default:
		lResult = CallWindowProc(pfnStaticProc,hWnd,msg,wParam,lParam);
		break;
	}

	return lResult;
}