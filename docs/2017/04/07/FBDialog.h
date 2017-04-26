//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBDialog.h

	��Ȩ��Firebird Software Workroom ����

	��������Դ����İ�Ȩ�ܡ��л����񹲺͹�����Ȩ�����Լ���
		  ����ط��ɺ���Լ�ı������κ��л���õ���Դ�����
		  ���˺ͻ�����δ��������ȷ��Ȩ�����ý���Դ��������
		  �κ���ҵĿ��(ֱ�ӵĻ��ӵ�)�����ڷ���ҵĿ�ĵ�ʹ
		  �� (�������ơ�������������޸�)�� ԭ����û���ر�
		  �������������������ĵ���˵������Դ��������ԭ
		  ���ߵ�����Ȩ��

	��д���ش���(chings)	2000.4

	���磺Tel��(0792)6323086	E_mail��chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#ifndef _FBDIALOG_H__
#define _FBDIALOG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FBWnd.h"
//####################################################################
BOOL CALLBACK FBDlgProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam);
//####################################################################

class CModalDlg : public CFBWnd  
{
public:
	CModalDlg();
	virtual ~CModalDlg();

	BOOL Create(CFBWnd* pParent,UINT idTemplate);
	void SetTemplate(LPTSTR szTemplate){
		m_pszTemplate = szTemplate;}

	virtual int DoModal();

protected:
	LPTSTR		m_pszTemplate;

	virtual void OnInitDialog(){}
	virtual void OnCommand(UINT uCmdID,UINT code){}
	virtual void OnNotify(LPNMHDR pNMHDR,LRESULT &lResult){}
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);

	friend BOOL CALLBACK FBDlgProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam);
};

#endif // _FBDIALOG_H__
