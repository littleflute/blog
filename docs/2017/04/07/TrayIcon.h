//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���TrayIcon.h	��CTrayIcon��ͷ�ļ�

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