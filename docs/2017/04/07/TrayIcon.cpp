//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���TrayIcon.h	��CTrayIcon��ִ���ļ�

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
#include "TrayIcon.h"
//#####################################################################
CTrayIcon::CTrayIcon()
{
	memset(&m_Data,0,sizeof(NOTIFYICONDATA));
	m_Data.cbSize = sizeof(NOTIFYICONDATA);
	m_Data.uCallbackMessage = FBNM_TRAYICON;
	m_Data.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
	m_hMenu = NULL;
}

CTrayIcon::~CTrayIcon()
{
	if(m_hMenu)
		DestroyMenu(m_hMenu);
}
//#####################################################################
BOOL CTrayIcon::Create(CFBWnd* pOwner,UINT uID,HICON hIcon,LPTSTR szTip)
{
	if(pOwner == NULL)
		return FALSE;

	m_pOwner = pOwner;

	m_Data.hIcon = hIcon;
	m_Data.hWnd = pOwner->m_hWnd;
	m_Data.uID = uID;

	if(szTip)
		lstrcpy(m_Data.szTip,szTip);

	return TRUE;
}
//#####################################################################
BOOL CTrayIcon::Open()
{
	return Shell_NotifyIcon(NIM_ADD,&m_Data);
}
//#####################################################################
void CTrayIcon::Close()
{
	Shell_NotifyIcon(NIM_DELETE,&m_Data);
}
//#####################################################################
void CTrayIcon::SetMenu(UINT uID)
{
	if(m_pOwner == NULL)return;

	m_hMenu = LoadMenu(m_pOwner->GetInstance(),MAKEINTRESOURCE(uID));
}
//#####################################################################
BOOL CTrayIcon::ModifyIcon(HICON hIcon)
{
	if(!hIcon)return FALSE;

	UINT flag = m_Data.uFlags;
	m_Data.uFlags = NIF_ICON;
	m_Data.hIcon = hIcon;

	BOOL bRet = Shell_NotifyIcon(NIM_MODIFY,&m_Data);
	m_Data.uFlags = flag;
	return bRet;
}
//#####################################################################
BOOL CTrayIcon::ModifyTip(LPTSTR szTip)
{
	if(!szTip)return FALSE;

	UINT flag = m_Data.uFlags;
	m_Data.uFlags = NIF_TIP;
	lstrcpy(m_Data.szTip,szTip);

	BOOL bRet = Shell_NotifyIcon(NIM_MODIFY,&m_Data);
	m_Data.uFlags = flag;
	return bRet;
}
//#####################################################################
void CTrayIcon::PopupMenu()
{
	if(!m_hMenu || !m_pOwner)return;

	POINT pt;
	GetCursorPos(&pt);

	HMENU hMenu = GetSubMenu(m_hMenu,0);
	TrackPopupMenu(hMenu,TPM_RIGHTALIGN|TPM_LEFTBUTTON |
				   TPM_RIGHTBUTTON,pt.x,pt.y,0,
				   m_pOwner->m_hWnd,NULL);
}