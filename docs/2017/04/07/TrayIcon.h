//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：TrayIcon.h	类CTrayIcon的头文件

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
#ifndef _TRAYICON_H__
#define _TRAYICON_H__

#include <shellapi.h>
#include "FBWnd.h"

#define FBNM_TRAYICON		WM_USER+101
//######################################################################
class CTrayIcon
{
public:
	CTrayIcon();
	~CTrayIcon();

	BOOL Create(CFBWnd* pOwner,UINT uID,HICON hIcon,LPTSTR szTip);
	BOOL Open();
	void Close();
	BOOL ModifyIcon(HICON hIcon);
	BOOL ModifyTip(LPTSTR szTip);
	void SetIcon(HICON hIcon){
		m_Data.hIcon = hIcon;}
	void SetMenu(UINT uID);
	void SetMenu(HMENU hMenu){
		m_hMenu = hMenu;}
	HMENU GetMenu(){
		return m_hMenu;}
	void PopupMenu();
protected:
	CFBWnd*				m_pOwner;
	HMENU				m_hMenu;
	NOTIFYICONDATA		m_Data;
};
//######################################################################
#endif//_TRAYICON_H__