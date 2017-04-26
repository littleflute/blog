//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：TrayIcon.h	类CTrayIcon的执行文件

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