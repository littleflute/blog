//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	�ļ���about.h	��CAboutDlg��ͷ�ļ�

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
#ifndef _ABOUT_H_INCLUDED
#define _ABOUT_H_INCLUDED
///////////////////////////////////////////////////////////////////////////////////

#include "FBDialog.h"
///////////////////////////////////////////////////////////////////////////////////

class CAboutDlg : public CModalDlg
{
public:
	CAboutDlg();
	~CAboutDlg();

protected:
	static WNDPROC	pfnStaticProc;
	static HCURSOR	m_hLinkCursor;
	static BOOL		m_bOverHLink;

	virtual void OnInitDialog();
	virtual void OnCommand(UINT uCmdID,UINT code);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);

	static LRESULT CALLBACK StaticProc (HWND hWnd, UINT msg, UINT wParam, LPARAM lParam);
};

#endif // _ABOUT_H_INCLUDED