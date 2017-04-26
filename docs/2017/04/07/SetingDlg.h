//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���SetingDlg.h ��CSetingDlg��ͷ�ļ�

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

#ifndef _SETINGDLG_H__
#define _SETINGDLG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainWnd.h"
#include "FBDialog.h"

class CSetingDlg : public CModalDlg  
{
public:
	CSetingDlg();
	virtual ~CSetingDlg();

	LPAPP_SETINGS GetSetings(){
		return m_pas;}

	char		m_strDefDir[MAX_PATH];
	char		m_strBackFile[MAX_PATH];
protected:
	LPAPP_SETINGS		m_pas;
	RECT				rc1,rc2,rc3;

	void DrawColorRect();
	void OnLButtonDblclk(POINT& pt);
	void OnSelDir();
	void OnSelBkFile();
	void OnBtnClicked(UINT uID);
	void OnOk();

	virtual void OnInitDialog();
	virtual void OnCommand(UINT uCmdID,UINT code);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};

#endif //_SETINGDLG_H__
